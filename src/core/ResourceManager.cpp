#include "ResourceManager.h"
#include "Resource.h"
#include "Renderer.h"
#include <SDL_image.h>

namespace zelda::engine
{

void ResourceManager::loadSprite(SpriteResource resource, const std::string& path, const Colour transparencyColour)
{
    // A pinkish colour is used for transpareny
    assert(!path.empty());
    assert(resource > SpriteResource::NONE && resource < SpriteResource::COUNT);
    m_spriteResources.emplace(resource, Resource::loadSprite(Renderer::instance(), path, transparencyColour));
}

std::shared_ptr<Sprite> ResourceManager::operator[](SpriteResource resource)
{
    assert(resource > SpriteResource::NONE && resource < SpriteResource::COUNT);
    auto sprite = m_spriteResources[resource];
    assert(sprite && "Sprite doesn't exist");
    assert(sprite->data());
    return sprite;
}

} // namespace zelda::engine