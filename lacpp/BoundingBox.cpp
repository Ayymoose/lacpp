#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
    m_x = 0;
    m_y = 0;
    m_w = 0;
    m_h = 0;
}

BoundingBox::BoundingBox(int x, int y, int w, int h)
{
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = h;
}

bool BoundingBox::intersects(const BoundingBox& A, const BoundingBox& B)
{
    return (A.m_x < B.m_x + B.m_w) && (A.m_y < B.m_y + B.m_h) && (A.m_x + A.m_w > B.m_x) && (A.m_y + A.m_h > B.m_y);
}
