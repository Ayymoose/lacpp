#include "ResourceManager.h"
#include "Resource.h"
#include "Renderer.h"
#include "Singleton.h"
#include "SDL_Assert.h"

namespace Zelda
{

void ResourceManager::loadSprites() noexcept
{
    // A pinkish colour is used for transpareny
    constexpr Colour TRANSPARENCY_COLOUR = SDL_RGB(255, 0, 128);

    m_spriteResources.emplace(SpriteResource::SPR_DUNGEON_1_TAIL_CAVE, Resource::loadSprite(Renderer::getInstance(), RESOURCE_DUNGEONS_PATH + "tm_tail_cave.png", TRANSPARENCY_COLOUR));
    m_spriteResources.emplace(SpriteResource::SPR_WORLD_MAP, Resource::loadSprite(Renderer::getInstance(), RESOURCE_MISC_PATH + "tm_worldmap.png", TRANSPARENCY_COLOUR));
    m_spriteResources.emplace(SpriteResource::SPR_LINK, Resource::loadSprite(Renderer::getInstance(), RESOURCE_SPRITE_LINK_PATH + "link.png", TRANSPARENCY_COLOUR));
    m_spriteResources.emplace(SpriteResource::SPR_INVENTORY, Resource::loadSprite(Renderer::getInstance(), RESOURCE_OBJECT_PATH + "inventory.png", TRANSPARENCY_COLOUR));
    m_spriteResources.emplace(SpriteResource::SPR_WEAPON, Resource::loadSprite(Renderer::getInstance(), RESOURCE_OBJECT_PATH + "weapons.png", TRANSPARENCY_COLOUR));
    m_spriteResources.emplace(SpriteResource::SPR_TEXT, Resource::loadSprite(Renderer::getInstance(), RESOURCE_MISC_PATH + "dialogue.png", TRANSPARENCY_COLOUR));
    m_spriteResources.emplace(SpriteResource::SPR_ENEMY, Resource::loadSprite(Renderer::getInstance(), RESOURCE_ENEMY_PATH + "enemy.png", TRANSPARENCY_COLOUR));
}

Sprite ResourceManager::operator[](SpriteResource resource) noexcept
{
    assert(resource > SpriteResource::SPR_RESOURCE_NONE && resource < SpriteResource::SPR_RESOURCE_COUNT);
    auto sprite = m_spriteResources[resource];
    assert(sprite.data());
    return sprite;
}

ResourceManager::~ResourceManager()
{
    // Free all loaded resources
    for (auto& [spriteResource, sprite]: m_spriteResources)
    {
        sprite.free();
    }
}

}