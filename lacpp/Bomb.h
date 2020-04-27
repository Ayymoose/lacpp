#pragma once

#include "Weapon.h"
#include <iostream>

class Bomb : public Weapon
{
public:
    Bomb();
    ~Bomb() = default;

    void render(SDL_Renderer* pRenderer) override;
    void useWeapon() override;
    void setPosition(Vec2<float> position) override;
    bool exploded() const;
private:
    bool m_exploded;
};
