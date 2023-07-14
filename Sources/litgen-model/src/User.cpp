
#include "User.h"

void User::populateUsers(const std::vector<PACKET_INFO *> &pkts, double sessionThreshold)
{
    if (pkts.empty()) 
    {
        return;
    }

    // Concatenate ipDst and portSrc to populate user
    const PACKET_INFO* firstPacket = pkts.front();
    this->user = firstPacket->ipDst + ":" + std::to_string(firstPacket->portSrc);

    std::vector<std::vector<PACKET_INFO*>> sessionPkts;
    std::vector<PACKET_INFO*> currentSession;

    double previousArrivalTime = pkts.front()->arrivalTime;

    for (const auto& pkt : pkts) 
    {
        double delta = pkt->arrivalTime - previousArrivalTime;

        if (delta > sessionThreshold) {
            sessionPkts.push_back(currentSession);
            currentSession.clear();
        }

        currentSession.push_back(pkt);
        previousArrivalTime = pkt->arrivalTime;
    }

    sessionPkts.push_back(currentSession);

    for (const auto& sessionPkt : sessionPkts) {
        Session session;
        session.populateSession(sessionPkt);
        sessions.push_back(session);
    }
}

std::string User::getUser() const
{
    return user;
}

void User::setUser(const std::string& user) {
    this->user = user;
}

std::vector<Session> User::getSessions() const {
    return sessions;
}

void User::setSessions(const std::vector<Session>& sessions) {
    this->sessions = sessions;
}