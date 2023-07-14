
#include "Object.h"

void Object::populateObject(const std::vector<PACKET_INFO *> &pkts)
{
    if (pkts.empty()) 
    {
        return;
    }

    server = pkts[0]->ipSrc + ":" + std::to_string(pkts[0]->portDst);

    for (const auto& pkt : pkts) {
        Packet packet;
        packet.setArrivalTime(pkt->arrivalTime);
        packet.setPacketSize(pkt->pktSize);
        this->packets.push_back(packet);
    }
}

std::string Object::getServer() const
{
    return server;
}

void Object::setServer(const std::string& server) {
    this->server = server;
}

std::vector<Packet> Object::getPackets() const {
    return packets;
}

void Object::setPackets(const std::vector<Packet>& packets) {
    this->packets = packets;
}
