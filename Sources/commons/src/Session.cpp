#include "Session.h"


void Session::sortObjects()
{
    std::sort(this->objects.begin(), this->objects.end(),
              [](const Object& a, const Object& b) {
                  return a.getFirstArrivalTime() < b.getFirstArrivalTime();
              });
}

void Session::populateSession(const std::vector<PACKET_INFO *> &pkts)
{
    if (pkts.empty()) 
    {
        return;
    }

    std::unordered_map<unsigned long, std::vector<PACKET_INFO*>> objectPkts;

    for (const auto& pkt : pkts) 
    {
        objectPkts[pkt->userFlowId].push_back(pkt);
        // std::vector<PACKET_INFO *> v = objectPkts[pkt->userFlowId];
    }

    std::vector<PACKET_INFO*> tempObjectPkts;
    for (const auto& entry : objectPkts) 
    {
        const std::vector<PACKET_INFO*>& pktVec = entry.second;
        Object object;
        bool newPackets = false;
        for (const auto& pkt : pktVec) 
        {
            tempObjectPkts.push_back(pkt);

            if (pkt->fin  == true || pkt->rst == true) 
            {
                object.populateObject(tempObjectPkts);
                this->objects.push_back(object);
                tempObjectPkts.clear();
                object = Object();
                newPackets = false;
            }
            else
            {
                newPackets = true;
            }
        }
        if (newPackets)
        {
            object.populateObject(tempObjectPkts);
            this->objects.push_back(object);
            tempObjectPkts.clear();            
        }
    }

    this->sortObjects();
}

const std::vector<Object> Session::getObjects() const
{
    return this->objects;
}

int Session::nObjects() const
{
    return this->objects.size();
}

void Session::objectsInterArrivalTimes(std::vector<double>& interArrivalTimes) const
{
    interArrivalTimes.clear();
    interArrivalTimes.reserve(this->objects.size() - 1);

    for (size_t i = 1; i < this->objects.size(); ++i)
    {
        double interArrivalTime = this->objects[i].getFirstArrivalTime() - this->objects[i - 1].getFirstArrivalTime();
        interArrivalTimes.push_back(interArrivalTime);
    }
}

void Session::objectsNPackets(std::vector<int>& nPackets) const
{
    nPackets.clear();
    nPackets.reserve(this->objects.size());
    for (size_t i = 1; i < this->objects.size(); ++i)
    {
        nPackets.push_back(this->objects[i].getNPackets());
    }
}

void Session::serverList(std::vector<std::string>& serverList) const
{
    serverList.clear();
    serverList.reserve(this->objects.size());
    for (size_t i = 1; i < this->objects.size(); ++i)
    {
        serverList.push_back(this->objects[i].getServer());
    }
}

double Session::getFirstArrival() const
{
    if (!this->objects.empty())
    {
        return this->objects[0].getFirstArrivalTime();
    }
    return 0.0;
}

void Session::toString(std::string& str) const
{
    std::ostringstream oss;
    oss << ".   .   .   Session Size: " << nObjects() << " objects" << std::endl;

    for (size_t i = 0; i < objects.size(); ++i) 
    {
        std::string* temp = new std::string();
        oss << ".   .   .   .   [object " << i + 1 << "]" << std::endl;
        objects[i].toString(*temp);
        oss << *temp;
        delete temp;
    }

    str = oss.str();
}
