#include "Resource.h"
#include "Renderer.h"
#include "Singleton.h"

void ResourceManager::loadGraphics()
{
    // Attempt to load all the graphic resources
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_BACKGROUND_OVERWORLD_MAIN, loadTexture("Resources\\Background\\Overworld\\bck-overworld_main.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_DUNGEON_1_TAIL_CAVE, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_DUNGEON_2_BOTTLE_GROTTO, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_DUNGEON_3_KEY_CAVERN, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_DUNGEON_4_ANGLER_TUNNEL, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_DUNGEON_5_CATFISH_MAW, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_DUNGEON_6_FACE_SHRINE, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_DUNGEON_7_EAGLE_TOWER, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_DUNGEON_8_TURTLE_ROCK, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_DUNGEON_9_COLOUR_DUNGEON, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_DUNGEON_10_WIND_FISH_EGG, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_KANALET_CASTLE, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_DREAM_SHRINE, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_ANCIENT_RUINS, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_MOBLIN_CAVE, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_0, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_1, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_2, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_3, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_4, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_5, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_6, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_7, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_8, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_9, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_10, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_11, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_12, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_13, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_14, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_15, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_16, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_17, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_18, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_19, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_CAVE_20, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_0, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_1, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_2, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_3, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_4, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_5, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_6, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_7, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_8, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_9, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_10, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_11, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_12, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_13, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_14, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_15, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_16, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_17, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_18, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_19, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_20, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_21, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_HOUSE_22, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
    m_Resources.insert(std::pair<RESOURCE, SDL_Texture*>(RSC_INTERIOR_TELEPHONE_HOUSE, loadTexture("Resources\\Background\\Interior\\interior_cave_martha_bay.png")));
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

SDL_Texture* ResourceManager::loadTexture(std::string path)
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
        //  texture from surface pixels

        newTexture = SDL_CreateTextureFromSurface(Renderer::getInstance().getRenderer(), loadedSurface);
        if (newTexture == nullptr)
        {
            fprintf(stderr, "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    assert(newTexture != nullptr);
    return newTexture;
}