#pragma once

#include "Enemy.h"
#include "Renderable.h"

class ThreeOfAKind : public Enemy, public Renderable
{
public:
    ThreeOfAKind() : m_steps(0)
    {
    }
    ThreeOfAKind(float x, float y);

    // Renderable overrides
    void render(SDL_Renderer* renderer) noexcept override;

    // BasicCharacter overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;

    // Enemy overrides
    void attack() noexcept override;
    void die() noexcept override;
private:
    int m_steps;
};
