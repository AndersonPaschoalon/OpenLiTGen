#ifndef __TIMER_H__
#define __TIMER_H__ 1

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

class Timer 
{
    private:
        static std::chrono::time_point<std::chrono::high_resolution_clock> start;

    public:

        static void init();
        static std::string elapsedTime();
};


#endif // __TIMER_H__