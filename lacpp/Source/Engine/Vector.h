#pragma once

namespace Zelda
{

    // 2D vector class
    template <typename T>
    class Vector
    {
    public:
        Vector() : x(0), y(0) {};
        Vector(T x, T y)
        {
            this->x = x;
            this->y = y;
        }

        Vector<T> operator*(int scalar) noexcept
        {
            this->x *= scalar;
            this->y *= scalar;
            return *this;
        }

        /*  Vector<T> operator+=(int value)
          {
              this->x += value;
              this->y += value;
              return *this;
          }*/

        Vector<T> operator+=(Vector<T> other) noexcept
        {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }

        Vector<T> operator=(Vector<T> other) noexcept
        {
            this->x = other.x;
            this->y = other.y;
            return *this;
        }

        Vector<T> operator-(Vector<T> other) noexcept
        {
            this->x -= other.x;
            this->y -= other.y;
            return *this;
        }

        bool operator==(Vector<T> other) noexcept
        {
            return (this->x == other.x && this->y == other.y);
        }

        bool operator!=(Vector<T> other) noexcept
        {
            return !operator==(other);
        }

        // Cross product of 2 2D vectors
        static constexpr T cross(const Vector& v1, const Vector& v2) noexcept
        {
            assert(false);
            return 0;
        }

        // Dot product of 2 2D vectors 
        static constexpr T dot(const Vector& v1, const Vector& v2) noexcept
        {
            return v1.x * v2.x + v1.y * v2.y;
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
            return sqrt(x * x + y * y);
        }

        // Just easier to have it public
        T x;
        T y;
    };
}