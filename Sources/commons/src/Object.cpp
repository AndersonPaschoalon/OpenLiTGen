
#include "Object.h"


void Object::populateObject(const std::vector<PACKET_INFO *> &pkts)
{
    if (pkts.empty()) 
    {
        return;
    }

    server = pkts[0]->ipSrc + ":" + std::to_string(pkts[0]->portDst);

    for (const auto& pkt : pkts) 
    {
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

void Object::setServer(const std::string& server) 
{
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

const int Object::getNPackets() const
{
    return this->packets.size();
}

const int Object::dataSize() const
{
    int total = 0;
    std::vector<short> pktSizes;

    this->getPktSizes(pktSizes);
    for (short size: pktSizes)
    {
        total += size;
    }
    return total;
}

const void Object::getArrivalTimes(std::vector<double>& arrivals) const
{
    arrivals.clear();
    arrivals.reserve(packets.size());

    for (const auto& pkt: this->packets)
    {
        arrivals.push_back(pkt.getArrivalTime());
    }
}

const void Object::getPktSizes(std::vector<short>& pktSizes) const
{
    pktSizes.clear();
    pktSizes.reserve(packets.size());

    for (const auto& pkt: this->packets)
    {
        pktSizes.push_back(pkt.getPacketSize());
    }
}

const void Object::getInterArrivalTimes(std::vector<double>& interArrivalTimes) const
{
    std::vector<double> arrivalTimes;
    this->getArrivalTimes(arrivalTimes);

    interArrivalTimes.clear();
    interArrivalTimes.reserve(arrivalTimes.size() - 1);

    for (size_t i = 1; i < arrivalTimes.size(); ++i)
    {
        double interArrivalTime = arrivalTimes[i] - arrivalTimes[i - 1];
        interArrivalTimes.push_back(interArrivalTime);
    }
}

const void Object::toString(std::string& str) const
{
    std::ostringstream oss;

    oss << ".   .   .   .   Server: " << server << std::endl;
    oss << ".   .   .   .   Arrivals: ";
    std::vector<double> arrivals;
    this->getArrivalTimes(arrivals);
    for (size_t i = 0; i < arrivals.size(); ++i) 
    {
        oss << std::fixed << std::setprecision(8) << arrivals[i];
        if (i != arrivals.size() - 1) 
        {
            oss << ", ";
        }
    }
    oss << std::endl;

    oss << ".   .   .   .   PktSizes: ";
    std::vector<short> pktSizes;
    this->getPktSizes(pktSizes);
    for (size_t i = 0; i < pktSizes.size(); ++i) 
    {
        oss << pktSizes[i];
        if (i != pktSizes.size() - 1) 
        {
            oss << ", ";
        }
    }
    oss << std::endl;

    str = oss.str();
}
