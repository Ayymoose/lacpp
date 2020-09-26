#pragma once

#include "Weapon.h"
#include <iostream>


class Arrow : public Weapon
{
public:
    Arrow();
    void render(SDL_Renderer* pRenderer) noexcept override;
    void setPosition(Vector<float> position) override;

private:
    Vector<float> m_dirVec;
    int m_speed;

};