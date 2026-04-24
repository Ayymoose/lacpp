#pragma once

#include "core/Logger.h"

#include <exception>
#include <format>

// Use for SDL_* functions which should always return 0 on success.
// Logs the failing expression, file, line, and SDL error then terminates.
#define SDL_CHECK(expr)                                                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((expr) != 0)                                                                                               \
        {                                                                                                              \
            zelda::Logger::instance().log<zelda::Logger::Mask::ERROR>(                                                 \
                std::format("SDL_CHECK(" #expr ") failed at {}:{}: {}", __FILE__, __LINE__, SDL_GetError()));          \
            std::terminate();                                                                                          \
        }                                                                                                              \
    } while (0)
