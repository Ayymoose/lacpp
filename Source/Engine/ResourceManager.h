#pragma once

#include <string>
#include <cassert>
#include <unordered_map>
#include <memory>

#include "Colour.h"
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

    // TEST
    SPR_BALL,
    SPR_RESOURCE_COUNT
};


class ResourceManager : public Singleton<ResourceManager>
{
    friend class Singleton<ResourceManager>;
public:

    void loadSprite(SpriteResource resource, const std::string& path, const Colour transparencyColour);
    std::shared_ptr<Sprite> operator[](SpriteResource resource);

private:
    ResourceManager() = default;

    // Map between resources and pointer to all textures
    std::unordered_map<SpriteResource, std::shared_ptr<Sprite>> m_spriteResources;
};
}