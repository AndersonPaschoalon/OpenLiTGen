#include "Model.h"

bool comparePacketInfo(const PACKET_INFO *a, const PACKET_INFO *b)
{
    return a->arrivalTime < b->arrivalTime;
}

// This function iterates over the pkts vector, filters the packets based on the given userId and userFlowId, and builds MOD_OBJECT instances accordingly. It appends each packet with the matching IDs to the corresponding MOD_OBJECT's pkts vector. If a packet with the fin or rst flag is encountered, it finalizes the current MOD_OBJECT and adds it to the objLists vector. Finally, if there is an unfinished MOD_OBJECT at the end of the iteration, it is also added to the objLists.
// Make sure to free the memory of the MOD_OBJECT instances when they are no longer needed to avoid memory leaks.
void buildObjectList(std::vector<PACKET_INFO*>& pkts, unsigned long userId, unsigned long userFlowId, std::vector<MOD_OBJECT*>& objLists)
{
    MOD_OBJECT* currentObject = nullptr;

    for (PACKET_INFO* pkt : pkts)
    {
        if (pkt->userId == userId && pkt->userFlowId == userFlowId)
        {
            if (currentObject == nullptr)
            {
                currentObject = new MOD_OBJECT;
                currentObject->userFlowId = userFlowId;
                currentObject->objectId = objLists.size();
                currentObject->srcIp = pkt->ipSrc;
                currentObject->dstPort = pkt->portDst;
            }

            MOD_PACKET modPacket;
            modPacket.arrivalTime = pkt->arrivalTime;
            modPacket.pktSize = pkt->pktSize;

            currentObject->pkts.push_back(modPacket);

            if (pkt->fin || pkt->rst)
            {
                objLists.push_back(currentObject);
                currentObject = nullptr;
            }
        }
    }

    if (currentObject != nullptr)
    {
        objLists.push_back(currentObject);
    }
}
