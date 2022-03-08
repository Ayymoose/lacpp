#pragma once
#include <cstdint>

namespace Zelda
{

using Colour = uint32_t;

constexpr Colour COLOUR_BLACK = 0;

constexpr inline Colour SDL_RGB(Colour r, Colour g, Colour b)
{
    return ((r) | ((g) << 8) | ((b) << 16));
}

constexpr inline Colour SDL_Red(Colour colour)
{
    return ((colour) & 0x0000FF);
}

constexpr inline Colour SDL_Green(Colour colour)
{
    return (((colour) >> 8) & 0x0000FF);
}

constexpr inline Colour SDL_Blue(Colour colour)
{
    return (((colour) >> 16) & 0x0000FF);
}

}