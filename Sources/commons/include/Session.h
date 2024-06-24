
#ifndef __SESSION_H__ 
#define __SESSION_H__ 1

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <vector>
#include "PacketInfo.h"
#include "Object.h"
#include <unordered_map>

class Session 
{
    private:
        std::vector<Object> objects;
        void sortObjects();

    public:
        void populateSession(const std::vector<PACKET_INFO *> &pkts);

        const std::vector<Object> getObjects() const;
        int nObjects() const;
        void objectsInterArrivalTimes(std::vector<double>& interArrivalsTimes) const;
        void objectsNPackets(std::vector<int>& objNPackets) const;
        void serverList(std::vector<std::string>& servers) const;
        double getFirstArrival() const;
        void toString(std::string& str) const;
};

#endif // __SESSION_H__