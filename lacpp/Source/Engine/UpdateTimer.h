#pragma once

#include <cstdint>

// The game is locked to 60 fps because of VSync
// So everything runs at 60 fps
// It seems like using timers for scrolling to lock it 60fps was messing with that
// It's not choppy anymore

// #define FPS_60 (1.0 / 60.0) 
#define FPS_66 (1.0f / 60.0f)   
#define FPS_33 (1.0 / 33.0f)    // To be adjusted!
#define PLAYER_ANIMATION_FPS (1.0 / 10.0f)
#define BACKGROUND_OBJECT_FPS (1.0 / 6.0f)
#define INSTRUMENT_FPS (1.0 / 6.0f)

#define LINK_FALL_FPS (1.0 / 3.0f)
#define LINK_DROWN_FPS (1.0 / 3.0f)
#define LINK_FLAME_ROD_ANIMATION_FPS (1.0 / 4.0f)

#define INVENTORY_SELECTOR_FPS (1.0 / 4.0f)
#define PUSH_SELECTOR_FPS (1.0 / 2.0f)


// Weapon related timers
#define ARROW_SPEED_FPS (1.0 / 69.0f)
#define BOOMERANG_SPEED_FPS (1.0 / 69.0f)
#define BOOMERANG_ROTATION_FPS (1.0 / 12.0f)
#define BOMB_START_TIME (1.5f)
#define BOMB_EXPLODE_TIME (0.1f)
#define BOMB_ANIMATION_TIME (1.0 / 12.0f)
#define FLAME_ROD_SPEED (1.0 / 69.0f)

#define SWORD_ATTACK_FPS (1.0 / 30.0f)

class UpdateTimer
{
public:
    UpdateTimer();
    bool update(float dt);
    void reset();
    // m_counter is incremented everytime the timer is updated
    // It can be used as a kind of counter
    uint32_t m_counter;
private:
    uint32_t m_previousUpdateTime;
    bool m_reset;
};