#ifndef PLAYER_H
#define PLAYER_H

#include "Renderable.h"
#include "Controllable.h"
#include "Vec2.h"
#include "Character.h"
#include "UpdateTimer.h"
#include "Inventory.h"
#include "Singleton.h"
#include "BoundingBox.h"
#include "CollisionMap.h"

enum PlayerState
{
    LINK_WALK_NONE = -1,
    LINK_WALK_LEFT = 0,
    LINK_WALK_RIGHT,
    LINK_WALK_UP,
    LINK_WALK_DOWN,

    LINK_WALK_LEFT_SMALL_SHIELD,
    LINK_WALK_RIGHT_SMALL_SHIELD,
    LINK_WALK_UP_SMALL_SHIELD,
    LINK_WALK_DOWN_SMALL_SHIELD,

    LINK_WALK_LEFT_BIG_SHIELD,
    LINK_WALK_RIGHT_BIG_SHIELD,
    LINK_WALK_UP_BIG_SHIELD,
    LINK_WALK_DOWN_BIG_SHIELD,

    LINK_HOLD_LEFT,
    LINK_HOLD_RIGHT,
    LINK_HOLD_UP,
    LINK_HOLD_DOWN,

    LINK_BLOCK_LEFT_SMALL_SHIELD,
    LINK_BLOCK_RIGHT_SMALL_SHIELD,
    LINK_BLOCK_UP_SMALL_SHIELD,
    LINK_BLOCK_DOWN_SMALL_SHIELD,

    LINK_BLOCK_LEFT_BIG_SHIELD,
    LINK_BLOCK_RIGHT_BIG_SHIELD,
    LINK_BLOCK_UP_BIG_SHIELD,
    LINK_BLOCK_DOWN_BIG_SHIELD,

    LINK_PUSH_LEFT,
    LINK_PUSH_RIGHT,
    LINK_PUSH_UP,
    LINK_PUSH_DOWN,

    LINK_SWIM_LEFT,
    LINK_SWIM_RIGHT,
    LINK_SWIM_UP,
    LINK_SWIM_DOWN,

    LINK_PULL_LEFT,
    LINK_PULL_RIGHT,
    LINK_PULL_UP,
    LINK_PULL_DOWN,

    LINK_FALL,
    LINK_PRIZE_ONE_HAND,
    LINK_PRIZE_TWO_HAND,

    LINK_SLEEPING,
    LINK_AWAKE,

    LINK_DIG_LEFT,
    LINK_DIG_RIGHT,
    LINK_DIG_UP,
    LINK_DIG_DOWN,

    LINK_HOOK_LEFT,
    LINK_HOOK_RIGHT,
    LINK_HOOK_UP,
    LINK_HOOK_DOWN,

    LINK_SWORD_LEFT,
    LINK_SWORD_RIGHT,
    LINK_SWORD_UP,
    LINK_SWORD_DOWN,

    LINK_JUMP_LEFT,
    LINK_JUMP_RIGHT,
    LINK_JUMP_UP,
    LINK_JUMP_DOWN,
    
    LINK_DIE,
    LINK_DROWN,
    LINK_PLAY_INSTRUMENT,

    LINK_DIVE_LEFT_OR_UP,
    LINK_DIVE_RIGHT_OR_DOWN,

    /*
    TODO: To add these 32x16 sprites
    LINK_FISH_RIGHT,
    LINK_FISH_LEFT,

    */
    LINK_COUNT
};

#define PLAYER_MAX_HEALTH 14.0
#define PLAYER_BOUNDING_BOX_WIDTH_OFFSET 3
#define PLAYER_BOUNDING_BOX_WIDTH 10
#define PLAYER_BOUNDING_BOX_HEIGHT 8
#define PLAYER_CORNER_CUTTING_BOUNDARY 5
class Player : public Controllable, public Renderable, public Character, public Singleton<Player>
{
public:
    Player();
    ~Player();
    void render(SDL_Renderer* pRenderer) override;
    void control() override;

    void attack() override;
    void die()  override;

    void resetAnimation();

    Vec2<float> position() const override;

    void damage(float damage) override;
    void replenish(float hearts);
    void addPosition(int x, int y);
    float health() const override;
    float maxHealth() const;

    void updateState();

    int m_currentCollisionMapX;
    int m_currentCollisionMapY;
    COLLISION_AREA m_collisionArea;

private:
    int m_speed;
    float m_healthMax;
    Inventory m_inventory;
    int m_speed_x;
    int m_speed_y;
    BoundingBox m_boundingBox;
    CollisionMap m_collisionMap;
    bool handleStaticCollisions(int horizontalSpeed, int verticalSpeed);
    UpdateTimer m_movementTimer;

    bool m_useShield;
    bool m_shootArrow;

    void useWeapon(WEAPON weapon);

    bool m_dirLockRight;
    bool m_dirLockUp;
    bool m_dirLockDown;
    bool m_dirLockLeft;

    // Player animation state
    PlayerState m_state;

    const Animation m_animations[LINK_COUNT] =
    {

       // x   y currentFrame maxFrame,    animationFPS,     orientation,  flip
        {0   ,0,    0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_WALK_LEFT 
        {96  ,0 ,   0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_WALK_RIGHT
        {64  ,0 ,   0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_WALK_UP
        {32  ,0 ,   0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_WALK_DOWN
        {0   ,16 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_WALK_LEFT_SMALL_SHIELD
        {96  ,16 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_WALK_RIGHT_SMALL_SHIELD
        {64  ,16 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_WALK_UP_SMALL_SHIELD
        {32  ,16 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_WALK_DOWN_SMALL_SHIELD
        {0   ,32 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_WALK_LEFT_BIG_SHIELD
        {96  ,32 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_WALK_RIGHT_BIG_SHIELD
        {64  ,32 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_WALK_UP_BIG_SHIELD
        {32  ,32 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_WALK_DOWN_BIG_SHIELD
        {0   ,48 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_HOLD_LEFT
        {96  ,48 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_HOLD_RIGHT
        {64  ,48 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_HOLD_UP
        {32  ,48 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_HOLD_DOWN
        {0   ,64 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_BLOCK_LEFT_SMALL_SHIELD
        {96  ,64 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_BLOCK_RIGHT_SMALL_SHIELD
        {64  ,64 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_BLOCK_UP_SMALL_SHIELD
        {32  ,64 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_BLOCK_DOWN_SMALL_SHIELD
        {0   ,80 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_BLOCK_LEFT_BIG_SHIELD
        {96  ,80 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_BLOCK_RIGHT_BIG_SHIELD
        {64  ,80 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_BLOCK_UP_BIG_SHIELD
        {32  ,80 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_BLOCK_DOWN_BIG_SHIELD
        {0   ,96 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_PUSH_LEFT
        {96  ,96 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_PUSH_RIGHT
        {64  ,96 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_PUSH_UP
        {32  ,96 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // LINK_PUSH_DOWN
        {0   ,112 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_SWIM_LEFT
        {96  ,112 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_SWIM_RIGHT
        {64  ,112 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_SWIM_UP
        {32  ,112 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_SWIM_DOWN
        {0   ,128 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_PULL_LEFT
        {96  ,128 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_PULL_RIGHT
        {64  ,128 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_PULL_UP
        {32  ,128 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_PULL_DOWN
        {0   ,144 ,  0,          2,     LINK_FALL_FPS,           0,         SDL_FLIP_NONE},   // LINK_FALL
        {64  ,144 ,  0,          0,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_PRIZE_ONE_HAND
        {80  ,144 ,  0,          0,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_PRIZE_TWO_HAND
        {96  ,144 ,  0,          0,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_SLEEPING
        {112 ,144 ,  0,          0,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_AWAKE
        {0   ,160 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_DIG_LEFT
        {96  ,160 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_DIG_RIGHT
        {64  ,160 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_DIG_UP
        {32  ,160 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_DIG_DOWN
        {0   ,176 ,  0,          0,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_HOOK_LEFT
        {96  ,176 ,  0,          0,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_HOOK_RIGHT
        {64  ,176 ,  0,          0,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_HOOK_UP
        {32  ,176 ,  0,          0,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_HOOK_DOWN
        {0   ,192 ,  0,          2,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_SWORD_LEFT
        {48  ,192 ,  0,          2,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_SWORD_RIGHT
        {0   ,208 ,  0,          2,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_SWORD_UP
        {48  ,208 ,  0,          2,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_SWORD_DOWN
        {0   ,224 ,  0,          3,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_JUMP_LEFT
        {0   ,240 ,  0,          3,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_JUMP_RIGHT
        {64  ,224 ,  0,          3,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_JUMP_UP
        {64  ,240 ,  0,          3,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_JUMP_DOWN
        {0   ,256 ,  0,          4,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},   // LINK_DIE
        {80  ,256 ,  0,          1,     LINK_DROWN_FPS,          0,         SDL_FLIP_NONE},   // LINK_DROWN
        {96  ,192 ,  0,          1,     LINK_DROWN_FPS,          0,         SDL_FLIP_NONE},   // LINK_PLAY_INSTRUMENT
        {96  ,208 ,  0,          1,     LINK_DROWN_FPS,          0,         SDL_FLIP_HORIZONTAL},   // LINK_DIVE_LEFT_OR_UP
        {96  ,208 ,  0,          1,     LINK_DROWN_FPS,          0,         SDL_FLIP_NONE},   // LINK_DIVE_RIGHT_OR_DOWN
    };

};


#endif // !PLAYER_H
