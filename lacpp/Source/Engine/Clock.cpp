#include "Clock.h"
#include <SDL.h>

Clock::Clock()
{
    m_startTime = 0;
    m_started = false;
}

void Clock::start()
{
    if (!m_started)
    {
        m_startTime = SDL_GetTicks();
        m_started = true;
    }
}

void Clock::reset()
{
    m_startTime = SDL_GetTicks();//0;
    m_started = false;
}

bool Clock::elapsed(float timeMs)
{
    auto ticksNow = SDL_GetTicks();
    return ((ticksNow - m_startTime) / 1000.0f) > timeMs;
}
