#pragma once

#include <SDL_rect.h>
#include <iostream>

#include "FloatingPoint.h"

namespace Zelda
{
    template<typename T>
    struct Rect
    {
        static_assert(std::is_arithmetic_v<T>, "Invalid template type");

        friend std::ostream& operator<< (std::ostream& ostream, const Rect<T>& r)
        {
            ostream << '(' << r.x << ',' << r.y << ',' << r.w << ',' << r.h << ')';
            return ostream;
        }

        constexpr Rect() : x{}, y{}, w{}, h{} {}
        constexpr Rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}

        bool operator==(const Rect& other) const
        {
            return 
                FloatingPoint<T>::almostEqual(other.x,x) && FloatingPoint<T>::almostEqual(other.y, y) && 
                FloatingPoint<T>::almostEqual(other.w,w) && FloatingPoint<T>::almostEqual(other.h, h);
        }

        bool operator!=(const Rect& other) const
        {
            return !operator==(other);
        }

        T x;
        T y;
        T w;
        T h;
    };

    // if RectType is Rect<integral type> then return SDL_Rect
    // if RectType is Rect<floating point type> then return SDL_FRect

    template<typename T>
    std::enable_if_t<std::is_integral_v<T>, SDL_Rect> rectToSDLRect(const Rect<T>& rect)
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
    std::enable_if_t<std::is_floating_point_v<T>, SDL_FRect> rectToSDLRect(const Rect<T>& rect)
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