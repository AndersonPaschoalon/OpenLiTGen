#include "TgPcap.h"
#include <iostream>
#include <fstream>
#include <cstring>


TgPcap::TgPcap()
{
}

TgPcap::~TgPcap()
{
    if (this->pcapWriter) 
    {
        delete this->pcapWriter;
    }    
}

std::string TgPcap::toString()
{
    return std::string("TgPcap");
}

void TgPcap::generate(const char* target) 
{

}
