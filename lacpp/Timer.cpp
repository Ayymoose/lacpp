#include "Timer.h"
#include <SDL.h>

Timer::Timer()
{
    m_Ticks = SDL_GetTicks();
}

Timer::~Timer()
{

}