#pragma once

#include "Weapon.h"
#include <iostream>

namespace Zelda
{

class Sword : public Weapon
{
public:
    Sword();
    void render() noexcept override;
    void update() noexcept override;
    void setPosition(Vector<float> position) override;

private:

};

}