#ifndef __TINS_SNIFFER__H__
#define __TINS_SNIFFER__H__ 1

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <tins/tins.h>
#include "PacketInfo.h"



class TinsSniffer 
{
    public:
    
        static bool analyze(const std::string& pcapFile, std::vector<PACKET_INFO*>& pkts); 
        static bool free(std::vector<PACKET_INFO*> pkts);
        static bool echo(const std::vector<PACKET_INFO*>& pkts);

    private:

        static double delta(Tins::Timestamp current, Tins::Timestamp last);
        static void userAndFlowIdAssingment(std::vector<PACKET_INFO*> pkts);
};

#endif // __TINS_SNIFFER__H__