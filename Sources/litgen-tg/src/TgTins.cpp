#include "TgTins.h"

TgTins::TgTins()
{
    // Constructor implementation, initialize interface if needed
    iface = Tins::NetworkInterface::default_interface();
    sender = Tins::PacketSender();    
}

TgTins::~TgTins()
{
}

std::string TgTins::toString()
{
    return std::string("TgTins");
}

void TgTins::generate(const char* target) 
{
    try {
        for (const auto& pdu : *(this->packetVector)) {
            // Construct Ethernet layer
            Tins::EthernetII eth = Tins::EthernetII() /
                                   Tins::IP(pdu->getIpDst(), pdu->getIpSrc()) /
                                   Tins::UDP(pdu->getPortDst(), pdu->getPortSrc());

            // Fill the payload with dummy data
            std::vector<uint8_t> payload(pdu->getPacketSize(), 0);
            eth.rfind_pdu<Tins::UDP>().inner_pdu(Tins::RawPDU(payload));

            // Send the packet to the target interface
            sender.send(eth, iface);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error sending packets: " << e.what() << std::endl;
    }    
}
