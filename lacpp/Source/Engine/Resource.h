#pragma once

#include <string>
#include <assert.h>
#include <SDL_image.h>
#include <map>
#include "Singleton.h"

// A pinkish colour is used for transparency
#define TRANSPARENCY_COLOUR (SDL_RGB(255,0,128))

namespace Zelda
{

    const std::string ResourceDungeonsPath = R"(Resources\Background\Dungeon\)";
    const std::string ResourceSpriteLinkPath = R"(Resources\Sprite\Link\)";
    const std::string ResourceObjectsPath = R"(Resources\Sprite\Object\)";
    const std::string ResourceMiscPath = R"(Resources\Background\Misc\)";
    enum class Graphic
    {
        GFX_RESOURCE_NONE = -1,
        // Main overworld
        GFX_BACKGROUND_OVERWORLD_MAIN,

        // Dungeons
        GFX_DUNGEON_1_TAIL_CAVE,
        GFX_DUNGEON_2_BOTTLE_GROTTO,
        GFX_DUNGEON_3_KEY_CAVERN,
        GFX_DUNGEON_4_ANGLER_TUNNEL,
        GFX_DUNGEON_5_CATFISH_MAW,
        GFX_DUNGEON_6_FACE_SHRINE,
        GFX_DUNGEON_7_EAGLE_TOWER,
        GFX_DUNGEON_8_TURTLE_ROCK,
        GFX_DUNGEON_9_COLOUR_DUNGEON,
        GFX_DUNGEON_10_WIND_FISH_EGG,

        // Interiors
        GFX_INTERIOR_KANALET_CASTLE,
        GFX_INTERIOR_DREAM_SHRINE,
        GFX_INTERIOR_ANCIENT_RUINS,

        // Caves
        GFX_CAVE_MOBLIN_CAVE,
        GFX_CAVE_0,
        GFX_CAVE_1,
        GFX_CAVE_2,
        GFX_CAVE_3,
        GFX_CAVE_4,
        GFX_CAVE_5,
        GFX_CAVE_6,
        GFX_CAVE_7,
        GFX_CAVE_8,
        GFX_CAVE_9,
        GFX_CAVE_10,
        GFX_CAVE_11,
        GFX_CAVE_12,
        GFX_CAVE_13,
        GFX_CAVE_14,
        GFX_CAVE_15,
        GFX_CAVE_16,
        GFX_CAVE_17,
        GFX_CAVE_18,
        GFX_CAVE_19,
        GFX_CAVE_20,

        // Houses
        GFX_INTERIOR_HOUSE_0,
        GFX_INTERIOR_HOUSE_1,
        GFX_INTERIOR_HOUSE_2,
        GFX_INTERIOR_HOUSE_3,
        GFX_INTERIOR_HOUSE_4,
        GFX_INTERIOR_HOUSE_5,
        GFX_INTERIOR_HOUSE_6,
        GFX_INTERIOR_HOUSE_7,
        GFX_INTERIOR_HOUSE_8,
        GFX_INTERIOR_HOUSE_9,
        GFX_INTERIOR_HOUSE_10,
        GFX_INTERIOR_HOUSE_11,
        GFX_INTERIOR_HOUSE_12,
        GFX_INTERIOR_HOUSE_13,
        GFX_INTERIOR_HOUSE_14,
        GFX_INTERIOR_HOUSE_15,
        GFX_INTERIOR_HOUSE_16,
        GFX_INTERIOR_HOUSE_17,
        GFX_INTERIOR_HOUSE_18,
        GFX_INTERIOR_HOUSE_19,
        GFX_INTERIOR_HOUSE_20,
        GFX_INTERIOR_HOUSE_21,
        GFX_INTERIOR_HOUSE_22,

        //Misc
        GFX_INTERIOR_TELEPHONE_HOUSE,
        GFX_INVENTORY,
        GFX_FILE_MENU_1,
        GFX_FILE_MENU_2,
        GFX_FILE_MENU_3,
        GFX_TEXT,

        // Background Objects
        GFX_CANDLE,
        GFX_TORCH_1,
        GFX_TORCH_2,
        GFX_SPIKE,
        GFX_WATER_1,
        GFX_WATER_2,
        GFX_WATER_3,
        GFX_WATER_4,
        GFX_RAPID,
        GFX_FLOWER_1,
        GFX_FLOWER_2,

        GFX_WEAPON,


        // Sprites
        GFX_LINK,

        GFX_RESOURCE_COUNT
    };

    // There really should be another class (e.g ResourceManager) to manage
    // a list of Resource objects but I'm just lazy so
    // Resource is the object which manages all resources

    class ResourceManager : public Singleton<ResourceManager>
    {
    public:

        SDL_Texture* operator[](Graphic resource) noexcept
        {
            assert(resource > Graphic::GFX_RESOURCE_NONE && resource < Graphic::GFX_RESOURCE_COUNT);
            return m_resources[resource];
        }

        void loadGraphics() noexcept;
        void loadSounds() noexcept;
        virtual ~ResourceManager();

    private:
        // Load a texture and specify the transparent colour
        SDL_Texture* loadTexture(const std::string& path, uint32_t transparency) noexcept;

        // Map between resources and pointer to all textures
        std::map<Graphic, SDL_Texture*> m_resources;
    };
}