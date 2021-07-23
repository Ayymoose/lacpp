#pragma once

#include "Enemy.h"
#include "Renderable.h"

namespace Zelda
{

class WaterTektite : public Renderable, public Enemy
{
public:
    WaterTektite() : m_strideLength(0), m_strided(0), m_stride(false)
    {

    }
    WaterTektite(float x, float y);

    // Renderable overrides
    void render(SDL_Renderer* renderer) noexcept override;

    // BasicCharacter overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;

    // Enemy overrides
    void attack() noexcept override;
    void die() noexcept override;
private:
    float m_strideLength;
    float m_strided;
    bool m_stride;
};

}