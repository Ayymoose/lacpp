#pragma once

#include <iostream>

// Custom assert to display message

#ifdef NDEBUG
    #define ZD_ASSERT(assertion, message)
#else
    #define ZD_ASSERT(assertion, message) do { if (!(assertion)) { std::cerr << message << std::endl; __debugbreak(); std::terminate(); } } while (0)
#endif

