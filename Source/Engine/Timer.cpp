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
    // This is untested with frame rates > 60FPS!
    // Rounding up should stop the stuttering/jittery motion when it returns false because
    // at 60fps, we have 16.7ms per frame
    float elapsedTime =  ((SDL_GetTicks() - m_startTime) / 1000.0f) + 0.005f;
    if (elapsedTime > ticksMs)
    {
        m_startTime = SDL_GetTicks();
        return true;
    }
    return false;
}
