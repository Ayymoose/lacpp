#pragma once

#include "Weapon.h"
#include <iostream>


namespace Zelda
{

constexpr float BOOMERANG_ROTATION_FPS = (1.0f / 12.0f);

class Boomerang : public Weapon
{
public:
    Boomerang();
    void render(SDL_Renderer* renderer) noexcept override;
    void returnToPlayer();
    void setPosition(Vector<float> position) override;

private:
    Vector<float> m_dirVec;
    bool m_return;
    int m_speed;

};

}