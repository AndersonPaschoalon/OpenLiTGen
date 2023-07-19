#include "TinsSniffer.h"
#include "NetworkTraffic.h"
#include "LitModel.h"


int main() 
{

    // capture all packets raw data
    std::vector<PACKET_INFO *> pkts;
    TinsSniffer::analyze("../../../Pcaps/lanDiurnal.pcap", pkts); // "../../Pcap/SkypeIRC.cap"
    // TinsSniffer::echo(pkts);

    // classify the data for modelling
    std::string* str = new std::string();
    str->clear();
    NetworkTraffic* netTraffic = new NetworkTraffic("SkypeIRC.cap", "Pcap for tests.");
    netTraffic->populateTraffic(pkts, 300.00);
    netTraffic->toString(*str);
    std::cout << *str;

    // generate a traffic model, and save 
    LitModel lit;
    lit.calc(*netTraffic);
    lit.save();

    // free allocated memory
    TinsSniffer::free(pkts);
    delete netTraffic;
    delete str;

    return 0;
}