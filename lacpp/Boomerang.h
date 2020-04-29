#pragma once

#include "UpdateTimer.h"
#include "Weapon.h"
#include <iostream>

class Boomerang : public Weapon
{
public:
    Boomerang();
    ~Boomerang() = default;

    void render(SDL_Renderer* pRenderer) override;
    void useWeapon() override;
    void returnToPlayer();
    void setPosition(Vec2<float> position) override;

private:
    Vec2<float> m_dirVec;
    bool m_return;
    int m_speed;

};