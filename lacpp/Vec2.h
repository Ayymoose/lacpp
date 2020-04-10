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

    // Cross product of 2 2D vectors
    static T cross(const Vec2& v1, const Vec2& v2)
    {
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
