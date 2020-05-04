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

    int m_flameRodWidth;
    int m_flameRodHeight;
    Vec2<float> m_flameRodPosition;
    int m_flameRodOrientation;
    bool m_display;
};