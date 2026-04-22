#pragma once

#include "IRenderable.h"
#include "Controllable.h"
#include "Character.h"
#include "IUpdateable.h"
#include "zelda_gui/Inventory.h"
#include "zelda_gui/Worldmap.h"
#include "core/Vector.h"

namespace zelda::core
{

enum PlayerState
{
    WALK_NONE = -1,
    WALK_LEFT = 0,
    WALK_RIGHT,
    WALK_UP,
    WALK_DOWN,

    WALK_LEFT_SMALL_SHIELD,
    WALK_RIGHT_SMALL_SHIELD,
    WALK_UP_SMALL_SHIELD,
    WALK_DOWN_SMALL_SHIELD,

    WALK_LEFT_BIG_SHIELD,
    WALK_RIGHT_BIG_SHIELD,
    WALK_UP_BIG_SHIELD,
    WALK_DOWN_BIG_SHIELD,

    HOLD_LEFT,
    HOLD_RIGHT,
    HOLD_UP,
    HOLD_DOWN,

    BLOCK_LEFT_SMALL_SHIELD,
    BLOCK_RIGHT_SMALL_SHIELD,
    BLOCK_UP_SMALL_SHIELD,
    BLOCK_DOWN_SMALL_SHIELD,

    BLOCK_LEFT_BIG_SHIELD,
    BLOCK_RIGHT_BIG_SHIELD,
    BLOCK_UP_BIG_SHIELD,
    BLOCK_DOWN_BIG_SHIELD,

    PUSH_LEFT,
    PUSH_RIGHT,
    PUSH_UP,
    PUSH_DOWN,

    SWIM_LEFT,
    SWIM_RIGHT,
    SWIM_UP,
    SWIM_DOWN,

    PULL_LEFT,
    PULL_RIGHT,
    PULL_UP,
    PULL_DOWN,

    FALL,
    PRIZE_ONE_HAND,
    PRIZE_TWO_HAND,

    SLEEPING,
    AWAKE,

    DIG_LEFT,
    DIG_RIGHT,
    DIG_UP,
    DIG_DOWN,

    HOOK_LEFT,
    HOOK_RIGHT,
    HOOK_UP,
    HOOK_DOWN,

    SWORD_LEFT,
    SWORD_RIGHT,
    SWORD_UP,
    SWORD_DOWN,

    JUMP_LEFT,
    JUMP_RIGHT,
    JUMP_UP,
    JUMP_DOWN,

    DIE,
    DROWN,
    PLAY_INSTRUMENT,

    DIVE_LEFT_OR_UP,
    DIVE_RIGHT_OR_DOWN,

    COUNT
};

#define PLAYER_BOUNDING_BOX_WIDTH_OFFSET 3
#define PLAYER_BOUNDING_BOX_WIDTH        10
#define PLAYER_BOUNDING_BOX_HEIGHT       8
#define PLAYER_CORNER_CUTTING_BOUNDARY   5

constexpr float PLAYER_ANIMATION_FPS = 1.0f / 10.0f;
constexpr float LINK_FALL_FPS = 1.0f / 3.0f;
constexpr float LINK_FLAME_ROD_ANIMATION_FPS = 1.0f / 4.0f;
constexpr float SWORD_ATTACK_FPS = 1.0f / 30.0f;
constexpr float LINK_DROWN_FPS = 1.0f / 3.0f;


constexpr float LINK_MAX_HEARTS = 16.0;
constexpr float LINK_MIN_HEARTS = 3.0;

class Link :
    public IRenderable,
    public Controllable,
    public Character,
    public engine::Singleton<Link>,
    public IUpdateable
{
public:
    Link();

    // Renderable overrides
    void render() override;

    // Updateable
    void update() override;

    // Character overrides
    float health() const override;

    engine::Vector<float> position() const override;

protected:
    void attack() override;
    void die() override;
    void move() override;

public:
    // Controllable overrides
    void control() override;

    void resetAnimation();
    void replenish(float hearts);

    void addPosition(float x, float y);
    void setPosition(float x, float y);


    void setCurrentHealth(float health)
    {
        assert(health >= 0.0 && health <= LINK_MAX_HEARTS);
        m_health = health;
    }
    void setMaxHealth(float maxHealth)
    {
        assert(maxHealth >= LINK_MIN_HEARTS && maxHealth <= LINK_MAX_HEARTS);
        m_healthMax = maxHealth;
    }

    float maxHeartPieces() const;
    void updateState();

    bool moving() const;
    Direction direction() const;

private:
    float m_healthMax;
    gui::Inventory m_inventory;
    float m_speedX;
    float m_speedY;

    // void useWeapon(WeaponItem weapon);

    bool m_dirLockRight = false;
    bool m_dirLockUp    = false;
    bool m_dirLockDown  = false;
    bool m_dirLockLeft  = false;

    bool m_moving = false;

    // Link animation state
    PlayerState m_state;

    void animate();

    const Animation m_animations[COUNT] = {
        // TODO: Add x and y offset to this
        // x   y startFrame endFrame,    animationFPS,     orientation,  flip
        {0, 0, 0, 1, PLAYER_ANIMATION_FPS},            // LINK_WALK_LEFT
        {96, 0, 0, 1, PLAYER_ANIMATION_FPS},           // LINK_WALK_RIGHT
        {64, 0, 0, 1, PLAYER_ANIMATION_FPS},           // LINK_WALK_UP
        {32, 0, 0, 1, PLAYER_ANIMATION_FPS},           // LINK_WALK_DOWN
        {0, 16, 0, 1, PLAYER_ANIMATION_FPS},           // LINK_WALK_LEFT_SMALL_SHIELD
        {96, 16, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_WALK_RIGHT_SMALL_SHIELD
        {64, 16, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_WALK_UP_SMALL_SHIELD
        {32, 16, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_WALK_DOWN_SMALL_SHIELD
        {0, 32, 0, 1, PLAYER_ANIMATION_FPS},           // LINK_WALK_LEFT_BIG_SHIELD
        {96, 32, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_WALK_RIGHT_BIG_SHIELD
        {64, 32, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_WALK_UP_BIG_SHIELD
        {32, 32, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_WALK_DOWN_BIG_SHIELD
        {0, 48, 0, 1, PLAYER_ANIMATION_FPS},           // LINK_HOLD_LEFT
        {96, 48, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_HOLD_RIGHT
        {64, 48, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_HOLD_UP
        {32, 48, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_HOLD_DOWN
        {0, 64, 0, 1, PLAYER_ANIMATION_FPS},           // LINK_BLOCK_LEFT_SMALL_SHIELD
        {96, 64, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_BLOCK_RIGHT_SMALL_SHIELD
        {64, 64, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_BLOCK_UP_SMALL_SHIELD
        {32, 64, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_BLOCK_DOWN_SMALL_SHIELD
        {0, 80, 0, 1, PLAYER_ANIMATION_FPS},           // LINK_BLOCK_LEFT_BIG_SHIELD
        {96, 80, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_BLOCK_RIGHT_BIG_SHIELD
        {64, 80, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_BLOCK_UP_BIG_SHIELD
        {32, 80, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_BLOCK_DOWN_BIG_SHIELD
        {0, 96, 0, 1, PLAYER_ANIMATION_FPS},           // LINK_PUSH_LEFT
        {96, 96, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_PUSH_RIGHT
        {64, 96, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_PUSH_UP
        {32, 96, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_PUSH_DOWN
        {0, 112, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_SWIM_LEFT
        {96, 112, 0, 1, PLAYER_ANIMATION_FPS},         // LINK_SWIM_RIGHT
        {64, 112, 0, 1, PLAYER_ANIMATION_FPS},         // LINK_SWIM_UP
        {32, 112, 0, 1, PLAYER_ANIMATION_FPS},         // LINK_SWIM_DOWN
        {0, 128, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_PULL_LEFT
        {96, 128, 0, 1, PLAYER_ANIMATION_FPS},         // LINK_PULL_RIGHT
        {64, 128, 0, 1, PLAYER_ANIMATION_FPS},         // LINK_PULL_UP
        {32, 128, 0, 1, PLAYER_ANIMATION_FPS},         // LINK_PULL_DOWN
        {0, 144, 0, 2, LINK_FALL_FPS},                 // LINK_FALL
        {64, 144, 0, 0, PLAYER_ANIMATION_FPS},         // LINK_PRIZE_ONE_HAND
        {80, 144, 0, 0, PLAYER_ANIMATION_FPS},         // LINK_PRIZE_TWO_HAND
        {96, 144, 0, 0, PLAYER_ANIMATION_FPS},         // LINK_SLEEPING
        {112, 144, 0, 0, PLAYER_ANIMATION_FPS},        // LINK_AWAKE
        {0, 160, 0, 1, PLAYER_ANIMATION_FPS},          // LINK_DIG_LEFT
        {96, 160, 0, 1, PLAYER_ANIMATION_FPS},         // LINK_DIG_RIGHT
        {64, 160, 0, 1, PLAYER_ANIMATION_FPS},         // LINK_DIG_UP
        {32, 160, 0, 1, PLAYER_ANIMATION_FPS},         // LINK_DIG_DOWN
        {0, 176, 0, 0, LINK_FLAME_ROD_ANIMATION_FPS},  // LINK_HOOK_LEFT
        {96, 176, 0, 0, LINK_FLAME_ROD_ANIMATION_FPS}, // LINK_HOOK_RIGHT
        {64, 176, 0, 0, LINK_FLAME_ROD_ANIMATION_FPS}, // LINK_HOOK_UP
        {32, 176, 0, 0, LINK_FLAME_ROD_ANIMATION_FPS}, // LINK_HOOK_DOWN
        {0, 192, 0, 2, SWORD_ATTACK_FPS},              // LINK_SWORD_LEFT
        {48, 192, 0, 2, SWORD_ATTACK_FPS},             // LINK_SWORD_RIGHT
        {0, 208, 0, 2, SWORD_ATTACK_FPS},              // LINK_SWORD_UP
        {48, 208, 0, 2, SWORD_ATTACK_FPS},             // LINK_SWORD_DOWN
        {0, 224, 0, 3, PLAYER_ANIMATION_FPS},          // LINK_JUMP_LEFT
        {0, 240, 0, 3, PLAYER_ANIMATION_FPS},          // LINK_JUMP_RIGHT
        {64, 224, 0, 3, PLAYER_ANIMATION_FPS},         // LINK_JUMP_UP
        {64, 240, 0, 3, PLAYER_ANIMATION_FPS},         // LINK_JUMP_DOWN
        {0, 256, 0, 4, PLAYER_ANIMATION_FPS},          // LINK_DIE
        {80, 256, 0, 1, LINK_DROWN_FPS},               // LINK_DROWN
        {96, 192, 0, 1, LINK_DROWN_FPS},               // LINK_PLAY_INSTRUMENT
        {96, 208, 0, 1, LINK_DROWN_FPS},               // LINK_DIVE_LEFT_OR_UP
        {96, 208, 0, 1, LINK_DROWN_FPS},               // LINK_DIVE_RIGHT_OR_DOWN
    };
};

} // namespace zelda::core