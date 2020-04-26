#ifndef VEC2_H
#define VEC2_H

// 2D vector class
template <typename T>
class Vec2
{
public:
    Vec2()
    {
        x = 0;
        y = 0;
    }
    Vec2(T x, T y)
    {
        this->x = x;
        this->y = y;
    }
    ~Vec2() = default;


    Vec2<T> operator*(int scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }

  /*  Vec2<T> operator+=(int value)
    {
        this->x += value;
        this->y += value;
        return *this;
    }*/

    Vec2<T> operator+=(Vec2<T> other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Vec2<T> operator=(Vec2<T> other)
    {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }

    Vec2<T> operator-(Vec2<T> other)
    {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    bool operator==(Vec2<T> other)
    {
        return (this->x == other.x && this->y == other.y);
    }

    bool operator!=(Vec2<T> other)
    {
        return !operator==(other);
    }

    // Cross product of 2 2D vectors
    static T cross(const Vec2& v1, const Vec2& v2)
    {
        assert(false);
        return 0;
    }

    // Dot product of 2 2D vectors
    static T dot(const Vec2& v1, const Vec2& v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    // Normalise a vector
    void normalise()
    {
        // TODO: Double/float epsilon
        assert(length() != 0);
        x /= length();
        y /= length();
    }

    // Vector length
    double length() const
    {
        return sqrt(x * x + y * y);
    }

    // Just easier to have it public
    T x;
    T y;
};

#endif // !VEC2_H
