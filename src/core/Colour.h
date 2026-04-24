#pragma once

namespace zelda::engine
{

struct Colour
{
    using colour = uint32_t;

    static constexpr colour BLACK = 0;

    static constexpr colour makeRGB(const colour r, const colour g, const colour b) { return r | g << 8 | b << 16; }

    static constexpr colour makeRed(const colour colour) { return colour & 0x0000FF; }

    static constexpr colour makeGreen(const colour colour) { return colour >> 8 & 0x0000FF; }

    static constexpr colour makeBlue(const colour colour) { return colour >> 16 & 0x0000FF; }
};


} // namespace zelda::engine