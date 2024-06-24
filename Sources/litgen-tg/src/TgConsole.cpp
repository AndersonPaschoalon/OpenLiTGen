#include "TgConsole.h"

TgConsole::TgConsole()
{
}

TgConsole::~TgConsole()
{
}

std::string TgConsole::toString()
{
    return std::string("TgConsole");
}

void TgConsole::generate(const char* target) 
{
    auto startTime = std::chrono::steady_clock::now();
    
    for (const auto& pdu : *(this->packetVector)) {
        // Calculate the duration to wait until the packet's arrival time
        auto arrivalTime = startTime + std::chrono::nanoseconds(static_cast<long long>(pdu->getArrivalTime() * 1e9));
        auto currentTime = std::chrono::steady_clock::now();
        auto waitDuration = arrivalTime - currentTime;

        // Wait until the packet's arrival time
        if (waitDuration > std::chrono::nanoseconds::zero()) {
            std::this_thread::sleep_for(waitDuration);
        }

        // Output the packet details
        std::cout << "Arrival Time: " << pdu->getArrivalTime() << ", "
                  << "Src: " << pdu->getIpSrc() << ":" << pdu->getPortSrc() << ", "
                  << "Dst: " << pdu->getIpDst() << ":" << pdu->getPortDst() << ", "
                  << "Size: " << pdu->getPacketSize() << "\n";
    }
}
