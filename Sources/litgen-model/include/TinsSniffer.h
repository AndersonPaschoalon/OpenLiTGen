#ifndef __TINS_SNIFFER__H__
#define __TINS_SNIFFER__H__ 1

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <tins/tins.h>
#include "PacketInfo.h"
#include "BaseSniffer.h"


class TinsSniffer: public BaseSniffer
{
    public:

        TinsSniffer();
        ~TinsSniffer();
        
        bool analyze(const std::string& pcapFile, std::vector<PACKET_INFO*>& pkts); 

    private:

        static double delta(Tins::Timestamp current, Tins::Timestamp last);
};

#endif // __TINS_SNIFFER__H__