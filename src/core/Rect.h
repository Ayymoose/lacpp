#pragma once

#include "FloatingPoint.h"

#include <SDL_rect.h>
#include <concepts>
#include <iostream>

namespace zelda::engine
{

template <typename T>
    requires std::is_arithmetic_v<T>
struct Rect
{
    T x{};
    T y{};
    T w{};
    T h{};

    friend std::ostream& operator<<(std::ostream& ostream, const Rect& r)
    {
        ostream << '(' << r.x << ',' << r.y << ',' << r.w << ',' << r.h << ')';
        return ostream;
    }

    constexpr Rect() = default;

    constexpr Rect(T dx, T dy, T dw, T dh)
        : x(dx)
        , y(dy)
        , w(dw)
        , h(dh)
    {}

    [[nodiscard]] constexpr bool operator==(const Rect& other) const
    {
        return FloatingPoint<T>::almostEqual(other.x, x) && FloatingPoint<T>::almostEqual(other.y, y)
               && FloatingPoint<T>::almostEqual(other.w, w) && FloatingPoint<T>::almostEqual(other.h, h);
    }
};

// if RectType is Rect<integral type> then return SDL_Rect
// if RectType is Rect<floating point type> then return SDL_FRect

template <std::integral T>
[[nodiscard]] SDL_Rect rectToSDLRect(const Rect<T>& rect)
{
    return SDL_Rect{static_cast<int>(rect.x),
                    static_cast<int>(rect.y),
                    static_cast<int>(rect.w),
                    static_cast<int>(rect.h)};
}

// Note: SDL_FRect uses float fields, so Rect<double> values will be narrowed to float precision
template <std::floating_point T>
[[nodiscard]] SDL_FRect rectToSDLRect(const Rect<T>& rect)
{
    return SDL_FRect{static_cast<float>(rect.x),
                     static_cast<float>(rect.y),
                     static_cast<float>(rect.w),
                     static_cast<float>(rect.h)};
}

} // namespace zelda::engine
