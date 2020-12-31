#include "Timer.h"
#include <SDL.h>

Timer::Timer() : m_startTime(SDL_GetTicks())//, m_started(true)
{
}
/*
void Timer::start()
{
    if (!m_started)
    {
        m_startTime = SDL_GetTicks();
        m_started = true;
    }
}*/

void Timer::reset()
{
    m_startTime = SDL_GetTicks();
}

bool Timer::elapsed(float timeMs)
{
    auto ticksNow = SDL_GetTicks();
    if (((ticksNow - m_startTime) / 1000.0f) > timeMs)
    {
        m_startTime = SDL_GetTicks();
        return true;
    }
    return false;
}
