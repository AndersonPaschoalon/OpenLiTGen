#ifndef __BASESNIFFER_H__
#define __BASESNIFFER_H__ 1

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
    virtual bool free(std::vector<PACKET_INFO *> &pkts);

    /// @brief 
    /// @param pkts 
    /// @return 
    virtual bool echo(const std::vector<PACKET_INFO *> &pkts);


    /// @brief 
    /// @param pkts 
    /// @return 
    static bool baseFree(std::vector<PACKET_INFO *> &pkts);

    /// @brief 
    /// @param pkts 
    /// @return 
    static bool baseEcho(const std::vector<PACKET_INFO *> &pkts);

protected:
    static void userAndFlowIdAssignment(std::vector<PACKET_INFO *> &pkts);
};

#endif // __BASESNIFFER_H__
