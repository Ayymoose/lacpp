#pragma once

#include "Renderable.h"
#include "Controllable.h"
#include "Vector.h"
#include "Character.h"
#include "Inventory.h"
#include "Singleton.h"
#include "BoundingBox.h"
#include "CollisionMap.h"
#include "Bomb.h"
#include "Arrow.h"
#include "FlameRod.h"
#include "Boomerang.h"
#include "Timer.h"
#include "Sword.h"
#include "Cullable.h"
#include "Worldmap.h"

#include <memory>

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

constexpr float PLAYER_ANIMATION_FPS = 1.0f / 10.0f;
constexpr float LINK_FALL_FPS = 1.0f / 3.0f;
constexpr float LINK_FLAME_ROD_ANIMATION_FPS = 1.0f / 4.0f;
constexpr float SWORD_ATTACK_FPS = 1.0f / 30.0f;
constexpr float LINK_DROWN_FPS = 1.0f / 3.0f;

class Link : public Renderable, public Controllable, public Character, public Singleton<Link>, public CullableParent
{
    friend class Singleton<Link>;
public:
    // Renderable overrides
    void render(SDL_Renderer* renderer) noexcept override;

    // Character overrides
    float health() const noexcept override;
    Vector<float> position() const noexcept override;
    void attack() noexcept override;
    void die() noexcept override;
    void move() noexcept override;

    // Controllable overrides
    void control() noexcept override;

    // CullableParent overrides
    void cull() noexcept override;
 
    void resetAnimation() noexcept;
    void replenish(float hearts) noexcept;
    void addPosition(int x, int y) noexcept;
    float maxHealth() const noexcept;
    void updateState() noexcept;

    bool moving() const noexcept;
    Direction direction() const noexcept;

    //int m_currentCollisionMapX;
    //int m_currentCollisionMapY;
    //CollisionArea m_collisionArea;

    void setDungeonMarkerLocation(int x, int y) noexcept;

private:
    Link();
    float m_healthMax;
    Inventory m_inventory;
    int m_speedX;
    int m_speedY;
    BoundingBox m_boundingBox;
    //CollisionMap m_collisionMap;

    Worldmap m_worldmap;

    bool handleStaticCollisions(int horizontalSpeed, int verticalSpeed) noexcept;
    void useWeapon(WEAPON weapon) noexcept;

    Timer m_movementTimer;
    bool m_useShield;

    bool m_dirLockRight;
    bool m_dirLockUp;
    bool m_dirLockDown;
    bool m_dirLockLeft;

    // Weapons
    Boomerang* m_boomerang;
    FlameRod* m_flameRod;
    std::unique_ptr<Sword> m_sword;
    std::vector<std::unique_ptr<Arrow>> m_quiver;
    std::unique_ptr<Bomb> m_bomb;

    bool m_canUseArrow;
    bool m_usingArrow;
    bool m_moveable;
    bool m_moving;
    bool m_usingSword;

    // Link animation state
    PlayerState m_state;

    // Temporary test
    bool m_useWeapon;
    bool m_usingWeapon;
    void animate();
    Timer m_clockAnimation;

    const Animation m_animations[LINK_COUNT] =
    {
        // TODO: Add x and y offset to this
       // x   y startFrame endFrame,    animationFPS,     orientation,  flip
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
        {0   ,176 ,  0,          0,     LINK_FLAME_ROD_ANIMATION_FPS,    0, SDL_FLIP_NONE},   // LINK_HOOK_LEFT
        {96  ,176 ,  0,          0,     LINK_FLAME_ROD_ANIMATION_FPS,    0, SDL_FLIP_NONE},   // LINK_HOOK_RIGHT
        {64  ,176 ,  0,          0,     LINK_FLAME_ROD_ANIMATION_FPS,    0, SDL_FLIP_NONE},   // LINK_HOOK_UP
        {32  ,176 ,  0,          0,     LINK_FLAME_ROD_ANIMATION_FPS,    0, SDL_FLIP_NONE},   // LINK_HOOK_DOWN
        {0   ,192 ,  0,          2,     SWORD_ATTACK_FPS,    0,         SDL_FLIP_NONE},   // LINK_SWORD_LEFT
        {48  ,192 ,  0,          2,     SWORD_ATTACK_FPS,    0,         SDL_FLIP_NONE},   // LINK_SWORD_RIGHT
        {0   ,208 ,  0,          2,     SWORD_ATTACK_FPS,    0,         SDL_FLIP_NONE},   // LINK_SWORD_UP
        {48  ,208 ,  0,          2,     SWORD_ATTACK_FPS,    0,         SDL_FLIP_NONE},   // LINK_SWORD_DOWN
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
