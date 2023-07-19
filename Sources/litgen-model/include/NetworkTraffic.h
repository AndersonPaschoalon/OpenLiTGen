#ifndef __NETWORKTRAFFIC_H__
#define __NETWORKTRAFFIC_H__

#include <vector>
#include <sstream>
#include <unordered_map>
#include "User.h"
#include "PacketInfo.h"

class NetworkTraffic 
{
    private:

        std::string trafficName;
        std::string trafficDescription;
        std::vector<User> users;

    public:

        NetworkTraffic(std::string name, std::string description);

        void populateTraffic(const std::vector<PACKET_INFO*>& pkts, double sessionThreshold);
        const std::vector<User> getUsers() const;
        const int nUsers() const;
        const void toString(std::string& str) const;
        const std::string getName() const;
        const std::string getDescription() const;
        const void queryUsersData(int& nUsers, std::vector<std::string>& userList) const;
        const void querySessionsData(std::vector<double>& interSessionTimes, std::vector<int>& nObjectsPersection) const;
        const void queryObjectData(std::vector<double>& interObjectTimes, std::vector<int>& npacketsPerObject, std::vector<std::string>& serverList) const;
        const void queryPacketData(std::vector<double>& interPacketTimes, std::vector<short> packetSizes);

};

#endif // __NETWORKTRAFFIC_H__