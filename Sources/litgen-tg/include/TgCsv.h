#ifndef __TG_CSV__H__
#define __TG_CSV__H__ 1

#include "TgEngine.h"


class TgCsv: public TgEngine
{

    public:

        TgCsv();

        ~TgCsv();

        std::string toString();

        void generate(const char* target) ;


    private:

};



#endif // __TG_CSV__H__
