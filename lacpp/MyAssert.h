#pragma once

#include <iostream>
#include <assert.h>


#ifdef NDEBUG
    #define DASSERT(assertion, message) ((void)0)
#else
    #define DASSERT(assertion, message) if (!(assertion)) { std::cerr << "Assertion failed: " << message << std::endl; assert(false); }
#endif

