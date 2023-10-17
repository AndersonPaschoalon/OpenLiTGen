#ifndef CSVSNIFFER_H
#define CSVSNIFFER_H 1

#include <fstream>      // For file input/output
#include <sstream>      // For string stream operations
#include <iostream>     // For standard input/output operations
#include <vector>       // For using std::vector
#include <algorithm>    // For std::sort
#include <string>
#include <cpptools.h>
#include "BaseSniffer.h"


class CsvSniffer : public BaseSniffer
{
public:
    CsvSniffer();
    virtual ~CsvSniffer();

    bool analyze(const std::string &csvFile, std::vector<PACKET_INFO *> &pkts) override;

private:

    void populatePacketInfo(const std::string& line, double& firstArrival, PACKET_INFO* packetInfo);
};

#endif // CSVSNIFFER_H
