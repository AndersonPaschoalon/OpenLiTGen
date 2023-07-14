#include "NetworkTraffic.h"

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
            users.push_back(user);
        }
        
}

std::vector<User> NetworkTraffic::getUsers() const
{
    return users;
}

void NetworkTraffic::setUsers(const std::vector<User>& users) {
    this->users = users;
}

