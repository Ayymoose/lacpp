#pragma once

#include "Vector.h"
#include "BasicCharacter.h"
#include "Resource.h"
#include "Camera.h"
#include "ZD_Assert.h"
#include "Renderer.h"
#include "Clock.h"
#include "Engine.h"
#include "Link.h"

enum class EnemySprite
{
    ENEMY_NONE = -1,
    ENEMY_ARMOS,                // NOT DONE
    ENEMY_BEETLE,               // NOT DONE
    ENEMY_WATER_TEKTITE,
    ENEMY_BOARBLIN,             // NOT DONE
    ENEMY_BUZZ_BLOB,
    ENEMY_CROW,                 // NOT DONE
    ENEMY_DACTO,                // NOT DONE
    ENEMY_DARKNUT,              // NOT DONE
    ENEMY_GHINI,                // NOT DONE
    ENEMY_GIANT_GOPONGA_FLOWER, // NOT DONE
    ENEMY_GOPONGA_FLOWER,
    ENEMY_LIKE_LIKE,
    ENEMY_MAD_BOMBER,           // NOT DONE
    ENEMY_MINI_MOLDORM,         // NOT DONE
    ENEMY_MOBLIN,               // NOT DONE
    ENEMY_OCTOROK,              // NOT DONE
    ENEMY_LEEVER,
    ENEMY_PINCER,               // NOT DONE
    ENEMY_PIRANHA,              // NOT DONE
    ENEMY_POKEY,                // NOT DONE
    ENEMY_SEA_URCHIN,
    ENEMY_SHROUDED_STALFOS,     // NOT DONE
    ENEMY_SPINY_BEETLE,         // NOT DONE
    ENEMY_SWORD_STALFOS,        // NOT DONE
    ENEMY_WINGED_OCTOROK,       // NOT DONE
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
    ENEMY_RED_BOMBITE,          // NOT DONE
    ENEMY_GREEN_BOMBITE,        // NOT DONE
    ENEMY_KEESE,                // NOT DONE
    ENEMY_ZOL,                  // NOT DONE
    ENEMY_GEL,                  // NOT DONE
    ENEMY_WIZZROBE,             // NOT DONE
    ENEMY_MOUTH_VIRE,           // NOT DONE
    ENEMY_STALFOS,              // NOT DONE
    ENEMY_ORB_MONSTER,          // NOT DONE
    ENEMY_PAIRODD,              // NOT DONE
    ENEMY_CAMO_GOBLIN,          // NOT DONE
    ENEMY_BONE_PUTTER,          // NOT DONE
    ENEMY_BATTLE_BAT,           // NOT DONE
    ENEMY_SPIKED_BEETLE,        // NOT DONE
    ENEMY_BOO_BUDDY,            // NOT DONE
    ENEMY_BLAZING_BAT,          // NOT DONE
    ENEMY_COUNT
};

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
    Enemy(int x, int y) : m_auxiliaryFrame(0), m_moving(true)
    {
        m_positionVector.x = x;
        m_positionVector.y = y;
    }

    // Generic timer
    Clock m_enemyTimer;
    int m_auxiliaryFrame;
    bool m_moving;

    // Enemy frames
    #define ENEMY_SEA_URCHIN_FPS (1.0f / 4.0f)
    #define ENEMY_BEAMOS_FPS (1.0f / 4.0f)
    #define ENEMY_GOPONGA_FLOWER_FPS (1.0f / 2.0f)
    #define ENEMY_GIBDO_FPS (1.0f / 3.0f)
    #define ENEMY_LIKE_LIKE_FPS (1.0f / 3.0f)
    #define ENEMY_HARDHAT_BEETLE_FPS (1.0f / 6.0f)
    #define ENEMY_BUBBLE_FPS (1.0f / 10.0f)
    #define ENEMY_STAR_FPS (1.0f / 4.0f)
    #define ENEMY_VACUUM_FPS (0.25f)
    #define ENEMY_SHY_GUY_FPS (0.25f)
    #define ENEMY_WATER_TEKTITE_FPS (1.0f / 4.0f)
    #define ENEMY_IRON_MASK_FPS (1.0f / 10.0f)
    #define ENEMY_THREE_OF_A_KIND_FPS (1.0f / 6.0f)
    #define ENEMY_SPARK_FPS (1.0f / 16.0f)
    #define ENEMY_LEEVER_FPS (1.0f / 8.0f)
    #define ENEMY_SAND_CRAB_FPS (1.0f / 8.0f)
    #define ENEMY_BUZZ_BLOB_FPS (1.0f / 6.0f)
    #define ENEMY_ZOMBIE_FPS (1.0f / 4.0f)
    #define ENEMY_PEAHAT_FPS (1.0f / 16.0f)

    const Animation m_enemy[static_cast<size_t>(EnemySprite::ENEMY_COUNT)] =
    {
         //   x   y      startFrame  endFrame,    animationFPS,     orientation,  flip
             {0   ,0,    0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_ARMOS 
             {96  ,0 ,   0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_BEETLE
             {128 ,96,   0,          1,     ENEMY_WATER_TEKTITE_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_WATER_TEKTITE
             {32  ,0 ,   0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_BOARBLIN
             {96   ,144 ,  0,          1,     ENEMY_BUZZ_BLOB_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_BUZZ_BLOB
             {96  ,16 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_CROW
             {64  ,16 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_DACTO
             {32  ,16 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_DARKNUT
             {0   ,32 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_GHINI
             {96  ,32 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_GIANT_GOPONGA_FLOWER
             {176  ,48 ,  0,          1,     ENEMY_GOPONGA_FLOWER_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_GOPONGA_FLOWER
             {144  ,48 ,  0,          1,     ENEMY_LIKE_LIKE_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_LIKE_LIKE
             {0   ,48 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_MAD_BOMBER
             {96  ,48 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_MINI_MOLDORM
             {64  ,48 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_MOBLIN
             {32  ,48 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_OCTOROK
             {0   ,144 ,  0,          1,     ENEMY_LEEVER_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_LEEVER
             {96  ,64 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_PINCER
             {64  ,64 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_PIRANHA
             {32  ,64 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_POKEY
             {0   ,64 ,  0,          3,     ENEMY_SEA_URCHIN_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_SEA_URCHIN
             {96  ,80 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_SHROUDED_STALFOS
             {64  ,80 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_SPINY_BEETLE
             {32  ,80 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_SWORD_STALFOS
             {0   ,96 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_WINGED_OCTOROK
             {96  ,96 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_ZIRRO
             {0  ,160 ,  0,          1,     ENEMY_ZOMBIE_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_ZOMBIE
             {32  ,96 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_ZORA
             {80  ,64 ,  0,          7,     ENEMY_BEAMOS_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_BEAMOS
             {0   ,80 ,  0,          1,     ENEMY_GIBDO_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_GIBDO
             {32  ,80 ,  0,          1,     ENEMY_HARDHAT_BEETLE_FPS,    0,         SDL_FLIP_NONE},    // ENEMY_HARDHAT_BEETLE
             {64  ,80 ,  0,          1,     ENEMY_BUBBLE_FPS,    0,         SDL_FLIP_NONE}, // ENEMY_BUBBLE
             {96  ,80 ,  0,          3,     ENEMY_STAR_FPS,    0,         SDL_FLIP_NONE}, // ENEMY_STAR
             {160 ,80 ,  0,          1,     ENEMY_VACUUM_FPS,    0,         SDL_FLIP_NONE}, // ENEMY_VACUUM
             {64  ,64 ,  0,          0,     0,    0,         SDL_FLIP_NONE}, // ENEMY_BLADETRAP
             {0   ,96 ,  0,          1,     PLAYER_ANIMATION_FPS,    0,         SDL_FLIP_NONE}, // ENEMY_ARM_MIMIC
             {0   ,112 ,  0,          1,     ENEMY_SHY_GUY_FPS,    0,         SDL_FLIP_NONE}, // ENEMY_SHY_GUY
             {0   ,128 ,  0,          1,     ENEMY_IRON_MASK_FPS,    0,         SDL_FLIP_NONE}, // ENEMY_IRON_MASK
             {128   ,112 ,  0,          3,     ENEMY_THREE_OF_A_KIND_FPS,    0,         SDL_FLIP_NONE}, // ENEMY_THREE_OF_A_KIND
             {160   ,96 ,  0,          1,     ENEMY_SPARK_FPS,    0,         SDL_FLIP_NONE}, // ENEMY_SPARK
             {160   ,128 ,  0,          1,     ENEMY_SAND_CRAB_FPS,    0,         SDL_FLIP_NONE}, // ENEMY_SANDCRAB
             {96   ,160 ,  0,          1,     ENEMY_PEAHAT_FPS,    0,         SDL_FLIP_NONE}// ENEMY_PEAHAT
    };

};