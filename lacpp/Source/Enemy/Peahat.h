#pragma once

#include "Enemy.h"
#include "Renderable.h"

class Peahat : public Enemy, public Renderable
{
public:
    Peahat() : m_startingUp(false), m_risen(0), m_coolDown(false)
    {
    }
    Peahat(int x, int y);

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
