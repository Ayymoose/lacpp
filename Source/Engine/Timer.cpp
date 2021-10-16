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

bool Timer::elapsed(float ticksMs)
{
    float elapsedTime =  ((SDL_GetTicks() - m_startTime) / 1000.0f);
    if (elapsedTime > ticksMs)
    {
        m_startTime = SDL_GetTicks();
        return true;
    }
    return false;
}
