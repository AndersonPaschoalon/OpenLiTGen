#include "TinsSniffer.h"
#include "NetworkTraffic.h"



int main() 
{

    // capture all packets raw data
    std::vector<PACKET_INFO *> pkts;
    TinsSniffer::analyze("../../Pcap/SkypeIRC.cap", pkts);
    // TinsSniffer::echo(pkts);

    // classify the data for modelling
    NetworkTraffic* netTraffic = new NetworkTraffic("SkypeIRC.cap", "Pcap for tests.");
    netTraffic->populateTraffic(pkts, 300.00);
    netTraffic->echo();

    // free allocated memory
    TinsSniffer::free(pkts);
    delete netTraffic;

    return 0;
}