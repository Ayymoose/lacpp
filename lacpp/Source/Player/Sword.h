#pragma once

#include "Weapon.h"
#include <iostream>

class Sword : public Weapon
{
public:
    Sword();
    void render(SDL_Renderer* pRenderer) noexcept override;
    void setPosition(Vector<float> position) override;

private:

};