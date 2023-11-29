#ifndef __PDU_H__
#define __PDU_H__

#include <string>

class PDU {
public:

    PDU();

    double getArrivalTime() const;
    void setArrivalTime(double arrivalTime);

    int getPacketSize() const;
    void setPacketSize(int packetSize);

    const std::string& getIpDst() const;
    void setIpDst(const std::string& ipDst);

    const std::string& getIpSrc() const;
    void setIpSrc(const std::string& ipSrc);

    int getPortDst() const;
    void setPortDst(int portDst);

    int getPortSrc() const;
    void setPortSrc(int portSrc);

private:
    double arrivalTime;
    int packetSize;
    std::string ipDst;
    std::string ipSrc;
    int portDst;
    int portSrc;
};

#endif // __PDU_H__
