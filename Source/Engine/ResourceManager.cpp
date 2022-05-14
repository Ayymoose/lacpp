#include "ResourceManager.h"
#include "Resource.h"
#include "Renderer.h"
#include <SDL_image.h>

namespace Zelda
{

void ResourceManager::loadSprite(SpriteResource resource, const std::string& path, const Colour transparencyColour)
{
    // A pinkish colour is used for transpareny
    assert(!path.empty());
    assert(resource > SpriteResource::SPR_RESOURCE_NONE && resource < SpriteResource::SPR_RESOURCE_COUNT);
    m_spriteResources.emplace(resource, Resource::loadSprite(Renderer::getInstance(), path, transparencyColour));
}

std::shared_ptr<Sprite> ResourceManager::operator[](SpriteResource resource) noexcept
{
    assert(resource > SpriteResource::SPR_RESOURCE_NONE && resource < SpriteResource::SPR_RESOURCE_COUNT);
    auto sprite = m_spriteResources[resource];
    assert(sprite->data());
    return sprite;
}

ResourceManager::~ResourceManager()
{
    // Free all loaded resources
    /*for (auto& [spriteResource, sprite]: m_spriteResources)
    {
        sprite.free();
    }*/
}

}