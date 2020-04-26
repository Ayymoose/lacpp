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


/*

    Weapons that can be instantiated

    - Bow (Arrows)
    - Bomb
    - Hookshot
    - Flame rod
    - Sword
    - Magic Powder
    - Boomerang


*/

enum WPN_SPRITES
{
    WPN_SPRITE_NONE = -1,
    WPN_SPRITE_BOW,
    WPN_SPRITE_BOOMERANG,
    WPN_SPRITE_COUNT
};

class Weapon : public Renderable
{
public:
    Weapon()
    {
        m_direction = DIRECTION_NONE;
        m_depth = BACKGROUND_OBJECT_DEPTH;
        Renderer::getInstance().addRenderable(this);
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

    virtual void setPosition(Vec2<float> position) = 0;

    virtual void useWeapon() = 0;

    virtual BoundingBox boundingBox() const
    {
        return m_boundingBox;
    }

protected:
    Vec2<float> m_position;
    DIRECTION m_direction;
    UpdateTimer m_weaponTimer;
    BoundingBox m_boundingBox;

    // Weapon sprite sources
    SDL_Rect m_weaponSpritesSrc[WPN_SPRITE_COUNT] =
    {
        {0,0,8,16},      // WPN_SPRITE_BOW
        {10,0,8,16},     // WPN_SPRITE_BOOMERANG
    };

};

#endif