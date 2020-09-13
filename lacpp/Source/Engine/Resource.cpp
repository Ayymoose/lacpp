#include "Resource.h"
#include "Renderer.h"
#include "Singleton.h"
#include "ZD_Assert.h"
#include "Drawing.h"

using namespace Zelda;

void ResourceManager::loadGraphics() noexcept
{
    // Attempt to load all the graphic resources
    m_Resources.emplace(std::pair<Graphic, SDL_Texture*>(Graphic::GFX_DUNGEON_1_TAIL_CAVE, loadTexture(Zelda::ResourceDungeonsPath + "dungeon_tail_cave.png", TRANSPARENCY_COLOUR)));
    m_Resources.emplace(std::pair<Graphic, SDL_Texture*>(Graphic::GFX_LINK, loadTexture(Zelda::ResourceSpriteLinkPath + "link.png", TRANSPARENCY_COLOUR)));
    m_Resources.emplace(std::pair<Graphic, SDL_Texture*>(Graphic::GFX_CANDLE, loadTexture(Zelda::ResourceObjectsPath + "candle.png", TRANSPARENCY_COLOUR)));
    m_Resources.emplace(std::pair<Graphic, SDL_Texture*>(Graphic::GFX_TORCH_1, loadTexture(Zelda::ResourceObjectsPath + "torch.png", TRANSPARENCY_COLOUR)));
    m_Resources.emplace(std::pair<Graphic, SDL_Texture*>(Graphic::GFX_INVENTORY, loadTexture(Zelda::ResourceObjectsPath + "inventory.png", TRANSPARENCY_COLOUR)));
    m_Resources.emplace(std::pair<Graphic, SDL_Texture*>(Graphic::GFX_WEAPON, loadTexture(Zelda::ResourceObjectsPath + "weapons.png", TRANSPARENCY_COLOUR)));

}

void Zelda::ResourceManager::loadSounds() noexcept
{
    // TODO: Load sounds
}

ResourceManager::~ResourceManager()
{
    // Free all loaded resources
    for (auto iterator = m_Resources.begin(); iterator != m_Resources.end(); iterator++)
    {
        SDL_Texture* pTexture = (*iterator).second;
        SDL_DestroyTexture(pTexture);
    }
}

SDL_Texture* ResourceManager::loadTexture(const std::string& path, uint32_t transparency) noexcept
{
    // The final texture
    SDL_Texture* newTexture = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        fprintf(stderr,"Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Set transparency
        ZD_ASSERT(SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, SDL_RED(transparency), SDL_GREEN(transparency), SDL_BLUE(transparency))) == 0, "SDL Error: " << SDL_GetError());

        // Create texture from surface
        newTexture = SDL_CreateTextureFromSurface(Renderer::getInstance().getRenderer(), loadedSurface);
        ZD_ASSERT(newTexture != nullptr, "SDL Error: " << SDL_GetError());

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    assert(newTexture != nullptr);

    // Below sets the SDL_TEXTUREACCESS_TARGET access to our texture as we can't set it on a surface it seems
    // So we must copy every texture created from surface to a new one.
    // A limitation of SDL
    int textureWidth,textureHeight;
    ZD_ASSERT(SDL_QueryTexture(newTexture, nullptr, nullptr, &textureWidth, &textureHeight) == 0, "SDL Error: " << SDL_GetError());
    auto texture = SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, textureWidth, textureHeight);
    assert(texture != nullptr);
    CopyToTexture(Renderer::getInstance().getRenderer(), newTexture, texture, nullptr, nullptr);
    ZD_ASSERT(SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) == 0, "SDL Error: " << SDL_GetError());
    
    return texture;
}