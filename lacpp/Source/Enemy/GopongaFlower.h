#pragma once

#include "Enemy.h"
#include "Renderable.h"

namespace Zelda
{

class GopongaFlower : public Renderable, public Enemy
{
public:
    GopongaFlower(float x, float y);

    // Renderable overrides
    void render(SDL_Renderer* renderer) noexcept override;

    // BasicCharacter overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;

    // Enemy overrides
    void attack() noexcept override;
    void die() noexcept override;
};

}