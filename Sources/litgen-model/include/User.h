
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

    std::string getUser() const;
    void setUser(const std::string& user);
    std::vector<Session> getSessions() const;
    void setSessions(const std::vector<Session>& sessions);
};

#endif // __USER_H__