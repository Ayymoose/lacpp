#pragma once

#include "Weapon.h"
#include <iostream>

class FlameRod : public Weapon
{
public:
    FlameRod();
    ~FlameRod() = default;

    void render(SDL_Renderer* pRenderer) override;
    void useWeapon() override;
    void setPosition(Vec2<float> position) override;

private:
    Vec2<float> m_dirVec;
    int m_speed;

};