# pragma once

#include "Vector.h"
#include "BasicCharacter.h"
#include "Resource.h"
#include "Camera.h"
#include "SDL_Assert.h"
#include "Renderer.h"
#include "Timer.h"
#include "Engine.h"
#include "Link.h"

namespace Zelda
{

enum EnemySprite
{
    ENEMY_NONE = -1,
    ENEMY_ARMOS,                // NOT DONE
    ENEMY_BEETLE,               // NOT DONE
    ENEMY_WATER_TEKTITE,
    ENEMY_PIG_WARRIOR,
    ENEMY_BUZZ_BLOB,
    ENEMY_CROW,                 // NOT DONE
    ENEMY_DACTO,                // NOT DONE
    ENEMY_DARKNUT,
    ENEMY_GHINI,                // NOT DONE
    ENEMY_GIANT_GOPONGA_FLOWER, // NOT DONE
    ENEMY_GOPONGA_FLOWER,
    ENEMY_LIKE_LIKE,
    ENEMY_MAD_BOMBER,           // NOT DONE
    ENEMY_MINI_MOLDORM,         // NOT DONE
    ENEMY_MOBLIN,
    ENEMY_OCTOROK,
    ENEMY_LEEVER,
    ENEMY_PINCER,               // NOT DONE
    ENEMY_PIRANHA,              // NOT DONE
    ENEMY_POKEY,                // NOT DONE
    ENEMY_SEA_URCHIN,
    ENEMY_SHROUDED_STALFOS,
    ENEMY_SPINY_BEETLE,         // NOT DONE
    ENEMY_ZIRRO,                // NOT DONE
    ENEMY_ZOMBIE,
    ENEMY_ZORA,                 // NOT DONE
    ENEMY_BEAMOS,
    ENEMY_GIBDO,
    ENEMY_HARDHAT_BEETLE,
    ENEMY_BUBBLE,
    ENEMY_STAR,
    ENEMY_VACUUM,
    ENEMY_BLADETRAP,
    ENEMY_ARM_MIMIC,
    ENEMY_SHY_GUY,
    ENEMY_IRON_MASK,
    ENEMY_THREE_OF_A_KIND,
    ENEMY_SPARK,
    ENEMY_SAND_CRAB,
    ENEMY_PEAHAT,
    ENEMY_ROPE,                 // NOT DONE
    ENEMY_MONKEY,               // NOT DONE
    ENEMY_TEKTIKE,              // NOT DONE
    ENEMY_POLS_VOICE,           // NOT DONE
    ENEMY_BALL_AND_CHAIN,       // NOT DONE
    ENEMY_KIRBY,                // NOT DONE
    ENEMY_BOMBITE,              // NOT DONE
    ENEMY_KEESE,                // NOT DONE
    ENEMY_ZOL,                  // NOT DONE
    ENEMY_GEL,                  // NOT DONE
    ENEMY_WIZZROBE,             // NOT DONE
    ENEMY_MOUTH_VIRE,           // NOT DONE
    ENEMY_STALFOS,              // NOT DONE
    ENEMY_ORB_MONSTER,          // NOT DONE
    ENEMY_PAIRODD,
    ENEMY_GOOMBA,
    ENEMY_CAMO_GOBLIN,          // NOT DONE
    ENEMY_BONE_PUTTER,          // NOT DONE
    ENEMY_BATTLE_BAT,           // NOT DONE
    ENEMY_SPIKED_BEETLE,        // NOT DONE
    ENEMY_BOO_BUDDY,            // NOT DONE
    ENEMY_BLAZING_BAT,          // NOT DONE
    ENEMY_COUNT
};

// Applies to 
// TODO: Octorok
// Shrouded Stalfos
// Moblin
// Pig Warrior
// Darknut
enum class EnemyType
{
    Basic,
    Winged,
    Armed
};

// Enemy frames
constexpr float ENEMY_SEA_URCHIN_FPS(1.0f / 4.0f);
constexpr float ENEMY_BEAMOS_FPS(1.0f / 4.0f);
constexpr float ENEMY_GOPONGA_FLOWER_FPS(1.0f / 2.0f);
constexpr float ENEMY_GIBDO_FPS(1.0f / 3.0f);
constexpr float ENEMY_LIKE_LIKE_FPS(1.0f / 3.0f);
constexpr float ENEMY_HARDHAT_BEETLE_FPS(1.0f / 6.0f);
constexpr float ENEMY_BUBBLE_FPS(1.0f / 10.0f);
constexpr float ENEMY_STAR_FPS(1.0f / 4.0f);
constexpr float ENEMY_VACUUM_FPS(0.25f);
constexpr float ENEMY_SHY_GUY_FPS(0.25f);
constexpr float ENEMY_WATER_TEKTITE_FPS(1.0f / 4.0f);
constexpr float ENEMY_IRON_MASK_FPS(1.0f / 10.0f);
constexpr float ENEMY_THREE_OF_A_KIND_FPS(1.0f / 6.0f);
constexpr float ENEMY_SPARK_FPS(1.0f / 16.0f);
constexpr float ENEMY_LEEVER_FPS(1.0f / 8.0f);
constexpr float ENEMY_SAND_CRAB_FPS(1.0f / 8.0f);
constexpr float ENEMY_BUZZ_BLOB_FPS(1.0f / 6.0f);
constexpr float ENEMY_ZOMBIE_FPS(1.0f / 4.0f);
constexpr float ENEMY_PEAHAT_FPS(1.0f / 16.0f);
constexpr float ENEMY_PAIRODD_FPS(1.0f / 6.0f);
constexpr float ENEMY_GOOMBA_FPS(1.0f / 4.0f);
constexpr float ENEMY_OCTOROK_FPS(1.0f / 4.0f);
constexpr float ENEMY_PIG_WARRIOR_FPS(1.0f / 6.0f);
constexpr float ENEMY_MOBLIN_FPS(1.0f / 6.0f);
constexpr float ENEMY_DARKNUT_FPS(1.0f / 6.0f);
constexpr float ENEMY_SHROUDED_STALFOS_FPS(1.0f / 6.0f);

class Enemy : public BasicCharacter
{
public:
    virtual ~Enemy() = default;

    // Attack
    virtual void attack() noexcept = 0;

    // Die
    virtual void die() noexcept = 0;

protected:
    Enemy() : m_auxiliaryFrame(0), m_moving(false)
    {
    }
    Enemy(float x, float y) : m_auxiliaryFrame(0), m_moving(true)
    {
        m_position.x = x;
        m_position.y = y;
    }

    // Basic enemy animation 1,2,3 -> 1,2,3 -> 1,2,3 ...
    void basicEnemyAnimate() noexcept
    {
        // TODO: Fill out
    }

    // Moves in random directions continuously
   /* void basicEnemyMovement() noexcept
    {
        // Move's randomly in 4 directions only
        // Bouncing off objects
        // Any attempt to move out of the camera will flip it's direction
        // If pushed out the camera by Link, will reach the edge only

        // Basic AI movement
        // Every second, if we hit 1/4 then change direction to a new direction
        // The new direction must not be the same direction and can't be the opposite of the last direction

        // BUG: The enemy can still get stuck at the border between the camera edge it seems and "vibrate"
        static Timer moveTimer;
        if (moveTimer.elapsed(0.25f))
        {
            // Try to change direction
            auto chance = random(1, 3);
            if (chance == 2)
            {
                auto dir = random(0, 3);
                const Vector<float> dirs[4] =
                {
                    {m_speed,0}, {-m_speed, 0}, {0, -m_speed}, {0, m_speed}
                };
                m_directionVector = dirs[dir];
            }
        }

        // If attempt to move out of view, flip direction
        if (!Camera::getInstance().visible(
            {
                m_position.x,
                m_position.y,
                static_cast<float>(m_width),
                static_cast<float>(m_height)
            }
        ))
        {
            m_directionVector = -m_directionVector;
        }

        m_position += m_directionVector;
    }*/

    // TODO: Common move function for Moblin, Shrouded Stalfos, Octorok etc

    // Generic timer
    Timer m_enemyTimer;
    int m_auxiliaryFrame;
    bool m_moving;

    const Animation m_enemy[ENEMY_COUNT] =
    {
        //   x   y      startFrame  endFrame,    animationFPS,    
            {0   ,0,    0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_ARMOS 
            {96  ,0 ,   0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_BEETLE
            {128 ,96,   0,          1,           ENEMY_WATER_TEKTITE_FPS},       // ENEMY_WATER_TEKTITE
            {0   ,48 ,  0,          1,           ENEMY_PIG_WARRIOR_FPS},         // ENEMY_PIG_WARRIOR
            {96  ,144 , 0,          1,           ENEMY_BUZZ_BLOB_FPS},           // ENEMY_BUZZ_BLOB
            {96  ,16 ,  0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_CROW
            {64  ,16 ,  0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_DACTO
            {0   ,16 ,  0,          1,           ENEMY_DARKNUT_FPS},             // ENEMY_DARKNUT
            {0   ,32 ,  0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_GHINI
            {96  ,32 ,  0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_GIANT_GOPONGA_FLOWER
            {176 ,48 ,  0,          1,           ENEMY_GOPONGA_FLOWER_FPS},      // ENEMY_GOPONGA_FLOWER
            {144 ,48 ,  0,          1,           ENEMY_LIKE_LIKE_FPS},           // ENEMY_LIKE_LIKE
            {0   ,48 ,  0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_MAD_BOMBER
            {96  ,48 ,  0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_MINI_MOLDORM
            {0   ,32 ,  0,          1,           ENEMY_MOBLIN_FPS},              // ENEMY_MOBLIN
            {0   ,0 ,   0,          1,           ENEMY_OCTOROK_FPS},             // ENEMY_OCTOROK
            {0   ,144 , 0,          1,           ENEMY_LEEVER_FPS},              // ENEMY_LEEVER
            {96  ,64 ,  0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_PINCER
            {64  ,64 ,  0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_PIRANHA
            {32  ,64 ,  0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_POKEY
            {0   ,64 ,  0,          3,           ENEMY_SEA_URCHIN_FPS},          // ENEMY_SEA_URCHIN
            {0   ,208 , 0,          1,           ENEMY_SHROUDED_STALFOS_FPS},    // ENEMY_SHROUDED_STALFOS
            {64  ,80 ,  0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_SPINY_BEETLE
            {32  ,80 ,  0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_SWORD_STALFOS
            {0   ,96 ,  0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_WINGED_OCTOROK
            {96  ,96 ,  0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_ZIRRO
            {0   ,160 , 0,          1,           ENEMY_ZOMBIE_FPS},              // ENEMY_ZOMBIE
            {32  ,96 ,  0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_ZORA
            {80  ,64 ,  0,          7,           ENEMY_BEAMOS_FPS},              // ENEMY_BEAMOS
            {0   ,80 ,  0,          1,           ENEMY_GIBDO_FPS},               // ENEMY_GIBDO
            {32  ,80 ,  0,          1,           ENEMY_HARDHAT_BEETLE_FPS},      // ENEMY_HARDHAT_BEETLE
            {64  ,80 ,  0,          1,           ENEMY_BUBBLE_FPS},              // ENEMY_BUBBLE
            {96  ,80 ,  0,          3,           ENEMY_STAR_FPS},                // ENEMY_STAR
            {160 ,80 ,  0,          1,           ENEMY_VACUUM_FPS},              // ENEMY_VACUUM
            {64  ,64 ,  0,          0,           0},                             // ENEMY_BLADETRAP
            {0   ,96 ,  0,          1,           PLAYER_ANIMATION_FPS},          // ENEMY_ARM_MIMIC
            {0   ,112 , 0,          1,           ENEMY_SHY_GUY_FPS},             // ENEMY_SHY_GUY
            {0   ,128 , 0,          1,           ENEMY_IRON_MASK_FPS},           // ENEMY_IRON_MASK
            {128 ,112 , 0,          3,           ENEMY_THREE_OF_A_KIND_FPS},     // ENEMY_THREE_OF_A_KIND
            {160 ,96 ,  0,          1,           ENEMY_SPARK_FPS},               // ENEMY_SPARK
            {160 ,128 , 0,          1,           ENEMY_SAND_CRAB_FPS},           // ENEMY_SANDCRAB
            {96  ,160 , 0,          1,           ENEMY_PEAHAT_FPS},              // ENEMY_PEAHAT

            {0   ,64 ,  0,          3,           ENEMY_SEA_URCHIN_FPS},         // ENEMY_ROPE
            {96  ,80 ,  0,          1,           PLAYER_ANIMATION_FPS},         // ENEMY_MONKEY
            {64  ,80 ,  0,          1,           PLAYER_ANIMATION_FPS},         // ENEMY_TEKTIKE
            {32  ,80 ,  0,          1,           PLAYER_ANIMATION_FPS},         // ENEMY_POLS_VOICE
            {0   ,96 ,  0,          1,           PLAYER_ANIMATION_FPS},         // ENEMY_BALL_AND_CHAIN
            {96  ,96 ,  0,          1,           PLAYER_ANIMATION_FPS},         // ENEMY_KIRBY
            {0   ,160 , 0,          1,           ENEMY_ZOMBIE_FPS},             // ENEMY_RED_BOMBITE
            {32  ,96 ,  0,          1,           PLAYER_ANIMATION_FPS},         // ENEMY_GREEN_BOMBITE
            {80  ,64 ,  0,          7,           ENEMY_BEAMOS_FPS},             // ENEMY_KEESE
            {0   ,80 ,  0,          1,           ENEMY_GIBDO_FPS},              // ENEMY_ZOL
            {32  ,80 ,  0,          1,           ENEMY_HARDHAT_BEETLE_FPS},     // ENEMY_GEL
            {64  ,80 ,  0,          1,           ENEMY_BUBBLE_FPS},             // ENEMY_WIZZROBE
            {96  ,80 ,  0,          3,           ENEMY_STAR_FPS},               // ENEMY_MOUTH_VIRE
            {160 ,80 ,  0,          1,           ENEMY_VACUUM_FPS},             // ENEMY_STALFOS
            {64  ,64 ,  0,          0,           0},                            // ENEMY_ORB_MONSTER
            {0   ,192 , 0,          3,           ENEMY_PAIRODD_FPS},            // ENEMY_PAIRODD
            {96  ,176 , 0,          1,           ENEMY_GOOMBA_FPS},             // ENEMY_GOOMBA
            {0   ,112 , 0,          1,           ENEMY_SHY_GUY_FPS},            // ENEMY_CAMO_GOBLIN
            {0   ,128 , 0,          1,           ENEMY_IRON_MASK_FPS},          // ENEMY_BONE_PUTTER
            {128 ,112 , 0,          3,           ENEMY_THREE_OF_A_KIND_FPS},    // ENEMY_BATTLE_BAT
            //{160 ,96 ,  0,          1,           ENEMY_SPARK_FPS},              // ENEMY_SPIKED_BEETLE
            //{160 ,128 , 0,          1,           ENEMY_SAND_CRAB_FPS},          // ENEMY_BOO_BUDDY
            //{96  ,160 , 0,          1,           ENEMY_PEAHAT_FPS}              // ENEMY_BLAZING_BAT
    };

};

}