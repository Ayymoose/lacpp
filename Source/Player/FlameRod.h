#pragma once

#include "Weapon.h"
#include <iostream>

namespace Zelda
{

class FlameRod : public Weapon
{
public:
    FlameRod();
    void render(SDL_Renderer* renderer) noexcept override;
    void setPosition(Vector<float> position) override;
private:
    Vector<float> m_dirVec;
    int m_speed;

    int m_flameRodWidth;
    int m_flameRodHeight;
    Vector<float> m_flameRodPosition;
    int m_flameRodOrientation;
    bool m_display;
};

}