#include "Vec2.h"
#include <cmath>
#include <cassert>

Vec2::Vec2()
{
    x = 0;
    y = 0;
}

Vec2::Vec2(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Vec2::cross(const Vec2& v1, const Vec2& v2)
{
    return 0;
}

int Vec2::dot(const Vec2& v1, const Vec2& v2)
{
    return v1.x* v2.x + v1.y * v2.y;
}

void Vec2::normalise()
{
    assert(length() != 0);
    x /= length();
    y /= length();
}

double Vec2::length() const
{
    return sqrt(x * x + y * y);
}

void Vec2::set(int x, int y)
{
    this->x = x;
    this->y = y;
}