#include "Timer.h"

std::chrono::time_point<std::chrono::high_resolution_clock> Timer::start;

void Timer::init()
{
    Timer::start = std::chrono::high_resolution_clock::now();
}

std::string Timer::elapsedTime()
{
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - Timer::start).count();

        int hours = duration / 3600;
        int minutes = (duration % 3600) / 60;
        int seconds = duration % 60;

        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":";
        oss << std::setw(2) << std::setfill('0') << minutes << ":";
        oss << std::setw(2) << std::setfill('0') << seconds;

        return oss.str();
}
