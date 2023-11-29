#ifndef __TG_TINS__H__
#define __TG_TINS__H__ 1

#include "TgEngine.h"


class TgTins: public TgEngine
{

    public:

        TgTins();

        ~TgTins();

        std::string toString();

        void generate(const char* target) ;


    private:

};



#endif // __TG_TINS__H__
