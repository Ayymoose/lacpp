#include <SDL.h>
#include "ZD_Assert.h"
#include "Drawing.h"

// Some handy drawing functions

// Copies srcTexture to dstTexture using srcRect for srcTexture and dstRect for dstRect
void CopyToTexture(SDL_Renderer* pRenderer, SDL_Texture* srcTexture, SDL_Texture* dstTexture, SDL_Rect* srcRect, SDL_Rect* dstRect)
{
    auto currentRenderingTarget = SDL_GetRenderTarget(pRenderer);
    ZD_ASSERT(SDL_SetRenderTarget(pRenderer, dstTexture) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_RenderCopy(pRenderer, srcTexture, srcRect, dstRect) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_SetRenderTarget(pRenderer, currentRenderingTarget) == 0, "SDL Error: " << SDL_GetError());
}

// Colours a part of a texture (or whole use nullptr with a given colour 
void ColourTexture(SDL_Renderer* pRenderer, SDL_Texture* srcTexture, SDL_Rect* srcRect, uint32_t colour)
{
    auto currentRenderingTarget = SDL_GetRenderTarget(pRenderer);
    ZD_ASSERT(SDL_SetRenderTarget(pRenderer, srcTexture) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_SetRenderDrawColor(pRenderer, SDL_RED(colour), SDL_GREEN(colour), SDL_BLUE(colour), 0) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_RenderFillRect(pRenderer, srcRect) == 0, "SDL Error: " << SDL_GetError());
    ZD_ASSERT(SDL_SetRenderTarget(pRenderer, currentRenderingTarget) == 0, "SDL Error: " << SDL_GetError());
}

void PalleteSwap(SDL_Renderer* pRenderer, SDL_Texture* srcTexture, const std::vector<std::pair<int, int>>& palletes)
{
    // TODO:
}


