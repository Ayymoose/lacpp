#if 0


#pragma once

#include "Enemy.h"
#include "Renderable.h"

namespace Zelda
{

class Zombie : public Renderable, public Enemy
{
public:
    Zombie() : m_emerging(false), m_burrowing(false)
    {
    }
    Zombie(float x, float y);

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
    bool m_emerging;
    bool m_burrowing;
    Timer m_emergeTimer;
};

}

#endif