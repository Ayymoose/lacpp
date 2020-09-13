#pragma once

#include "Weapon.h"
#include <iostream>

class Sword : public Weapon
{
public:
    Sword();
    virtual ~Sword();
    void render(SDL_Renderer* pRenderer) noexcept override;
    void useWeapon() override;
    void setPosition(Vector<float> position) override;

private:

};