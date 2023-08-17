#pragma once

#include <cstdint>

namespace Zelda
{
    using Colour = uint32_t;

    constexpr Colour COLOUR_BLACK = 0;

    constexpr inline Colour make_rgb(const Colour r, const Colour g, const Colour b)
    {
        return ((r) | ((g) << 8) | ((b) << 16));
    }

    constexpr inline Colour make_red(const Colour colour)
    {
        return ((colour) & 0x0000FF);
    }

    constexpr inline Colour make_green(const Colour colour)
    {
        return (((colour) >> 8) & 0x0000FF);
    }

    constexpr inline Colour make_blue(const Colour colour)
    {
        return (((colour) >> 16) & 0x0000FF);
    }

}