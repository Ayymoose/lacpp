#pragma once

#include "Depth.h"
#include "Renderable.h"
#include "Inventory.h"
#include "Vector.h"
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

#define SPRITE_SPACING 2

enum WeaponSprites
{
    WPN_SPRITE_NONE = -1,
    WPN_SPRITE_BOW,
    WPN_SPRITE_BOOMERANG,
    WPN_SPRITE_BOMB,
    WPN_SPRITE_FLAMEROD_FLAME,
    WPN_SPRITE_FLAMEROD,
    WPN_SPRITE_SWORD,
    WPN_SPRITE_COUNT
};

class Weapon : public Renderable
{
public:
    Weapon()
    {
        m_direction = DIRECTION_NONE;
        m_depth = ZD_DEPTH_BACKGROUND_OBJECT;
        Renderer::getInstance().addRenderable(this);
    }

    virtual ~Weapon() = default;

    virtual Vector<float> position() const
    {
        return m_position;
    }

    virtual void setDirection(Direction direction)
    {
        m_direction = direction;
    }

    virtual void setPosition(Vector<float> position) = 0;

    virtual void useWeapon() = 0;

    virtual BoundingBox boundingBox() const
    {
        return m_boundingBox;
    }

protected:
    Vector<float> m_position;
    Direction m_direction;
    UpdateTimer m_weaponTimer;
    BoundingBox m_boundingBox;

    // Weapon sprite sources
    SDL_Rect m_weaponSpritesSrc[WPN_SPRITE_COUNT] =
    {
        {0,0,8,16},     // WPN_SPRITE_BOW
        {10,0,8,16},    // WPN_SPRITE_BOOMERANG
        {40,0,16,16},   // WPN_SPRITE_BOMB
        {72,16,16,16},  // WPN_SPRITE_FLAMEROD_FLAME
        {30,0, 8, 16},  // WPN_SPRITE_FLAMEROD
        {0,16, 16, 16}  // WPN_SPRITE_SWORD
    };

};