#pragma once

#include "core/Renderable.h"
#include "core/Controllable.h"
#include "Character.h"
#include "core/Updateable.h"
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
    public engine::Renderable,
    public engine::Controllable,
    public Character,
    public engine::Singleton<Link>,
    public engine::Updateable
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
    engine::Direction direction() const;

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

};

} // namespace zelda::core