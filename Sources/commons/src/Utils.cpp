#include "Utils.h"

void splitString(const char* inputStr, const char separator,  std::string& firstHalf, std::string& secondHalf) 
{
    std::string input = inputStr;
    size_t pos = input.find(separator);

    if (pos != std::string::npos) 
    {
        firstHalf = input.substr(0, pos);
        secondHalf = input.substr(pos + 1);
    } 
    else 
    {
        firstHalf = input;
        secondHalf = "";
    }
}