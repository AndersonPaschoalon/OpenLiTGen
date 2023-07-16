#include "TinsSniffer.h"

bool TinsSniffer::analyze(const std::string &pcapFile, std::vector<PACKET_INFO*>& pkts)
{
    Tins::FileSniffer sniffer(pcapFile);
    Tins::Packet packet;
    Tins::Timestamp firstPacketTime;
    double dFirstPakcetTime = 0;

    // (1) Read all the raw data from the packets
    packet = sniffer.next_packet();
    if(packet == 0)
    {
        printf("Error reading packets from the file %s\n", pcapFile.c_str());
        return false;
    }
    firstPacketTime = packet.timestamp();
    while (true) 
    {
        if (packet.pdu()->find_pdu<Tins::IP>()) 
        {
            const auto& ip = packet.pdu()->rfind_pdu<Tins::IP>();

            if (ip.find_pdu<Tins::TCP>()) 
            {
                // allocate memory for the new packet
                PACKET_INFO* currentPacket = new PACKET_INFO;

                const auto& tcp = ip.rfind_pdu<Tins::TCP>();
                Tins::Timestamp current = packet.timestamp();

                double arrivalTime = TinsSniffer::delta(current, firstPacketTime);
                currentPacket->arrivalTime = arrivalTime;
                currentPacket->pktSize = packet.pdu()->size();
                Tins::IPv4Address ipSrc = ip.src_addr();
                Tins::IPv4Address ipDst = ip.dst_addr();
                currentPacket->ipSrc = ipSrc.to_string();
                currentPacket->ipDst = ipDst.to_string();
                currentPacket->portSrc = tcp.sport();
                currentPacket->portDst = tcp.dport();
                currentPacket->syn = tcp.get_flag(Tins::TCP::SYN);
                currentPacket->ack = tcp.get_flag(Tins::TCP::ACK);
                currentPacket->fin = tcp.get_flag(Tins::TCP::FIN);
                currentPacket->rst = tcp.get_flag(Tins::TCP::RST);

                // append to the packet list
                pkts.push_back(currentPacket);

            }
        }

        //next packet
        packet = sniffer.next_packet();
        if(packet == 0 )
        {
            printf("Packet capture of the file %s finisehd.\n", pcapFile.c_str());
            break;
        }
    }

    // (2) Sort the packets according to arrival time
    std::sort(pkts.begin(), pkts.end(), comparePacketInfo);

    // (3) User and Flow Ids assingments
    TinsSniffer::userAndFlowIdAssingment(pkts);

}

bool TinsSniffer::free(std::vector<PACKET_INFO *> pkts)
{
    for (int i = 0; i < pkts.size(); i++)
    {
        delete pkts[i];
        pkts[i] = nullptr;
    }
    pkts.clear();

    return false;
}

bool TinsSniffer::echo(const std::vector<PACKET_INFO *>& pkts)
{
    for (const auto& pkt : pkts) {
        std::cout << "Time: " << pkt->arrivalTime << ", ";
        std::cout << "Size: " << pkt->pktSize << ", ";
        std::cout << "UserID: " << pkt->userId << ", ";
        std::cout << "UserFlowID: " << pkt->userFlowId << ", ";
        std::cout << "SrcIP: " << pkt->ipSrc << ", ";
        std::cout << "DstIP: " << pkt->ipDst << ", ";
        std::cout << "Proto: " << pkt->transportProtocol << ", ";
        std::cout << "SrcPort: " << pkt->portSrc << ", ";
        std::cout << "DstPort: " << pkt->portDst << ", ";
        std::cout << "SYN: " << pkt->syn << ", ";
        std::cout << "ACK: " << pkt->ack << ", ";
        std::cout << "FIN: " << pkt->fin << ", ";
        std::cout << "RST: " << pkt->rst << std::endl;
    }
    return true;
}

double TinsSniffer::delta(Tins::Timestamp current, Tins::Timestamp last)
{
    int csec = current.seconds();
    int lsec = last.seconds();
    int cus = current.microseconds();
    double delta = 0;

    int deltaSec = csec - lsec;
    if (deltaSec == 0)
    {
        int lus = last.microseconds();
        delta = (cus - lus)*10e-6;
    }
    else
    {
        delta = deltaSec + cus*10e-6;
    }

    return delta;
}

void TinsSniffer::userAndFlowIdAssingment(std::vector<PACKET_INFO *> pkts)
{
    // Map to store the user ID counters
    std::map<std::pair<std::string, int>, unsigned long> userIdMap;    // IP dst and src port -> userId

    // Map the userFlowIds for each user
    // (key:user, value:map(key:flowPair, value:userFlowId))
    std::map<unsigned long, std::map<std::pair<std::string, int>, unsigned long>> userFlowIdMapForUsers;


    // Counter variable for userId
    unsigned long userIdCounter = 0;

    // Loop through the pkts vector to fill the userId
    for (const auto& pkt : pkts) 
    {
        const std::string& ipDst = pkt->ipDst;
        int srcPort = pkt->portSrc;
        
        const std::string& ipSrc = pkt->ipSrc;
        int dstPort = pkt->portDst;

        // Create a unique key for userId map (IP dst and src port)
        std::pair<std::string, int> userIdKey = std::make_pair(ipDst, srcPort);
        // make user flow key
        std::pair<std::string, int> userFlowIdKey = std::make_pair(ipSrc, dstPort);

        // Check if the userId already exists in the map
        if (userIdMap.find(userIdKey) == userIdMap.end()) 
        {
            // key DOES NOT EXIST, iterator reached the end!
            // Assign a new userId and update the counter
            userIdMap[userIdKey] = userIdCounter++;

            // create a new key for the user flow
            std::pair<std::string, int> userFlowId = std::make_pair(ipSrc, dstPort);
            // create a map for the flows
            std::map<std::pair<std::string, int>, unsigned long> userFlowsMap;
            userFlowsMap[userFlowId] = 0;

            // add the new map to the users map
            userFlowIdMapForUsers[userIdCounter] = userFlowsMap;
        }
        else
        {
            // already exist

            // retrieve user id
            unsigned long userId = userIdMap[userIdKey];

            // search for the userFlowId key the the users map
            if (userFlowIdMapForUsers[userId].find(userFlowIdKey) == userFlowIdMapForUsers[userId].end()) 
            {
                // does not exist -> add a new userFlow id
                // calc the new flow id
                long int newUserFlowId = 0;
                for (const auto& pair : userFlowIdMapForUsers[userId]) 
                {
                    if (pair.second > newUserFlowId)
                    {
                        newUserFlowId = pair.second ;
                    }
                }
                newUserFlowId++;
                // set the new user flow id as value for the set
                (userFlowIdMapForUsers[userId])[userFlowIdKey] = newUserFlowId;

            }
            // if value already exist, it can be already accessed. nothing to do. 

        }

        // Fill the userId field
        pkt->userId = userIdMap[userIdKey];
        pkt->userFlowId = (userFlowIdMapForUsers[userIdMap[userIdKey]])[userFlowIdKey];

    }
}
