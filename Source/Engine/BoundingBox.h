#pragma once

class BoundingBox
{
public:
    BoundingBox() : x(0), y(0), w(0), h(0) {};
    BoundingBox(int x, int y, int w, int h);
    static bool intersects(const BoundingBox& b1, const BoundingBox& b2);

    int x;
    int y;
    int w;
    int h;
};