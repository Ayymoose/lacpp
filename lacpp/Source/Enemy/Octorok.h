#pragma once

#include "Enemy.h"
#include "Renderable.h"

enum class OctorokType
{
    Basic,
    Winged
};

class Octorok : public Renderable, public Enemy
{
public:
    Octorok(OctorokType octorokType, float x, float y);

    // Renderable overrides
    void render(SDL_Renderer* renderer) noexcept override;

    // BasicCharacter overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;

    // Enemy overrides
    void attack() noexcept override;
    void die() noexcept override;
private:
    OctorokType m_type;
    int m_steps;
};
