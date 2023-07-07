#include "TinsSniffer.h"

int main() 
{
    std::vector<PACKET_INFO *> pkts;
    TinsSniffer sniffer;
    TinsSniffer::analyze("../../Pcap/SkypeIRC.cap", pkts);
    TinsSniffer::echo(pkts);
    TinsSniffer::free(pkts);
    return 0;
}