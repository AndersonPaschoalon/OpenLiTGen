
#ifndef __OBJECT_H__
#define __OBJECT_H__


#include <iomanip>  
#include <iostream>
#include <string>
#include <vector>
#include "PacketInfo.h"
#include "Packet.h"

class Object 
{
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
        const int getNPackets() const;
        const int dataSize() const;
        const void getArrivalTimes(std::vector<double>& arrivalsTimes) const;
        const void getPktSizes(std::vector<short>& pktSizes) const;
        const void getInterArrivalTimes(std::vector<double>& interArrivalTimes) const;
        const void toString(std::string& str) const;
};

#endif // __OBJECT_H__