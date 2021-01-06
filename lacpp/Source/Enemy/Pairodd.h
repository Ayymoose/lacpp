#pragma once

#include "Enemy.h"
#include "Renderable.h"

class Pairodd : public Renderable, public Enemy
{
public:
    Pairodd(float x, float y);

    // Renderable overrides
    void render(SDL_Renderer* renderer) noexcept override;

    // BasicCharacter overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;

    // Enemy overrides
    void attack() noexcept override;
    void die() noexcept override;

private:
    bool m_idle;
    SDL_RendererFlip m_flip;
    bool m_disappear;
    bool m_appear;
};