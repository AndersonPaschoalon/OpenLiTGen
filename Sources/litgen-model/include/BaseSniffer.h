#ifndef BASESNIFFER_H
#define BASESNIFFER_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include "PacketInfo.h"


class BaseSniffer
{
public:

    virtual ~BaseSniffer();

    /// @brief 
    /// @param pcapFile 
    /// @param pkts 
    /// @return 
    virtual bool analyze(const std::string &pcapFile, std::vector<PACKET_INFO *> &pkts) = 0;

    /// @brief 
    /// @param pkts 
    /// @return 
    static bool free(std::vector<PACKET_INFO *> &pkts);

    /// @brief 
    /// @param pkts 
    /// @return 
    static bool echo(const std::vector<PACKET_INFO *> &pkts);

protected:
    static void userAndFlowIdAssignment(std::vector<PACKET_INFO *> &pkts);
};

#endif // BASESNIFFER_H
