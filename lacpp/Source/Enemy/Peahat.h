#pragma once

#include "Enemy.h"
#include "Renderable.h"

class Peahat : public Renderable, public Enemy
{
public:
    Peahat() : m_startingUp(false), m_coolDown(false), m_risen(0)
    {
    }
    Peahat(float x, float y);

    // Renderable overrides
    void render(SDL_Renderer* renderer) noexcept override;

    // BasicCharacter overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;

    // Enemy overrides
    void attack() noexcept override;
    void die() noexcept override;
private:
    bool m_startingUp;
    bool m_coolDown;
    float m_risen;
    Timer m_cooldownTimer;
};
