#pragma once
#include <cstdint>

// Basic timer functionality 

constexpr float FPS_60 = 1.0f / 60.0f;

class Timer
{
public:
    Timer();
    void reset();
    bool elapsed(float ticksMs);

private:
    uint32_t m_startTime;
};