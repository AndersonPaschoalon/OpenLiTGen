#include "NetworkTraffic.h"

NetworkTraffic::NetworkTraffic(std::string name, std::string description)
{
    this->trafficName = name;
    this->trafficDescription = description;
}

void NetworkTraffic::populateTraffic(const std::vector<PACKET_INFO *> &pkts, double sessionThreshold)
{
        std::unordered_map<unsigned long, std::vector<PACKET_INFO*>> userPktsMap;
        
        // map each packet for each unique user
        for (const auto& pkt : pkts) 
        {
            userPktsMap[pkt->userId].push_back(pkt);
        }
        
        // for each unique user create a new user entry and populate it with his packets
        for (const auto& [userId, userPkt] : userPktsMap) 
        {
            User user;
            user.populateUsers(userPkt, sessionThreshold);
            this->users.push_back(user);
        }
        
}

const std::vector<User> NetworkTraffic::getUsers() const
{
    return users;
}

const int NetworkTraffic::nUsers() const
{
    return this->users.size();
}

const void NetworkTraffic::toString(std::string& str) const
{
    std::ostringstream oss;
    oss << ".Network Traffic " << trafficName << ": " << trafficDescription << std::endl;

    for (size_t i = 0; i < this->users.size(); ++i) 
    {
        oss << ".   [User " << i + 1 << "]" << std::endl;

        // use heap
        std::string* temp = new std::string();
        users[i].toString(*temp);
        oss << *temp;
        delete temp;
    }

    str = oss.str();
}

const std::string NetworkTraffic::getName() const
{
    return this->trafficName;
}

const std::string NetworkTraffic::getDescription() const
{
    return this->trafficDescription;
}

const void NetworkTraffic::queryUsersData(int& nUsers, std::vector<std::string> &userList, bool removeDuplicatesFromUserList) const
{
    nUsers = this->nUsers();
    userList.clear();
    for (auto& user: this->users)
    {
        userList.push_back(user.getUser());
    }
    userList = VectorUtils::removeDuplicates(userList);
}

const void NetworkTraffic::querySessionsData(std::vector<double> &interSessionTimes, std::vector<int> &nObjectsPerSection) const
{
    interSessionTimes.clear();
    nObjectsPerSection.clear();
    for (auto& user: this->users)
    {
        std::vector<double> userInterSessions;
        std::vector<int> userNObjects;

        user.getInterSessionTimes(userInterSessions);
        interSessionTimes.insert(interSessionTimes.end(), userInterSessions.begin(), userInterSessions.end());

        user.getNObjectsPerSession(userNObjects);
        nObjectsPerSection.insert(nObjectsPerSection.end(), userNObjects.begin(), userNObjects.end());
    }
}

const void NetworkTraffic::queryObjectData(std::vector<double> &interObjectTimes, std::vector<int> &npacketsPerObject, std::vector<std::string> &serverList, bool removeDuplicatesFromServerList) const
{
    interObjectTimes.clear();
    npacketsPerObject.clear();
    serverList.clear();
    for (auto& user: this->users)
    {
        std::vector<Session> ss = user.getSessions();
        for(auto& session: ss)
        {
            std::vector<double> oit;
            session.objectsInterArrivalTimes(oit);
            interObjectTimes.insert(interObjectTimes.end(), oit.begin(), oit.end());

            std::vector<int> npo;
            session.objectsNPackets(npo);
            npacketsPerObject.insert(npacketsPerObject.end(), npo.begin(), npo.end());

            std::vector<std::string> sl;
            session.serverList(sl);
            serverList.insert(serverList.end(), sl.begin(), sl.end());
        }
    }

    serverList =  VectorUtils::removeDuplicates(serverList);
}

const void NetworkTraffic::queryPacketData(std::vector<double> &interPacketTimes, std::vector<short> packetSizes)
{
    interPacketTimes.clear();
    packetSizes.clear();
    for (auto& user: this->users)
    {
        std::vector<Session> ss = user.getSessions();
        for(auto& session: ss)
        {
            std::vector<Object> objs = session.getObjects();
            for(auto& object: objs)
            {
                std::vector<double> pit;
                object.getInterArrivalTimes(pit);
                interPacketTimes.insert(interPacketTimes.end(), pit.begin(), pit.end());

                std::vector<short> pks;
                object.getPktSizes(pks);
                packetSizes.insert(packetSizes.end(), pks.begin(), pks.end());                
            }
        }
    }
}






