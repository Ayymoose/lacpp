#pragma once

#include "Weapon.h"
#include <iostream>

namespace Zelda
{

class Arrow : public Weapon
{
public:
    Arrow();
    void render() noexcept override;
    void update() noexcept override;
    void setPosition(Vector<float> position) override;

private:
    Vector<float> m_dirVec;
    int m_speed;

};

}