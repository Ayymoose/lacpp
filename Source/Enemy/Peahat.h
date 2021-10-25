#if 0


#pragma once

#include "Enemy.h"
#include "Renderable.h"

namespace Zelda
{

class Peahat : public Renderable, public Enemy
{
public:
    Peahat(float x, float y);

    // Renderable overrides
    void render() noexcept override;
    void update() noexcept override;

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

}

#endif