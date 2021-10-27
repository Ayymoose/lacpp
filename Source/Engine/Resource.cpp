#include "Resource.h"
#include "Renderer.h"
#include "Singleton.h"
#include "ZD_Assert.h"

namespace Zelda
{

void ResourceManager::loadGraphics() noexcept
{
    // Attempt to load all the graphic resources
    m_resources.emplace(std::pair<Graphic, Sprite>(Graphic::GFX_DUNGEON_1_TAIL_CAVE, loadSprite(ResourceDungeonsPath + "tm_tail_cave.png", TRANSPARENCY_COLOUR)));
    m_resources.emplace(std::pair<Graphic, Sprite>(Graphic::GFX_WORLD_MAP, loadSprite(ResourceMiscPath + "tm_worldmap.png", TRANSPARENCY_COLOUR)));



    m_resources.emplace(std::pair<Graphic, Sprite>(Graphic::GFX_ANIMATED_TILES, loadSprite(ResourceObjectsPath + "animated_tiles.png", TRANSPARENCY_COLOUR)));
    m_resources.emplace(std::pair<Graphic, Sprite>(Graphic::GFX_LINK, loadSprite(ResourceSpriteLinkPath + "link.png", TRANSPARENCY_COLOUR)));
    m_resources.emplace(std::pair<Graphic, Sprite>(Graphic::GFX_INVENTORY, loadSprite(ResourceObjectsPath + "inventory.png", TRANSPARENCY_COLOUR)));
    m_resources.emplace(std::pair<Graphic, Sprite>(Graphic::GFX_WEAPON, loadSprite(ResourceObjectsPath + "weapons.png", TRANSPARENCY_COLOUR)));
    m_resources.emplace(std::pair<Graphic, Sprite>(Graphic::GFX_TEXT, loadSprite(ResourceMiscPath + "dialogue.png", TRANSPARENCY_COLOUR)));
    m_resources.emplace(std::pair<Graphic, Sprite>(Graphic::GFX_ENEMY, loadSprite(ResourceEnemyPath + "enemy.png", TRANSPARENCY_COLOUR)));

    //std::cout << "Loaded " << m_resources.size() << " resources\n";
}

ResourceManager::~ResourceManager()
{
    // Free all loaded resources
    for (auto const& texture : m_resources)
    {
        auto pTexture = texture.second;
        pTexture.free();
    }
}

// Load a PNG image to a texture with a RGB colour used for transparency
Sprite ResourceManager::loadSprite(const std::string& path, uint32_t transparency) noexcept
{
    // Load image at specified path
    auto loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        assert(false && IMG_GetError());
        return Sprite();
    }
    else
    {
        // Set transparency
        SDL_ASSERT(SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, SDL_RED(transparency), SDL_GREEN(transparency), SDL_BLUE(transparency))), SDL_ERROR_MESSAGE);

        // Create texture from surface
        auto newTexture = SDL_CreateTextureFromSurface(Renderer::getInstance().getRenderer(), loadedSurface);
        assert(newTexture);

        // Below sets the SDL_TEXTUREACCESS_TARGET access to our texture as we can't set it on a surface it seems
        // So we must copy every texture created from surface to a new one.
        // A limitation of SDL
        Sprite srcSprite(newTexture);
        auto texture = Sprite(Renderer::getInstance().getRenderer(), srcSprite.width(), srcSprite.height());
        Sprite destSprite(texture);
        Rect<int> spriteSize = { 0,0,srcSprite.width(), srcSprite.height() };
        Sprite::copySprite(Renderer::getInstance().getRenderer(), srcSprite, destSprite, spriteSize, spriteSize);

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);

        // TODO: What does this do?
        SDL_ASSERT(SDL_SetTextureBlendMode(destSprite.data(), SDL_BLENDMODE_BLEND), SDL_ERROR_MESSAGE);

        return destSprite;
    }
}

}