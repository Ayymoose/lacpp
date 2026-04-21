#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <filesystem>
#include <SDL_filesystem.h>

#include "Colour.h"
#include "Singleton.h"
#include "Sprite.h"

namespace zelda::engine
{

namespace fs = std::filesystem;

// Get base path once
inline fs::path GetBasePath()
{
    char *basePath = SDL_GetBasePath();
    if (!basePath)
    {
        throw std::runtime_error("Failed to get SDL base path");
    }

    fs::path result(basePath);
    SDL_free(basePath);
    return result;
}

// Build all resource paths from base
inline fs::path RESOURCE_ROOT = GetBasePath() / ".." / ".." / "resources";
inline fs::path RESOURCE_DUNGEONS_PATH = RESOURCE_ROOT / "background" / "dungeon";
inline fs::path RESOURCE_SPRITE_LINK_PATH = RESOURCE_ROOT / "sprite" / "link";
inline fs::path RESOURCE_OBJECT_PATH = RESOURCE_ROOT / "sprite" / "object";
inline fs::path RESOURCE_MISC_PATH = RESOURCE_ROOT / "background" / "misc";
inline fs::path RESOURCE_ENEMY_PATH = RESOURCE_ROOT / "sprite" / "enemy";

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
    void loadSprite(SpriteResource resource, const std::string &path, const Colour transparencyColour);
    std::shared_ptr<Sprite> operator[](SpriteResource resource);

private:
    ResourceManager() = default;

    // Map between resources and pointer to all textures
    std::unordered_map<SpriteResource, std::shared_ptr<Sprite>> m_spriteResources;
};
} // namespace zelda::engine