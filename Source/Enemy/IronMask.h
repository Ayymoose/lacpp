#pragma once

#include "Enemy.h"
#include "Renderable.h"

namespace Zelda
{

class IronMask : public Renderable, public Enemy
{
public:
    IronMask(float x, float y);

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
    bool m_exposed;
    int m_steps;
};

}