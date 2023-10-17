#include <iostream>
#include <string>
#include <getopt.h>
#include "BaseSniffer.h"
#include "TinsSniffer.h"
#include "CsvSniffer.h"
#include "NetworkTraffic.h"
#include "LitModel.h"


const char helpMenu[] = R"(
Options:
  -h, --help              Show this help message and exit.
  -v, --version           Show version information and exit.
  -p, --pcap <path>       Path to the input pcap file (mandatory).
  -m, --comment <text>    Human-readable description of the traffic (mandatory).
  -t, --session-threshold <seconds>
                          Threshold to separate sessions (default: 300.00 seconds).

Description:
  litgen-model.exe is a tool for traffic modelling using pcap files. It takes
  input parameters to generate a <pcap-name>.lit file with LitGen parameters
  for the traffic modelling.

Examples:
  litgen-model.exe -p input.pcap -m "Web Traffic" -t 180.00

  litgen-model.exe --pcap input.pcap --comment "DNS Traffic"

  litgen-model.exe -h    
)";

const char appVersion[] = R"(
   litgen-model.exe  version v0.1.0.0 
)";


void createLitModel(const char* pcapFileName, const char* pcapComment, double sessionThreshold);


int main(int argc, char* argv[]) 
{
    std::string pcapFileName;
    std::string pcapComment;
    double sessionThreshold = 300.00;
    bool flagPcapFileName = false;
    bool flagPcapComment = false;

    const char* const short_opts = "p:m:t:vh";
    const option long_opts[] = {
        {"pcap", required_argument, nullptr, 'p'},
        {"comment", required_argument, nullptr, 'm'},
        {"session-threshold", required_argument, nullptr, 't'},
        {"version", no_argument, nullptr, 'v'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, no_argument, nullptr, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1) {
        switch (opt) {
            case 'p':
                pcapFileName = optarg;
                flagPcapFileName = true;
                break;
            case 'm':
                pcapComment = optarg;
                flagPcapComment = true;
                break;
            case 't':
                sessionThreshold = std::stod(optarg);
                break;
            case 'v':
                printf("%s\n", appVersion);
                return 0;
            case 'h':
                printf("%s\n", helpMenu);
                return 0;
            default:
                break;
        }
    } 

    if(flagPcapFileName == true && flagPcapComment == true)
    {
        if(fileExists(pcapFileName.c_str()))
        {
            createLitModel(pcapFileName.c_str(), pcapComment.c_str(), sessionThreshold);
        }
        else
        {
            printf("Error: file %s could not be found. Please provide as input a valid pcap file path, and try again.", pcapFileName.c_str());
            printf("%s\n", helpMenu);
            return -1;
        }

    }
    else
    {
        printf("Error: You must set --pcap option and --comment option to run lit-model.exe, or use --help or --version.\n\n");
        printf("%s\n", helpMenu);
        return -2;
    }


    return 0;
}

void createLitModel(const char* pcapFileName, const char* pcapComment, double sessionThreshold)
{
    // capture all packets raw data
    std::vector<PACKET_INFO *> pkts;
    BaseSniffer* sniffer;

    // Sniffer Factory
    // TODO usar to lower
    bool isCsv = StringUtils::endsWith(pcapFileName, ".csv");
    if (isCsv)
    {
        sniffer = new CsvSniffer();
    }
    else // pcap as default
    {
        sniffer = new TinsSniffer();
    }

    sniffer->analyze(pcapFileName, pkts); 
    sniffer->echo(pkts);

    // classify the data for modelling
    // TODO usar lib cpptools
    std::string traceName = getFileName(pcapFileName, true);
    // string is too big, better to not use the heap!
    std::string* str = new std::string();
    str->clear();
    NetworkTraffic* netTraffic = new NetworkTraffic(traceName, pcapComment);
    netTraffic->populateTraffic(pkts, sessionThreshold);
    netTraffic->toString(*str);
    std::cout << *str;

    // generate a traffic model, and save 
    LitModel lit;
    lit.calc(*netTraffic);
    lit.save();

    // free allocated memory
    sniffer->free(pkts);
    delete netTraffic;
    delete str;
    delete sniffer;

}
