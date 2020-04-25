#include <cstdint>

#ifndef UPDATE_TIMER_H
#define UPDATE_TIMER_H

// #define FPS_60 (1.0 / 60.0) // I notice that with 16.7ms, the movement is choppy
#define FPS_66 (1.0 / 66.0)    // We need some extra delay between frame rendering maybe
#define FPS_33 (1.0 / 31.0)    // To be adjusted!
#define PLAYER_ANIMATION_FPS (1.0 / 10.0)
#define BACKGROUND_OBJECT_FPS (1.0 / 6.0)
#define INSTRUMENT_FPS (1.0 / 6.0)

#define LINK_FALL_FPS (1.0 / 3.0)
#define LINK_DROWN_FPS (1.0 / 3.0)

#define INVENTORY_SELECTOR_FPS (1.0 / 4.0)
#define PUSH_SELECTOR_FPS (1.0 / 2.0)
#define ARROW_SPEED_FPS (1.0 / 66.0)

class UpdateTimer
{
public:
    UpdateTimer();
    ~UpdateTimer() = default;
    bool update(double dt);
    void reset();
    // m_counter is incremented everytime the timer is updated
    // It can be used as a kind of counter
    uint32_t m_counter;
private:
    uint32_t m_previousUpdateTime;
};



#endif // !UPDATE_TIMER_H
