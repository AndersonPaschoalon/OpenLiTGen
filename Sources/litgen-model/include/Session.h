
#ifndef __SESSION_H__
#define __SESSION_H__

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
        const int nObjects() const;
        const std::vector<double> objectsInterArrivalTimes() const;
        const double getFirstArrival() const;
        const void echo() const;

};

#endif // __SESSION_H__