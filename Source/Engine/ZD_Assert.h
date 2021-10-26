#pragma once

#include <iostream>
#include <type_traits>

// TODO: Rename to SDL_Assert.h

#define SDL_ERROR_MESSAGE "SDL Error: " << SDL_GetError()
// Custom assert to display message

#ifdef NDEBUG
    // TODO: Check this actually works (is compiled out) in Release mode
    #define SDL_ASSERT(assertion, message) assertion
#else
    // Use for SDL_* functions which should always return 0
    #define SDL_ASSERT(assertion, message) \
    do \
    { \
        if (!((assertion) == 0))\
        {\
            std::cerr << message << std::endl; __debugbreak(); std::terminate(); \
        }\
    } while (0)
#endif

