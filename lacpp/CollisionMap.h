#ifndef COLLISION_MAP_H
#define COLLISION_MAP_H

#include "BoundingBox.h"
#include <vector>
#include <map>


enum COLLISION_AREA
{
    COLLISION_AREA_NONE = -1,
    COLLISION_AREA_TEST,
    COLLISION_AREA_COUNT
};

class CollisionMap
{
public:
    CollisionMap();
    bool collision(COLLISION_AREA area, const BoundingBox& b1);
    std::vector<BoundingBox> collisionMap(COLLISION_AREA area);

private:
    std::map<COLLISION_AREA, std::vector<BoundingBox>> m_collisionMap;

};


// Map of areas to a list of rects defining positions of static objects
// m_collisionMap[AREA] -> std::vector<BoundingBox>

#endif 