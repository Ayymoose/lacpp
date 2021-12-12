#if 0

#pragma once

#include <vector>
#include <map>


enum CollisionArea
{
    COLLISION_AREA_NONE = -1,
    COLLISION_TAIL_CAVE_0,
    COLLISION_TAIL_CAVE_1,
    COLLISION_TAIL_CAVE_2,
    COLLISION_TAIL_CAVE_3,
    COLLISION_TAIL_CAVE_4,
    COLLISION_TAIL_CAVE_5,
    COLLISION_TAIL_CAVE_6,
    COLLISION_TAIL_CAVE_7,
    COLLISION_TAIL_CAVE_8,
    COLLISION_TAIL_CAVE_9,
    COLLISION_TAIL_CAVE_10,
    COLLISION_TAIL_CAVE_11,
    COLLISION_TAIL_CAVE_12,
    COLLISION_TAIL_CAVE_13,
    COLLISION_TAIL_CAVE_14,
    COLLISION_TAIL_CAVE_15,
    COLLISION_TAIL_CAVE_16,
    COLLISION_TAIL_CAVE_17,
    COLLISION_TAIL_CAVE_18,
    COLLISION_TAIL_CAVE_19,
    COLLISION_TAIL_CAVE_20,
    COLLISION_TAIL_CAVE_21,
    COLLISION_TAIL_CAVE_22,
    COLLISION_TAIL_CAVE_23,
    COLLISION_TAIL_CAVE_24,
    COLLISION_TAIL_CAVE_25,
    COLLISION_TAIL_CAVE_26,
    COLLISION_TAIL_CAVE_27,
    COLLISION_TAIL_CAVE_28,
    COLLISION_AREA_COUNT
};

class CollisionMap
{
public:
    CollisionMap();
    std::vector<BoundingBox> collisionMap(CollisionArea area);

    // TODO: Put these in a single array
    // Map of areas to a list of rects defining positions of static objects
    CollisionArea m_tailCave[6][7] =
    {
        { COLLISION_AREA_NONE   ,COLLISION_AREA_NONE   ,COLLISION_AREA_NONE    ,COLLISION_AREA_NONE   ,COLLISION_TAIL_CAVE_28,COLLISION_TAIL_CAVE_27,COLLISION_TAIL_CAVE_26},
        { COLLISION_AREA_NONE   ,COLLISION_TAIL_CAVE_25,COLLISION_TAIL_CAVE_24 ,COLLISION_TAIL_CAVE_23,COLLISION_TAIL_CAVE_22,COLLISION_TAIL_CAVE_21,COLLISION_TAIL_CAVE_20},
        { COLLISION_TAIL_CAVE_19,COLLISION_AREA_NONE   ,COLLISION_TAIL_CAVE_18 ,COLLISION_TAIL_CAVE_17,COLLISION_TAIL_CAVE_16,COLLISION_TAIL_CAVE_15,COLLISION_TAIL_CAVE_14},
        { COLLISION_TAIL_CAVE_13,COLLISION_TAIL_CAVE_12,COLLISION_TAIL_CAVE_11 ,COLLISION_TAIL_CAVE_10,COLLISION_TAIL_CAVE_9 ,COLLISION_TAIL_CAVE_8 ,COLLISION_TAIL_CAVE_7},
        { COLLISION_TAIL_CAVE_6 ,COLLISION_AREA_NONE   ,COLLISION_TAIL_CAVE_5  ,COLLISION_TAIL_CAVE_4 ,COLLISION_TAIL_CAVE_3 ,COLLISION_AREA_NONE   ,COLLISION_AREA_NONE},
        { COLLISION_AREA_NONE   ,COLLISION_TAIL_CAVE_2 ,COLLISION_TAIL_CAVE_1  ,COLLISION_TAIL_CAVE_0 ,COLLISION_AREA_NONE   ,COLLISION_AREA_NONE   ,COLLISION_AREA_NONE}
    };


private:
    std::map<CollisionArea, std::vector<BoundingBox>> m_collisionMap;

};

#endif