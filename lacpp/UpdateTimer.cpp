#include "UpdateTimer.h"
#include <SDL.h>

UpdateTimer::UpdateTimer()
{
    m_previousUpdateTime = SDL_GetTicks();
    m_counter = 0;
    m_reset = false;
}

void UpdateTimer::reset()
{
    m_previousUpdateTime = SDL_GetTicks();
    m_reset = true;
}

bool UpdateTimer::update(float dt)
{
    // Problem is that we expect m_previousUpdateTime to be used as a start of reference
    // However if it isn't called straight away then that defeats the purpose of the timer
    // It will return true immediately when it should have returned false

    // If update() is not called immediately after reset() or creation then it will return a false update 
    // It could explain why screen scrolling and objects that use this timer have choppy movement

   /* if (!m_reset)
    {
        reset();
    }*/

    float elapsedTime = (SDL_GetTicks() - m_previousUpdateTime) / 1000.0f;
    if (elapsedTime > dt)
    {
        m_previousUpdateTime = SDL_GetTicks();
        m_counter++;
       // m_reset = false;
        return true;
    }
    else
    {
        return false;
    }
}
