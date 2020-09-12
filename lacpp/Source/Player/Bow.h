#pragma once

#include "Weapon.h"
#include <iostream>

class Bow : public Weapon
{
public:
    Bow();
    void render(SDL_Renderer* pRenderer) noexcept override;
    void useWeapon() override;
    void setPosition(Vector<float> position) override;

private:
    Vector<float> m_dirVec;
    int m_speed;

};