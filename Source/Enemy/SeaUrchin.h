#pragma once

#include "Enemy.h"
#include "Renderable.h"

namespace Zelda
{

class SeaUrchin : public Renderable, public Enemy
{
public:
    SeaUrchin(float x, float y);

    // Renderable overrides
    void render() noexcept override;
    void update() noexcept override;

    // BasicCharacter overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;

    // Enemy overrides
    void attack() noexcept override;
    void die() noexcept override;
};

}