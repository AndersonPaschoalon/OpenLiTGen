#ifndef __NETWORKTRAFFIC_H__
#define __NETWORKTRAFFIC_H__ 1

#include <vector>
#include <sstream>
#include <unordered_map>
#include <cpptools.h>
#include "User.h"
#include "PacketInfo.h"
#include "Utils.h"


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
        int nUsers() const;
        const void toString(std::string& str) const;
        const std::string getName() const;
        const std::string getDescription() const;
        void queryUsersData(int& nUsers, std::vector<std::string>& userList, bool removeDuplicatesFromUserList) const;
        void querySessionsData(std::vector<double>& interSessionTimes, std::vector<int>& nObjectsPersection) const;
        void queryObjectData(std::vector<double>& interObjectTimes, std::vector<int>& npacketsPerObject, std::vector<std::string>& serverList, bool removeDuplicatesFromServerList) const;
        void queryPacketData(std::vector<double>& interPacketTimes, std::vector<short> packetSizes);

};

#endif // __NETWORKTRAFFIC_H__