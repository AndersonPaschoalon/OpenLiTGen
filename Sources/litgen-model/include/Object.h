
#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>
#include <vector>
#include "PacketInfo.h"
#include "Packet.h"

class Object {
private:
    std::string server;
    std::vector<Packet> packets;

public:

    void populateObject(const std::vector<PACKET_INFO *> &pkts);

    std::string getServer() const;
    void setServer(const std::string& server);
    std::vector<Packet> getPackets() const;
    void setPackets(const std::vector<Packet>& packets);
};

#endif // __OBJECT_H__