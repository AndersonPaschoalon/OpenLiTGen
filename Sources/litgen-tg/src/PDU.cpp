#include "PDU.h"

PDU::PDU()
    : arrivalTime(0.0), packetSize(0), ipDst(""), ipSrc(""), portDst(0), portSrc(0) {}

double PDU::getArrivalTime() const 
{
    return arrivalTime;
}

void PDU::setArrivalTime(double arrivalTime) 
{
    this->arrivalTime = arrivalTime;
}

int PDU::getPacketSize() const 
{
    return packetSize;
}

void PDU::setPacketSize(int packetSize) 
{
    this->packetSize = packetSize;
}

const std::string& PDU::getIpDst() const 
{
    return ipDst;
}

void PDU::setIpDst(const std::string& ipDst) 
{
    this->ipDst = ipDst;
}

const std::string& PDU::getIpSrc() const 
{
    return ipSrc;
}

void PDU::setIpSrc(const std::string& ipSrc) 
{
    this->ipSrc = ipSrc;
}

int PDU::getPortDst() const 
{
    return portDst;
}

void PDU::setPortDst(int portDst) 
{
    this->portDst = portDst;
}

int PDU::getPortSrc() const 
{
    return portSrc;
}

void PDU::setPortSrc(int portSrc) 
{
    this->portSrc = portSrc;
}