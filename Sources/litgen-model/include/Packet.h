
#ifndef __PACKET_H__
#define __PACKET_H__ 1

#include "PacketInfo.h"


class Packet 
{
    private:
        double arrivalTime;
        short packetSize;

    public:
        double getArrivalTime() const;
        void setArrivalTime(double arrivalTime);
        short getPacketSize() const;
        void setPacketSize(short packetSize);
};

#endif // __PACKET_H__