#ifndef PLAYER_H
#define PLAYER_H

#include "Renderable.h"
#include "Controllable.h"
#include "Vec2.h"
#include "Character.h"

#include "UpdateTimer.h"

enum PlayerState
{
    LINK_WALK_LEFT = 0,
    LINK_WALK_RIGHT,
    LINK_WALK_DOWN,
    LINK_WALK_UP,

   /* LINK_PUSH_LEFT,
    LINK_PUSH_RIGHT,
    LINK_PUSH_DOWN,
    LINK_PUSH_UP,

    LINK_BLOCK_LEFT,
    LINK_BLOCK_DOWN_SMALL_SHIELD,
    LINK_BLOCK_UP,
    LINK_BLOCK_RIGHT,

    LINK_BLOCK_DOWN_BIG_SHIELD,

    LINK_WALK_DOWN_BIG_SHIELD,
    LINK_WALK_RIGHT_BIG_SHIELD,
    LINK_WALK_LEFT_BIG_SHIELD,

    LINK_WALK_LEFT_SMALL_SHIELD,
    LINK_WALK_RIGHT_SMALL_SHIELD,
    LINK_WALK_UP_SMALL_SHIELD,
    LINK_WALK_DOWN_SMALL_SHIELD,

    LINK_DIG_DOWN,
    LINK_DIG_UP,
    LINK_DIG_LEFT,
    LINK_DIG_RIGHT,

    LINK_HOLD_LEFT,
    LINK_HOLD_RIGHT,
    LINK_HOLD_UP,
    LINK_HOLD_DOWN,

    LINK_PULL_LEFT,
    LINK_PULL_RIGHT,
    LINK_PULL_UP,
    LINK_PULL_DOWN,

    LINK_SWIM_LEFT,
    LINK_SWIM_RIGHT,
    LINK_SWIM_UP,
    LINK_SWIM_DOWN,

    LINK_HOOK_LEFT,
    LINK_HOOK_RIGHT,
    LINK_HOOK_UP,
    LINK_HOOK_DOWN,

    LINK_JUMP_LEFT,
    LINK_JUMP_RIGHT,
    LINK_JUMP_UP,
    LINK_JUMP_DOWN,

    LINK_DEAD,
    LINK_SLEEP,
    LINK_PRIZE,

    LINK_FALL,
    LINK_PLAY_INSTRUMENT,

    LINK_SWORD_LEFT,
    LINK_SWORD_RIGHT,
    LINK_SWORD_UP,
    LINK_SWORD_DOWN,*/

    // Add here
    LINK_ANIMATIONS
};

class Player : public Controllable, public Renderable, public Character
{
public:
    Player();
    ~Player();
    void render(SDL_Renderer* pRenderer) override;
    void control();

    void attack();
    void die();

    void resetAnimation();

    Vec2 position() const
    {
        return m_position;
    }

    void addPosition(int x, int y)
    {
        m_position.x += x;
        m_position.y += y;
    }


private:
    Vec2 m_jumpVector;
    int m_speed;

    UpdateTimer m_movementTimer;

    bool m_dirLockRight;
    bool m_dirLockUp;
    bool m_dirLockDown;
    bool m_dirLockLeft;

    // Player animation state
    PlayerState m_state;

    const Animation m_animations[LINK_ANIMATIONS] =
    {
        {0,0,0,1,PLAYER_ANIMATION_FPS,0},    // LINK_WALK_LEFT 
        {103,0,0,1,PLAYER_ANIMATION_FPS,0},  // LINK_WALK_RIGHT
        {35,0,0,1,PLAYER_ANIMATION_FPS,0},   // LINK_WALK_DOWN
        {69,0,0,1,PLAYER_ANIMATION_FPS,0}    // LINK_WALK_UP
       /* {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},
        {0,0,0,1,12},*/
    };

};


#endif // !PLAYER_H
