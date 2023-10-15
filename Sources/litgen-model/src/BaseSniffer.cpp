#include "BaseSniffer.h"

BaseSniffer::~BaseSniffer()
{
}

bool BaseSniffer::free(std::vector<PACKET_INFO *> &pkts)
{
    for (int i = 0; i < pkts.size(); i++)
    {
        delete pkts[i];
        pkts[i] = nullptr;
    }
    pkts.clear();

    return false;
}

bool BaseSniffer::echo(const std::vector<PACKET_INFO *> &pkts)
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

void BaseSniffer::userAndFlowIdAssignment(std::vector<PACKET_INFO *> &pkts)
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