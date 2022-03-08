#include <SDL_scancode.h>

#pragma once

// Keyword control for Gameboy controls

namespace
{
    constexpr auto BUTTON_A = SDL_SCANCODE_Z;
    constexpr auto BUTTON_B = SDL_SCANCODE_X;
    constexpr auto BUTTON_UP = SDL_SCANCODE_UP;
    constexpr auto BUTTON_DOWN = SDL_SCANCODE_DOWN;
    constexpr auto BUTTON_LEFT = SDL_SCANCODE_LEFT;
    constexpr auto BUTTON_RIGHT = SDL_SCANCODE_RIGHT;
    constexpr auto BUTTON_START = SDL_SCANCODE_RETURN;
    constexpr auto BUTTON_SELECT = SDL_SCANCODE_J;
}

