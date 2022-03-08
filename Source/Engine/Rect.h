#pragma once

#include <SDL_rect.h>
#include <type_traits>

namespace Zelda
{

template<typename T>
struct Rect
{
    static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "Invalid template type");

    constexpr Rect() : x(0), y(0), w(0), h(0) {};
    constexpr Rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}

    bool operator==(const Rect& other) const noexcept
    {
        return (other.x == x) && (other.y == y) && (other.w == w) && (other.h == h);
    }

    bool operator!=(const Rect& other) const noexcept
    {
        return !operator==(other);
    }

    T x;
    T y;
    T w;
    T h;
};

// if RectType is Rect<int> then return SDL_Rect
// if RectType is Rect<float> then return SDL_FRect
inline auto rectToSDLRect(const Rect<int>& rect) noexcept
{
    return SDL_Rect{ rect.x, rect.y, rect.w, rect.h };
}

inline auto rectToSDLRect(const Rect<float>& rect) noexcept
{
    return SDL_FRect{ rect.x, rect.y, rect.w, rect.h };
}

}