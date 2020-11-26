#include <SDL.h>
#include "ZD_Assert.h"
#include "Drawing.h"

// Some handy drawing functions

// Copies srcTexture to dstTexture using srcRect for srcTexture and dstRect for dstRect
void copyToTexture(SDL_Renderer* renderer, SDL_Texture* srcTexture, SDL_Texture* dstTexture, SDL_Rect* srcRect, SDL_Rect* dstRect)
{
    auto currentRenderingTarget = SDL_GetRenderTarget(renderer);
    ZD_ASSERT(SDL_SetRenderTarget(renderer, dstTexture) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_RenderCopy(renderer, srcTexture, srcRect, dstRect) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_SetRenderTarget(renderer, currentRenderingTarget) == 0, "SDL Error: " << SDL_GetError());
}

// Colours a part of a texture (or whole use nullptr with a given colour 
void colourTexture(SDL_Renderer* renderer, SDL_Texture* srcTexture, SDL_Rect* srcRect, uint32_t colour)
{
    auto currentRenderingTarget = SDL_GetRenderTarget(renderer);
    ZD_ASSERT(SDL_SetRenderTarget(renderer, srcTexture) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_SetRenderDrawColor(renderer, SDL_RED(colour), SDL_GREEN(colour), SDL_BLUE(colour), 0) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_RenderFillRect(renderer, srcRect) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_SetRenderTarget(renderer, currentRenderingTarget) == 0, "SDL Error: " << SDL_GetError());
}

void palleteSwap(SDL_Renderer* renderer, SDL_Texture* srcTexture, const std::vector<std::pair<int, int>>& palletes)
{
    // TODO:
}


