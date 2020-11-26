#pragma once

#include <SDL_image.h>
#include "ZD_Assert.h"

struct Rectangle
{
    Rectangle(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
    int x;
    int y;
    int w;
    int h;
};

inline void createTileMapUniqueFromImage(const char* fileName, int startX, int startY, int spaceX, int spaceY, Rectangle tile)
{
   /*   Load an image (PNG)
        For each square on the image, hash it and store in map along with co - ordinates
        Discard all duplicates
        Create a new image
        Go through map and for each entry, copy the rect onto the image
        Save final image
        */

    // Need to be able to read parts of a texture/surface
    // And save parts to file
    
    SDL_Surface* surface = IMG_Load(fileName);
    ZD_ASSERT(surface != nullptr, "IMG Error: " << IMG_GetError());

    std::cout << "Loaded: " << fileName << '\n';
    std::cout << "Image width: " << surface->w << '\n';
    std::cout << "Image height: " << surface->h << '\n';

    std::string outputFile = R"(D:\Users\Ayman\Desktop\lacpp\lacpp\Resources\Test\output)";

    int tilesAcross = (surface->w - startX) / (tile.w + spaceX);
    int tilesDown = (surface->h - startY) / (tile.h + spaceY);
    int tileIndex = 0;
    for (int y = 0; y < tilesDown; y++)
    {
        for (int x = 0; x < tilesAcross; x++)
        {
            // Calculate new address of tile
            char* pixelAddress = static_cast<char*>(surface->pixels);

            // 3 bytes per pixel it seems
            pixelAddress += (3 * (startX + (x * (tile.w + spaceX)))) + ((y * (tile.h + spaceY) + startY) * surface->pitch);

            auto newSurface = SDL_CreateRGBSurfaceWithFormatFrom((void*)pixelAddress, tile.w, tile.h, 32, surface->pitch, surface->format->format);
            ZD_ASSERT(newSurface != nullptr, "SDL Error: " << SDL_GetError());
            ZD_ASSERT(IMG_SavePNG(newSurface, (outputFile + "." + std::to_string(tileIndex++) + ".png").c_str()) == 0, "SDL Error: " << SDL_GetError());

            SDL_FreeSurface(newSurface);
        }
    }
    SDL_FreeSurface(surface);
}

// Save texture to file
/*inline void saveTexture(const char* file_name, SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_Texture* target = SDL_GetRenderTarget(renderer);
    ZD_ASSERT(SDL_SetRenderTarget(renderer, texture) == 0, "SDL Error: " << SDL_GetError());
    int width, height;
    ZD_ASSERT(SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) == 0, "SDL Error: " << SDL_GetError());
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    ZD_ASSERT(surface != nullptr, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_RenderReadPixels(renderer, nullptr, surface->format->format, surface->pixels, surface->pitch) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(IMG_SavePNG(surface, file_name) == 0, "SDL Error: " << SDL_GetError());
    SDL_FreeSurface(surface);
    ZD_ASSERT(SDL_SetRenderTarget(renderer, target) == 0, "SDL Error: " << SDL_GetError());
}*/