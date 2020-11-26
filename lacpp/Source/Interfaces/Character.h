#pragma once

#include "Vector.h"
#include "BasicCharacter.h"

using namespace Zelda;

// Defines a base class for which NPC, Boss, enemies inherit from

// Link won't inherit from here 



class Character : public BasicCharacter
{
public:
    virtual ~Character() = default;
    /*virtual float health() const noexcept = 0;
    virtual void damage(float damage) noexcept = 0;
    virtual Direction direction() const noexcept = 0;
    virtual Vector<float> position() const noexcept = 0;*/
protected:
    Character() = default;

    // Character direction
   /* Direction m_direction;

    // Character health
    float m_health;

    // Position vector
    Vector<float> m_positionVector;*/

    // Attack
    virtual void attack() = 0;

    // Die
    virtual void die() = 0;

    // Move
    virtual void move() = 0;
};