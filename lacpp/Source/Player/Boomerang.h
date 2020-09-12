#pragma once

#include "UpdateTimer.h"
#include "Weapon.h"
#include <iostream>

class Boomerang : public Weapon
{
public:
    Boomerang();
    void render(SDL_Renderer* pRenderer) noexcept override;
    void useWeapon() override;
    void returnToPlayer();
    void setPosition(Vector<float> position) override;

private:
    Vector<float> m_dirVec;
    bool m_return;
    int m_speed;

};