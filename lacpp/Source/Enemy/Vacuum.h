#pragma once

#include "Enemy.h"
#include "Renderable.h"

constexpr int MAX_VACUUMS = 8;

class Vacuum : public Renderable, public Enemy
{
public:
    Vacuum(float x, float y);

    // Renderable overrides
    void render(SDL_Renderer* renderer) noexcept override;

    // BasicCharacter overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;

    // Enemy overrides
    void attack() noexcept override;
    void die() noexcept override;
private:
    int m_vacuums;
};
