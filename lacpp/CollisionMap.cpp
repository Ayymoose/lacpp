#include "CollisionMap.h"
#include <assert.h>

CollisionMap::CollisionMap()
{
    BoundingBox b1(0,80,16,48);
    BoundingBox b2(0, 0, 16, 48);
    BoundingBox b3(16, 0, 48, 16);
    BoundingBox b4(96, 0, 64, 16);
    BoundingBox b5(144, 16, 16, 96);
    BoundingBox b6(104, 112, 56, 16);
    BoundingBox b7(16, 112, 40, 16);
    BoundingBox b8(56, 104, 16, 24);
    BoundingBox b9(88, 104, 16, 24);
    BoundingBox b10(16, 16, 16, 16);
    BoundingBox b11(128, 16, 16, 16);
    BoundingBox b12(16, 96, 16, 16);
    BoundingBox b13(128, 96, 16, 16);
    BoundingBox b14(32, 32, 16, 48);
    BoundingBox b15(32, 32, 16, 48);
    BoundingBox b16(48, 32, 16, 16);
    BoundingBox b17(112, 32, 16, 48);
    BoundingBox b18(96, 32, 16, 16);
    std::vector<BoundingBox> vector;

    vector.emplace_back(b1);
    vector.emplace_back(b2);
    vector.emplace_back(b3);
    vector.emplace_back(b4);
    vector.emplace_back(b5);
    vector.emplace_back(b6);
    vector.emplace_back(b7);
    vector.emplace_back(b8);
    vector.emplace_back(b9);
    vector.emplace_back(b10);
    vector.emplace_back(b11);
    vector.emplace_back(b12);
    vector.emplace_back(b13);
    vector.emplace_back(b14);
    vector.emplace_back(b15);
    vector.emplace_back(b16);
    vector.emplace_back(b17);
    vector.emplace_back(b18);




    m_collisionMap[COLLISION_AREA_TEST] = vector;
}

bool CollisionMap::collision(COLLISION_AREA area, const BoundingBox& b1)
{
    assert(area > COLLISION_AREA_NONE && area < COLLISION_AREA_COUNT);

    std::vector<BoundingBox> boundingBoxes = m_collisionMap[area];
    bool collision = false;
    for (const BoundingBox& box : boundingBoxes)
    {
        if (BoundingBox::intersects(box, b1))
        {
            collision = true;
            break;
        }
    }

    return collision;
}

std::vector<BoundingBox> CollisionMap::collisionMap(COLLISION_AREA area)
{
    assert(area > COLLISION_AREA_NONE && area < COLLISION_AREA_COUNT);
    return m_collisionMap[area];
}
