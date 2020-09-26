#pragma once

#include "Clock.h"

// Common functionality shared across

// Could think of a better name
inline void toggleItem(bool& toggle, Clock& clock, float time)
{
    if (!toggle && clock.elapsed(time))
    {
        // Toggle the item in question!
        toggle = true;
        clock.reset();
    }
    else
    {
        if (clock.elapsed(time))
        {
            toggle = false;
            clock.reset();
        }
    }
}