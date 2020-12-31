#pragma once

#include "Timer.h"
#include <random>

// Common functionality shared across

// Could think of a better name
inline void toggleItem(bool& toggle, Timer& clock, float time)
{
    if (!toggle && clock.elapsed(time))
    {
        // Toggle the item in question!
        toggle = true;
        //clock.reset();
    }
    else
    {
        if (clock.elapsed(time))
        {
            toggle = false;
            //clock.reset();
        }
    }
}

// Generate a random int between start and end inclusive
inline int random(int start, int end)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(start, end); // define the range
    return distr(gen);
}