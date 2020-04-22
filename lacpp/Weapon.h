#ifndef WEAPON_H
#define WEAPON_H

#include "Renderable.h"
#include "Inventory.h"
#include "Vec2.h"

class Weapon : public Renderable
{
public:
    Weapon(WEAPON weapon);
    void render(SDL_Renderer* pRenderer) override;
private:
    WEAPON m_weapon;

};

#endif