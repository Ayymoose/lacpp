#pragma once

#include "Enemy.h"
#include "Renderable.h"

class Darknut : public Renderable, public Enemy
{
public:
    Darknut(EnemyType enemyType, float x, float y);

    // Renderable overrides
    void render(SDL_Renderer* renderer) noexcept override;

    // BasicCharacter overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;

    // Enemy overrides
    void attack() noexcept override;
    void die() noexcept override;
private:
    EnemyType m_type;
    int m_steps;
};
