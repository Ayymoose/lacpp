#include "Resource.h"
#include "Debug.h"
#include "Sprite.h"
#include "SDL_Assert.h"

#include <cassert>
#include <SDL_image.h>

namespace Zelda
{

// Load a PNG image to a texture with a RGB colour used for transparency
std::unique_ptr<Sprite> Resource::loadSprite(const Renderer& renderer, const std::string& path, const Colour transparency)
{
    assert(renderer.getRenderer());
    auto const loadedSurface = loadSprite(path, transparency);
    return std::make_unique<Sprite>(renderer.getRenderer(), loadedSurface);
}

SDL_Surface* Resource::loadSprite(const std::string& path, const Colour transparency)
{
    assert(!path.empty());
    // Load image at specified path
    // TODO: Use IMG_LoadTexture when transparency issue fixed
    auto const loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface)
    {
        DEBUG(DBG_ERROR, IMG_GetError());
        assert(false);
        return nullptr;
    }
    else
    {
        // Set transparency
        SDL_ASSERT(SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format,
            make_red(transparency),
            make_green(transparency),
            make_blue(transparency))));

        return loadedSurface;
    }
}


}