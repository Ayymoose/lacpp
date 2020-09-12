#include "BoundingBox.h"

BoundingBox::BoundingBox(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

bool BoundingBox::intersects(const BoundingBox& A, const BoundingBox& B)
{
    return (A.x < B.x + B.w) && (A.y < B.y + B.h) && (A.x + A.w > B.x) && (A.y + A.h > B.y);
}