#pragma once

#include "core/Vector.h"
#include "BasicCharacter.h"

// Defines a base class for which NPC, Boss, enemies inherit from

namespace zelda
{

class Character : public BasicCharacter
{
public:
    virtual ~Character() = default;

protected:
    Character() = default;

    // Attack
    virtual void attack() = 0;

    // Die
    virtual void die() = 0;

    // Move
    virtual void move() = 0;
};

} // namespace zelda