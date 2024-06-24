#ifndef __TG_TINS__H__
#define __TG_TINS__H__ 1

#include "TgEngine.h"
#include <iostream>
#include <tins/tins.h>


class TgTins: public TgEngine
{

    public:

        TgTins();

        ~TgTins();

        std::string toString();

        void generate(const char* target) ;


    private:

        Tins::NetworkInterface iface;
        Tins::PacketSender sender;

};



#endif // __TG_TINS__H__
