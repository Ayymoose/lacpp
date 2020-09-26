#pragma once

#include "Vector.h"

using namespace Zelda;
// Defines a base class for which NPC, Boss, Enemy and Link inherit from

enum class Direction
{
    DIRECTION_NONE = -1,
    DIRECTION_RIGHT,
    DIRECTION_LEFT,
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_COUNT
};

class Character
{
public:
    /*Character() = default;
    virtual ~Character() = default;*/
    virtual float health() const = 0;
    virtual void damage(float damage) = 0;
    Direction virtual direction() const = 0;
    virtual Vector<float> position() const = 0;
protected:
    // Character direction
    Direction m_direction;
    // Character health
    float m_health;

    // Position vector
    Vector<float> m_position;

    // Attack
    virtual void attack() = 0;

    // Die
    virtual void die() = 0;

    // Move
    virtual void move() = 0;
};