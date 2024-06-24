
#ifndef __USER_H__ 
#define __USER_H__ 1

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
        void getInterSessionTimes(std::vector<double>& interSessionTimes) const;
        void getNObjectsPerSession(std::vector<int>& nObjectsPerSession) const;
        void toString(std::string& str) const;
};

#endif // __USER_H__