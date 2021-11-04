#include "Timer.h"
#include <SDL.h>
#include <iostream>
#include "Camera.h"

Timer::Timer() : m_startTime(SDL_GetTicks())
{
}

void Timer::reset()
{
    m_startTime = SDL_GetTicks();
}

bool Timer::elapsed(double ticksMs)
{
    auto elapsedTime =  ((SDL_GetTicks() - m_startTime) / 1000.0);
    if (elapsedTime > ticksMs)
    {
        m_startTime = SDL_GetTicks();
        return true;
    }
    return false;
}

bool Timer::elapsed(int tickMs)
{
    auto elapsedTime = SDL_GetTicks() - m_startTime;
    if (elapsedTime > tickMs)
    {
        m_startTime = SDL_GetTicks();
        return true;
    }
    return false;
}
