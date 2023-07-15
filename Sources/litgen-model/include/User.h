
#ifndef __USER_H__
#define __USER_H__

#include <string>
#include <vector>
#include "PacketInfo.h"
#include "Session.h"

class User 
{
private:
    std::string user;
    std::vector<Session> sessions;

public:

    void populateUsers(const std::vector<PACKET_INFO *> &pkts, double sessionThreshold);

    const std::string getUser() const;
    const std::vector<Session> getSessions() const;
    const std::vector<double> getInterSessionTimes() const;
    const void echo() const;
};

#endif // __USER_H__