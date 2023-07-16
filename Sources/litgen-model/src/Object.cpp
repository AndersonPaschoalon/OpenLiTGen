
#include "Object.h"



void Object::populateObject(const std::vector<PACKET_INFO *> &pkts)
{
    if (pkts.empty()) 
    {
        return;
    }

    server = pkts[0]->ipSrc + ":" + std::to_string(pkts[0]->portDst);

    for (const auto& pkt : pkts) {
        Packet packet;
        packet.setArrivalTime(pkt->arrivalTime);
        packet.setPacketSize(pkt->pktSize);
        this->packets.push_back(packet);
    }
}

const std::string Object::getServer() const
{
    return this->server;
}

void Object::setServer(const std::string& server) {
    this->server = server;
}

const std::vector<Packet> Object::getPackets() const 
{
    return this->packets;
}

const double Object::getFirstArrivalTime() const
{
    if(!packets.empty())
    {
        return this->packets[0].getArrivalTime();
    }
    return 0.0;
}

const double Object::getLastArrivalTime() const
{
    if(!packets.empty())
    {
        return this->packets[this->packets.size() - 1].getArrivalTime();
    }
    return 0.0;
}

const int Object::getNPackets()
{
    return this->packets.size();
}

const int Object::dataSize()
{
    std::vector<short> pktSizes = this->getPktSizes();
    int total = 0;
    for (short size: pktSizes)
    {
        total += size;
    }
    return total;
}

const std::vector<double> Object::getArrivalTimes() const
{
    std::vector<double> arrivals;
    arrivals.reserve(packets.size());

    for (const auto& pkt: this->packets)
    {
        arrivals.push_back(pkt.getArrivalTime());
    }
    return arrivals;
}

const std::vector<short> Object::getPktSizes() const
{
    std::vector<short> pktSizes;
    pktSizes.reserve(packets.size());

    for (const auto& pkt: this->packets)
    {
        pktSizes.push_back(pkt.getPacketSize());
    }
    return pktSizes;
}

const std::vector<double> Object::getInterArrivalTimes() const
{
    const std::vector<double> arrivalTimes = getArrivalTimes();
    std::vector<double> interArrivalTimes;
    interArrivalTimes.reserve(arrivalTimes.size() - 1);

    for (size_t i = 1; i < arrivalTimes.size(); ++i)
    {
        double interArrivalTime = arrivalTimes[i] - arrivalTimes[i - 1];
        interArrivalTimes.push_back(interArrivalTime);
    }

    return interArrivalTimes;
}

const void Object::echo() const
{
    std::cout << ".   .   .   .   Server: " << server << std::endl;

    std::cout << ".   .   .   .   Arrivals: ";
    const std::vector<double> arrivals = getArrivalTimes();
    for (size_t i = 0; i < arrivals.size(); ++i) {
        std::cout << std::fixed << std::setprecision(8) << arrivals[i];
        if (i != arrivals.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    std::cout << ".   .   .   .   PktSizes: ";
    const std::vector<short> pktSizes = getPktSizes();
    for (size_t i = 0; i < pktSizes.size(); ++i) {
        std::cout << pktSizes[i];
        if (i != pktSizes.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}
