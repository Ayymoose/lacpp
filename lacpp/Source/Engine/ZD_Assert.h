#pragma once

#include <iostream>

// Custom assert to display message

#ifdef NDEBUG
    #define ZD_ASSERT(assertion, message) ((void)0)
#else
    #define ZD_ASSERT(assertion, message) do { if (!(assertion)) { std::cerr << message << std::endl; __debugbreak(); std::terminate(); } } while (0)
#endif

