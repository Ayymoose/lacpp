#pragma once

#include <iostream>
#include <type_traits>

#ifdef NDEBUG
    #define SDL_ASSERT(assertion, message) (assertion)
#else
    // Use for SDL_* functions which should always return 0 on success
    #define SDL_ASSERT(assertion) \
    do \
    { \
        if (!((assertion) == 0))\
        {\
            std::cerr << SDL_GetError() << std::endl; __debugbreak(); std::terminate(); \
        }\
    } while (0)
#endif

