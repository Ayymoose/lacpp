#include "Resource.h"
#include "Debug.h"

namespace Zelda
{

// Load a PNG image to a texture with a RGB colour used for transparency
Sprite Resource::loadSprite(const Renderer& renderer, const std::string& path, Colour transparency) noexcept
{
    assert(renderer.getRenderer());
    assert(!path.empty());
    // Load image at specified path
    auto const loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface)
    {
        DEBUG(DBG_ERROR, IMG_GetError());
        assert(false);
        return Sprite();
    }
    else
    {
        // Set transparency
        SDL_ASSERT(SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 
            SDL_Red(transparency), 
            SDL_Green(transparency), 
            SDL_Blue(transparency))));

        // Create texture from surface
        auto newTexture = SDL_CreateTextureFromSurface(renderer.getRenderer(), loadedSurface);
        assert(newTexture);

        // Below sets the SDL_TEXTUREACCESS_TARGET access to our texture as we can't set it on a surface it seems
        // So we must copy every texture created from surface to a new one.
        // A limitation of SDL
        Sprite srcSprite(newTexture);
        auto texture = Sprite(renderer.getRenderer(), srcSprite.width(), srcSprite.height());
        Sprite destSprite(texture);
        Rect<int> spriteSize = { 0,0,srcSprite.width(), srcSprite.height() };
        Sprite::copySprite(renderer.getRenderer(), srcSprite, destSprite, spriteSize, spriteSize);

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);

        // TODO: What does this do?
        SDL_ASSERT(SDL_SetTextureBlendMode(destSprite.data(), SDL_BLENDMODE_BLEND));

        return destSprite;
    }
}

}