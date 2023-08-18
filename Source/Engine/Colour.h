#pragma once

#include <cstdint>

namespace Zelda
{
    using Colour = uint32_t;

    constexpr Colour COLOUR_BLACK = 0;

    constexpr inline Colour makeRGB(const Colour r, const Colour g, const Colour b)
    {
        return ((r) | ((g) << 8) | ((b) << 16));
    }

    constexpr inline Colour makeRed(const Colour colour)
    {
        return ((colour) & 0x0000FF);
    }

    constexpr inline Colour makeGreen(const Colour colour)
    {
        return (((colour) >> 8) & 0x0000FF);
    }

    constexpr inline Colour makeBlue(const Colour colour)
    {
        return (((colour) >> 16) & 0x0000FF);
    }

}