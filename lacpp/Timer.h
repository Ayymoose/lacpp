#ifndef TIMER_H
#define TIMER_H
#include <SDL.h>

class Timer
{
public:
    Timer();
    ~Timer();
    unsigned int getTicks() const
    {
        return SDL_GetTicks() - m_Ticks;
    }

private:
    unsigned int m_Ticks;
};


#endif // !TIMER_H
