#pragma once

#include "Enemy.h"
#include "Renderable.h"

class Gibdo : public Renderable, public Enemy
{
public:
    Gibdo() = default;
    Gibdo(float x, float y);

    // Renderable overrides
    void render(SDL_Renderer* renderer) noexcept override;

    // BasicCharacter overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;

    // Enemy overrides
    void attack() noexcept override;
    void die() noexcept override;
};
