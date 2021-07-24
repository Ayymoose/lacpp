#pragma once

#include <assert.h>
#include <cmath>

namespace Zelda
{
// 2D vector class
template <typename T>
class Vector
{
public:
    constexpr Vector() : x(0), y(0) {};
    Vector(T x, T y)
    {
        this->x = x;
        this->y = y;
    }

    Vector<T> operator/(float div) const noexcept
    {
        assert(div != 0);
        return Vector<T>(x / div, y / div);
    }

    Vector<T> operator+(Vector<T> other) noexcept
    {
        return Vector<T>(x + other.x, y + other.y);
    }

    Vector<T> operator*(float scalar) const noexcept
    {
        return Vector<T>(x * scalar, y * scalar);
    }

    Vector<T> operator-() const noexcept
    {
        return Vector<T>(-x, -y);
    }

    Vector<T> operator+=(Vector<T> other) noexcept
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector<T> operator=(Vector<T> other) noexcept
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    Vector<T> operator-(Vector<T> other) const noexcept
    {
        return Vector<T>(x - other.x, y - other.y);
    }

    bool operator==(Vector<T> other) const noexcept
    {
        return (x == other.x && y == other.y);
    }

    bool operator!=(Vector<T> other) const noexcept
    {
        return !operator==(other);
    }

    // Distance between two vectors
    static constexpr float distanceBetween(const Vector& v1, const Vector& v2)
    {
        const auto dx = v1.x - v2.x;
        const auto dy = v1.y - v2.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    // Cross product of 2 2D vectors
    static constexpr T cross(const Vector& v1, const Vector& v2) noexcept
    {
        return (v1.x * v2.y) - (v1.y * v2.x);
    }

    // Dot product of 2 2D vectors 
    static constexpr T dot(const Vector& v1, const Vector& v2) noexcept
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    static constexpr Vector<T> normalise(const Vector& v) noexcept
    {
        float len = v.length();
        // TODO: Double/float epsilon comparison
        assert(len != 0);
        return Vector<T>(v.x / len, v.y / len);
    }

    // Normalise a vector
    void normalise() noexcept
    {
        float len = length();
        // TODO: Double/float epsilon comparison
        assert(len != 0);

        x /= len;
        y /= len;
    }

    // Vector length
    constexpr float length() const noexcept
    {
        return static_cast<float>(std::sqrt(x * x + y * y));
    }

    T x;
    T y;
};
}