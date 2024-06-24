#ifndef __TG_CONSOLE__H__
#define __TG_CONSOLE__H__ 1

#include "TgEngine.h"
#include <iostream>
#include <chrono>
#include <thread>

class TgConsole: public TgEngine
{

    public:

        TgConsole();

        ~TgConsole();

        std::string toString();

        void generate(const char* target) ;


    private:

};



#endif // __TG_CONSOLE__H__
