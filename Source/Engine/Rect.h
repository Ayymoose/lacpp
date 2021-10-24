#pragma once


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

    T x;
    T y;
    T w;
    T h;
};
}