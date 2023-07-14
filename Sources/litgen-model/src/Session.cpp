

#include "Session.h"


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

            if (pkt->fin || pkt->rst) 
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
}

std::vector<Object> Session::getObjects() const
{
    return objects;
}

void Session::setObjects(const std::vector<Object>& objects) {
    this->objects = objects;
}
