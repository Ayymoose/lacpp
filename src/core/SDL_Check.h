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

#define SDL_ASSERT(expr)                                                                                               \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(expr))                                                                                                   \
        {                                                                                                              \
            zelda::Logger::instance().log<zelda::Logger::Mask::ERROR>(                                                 \
                std::format("SDL_ASSERT(" #expr ") failed at {}:{}: {}", __FILE__, __LINE__, SDL_GetError()));         \
            std::terminate();                                                                                          \
        }                                                                                                              \
    } while (0)

#define SDL_CHECK_NO_ERROR()                                                                                           \
    do                                                                                                                 \
    {                                                                                                                  \
        if (auto error = std::string_view(SDL_GetError()); !error.empty())                                             \
        {                                                                                                              \
            zelda::Logger::instance().log<zelda::Logger::Mask::ERROR>(                                                 \
                std::format("SDL_CHECK_NO_ERROR() failed at {}:{}: {}", __FILE__, __LINE__, error));                   \
            std::terminate();                                                                                          \
        }                                                                                                              \
    } while (0)
