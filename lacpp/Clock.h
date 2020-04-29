#pragma once
#include <cstdint>

class Clock
{
public:
    Clock();
    ~Clock() = default;
    void start();
    void reset();
    bool elapsed(float timeMs);

private:
    uint32_t m_startTime;
    bool m_started;
};