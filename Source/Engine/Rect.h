#pragma once

#include <SDL_rect.h>

namespace Zelda
{

template<typename T>
struct Rect
{
    constexpr Rect() : x(0), y(0), w(0), h(0) {};
    constexpr Rect(T x, T y, T w, T h)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

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
inline SDL_Rect rectToSDLRect(const Rect<int>& rect)
{
    return SDL_Rect{ rect.x, rect.y, rect.w, rect.h };
}

inline SDL_FRect rectToSDLRect(const Rect<float>& rect)
{
    return SDL_FRect{ rect.x, rect.y, rect.w, rect.h };
}

}