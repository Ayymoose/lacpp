
#include "Drawing.h"

// Some handy drawing functions

namespace Zelda
{

// NOT RECOMMENDED FOR TIGHT LOOPS AS PUSHING AND POPPING OFF THE RENDERING TARGET INCURS A PERFORMANCE PENALTY!
// Copies srcTexture to dstTexture using srcRect for srcTexture and dstRect for dstRect
void copyToTexture(SDL_Renderer* renderer, SDL_Texture* srcTexture, SDL_Texture* dstTexture, SDL_Rect* srcRect, SDL_Rect* dstRect)
{
    // Push rendering target
    auto currentRenderingTarget = SDL_GetRenderTarget(renderer);
    SDL_ASSERT(SDL_SetRenderTarget(renderer, dstTexture), SDL_ERROR_MESSAGE);

    SDL_ASSERT(SDL_RenderCopy(renderer, srcTexture, srcRect, dstRect), SDL_ERROR_MESSAGE);
    // Pop rendering target
    SDL_ASSERT(SDL_SetRenderTarget(renderer, currentRenderingTarget), SDL_ERROR_MESSAGE);
}

// Colours a part of a texture (or whole use nullptr with a given colour 
void colourTexture(SDL_Renderer* renderer, SDL_Texture* srcTexture, SDL_Rect* srcRect, uint32_t colour)
{
    auto currentRenderingTarget = SDL_GetRenderTarget(renderer);
    SDL_ASSERT(SDL_SetRenderTarget(renderer, srcTexture), SDL_ERROR_MESSAGE);
    SDL_ASSERT(SDL_SetRenderDrawColor(renderer, SDL_RED(colour), SDL_GREEN(colour), SDL_BLUE(colour), 0), SDL_ERROR_MESSAGE);
    SDL_ASSERT(SDL_RenderFillRect(renderer, srcRect), SDL_ERROR_MESSAGE);
    SDL_ASSERT(SDL_SetRenderTarget(renderer, currentRenderingTarget), SDL_ERROR_MESSAGE);
}

SDL_Texture* pushRenderingTarget(SDL_Renderer* renderer, SDL_Texture* dstTexture)
{
    auto currentRenderingTarget = SDL_GetRenderTarget(renderer);
    SDL_ASSERT(SDL_SetRenderTarget(renderer, dstTexture), SDL_ERROR_MESSAGE);
    return currentRenderingTarget;
}

void popRenderingTarget(SDL_Renderer* renderer, SDL_Texture* srcTexture)
{
    SDL_ASSERT(SDL_SetRenderTarget(renderer, srcTexture), SDL_ERROR_MESSAGE);
}

}