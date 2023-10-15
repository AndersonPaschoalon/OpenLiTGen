#include "CsvSniffer.h"

CsvSniffer::CsvSniffer()
{
}

CsvSniffer::~CsvSniffer()
{
}

bool CsvSniffer::analyze(const std::string &csvFile, std::vector<PACKET_INFO *> &pkts)
{
    CsvParser* parser = new CsvParser();
    int ret = parser->load(csvFile.c_str());
    if(ret != 0)
    {
        printf("Error: could not load CSV file %s\n", csvFile.c_str());
        return false;
    }

    std::vector<std::string> line;
    bool boolRet = true;

    while (boolRet == true)
    {
        line.clear();
        boolRet = parser->getNextLine(line);
        printf("line -> %s\n", StringUtils::toString(line).c_str());
        if(boolRet == false)
        {
            break;
        }

        // create packet object
        PACKET_INFO* pkt = new PACKET_INFO;
        pkt->arrivalTime = std::stod(line[parser->pos("arrivalTime")]);
        pkt->pktSize = std::stoi(line[parser->pos("pktSize")]);
        pkt->ipSrc = line[parser->pos("ipSrc")];
        pkt->ipDst = line[parser->pos("ipDst")];
        pkt->transportProtocol = line[parser->pos("transportProtocol")];
        pkt->portSrc = std::stoi(line[parser->pos("portSrc")]);
        pkt->portDst = std::stoi(line[parser->pos("portDst")]);
        pkt->syn = StringUtils::toBool(line[parser->pos("syn")].c_str());
        pkt->ack = StringUtils::toBool(line[parser->pos("ack")].c_str());
        pkt->fin = StringUtils::toBool(line[parser->pos("fin")].c_str());
        pkt->rst = StringUtils::toBool(line[parser->pos("rst")].c_str());

        // append
        pkts.push_back(pkt);    
    }
    

    // Sort the packets according to arrival time
    std::sort(pkts.begin(), pkts.end(), comparePacketInfo);

    // Assign user and flow IDs
    userAndFlowIdAssignment(pkts);

    delete parser;

    return true;
}

void CsvSniffer::populatePacketInfo(const std::string& line, double& firstArrival, PACKET_INFO* packetInfo) {
    std::stringstream ss(line);
    std::string token;

    printf("oi -- populatePacketInfo:%s\n", line.c_str());
    // Extract tokens using ',' as the delimiter
    std::getline(ss, token, ',');
    if(firstArrival == 0)
    {
        firstArrival = std::stod(token);
    }
    packetInfo->arrivalTime = firstArrival - std::stod(token);

    std::getline(ss, token, ',');
    packetInfo->pktSize = std::stoi(token);

    std::getline(ss, packetInfo->ipSrc, ',');
    std::getline(ss, packetInfo->ipDst, ',');
    std::getline(ss, packetInfo->transportProtocol, ',');
    
    std::getline(ss, token, ',');
    packetInfo->portSrc = std::stoi(token);

    std::getline(ss, token, ',');
    packetInfo->portDst = std::stoi(token);

    std::getline(ss, token, ',');
    packetInfo->syn = (token == "true");

    std::getline(ss, token, ',');
    packetInfo->ack = (token == "true");

    std::getline(ss, token, ',');
    packetInfo->fin = (token == "true");

    std::getline(ss, token, ',');
    packetInfo->rst = (token == "true");
}
