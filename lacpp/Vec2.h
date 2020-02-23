#ifndef VEC2_H
#define VEC2_H

// 2D vector class

class Vec2
{
public:
    Vec2();
    Vec2(int x, int y);
    ~Vec2();

    // Cross product of 2 2D vectors
    static int cross(Vec2 a, Vec2 b);

    // Dot product of 2 2D vectors
    static int dot(Vec2 a, Vec2 b);

    // Vector length
    double length() const;

    void add(int x, int y);

    void set(int x, int y);

    int x() const
    {
        return m_v_x;
    }

    int y() const
    {
        return m_v_y;
    }

private:
    int m_v_x;
    int m_v_y;
    double m_length;
};

#endif // !VEC2_H
