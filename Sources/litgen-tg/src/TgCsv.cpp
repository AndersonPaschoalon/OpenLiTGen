#include "TgCsv.h"

TgCsv::TgCsv()
{
}

TgCsv::~TgCsv()
{
}

std::string TgCsv::toString()
{
    return std::string("TgCsv");
}

void TgCsv::generate(const char* target) 
{
    std::ofstream outFile(target, std::ios::out | std::ios::app);

    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open or create file " << target << "\n";
        return;
    }

    // Write the CSV header if the file is empty
    outFile.seekp(0, std::ios::end);
    if (outFile.tellp() == 0) {
        outFile << "Arrival Time,Src IP,Src Port,Dst IP,Dst Port,Size\n";
    }

    // Write the packet data
    for (const auto& pdu : *(this->packetVector)) {
        outFile << pdu->getArrivalTime() << ","
                << pdu->getIpSrc() << "," << pdu->getPortSrc() << ","
                << pdu->getIpDst() << "," << pdu->getPortDst() << ","
                << pdu->getPacketSize() << "\n";
    }

    outFile.close();
}
