#pragma once

#include <cassert>
#include <cmath>

namespace Zelda
{
    // 2D vector class
    template <typename T>
    class Vector
    {
    public:
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Invalid template type");

        constexpr Vector() : x(0), y(0) {};
        Vector(T x, T y) : x(x), y(y) {}

        constexpr Vector operator/(const double scalar) const
        {
            assert(scalar != 0);
            return Vector(x / scalar, y / scalar);
        }

        Vector operator+(const Vector& other) const
        {
            return Vector(x + other.x, y + other.y);
        }

        Vector operator*(const double scalar) const
        {
            return Vector(x * scalar, y * scalar);
        }

        Vector& operator*=(const double scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        Vector& operator/=(const double scalar)
        {
            assert(scalar != 0);
            x /= scalar;
            y /= scalar;
            return *this;
        }

        Vector operator-() const
        {
            return Vector(-x, -y);
        }

        Vector& operator+=(const Vector& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector& operator-=(const Vector& other)
        {
            return operator+=(-other);
        }

        Vector operator-(const Vector& other) const
        {
            return Vector(x - other.x, y - other.y);
        }

        bool operator==(const Vector& other) const
        {
            // EPSILON COMPARISON
            return ((x == other.x) && (y == other.y));
        }

        bool operator!=(const Vector& other) const
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
            // TODO: Double/float epsilon comparison
            assert(len != 0);
            return Vector(v.x / len, v.y / len);
        }

        // Normalise a vector
        // Note this will only work for float and double
        // TODO: SFINAE this out

        void /*std::enable_if_t<std::is_integral_v<T>, void>*/ normalise()
        {
            auto const len = length();
            // TODO: Double/float epsilon comparison
            assert(len != 0);

            x /= len;
            y /= len;
        }

        // Get the normal for this vector
        Vector normal() const
        {
            Vector vNormal = *this;
            auto len = length();
            // TODO: Double/float epsilon comparison
            assert(len != 0);

            return vNormal / len;
        }

        // Vector length
        constexpr auto length() const
        {
            return std::sqrt((x * x) + (y * y));
        }

        // Linear interpolate between two vectors
        // FLOAT DOUBLE only
        static constexpr Vector lerp(const Vector& A, const Vector& B, double alpha)
        {
            // A* t + B * (1.f - t);
            assert(alpha >= 0.0 && alpha <= 1.0);
            return Vector((1.0 - alpha) * A.x + alpha * B.x, (1.0 - alpha) * A.y + alpha * B.y);
        }

        T x;
        T y;
    };
}