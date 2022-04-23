#pragma once

#include <SDL_rect.h>
#include <type_traits>

namespace Zelda
{

template<typename T>
struct Rect
{
    static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Invalid template type");

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

    // TODO: Add method to check rect within rect

    T x;
    T y;
    T w;
    T h;
};

// if RectType is Rect<integral type> then return SDL_Rect
// if RectType is Rect<floating point type> then return SDL_FRect

template<typename T>
std::enable_if_t<std::is_integral_v<T>, SDL_Rect> rectToSDLRect(const Rect<T>& rect) noexcept
{
    return SDL_Rect
    {
        static_cast<int>(rect.x), 
        static_cast<int>(rect.y), 
        static_cast<int>(rect.w), 
        static_cast<int>(rect.h)
    };
}
template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, SDL_FRect> rectToSDLRect(const Rect<T>& rect) noexcept
{
    return SDL_FRect
    {
        rect.x, 
        rect.y,
        rect.w, 
        rect.h 
    };
}

}