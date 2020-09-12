#pragma once

#include <cstdint>

// The game is locked to 60 fps because of VSync
// So everything runs at 60 fps
// It seems like using timers for scrolling to lock it 60fps was messing with that
// It's not choppy anymore

// #define FPS_60 (1.0 / 60.0) 
#define FPS_66 (1.0f / 60.0f)   
#define FPS_33 (1.0 / 33.0)    // To be adjusted!
#define PLAYER_ANIMATION_FPS (1.0 / 10.0)
#define BACKGROUND_OBJECT_FPS (1.0 / 6.0)
#define INSTRUMENT_FPS (1.0 / 6.0)

#define LINK_FALL_FPS (1.0 / 3.0)
#define LINK_DROWN_FPS (1.0 / 3.0)
#define LINK_FLAME_ROD_ANIMATION_FPS (1.0 / 4.0)

#define INVENTORY_SELECTOR_FPS (1.0 / 4.0)
#define PUSH_SELECTOR_FPS (1.0 / 2.0)


// Weapon related timers
#define ARROW_SPEED_FPS (1.0 / 69.0)
#define BOOMERANG_SPEED_FPS (1.0 / 69.0)
#define BOOMERANG_ROTATION_FPS (1.0 / 12.0)
#define BOMB_START_TIME (1.5)
#define BOMB_EXPLODE_TIME (0.1)
#define BOMB_ANIMATION_TIME (1.0 / 12.0)
#define FLAME_ROD_SPEED (1.0 / 69.0)

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