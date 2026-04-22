#pragma once

#include "FloatingPoint.h"

#include <cassert>
#include <cmath>
#include <concepts>
#include <iostream>

namespace zelda::engine
{
// 2D vector class
template <typename T>
    requires std::is_arithmetic_v<T>
struct Vector
{
    T x{};
    T y{};

    friend std::ostream& operator<<(std::ostream& ostream, const Vector& v)
    {
        ostream << '(' << v.x << ',' << v.y << ')';
        return ostream;
    }

    constexpr Vector() = default;

    constexpr Vector(T dx, T dy)
        : x(dx)
        , y(dy)
    {}

    template <typename U>
        requires std::is_arithmetic_v<U>
    [[nodiscard]] constexpr Vector operator/(const U scalar) const
    {
        assert(scalar != 0);
        return Vector(x / scalar, y / scalar);
    }

    [[nodiscard]] constexpr Vector operator+(const Vector& other) const { return Vector(x + other.x, y + other.y); }

    [[nodiscard]] constexpr Vector operator-(const Vector& other) const { return Vector(x - other.x, y - other.y); }

    template <typename U>
        requires std::is_arithmetic_v<U>
    [[nodiscard]] constexpr Vector operator*(const U scalar) const
    {
        return Vector(x * scalar, y * scalar);
    }

    template <typename U>
        requires std::is_arithmetic_v<U>
    constexpr Vector& operator*=(const U scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    template <typename U>
        requires std::is_arithmetic_v<U>
    constexpr Vector& operator/=(const U scalar)
    {
        assert(scalar != 0);
        x /= scalar;
        y /= scalar;
        return *this;
    }

    [[nodiscard]] constexpr Vector operator-() const { return Vector(-x, -y); }

    constexpr Vector& operator+=(const Vector& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    constexpr Vector& operator-=(const Vector& other) { return operator+=(-other); }

    [[nodiscard]] constexpr bool operator==(const Vector& other) const
    {
        return FloatingPoint<T>::almostEqual(x, other.x) && FloatingPoint<T>::almostEqual(y, other.y);
    }

    // Distance between two vectors
    [[nodiscard]] static constexpr auto distanceBetween(const Vector& v1, const Vector& v2)
    {
        const auto dx = v1.x - v2.x;
        const auto dy = v1.y - v2.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    // Cross product of 2 2D vectors
    [[nodiscard]] static constexpr T cross(const Vector& v1, const Vector& v2) { return (v1.x * v2.y) - (v1.y * v2.x); }

    // Dot product of 2 2D vectors
    [[nodiscard]] static constexpr T dot(const Vector& v1, const Vector& v2) { return (v1.x * v2.x) + (v1.y * v2.y); }

    constexpr void normalise()
        requires std::floating_point<T>
    {
        const auto len = length();
        assert(len != 0);
        x /= len;
        y /= len;
    }

    // Get the normal for this vector
    [[nodiscard]] constexpr Vector normal() const
    {
        const auto len = length();
        assert(len != 0);
        return *this / len;
    }

    [[nodiscard]] constexpr auto length() const { return std::sqrt(x * x + y * y); }
};

} // namespace zelda::engine
