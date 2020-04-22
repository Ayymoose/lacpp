#include <string>
#include <assert.h>
#include <SDL_image.h>
#include <map>
#include "Singleton.h"

#ifndef RESOURCE_H
#define RESOURCE_H

enum RESOURCE
{
    RSC_RESOURCE_NONE = -1,
    // Main overworld
    RSC_BACKGROUND_OVERWORLD_MAIN,
    
    // Dungeons
    RSC_DUNGEON_1_TAIL_CAVE,
    RSC_DUNGEON_2_BOTTLE_GROTTO,
    RSC_DUNGEON_3_KEY_CAVERN,
    RSC_DUNGEON_4_ANGLER_TUNNEL,
    RSC_DUNGEON_5_CATFISH_MAW,
    RSC_DUNGEON_6_FACE_SHRINE,
    RSC_DUNGEON_7_EAGLE_TOWER,
    RSC_DUNGEON_8_TURTLE_ROCK,
    RSC_DUNGEON_9_COLOUR_DUNGEON,
    RSC_DUNGEON_10_WIND_FISH_EGG,

    // Interiors
    RSC_INTERIOR_KANALET_CASTLE,
    RSC_INTERIOR_DREAM_SHRINE,
    RSC_INTERIOR_ANCIENT_RUINS,

    // Caves
    RSC_CAVE_MOBLIN_CAVE,
    RSC_CAVE_0,
    RSC_CAVE_1,
    RSC_CAVE_2,
    RSC_CAVE_3,
    RSC_CAVE_4,
    RSC_CAVE_5,
    RSC_CAVE_6,
    RSC_CAVE_7,
    RSC_CAVE_8,
    RSC_CAVE_9,
    RSC_CAVE_10,
    RSC_CAVE_11,
    RSC_CAVE_12,
    RSC_CAVE_13,
    RSC_CAVE_14,
    RSC_CAVE_15,
    RSC_CAVE_16,
    RSC_CAVE_17,
    RSC_CAVE_18,
    RSC_CAVE_19,
    RSC_CAVE_20,

    // Houses
    RSC_INTERIOR_HOUSE_0,
    RSC_INTERIOR_HOUSE_1,
    RSC_INTERIOR_HOUSE_2,
    RSC_INTERIOR_HOUSE_3,
    RSC_INTERIOR_HOUSE_4,
    RSC_INTERIOR_HOUSE_5,
    RSC_INTERIOR_HOUSE_6,
    RSC_INTERIOR_HOUSE_7,
    RSC_INTERIOR_HOUSE_8,
    RSC_INTERIOR_HOUSE_9,
    RSC_INTERIOR_HOUSE_10,
    RSC_INTERIOR_HOUSE_11,
    RSC_INTERIOR_HOUSE_12,
    RSC_INTERIOR_HOUSE_13,
    RSC_INTERIOR_HOUSE_14,
    RSC_INTERIOR_HOUSE_15,
    RSC_INTERIOR_HOUSE_16,
    RSC_INTERIOR_HOUSE_17,
    RSC_INTERIOR_HOUSE_18,
    RSC_INTERIOR_HOUSE_19,
    RSC_INTERIOR_HOUSE_20,
    RSC_INTERIOR_HOUSE_21,
    RSC_INTERIOR_HOUSE_22,

    //Misc
    RSC_INTERIOR_TELEPHONE_HOUSE,
    RSC_INVENTORY,
    RSC_FILE_MENU_1,
    RSC_FILE_MENU_2,
    RSC_FILE_MENU_3,

    // Background Objects
    RSC_CANDLE,
    RSC_TORCH_1,
    RSC_TORCH_2,
    RSC_SPIKE,
    RSC_WATER_1,
    RSC_WATER_2,
    RSC_WATER_3,
    RSC_WATER_4,
    RSC_RAPID,
    RSC_FLOWER_1,
    RSC_FLOWER_2,
    
    

    // Sprites
    RSC_LINK,
    
    RSC_RESOURCE_COUNT
};

// There really should be another class (e.g ResourceManager) to manage
// a list of Resource objects but I'm just lazy so
// Resource is the object which manages all resources

class ResourceManager : public Singleton<ResourceManager>
{
    friend class Singleton<ResourceManager>;

public:

    SDL_Texture* operator[](RESOURCE resource)
    {
        assert(resource > RSC_RESOURCE_NONE && resource < RSC_RESOURCE_COUNT);
        return m_Resources[resource];
    }

    void loadGraphics();

    virtual ~ResourceManager();
    
private:

    ResourceManager() = default;

    // Load a texture
    SDL_Texture* loadTexture(const std::string& path);

    // Map between resources and pointer to all textures
    std::map<RESOURCE, SDL_Texture*> m_Resources;
};

#endif