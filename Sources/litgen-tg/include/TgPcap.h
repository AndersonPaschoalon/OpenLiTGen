#ifndef __TG_PCAP__H__
#define __TG_PCAP__H__ 1

#include "TgEngine.h"
#include <tins/tins.h>

class TgPcap: public TgEngine
{

    public:

        TgPcap();

        ~TgPcap();

        std::string toString();

        void generate(const char* target) ;


    private:

    Tins::FileSniffer* pcapWriter;

};



#endif // __TG_PCAP__H__
