#ifndef __PACKET_INFO_H__
#define __PACKET_INFO_H__ 1

#include <vector>
#include <string>

typedef struct _packet_info
{
    double arrivalTime = 0;
    unsigned short pktSize = 0;
    unsigned long userId = 0;
    unsigned long userFlowId = 0;
    std::string ipSrc = "";
    std::string ipDst = "";
    std::string transportProtocol = "";
    int portSrc = 0;
    int portDst = 0; 
    bool syn = false;
    bool ack = false;
    bool fin = false;
    bool rst = false;

} PACKET_INFO;

bool comparePacketInfo(const PACKET_INFO* a, const PACKET_INFO* b);

#endif // __PACKET_INFO_H__