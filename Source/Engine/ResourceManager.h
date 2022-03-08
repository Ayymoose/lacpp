#pragma once

#include <string>
#include <assert.h>
#include <SDL_image.h>
#include <unordered_map>
#include "Singleton.h"
#include "Sprite.h"

namespace Zelda
{

const std::string RESOURCE_DUNGEONS_PATH = R"(..\..\Resources\Background\Dungeon\)";
const std::string RESOURCE_SPRITE_LINK_PATH = R"(..\..\Resources\Sprite\Link\)";
const std::string RESOURCE_OBJECT_PATH = R"(..\..\Resources\Sprite\Object\)";
const std::string RESOURCE_MISC_PATH = R"(..\..\Resources\Background\Misc\)";
const std::string RESOURCE_ENEMY_PATH = R"(..\..\Resources\Sprite\Enemy\)";

enum class SpriteResource
{
    SPR_RESOURCE_NONE = -1,
    SPR_DUNGEON_1_TAIL_CAVE,
    SPR_WORLD_MAP,
    SPR_TEXT,
    SPR_INVENTORY,
    SPR_WEAPON,
    SPR_LINK,
    SPR_ANIMATED_TILES,
    SPR_ENEMY,
    SPR_RESOURCE_COUNT
};


class ResourceManager : public Singleton<ResourceManager>
{
    friend class Singleton<ResourceManager>;
public:

    Sprite operator[](SpriteResource resource) noexcept;
    void loadSprites() noexcept;

    ~ResourceManager();
private:
    ResourceManager() = default;

    // Map between resources and pointer to all textures
    std::unordered_map<SpriteResource, Sprite> m_spriteResources;
};
}