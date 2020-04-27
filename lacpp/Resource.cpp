#include "Resource.h"
#include "Renderer.h"
#include "Singleton.h"
#include "MyAssert.h"
#include "Drawing.h"

void ResourceManager::loadGraphics()
{
    // Attempt to load all the graphic resources
    m_Resources.emplace(std::pair<RESOURCE, SDL_Texture*>(RSC_DUNGEON_1_TAIL_CAVE, loadTexture("Resources\\Background\\Dungeon\\dungeon_tail_cave.png", TRANSPARENCY_COLOUR)));
    m_Resources.emplace(std::pair<RESOURCE, SDL_Texture*>(RSC_LINK, loadTexture("Resources\\Sprite\\Link\\link.png", TRANSPARENCY_COLOUR)));
    m_Resources.emplace(std::pair<RESOURCE, SDL_Texture*>(RSC_CANDLE, loadTexture("Resources\\Sprite\\Object\\candle.png", TRANSPARENCY_COLOUR)));
    m_Resources.emplace(std::pair<RESOURCE, SDL_Texture*>(RSC_TORCH_1, loadTexture("Resources\\Sprite\\Object\\torch.png", TRANSPARENCY_COLOUR)));
    m_Resources.emplace(std::pair<RESOURCE, SDL_Texture*>(RSC_INVENTORY, loadTexture("Resources\\Sprite\\Object\\inventory.png", TRANSPARENCY_COLOUR)));
    m_Resources.emplace(std::pair<RESOURCE, SDL_Texture*>(RSC_WEAPON, loadTexture("Resources\\Sprite\\Object\\weapons.png", TRANSPARENCY_COLOUR)));

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

SDL_Texture* ResourceManager::loadTexture(const std::string& path, uint32_t transparency)
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
        DASSERT(SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, SDL_RED(transparency), SDL_GREEN(transparency), SDL_BLUE(transparency))) == 0, SDL_GetError());

        // Create texture from surface
        newTexture = SDL_CreateTextureFromSurface(Renderer::getInstance().getRenderer(), loadedSurface);
        DASSERT(newTexture != nullptr, SDL_GetError());

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    assert(newTexture != nullptr);

    // Below sets the SDL_TEXTUREACCESS_TARGET access to our texture as we can't set it on a surface it seems
    // So we must copy every texture created from surface to a new one.
    // A limitation of SDL
    int textureWidth,textureHeight;
    DASSERT(SDL_QueryTexture(newTexture, nullptr, nullptr, &textureWidth, &textureHeight) == 0, SDL_GetError());
    auto texture = SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, textureWidth, textureHeight);
    assert(texture != nullptr);
    CopyToTexture(Renderer::getInstance().getRenderer(), newTexture, texture, nullptr, nullptr);
    DASSERT(SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) == 0, SDL_GetError());
    
    return texture;
}