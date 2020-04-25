#ifndef WEAPON_H
#define WEAPON_H

#include "Depth.h"
#include "Renderable.h"
#include "Inventory.h"
#include "Vec2.h"
#include "Character.h"
#include "UpdateTimer.h"
#include "Renderer.h"
#include "BoundingBox.h"

class Weapon : public Renderable
{
public:
    Weapon(WEAPON weapon)
    {
        m_weapon = weapon;
        m_width = 8;
        m_height = 16;
        m_direction = DIRECTION_NONE;
        m_depth = BACKGROUND_OBJECT_DEPTH;
        m_name = "Bow";
        Renderer::getInstance().addRenderable(this);

        m_perished = false;
    }

    virtual ~Weapon() = default;

    virtual Vec2<float> position() const
    {
        return m_position;
    }

    virtual void setDirection(DIRECTION direction)
    {
        m_direction = direction;
    }
    virtual void setPosition(Vec2<float> position)
    {
        m_position = position;
    }
    virtual void useWeapon() = 0;

    // Has the weapon perished
    virtual bool perished() = 0;

protected:
    WEAPON m_weapon;
    Vec2<float> m_position;
    DIRECTION m_direction;
    UpdateTimer m_weaponTimer;
    BoundingBox m_boundingBox;
    bool m_perished;
};

#endif