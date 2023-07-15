#include "NetworkTraffic.h"

NetworkTraffic::NetworkTraffic(std::string name, std::string description)
{
    this->trafficName = name;
    this->trafficDescription = description;
}

void NetworkTraffic::populateTraffic(const std::vector<PACKET_INFO *> &pkts, double sessionThreshold)
{
        std::unordered_map<unsigned long, std::vector<PACKET_INFO*>> userPktsMap;
        
        for (const auto& pkt : pkts) 
        {
            userPktsMap[pkt->userId].push_back(pkt);
        }
        
        for (const auto& [userId, userPkt] : userPktsMap) {
            User user;
            user.populateUsers(userPkt, sessionThreshold);
            this->users.push_back(user);
        }
        
}

const std::vector<User> NetworkTraffic::getUsers() const
{
    return users;
}

const int NetworkTraffic::nUsers() const
{
    return this->users.size();
}

const void NetworkTraffic::echo() const
{
    std::cout << "Network Traffic " << trafficName << ": " << trafficDescription << std::endl;

    for (size_t i = 0; i < this->users.size(); ++i) 
    {
        std::cout << "         *  [User " << i + 1 << "]" << std::endl;
        users[i].echo();
    }
}
