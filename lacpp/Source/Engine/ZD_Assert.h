#pragma once

#include <iostream>

// Custom assert to display message

#ifdef NDEBUG
    // Check this actually works in Release mode
    #define ZD_ASSERT(assertion, message) assertion
#else
    #define ZD_ASSERT(assertion, message) do { if (!(assertion)) { std::cerr << message << std::endl; __debugbreak(); std::terminate(); } } while (0)
#endif

