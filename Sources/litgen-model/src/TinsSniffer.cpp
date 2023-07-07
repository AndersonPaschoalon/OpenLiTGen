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

    // Map to store the userFlowId counters for each user
    std::unordered_map<unsigned long, unsigned long> userFlowIdMap;   // userId -> userFlowId counter

    // Counter variable for userId
    unsigned long userIdCounter = 0;

    // Loop through the pkts vector to fill the userId and userFlowId fields
    for (const auto& pkt : pkts) {
        const std::string& ipDst = pkt->ipDst;
        int srcPort = pkt->portSrc;

        // Create a unique key for userId map (IP dst and src port)
        std::pair<std::string, int> userIdKey = std::make_pair(ipDst, srcPort);

        // Check if the userId already exists in the map
        if (userIdMap.find(userIdKey) == userIdMap.end()) {
            // Assign a new userId and update the counter
            userIdMap[userIdKey] = userIdCounter++;
            // Initialize the userFlowId counter for this user
            userFlowIdMap[userIdMap[userIdKey]] = 0;
        }

        // Fill the userId field
        pkt->userId = userIdMap[userIdKey];

        // Fill the userFlowId field
        pkt->userFlowId = userFlowIdMap[userIdMap[userIdKey]]++;
    }
}
