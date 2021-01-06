#pragma once

#include "Enemy.h"
#include "Renderable.h"

class IronMask : public Renderable, public Enemy
{
public:
    IronMask() : m_exposed(false), m_steps(0)
    {
    }
    IronMask(float x, float y);

    // Renderable overrides
    void render(SDL_Renderer* renderer) noexcept override;

    // BasicCharacter overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;

    // Enemy overrides
    void attack() noexcept override;
    void die() noexcept override;
private:
    bool m_exposed;
    int m_steps;
};
