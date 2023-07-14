

#include "Packet.h"

double Packet::getArrivalTime() const {
    return arrivalTime;
}

void Packet::setArrivalTime(double arrivalTime) {
    this->arrivalTime = arrivalTime;
}

short Packet::getPacketSize() const {
    return packetSize;
}

void Packet::setPacketSize(short packetSize) {
    this->packetSize = packetSize;
}