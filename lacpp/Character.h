#ifndef CHARACTER_H
#define CHARACTER_H

#include "Vec2.h"

// Defines a base class for which NPC, Boss, Enemy and Player inherit from

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
    Vec2 m_position;
    virtual void attack() {};
    virtual void die() {};
    virtual Vec2 position() const = 0;
};



#endif // !CHARACTER_H
