#pragma once

#include "Vector.h"
#include "Depth.h"

using namespace Zelda;

enum class Direction
{
    DIRECTION_NONE = -1,
    DIRECTION_RIGHT,
    DIRECTION_LEFT,
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_COUNT
};

class BasicCharacter
{
public:
    virtual ~BasicCharacter() = default;
    virtual float health() const noexcept = 0;
    virtual Vector<float> position() const noexcept = 0;
protected:
    BasicCharacter() : m_direction(Direction::DIRECTION_NONE), m_health(0), m_speed(0)
    {
    }

    // Character direction
    Direction m_direction;

    // Character health
    float m_health;
    float m_speed;

    // Position vector
    Vector<float> m_positionVector;

    // Direction vector
    Vector<float> m_directionVector;
};