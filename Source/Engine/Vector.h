#pragma once

#include "FloatingPoint.h"
#include <iostream>
#include <cassert>
#include <cmath>

namespace Zelda
{
    // 2D vector class
    template <typename T>
    struct Vector
    {
        static_assert(std::is_arithmetic_v<T>, "Arithemtic only type allowed");

        friend std::ostream& operator<< (std::ostream& ostream, const Vector<T>& v)
        {
            ostream << '(' << v.x << ',' << v.y << ')';
            return ostream;
        }

        constexpr Vector() : x{}, y{} {}
        constexpr Vector(T x, T y) : x(x), y(y) {}

        constexpr Vector operator/(const double scalar) const
        {
            assert(scalar != 0);
            return Vector(x / scalar, y / scalar);
        }

        constexpr Vector operator+(const Vector& other) const
        {
            return Vector(x + other.x, y + other.y);
        }

        constexpr Vector operator*(const double scalar) const
        {
            return Vector(x * scalar, y * scalar);
        }

        constexpr Vector& operator*=(const double scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        constexpr Vector& operator/=(const double scalar)
        {
            assert(scalar != 0);
            x /= scalar;
            y /= scalar;
            return *this;
        }

        constexpr Vector operator-() const
        {
            return Vector(-x, -y);
        }

        constexpr Vector& operator+=(const Vector& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        constexpr Vector& operator-=(const Vector& other)
        {
            return operator+=(-other);
        }

        constexpr bool operator-(const Vector& other) const
        {
            return Vector(x - other.x, y - other.y);
        }

        constexpr bool operator==(const Vector& other) const
        {
            return FloatingPoint<T>::almostEqual(x, other.x) && FloatingPoint<T>::almostEqual(y, other.y);
        }

        constexpr bool operator!=(const Vector& other) const
        {
            return !operator==(other);
        }

        // Distance between two vectors
        static constexpr auto distanceBetween(const Vector& v1, const Vector& v2)
        {
            const auto dx = v1.x - v2.x;
            const auto dy = v1.y - v2.y;
            return std::sqrt((dx * dx) + (dy * dy));
        }

        // Cross product of 2 2D vectors
        static constexpr T cross(const Vector& v1, const Vector& v2)
        {
            return (v1.x * v2.y) - (v1.y * v2.x);
        }

        // Dot product of 2 2D vectors 
        static constexpr T dot(const Vector& v1, const Vector& v2)
        {
            return (v1.x * v2.x) + (v1.y * v2.y);
        }

        static constexpr Vector normalise(const Vector& v)
        {
            auto const len = v.length();
            assert(len != 0);
            return Vector(v.x / len, v.y / len);
        }

        // Note this will only work for float and double
        template <typename U = T>
        constexpr auto normalise() -> std::enable_if_t<std::is_floating_point_v<U>, void>
        {
            auto const len = length();
            assert(len != 0);

            x /= len;
            y /= len;
        }

        // Get the normal for this vector
        constexpr Vector normal() const
        {
            auto thisNormal = *this;
            auto len = length();
            assert(len != 0);
            return thisNormal / len;
        }

        constexpr auto length() const
        {
            return std::sqrt(x * x + y * y);
        }

        T x;
        T y;
    };

}