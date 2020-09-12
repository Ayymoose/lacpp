#pragma once

#include "Weapon.h"
#include <iostream>

class Sword : public Weapon
{
public:
    Sword();
    ~Sword() = default;

    void render(SDL_Renderer* pRenderer) override;
    void useWeapon() override;
    void setPosition(Vector<float> position) override;

private:

};