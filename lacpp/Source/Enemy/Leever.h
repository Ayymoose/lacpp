#pragma once

#include "Enemy.h"
#include "Renderable.h"

class Leever : public Renderable, public Enemy
{
public:
    Leever() : m_emerging(false), m_burrowing(false)
    {
    }
    Leever(float x, float y);

    // Renderable overrides
    void render(SDL_Renderer* renderer) noexcept override;

    // BasicCharacter overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;

    // Enemy overrides
    void attack() noexcept override;
    void die() noexcept override;
private:
    bool m_emerging;
    bool m_burrowing;
    Timer m_emergeTimer;
};
