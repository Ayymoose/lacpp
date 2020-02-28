#ifndef VEC2_H
#define VEC2_H

// 2D vector class

// int, float, double

class Vec2
{
public:
    Vec2();
    Vec2(int x, int y);
    ~Vec2() = default;

    // Cross product of 2 2D vectors
    static int cross(const Vec2& v1, const Vec2& v2);

    // Dot product of 2 2D vectors
    static int dot(const Vec2& v1, const Vec2& v2);

    // Normalise a vector
    void normalise();

    // Vector length
    double length() const;

    void set(int x, int y);

    // Just easier to have it public
    int x;
    int y;
};

#endif // !VEC2_H
