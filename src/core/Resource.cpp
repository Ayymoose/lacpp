#include "Resource.h"
#include "Logger.h"
#include "Sprite.h"
#include "SDL_Check.h"

#include <cassert>
#include <SDL_image.h>

namespace zelda::engine
{

// Load a PNG image to a texture with a RGB colour used for transparency
std::unique_ptr<Sprite> Resource::loadSprite(const Renderer& renderer, const std::string& path,
                                             Colour::colour transparency)
{
    assert(renderer.getRenderer());
    auto const loadedSurface = loadSprite(path, transparency);
    return std::make_unique<Sprite>(renderer.getRenderer(), loadedSurface);
}

SDL_Surface* Resource::loadSprite(const std::string& path, Colour::colour transparency)
{
    assert(!path.empty());
    // Load image at specified path
    // TODO: Use IMG_LoadTexture when transparency issue fixed
    auto const loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface)
    {
        Logger::instance().log<Logger::Mask::ERROR>(IMG_GetError());
        return nullptr;
    }
    else
    {
        // Set transparency
        SDL_CHECK(SDL_SetColorKey(loadedSurface,
                                  SDL_TRUE,
                                  SDL_MapRGB(loadedSurface->format,
                                             Colour::makeRed(transparency),
                                             Colour::makeGreen(transparency),
                                             Colour::makeBlue(transparency))));

        return loadedSurface;
    }
}


} // namespace zelda::engine