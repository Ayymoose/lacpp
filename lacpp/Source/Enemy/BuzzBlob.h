#pragma once

#include "Enemy.h"
#include "Renderable.h"

class BuzzBlob : public Renderable, public Enemy
{
public:
    BuzzBlob() : m_bigEyes(false)
    {
    };
    BuzzBlob(float x, float y);

    // Renderable overrides
    void render(SDL_Renderer* renderer) noexcept override;

    // BasicCharacter overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;

    // Enemy overrides
    void attack() noexcept override;
    void die() noexcept override;
private:
    bool m_bigEyes;
};
