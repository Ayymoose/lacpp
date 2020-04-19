#ifndef CHARACTER_H
#define CHARACTER_H

#include "Vec2.h"

// Defines a base class for which NPC, Boss, Enemy and Player inherit from

enum CHARACTER_DIRECTION
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
    Character() 
    {
        m_health = 0;
    };
    ~Character() = default;

    virtual float health() const
    {
        return m_health;
    }

    virtual void damage(float damage)
    {
        m_health -= damage;
    }

protected:
    float m_health;
    Vec2<float> m_position;
    virtual void attack() = 0;
    virtual void die() = 0;
    virtual Vec2<float> position() const = 0;
};



#endif // !CHARACTER_H
