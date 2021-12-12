#pragma once

#include "Weapon.h"
#include <iostream>
#include "Updateable.h"

namespace Zelda
{

class Sword : public Weapon, public Updateable
{
public:
    Sword();
    void render() noexcept override;
    void update() noexcept override;
    void setPosition(Vector<float> position) override;

private:

};

}