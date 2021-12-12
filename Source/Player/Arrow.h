#pragma once

#include "Weapon.h"
#include <iostream>
#include "Updateable.h"

namespace Zelda
{

class Arrow : public Weapon, public Updateable
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