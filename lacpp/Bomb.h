#pragma once

#include "Weapon.h"
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

class Bomb : public Weapon
{
public:
    Bomb();
    ~Bomb() = default;

    void render(SDL_Renderer* pRenderer) override;
    void useWeapon() override;
    void setPosition(Vec2<float> position) override;
    bool exploded() const;
private:
    bool m_exploded;
    bool m_startBomb;
    bool m_flashBomb;
    int m_flashCount;
};
