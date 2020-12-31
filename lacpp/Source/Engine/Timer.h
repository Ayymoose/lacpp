#pragma once
#include <cstdint>

// Basic timer functionality 

class Timer
{
public:
    Timer();
    //void start();
    void reset();
    bool elapsed(float timeMs);

private:
    uint32_t m_startTime;
    //bool m_started;
};