
#ifndef __OBJECT_H__
#define __OBJECT_H__


#include <iomanip>  
#include <iostream>
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

    const std::string getServer() const;
    void setServer(const std::string& server);
    const std::vector<Packet> getPackets() const;
    const double getFirstArrivalTime() const;
    const double getLastArrivalTime() const;
    const int getNPackets();
    const int dataSize();
    const std::vector<double> getArrivalTimes() const;
    const std::vector<short> getPktSizes() const;
    const std::vector<double> getInterArrivalTimes() const;
    const void echo() const;


};

#endif // __OBJECT_H__