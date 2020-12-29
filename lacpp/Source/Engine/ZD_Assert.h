#pragma once

#include <iostream>

// Custom assert to display message

#ifdef NDEBUG
    // TODO: Check this actually works (is compiled out) in Release mode
    #define ZD_ASSERT(assertion, message) assertion
#else
    // TODO: Fix macro as if we keep in release we'll be left with exp == 0 for SDL commands
    #define ZD_ASSERT(assertion, message) do { if (!(assertion)) { std::cerr << message << std::endl; __debugbreak(); std::terminate(); } } while (0)
#endif

