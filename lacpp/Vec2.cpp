#include "Vec2.h"
#include <cmath>

Vec2::Vec2()
{
    m_v_x = 0;
    m_v_y = 0;
    m_length = 0;
}

Vec2::Vec2(int x, int y)
{
    m_v_x = x;
    m_v_y = y;
    m_length = sqrt(x*x + y*y);
}

Vec2::~Vec2()
{

}

int Vec2::cross(Vec2 a, Vec2 b)
{
    return 0;
}

int Vec2::dot(Vec2 a, Vec2 b)
{
    return 0;
}

double Vec2::length() const
{
    return sqrt(m_v_x * m_v_x + m_v_y * m_v_y);
}

void Vec2::set(int x, int y)
{
    m_v_x = x;
    m_v_y = y;
}

void Vec2::add(int x, int y)
{
    m_v_x += x;
    m_v_y += y;
}
