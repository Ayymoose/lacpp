#pragma once

#include "Weapon.h"
#include "Cullable.h"
#include <iostream>

// How many times the bomb "flashes"
#define BOMB_FLASH_MAX 6

// Number of frames in the bomb animation
#define BOMB_FRAMES 5
#define BOMB_SPRITE_INERT 0
#define BOMB_SPRITE_FLASHING 1
#define BOMB_SPRITE_INITIAL_CLOUD 2
#define BOMB_SPRITE_EXPLOSION 3
#define BOMB_SPRITE_AFTER_SMOKE 4

constexpr float BOMB_START_TIME = 1.5f;
constexpr float BOMB_EXPLODE_TIME = 0.1f;
constexpr float BOMB_ANIMATION_TIME = (1.0f / 12.0f);

class Bomb : public Weapon, public CullableChild
{
public:
    Bomb();
    void render(SDL_Renderer* renderer) noexcept override;
    void setPosition(Vector<float> position) override;
    bool exploded() const;

    virtual bool cull() noexcept override;
private:
    bool m_exploded;
    bool m_startBomb;
    bool m_flashBomb;
    int m_flashCount;
};
