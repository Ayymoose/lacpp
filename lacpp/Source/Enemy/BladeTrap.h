#pragma once

#include "Enemy.h"
#include "Renderable.h"

class BladeTrap : public Enemy, public Renderable
{
public:
    BladeTrap() : m_range(0), m_attack(false), m_moved(false), m_retreat(false), m_retreatSpeed(0)
    {

    };
    BladeTrap(int x, int y);

    // Renderable overrides
    void render(SDL_Renderer* renderer) noexcept override;

    // BasicCharacter overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;

    // Enemy overrides
    void attack() noexcept override;
    void die() noexcept override;
    void move() noexcept override;

private:

    // How far the trap can detect Link
    int m_range;
    bool m_attack;
    bool m_retreat;
    float m_moved;
    float m_retreatSpeed;

    /*

        Blade Trap uses pair-point detection method 
        to determine which side the player is on

        P0 is the position vector

        P0----------P1
        |           |
        |           |
        |           |
        |           |
        P3----------P2

    */
};
