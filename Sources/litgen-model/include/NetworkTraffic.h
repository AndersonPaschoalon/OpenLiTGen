#ifndef __NETWORKTRAFFIC_H__
#define __NETWORKTRAFFIC_H__

#include <vector>
#include <unordered_map>
#include "User.h"
#include "PacketInfo.h"

class NetworkTraffic {
    private:

        std::string trafficName;
        std::string trafficDescription;
        std::vector<User> users;

    public:

        NetworkTraffic(std::string name, std::string description);

        void populateTraffic(const std::vector<PACKET_INFO*>& pkts, double sessionThreshold);

        const std::vector<User> getUsers() const;
        const int nUsers() const;
        const void echo() const;
};

#endif // __NETWORKTRAFFIC_H__