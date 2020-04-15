#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

class BoundingBox
{
public:
    BoundingBox();
    BoundingBox(int x, int y, int w, int h);
    static bool intersects(const BoundingBox& b1, const BoundingBox& b2);
    int x;
    int y;
    int w;
    int h;
};

#endif // BOUNDING_BOX_H
