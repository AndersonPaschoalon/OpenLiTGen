
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

const std::string User::getUser() const
{
    return this->user;
}

const std::vector<Session> User::getSessions() const {
    return this->sessions;
}

const std::vector<double> User::getInterSessionTimes() const
{
    std::vector<double> interSessionTimes;

    for (size_t i = 1; i < sessions.size(); ++i)
    {
        double interSessionTime = sessions[i].getFirstArrival() - sessions[i - 1].getFirstArrival();
        interSessionTimes.push_back(interSessionTime);
    }

    return interSessionTimes;
}

const void User::echo() const
{
    std::cout << "  User: " << user << ", Nsessions: " << sessions.size() << std::endl;

    for (size_t i = 0; i < sessions.size(); ++i) 
    {
        std::cout << "   *  [session" << i + 1 << "]" << std::endl;
        sessions[i].echo();
    }
}
