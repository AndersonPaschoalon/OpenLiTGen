#ifndef __NETWORKTRAFFIC_H__
#define __NETWORKTRAFFIC_H__

#include <vector>
#include <unordered_map>
#include "User.h"
#include "PacketInfo.h"

class NetworkTraffic {
private:
    std::vector<User> users;

public:

    void populateTraffic(const std::vector<PACKET_INFO*>& pkts, double sessionThreshold);
    std::vector<User> getUsers() const;
    void setUsers(const std::vector<User>& users);




};

#endif // __NETWORKTRAFFIC_H__