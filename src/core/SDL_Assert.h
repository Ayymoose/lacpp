#pragma once

#include <iostream>
#include <exception>

// Use for SDL_* functions which should always return 0 on success
// TODO: Output file/line information on assert
#define SDL_ASSERT(assertion)                                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!((assertion) == 0))                                                                                       \
        {                                                                                                              \
            std::cerr << SDL_GetError() << std::endl;                                                                  \
            std::terminate();                                                                                          \
        }                                                                                                              \
    } while (0)
