#pragma once

#include "Weapon.h"
#include <iostream>
#include "Updateable.h"

namespace Zelda
{

class FlameRod : public Weapon, public Updateable
{
public:
    FlameRod();
    void render() noexcept override;
    void update() noexcept override;
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