#pragma once

#include "Enemy.h"
#include "Renderable.h"

class Gibdo : public Enemy, public Renderable
{
public:
    Gibdo() = default;
    Gibdo(int x, int y);

    // Renderable overrides
    void render(SDL_Renderer* renderer) noexcept override;

    // BasicCharacter overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;

    // Enemy overrides
    void attack() noexcept override;
    void die() noexcept override;
    void move() noexcept override;
};
