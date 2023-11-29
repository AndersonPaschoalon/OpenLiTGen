#include "PacketInfo.h"

bool comparePacketInfo(const PACKET_INFO *a, const PACKET_INFO *b)
{
    return a->arrivalTime < b->arrivalTime;
}
