#include "UpdateTimer.h"
#include <SDL.h>

UpdateTimer::UpdateTimer()
{
    m_previousUpdateTime = SDL_GetTicks();
    m_counter = 0;
}

void UpdateTimer::reset()
{
    m_previousUpdateTime = SDL_GetTicks();
}

bool UpdateTimer::update(double dt)
{
    if ((SDL_GetTicks() - m_previousUpdateTime) / 1000.0 >= dt)
    {
        m_previousUpdateTime = SDL_GetTicks();
        m_counter++;
        return true;
    }
    else
    {
        return false;
    }
}
