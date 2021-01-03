#include "Resource.h"
#include "Renderer.h"
#include "Singleton.h"
#include "ZD_Assert.h"
#include "Drawing.h"

using namespace Zelda;

void ResourceManager::loadGraphics() noexcept
{
    // Attempt to load all the graphic resources
    m_resources.emplace(std::pair<Graphic, SDL_Texture*>(Graphic::GFX_DUNGEON_1_TAIL_CAVE, loadTexture(Zelda::ResourceDungeonsPath + "tm_tail_cave.png", TRANSPARENCY_COLOUR)));
    m_resources.emplace(std::pair<Graphic, SDL_Texture*>(Graphic::GFX_WORLD_MAP, loadTexture(Zelda::ResourceMiscPath + "tm_worldmap.png", TRANSPARENCY_COLOUR)));



    m_resources.emplace(std::pair<Graphic, SDL_Texture*>(Graphic::GFX_ANIMATED_TILES, loadTexture(Zelda::ResourceObjectsPath + "animated_tiles.png", TRANSPARENCY_COLOUR)));
    m_resources.emplace(std::pair<Graphic, SDL_Texture*>(Graphic::GFX_LINK, loadTexture(Zelda::ResourceSpriteLinkPath + "link.png", TRANSPARENCY_COLOUR)));
    m_resources.emplace(std::pair<Graphic, SDL_Texture*>(Graphic::GFX_INVENTORY, loadTexture(Zelda::ResourceObjectsPath + "inventory.png", TRANSPARENCY_COLOUR)));
    m_resources.emplace(std::pair<Graphic, SDL_Texture*>(Graphic::GFX_WEAPON, loadTexture(Zelda::ResourceObjectsPath + "weapons.png", TRANSPARENCY_COLOUR)));
    m_resources.emplace(std::pair<Graphic, SDL_Texture*>(Graphic::GFX_TEXT, loadTexture(Zelda::ResourceMiscPath + "dialogue.png", TRANSPARENCY_COLOUR)));
    m_resources.emplace(std::pair<Graphic, SDL_Texture*>(Graphic::GFX_ENEMY, loadTexture(Zelda::ResourceEnemyPath + "enemy.png", TRANSPARENCY_COLOUR)));

    std::cout << "Loaded " << m_resources.size() << " resources\n";
}

void Zelda::ResourceManager::loadSounds() noexcept
{
    // TODO: Load sounds
}

ResourceManager::~ResourceManager()
{
    // Free all loaded resources
    for (auto const& texture : m_resources)
    {
        SDL_Texture* pTexture = texture.second;
        SDL_DestroyTexture(pTexture);
    }
}

// Load a PNG image to a texture with a RGB colour used for transparency
SDL_Texture* ResourceManager::loadTexture(const std::string& path, uint32_t transparency) noexcept
{
    // The final texture
    SDL_Texture* newTexture = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        fprintf(stderr,"Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        assert(false);
    }
    else
    {
        // Set transparency
        SDL_ASSERT(SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, SDL_RED(transparency), SDL_GREEN(transparency), SDL_BLUE(transparency))), SDL_ERROR_MESSAGE);

        // Create texture from surface
        newTexture = SDL_CreateTextureFromSurface(Renderer::getInstance().getRenderer(), loadedSurface);
        // TODO: Fix SDL_ASSERT to handle nullptr checks
        assert(newTexture);

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    // Below sets the SDL_TEXTUREACCESS_TARGET access to our texture as we can't set it on a surface it seems
    // So we must copy every texture created from surface to a new one.
    // A limitation of SDL
    int textureWidth,textureHeight;
    SDL_ASSERT(SDL_QueryTexture(newTexture, nullptr, nullptr, &textureWidth, &textureHeight), SDL_ERROR_MESSAGE);
    auto texture = SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, textureWidth, textureHeight);
    assert(texture != nullptr);
    copyToTexture(Renderer::getInstance().getRenderer(), newTexture, texture, nullptr, nullptr);
    SDL_ASSERT(SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND), SDL_ERROR_MESSAGE);
    
    return texture;
}