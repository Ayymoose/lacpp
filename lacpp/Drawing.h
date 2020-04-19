#ifndef DRAWING_H
#define DRAWING_H

#include <SDL.h>

// Some handy drawing functions
//     b        g        r 
// 00000000 00000000 00000000 
#define SDL_RGB(r,g,b) ((r) | (g << 8) | (b << 16))
#define SDL_RED(colour) (colour & 0x0000FF)
#define SDL_GREEN(colour) ((colour >> 8) & 0x0000FF)
#define SDL_BLUE(colour) ((colour >> 16) & 0x0000FF)

// Copies srcTexture to dstTexture using srcRect for srcTexture and dstRect for dstRect
void CopyToTexture(SDL_Renderer* pRenderer, SDL_Texture* srcTexture, SDL_Texture* dstTexture, SDL_Rect* srcRect, SDL_Rect* dstRect)
{
    assert(SDL_SetRenderTarget(pRenderer, dstTexture) == 0);
    assert(SDL_RenderCopy(pRenderer, srcTexture, srcRect, dstRect) == 0);
    assert(SDL_SetRenderTarget(pRenderer, nullptr) == 0);
}

// Colours a part of a texture (or whole use nullptr with a given colour 
void ColourTexture(SDL_Renderer* pRenderer, SDL_Texture* srcTexture, SDL_Rect* srcRect, uint32_t colour)
{
    assert(SDL_SetRenderTarget(pRenderer, srcTexture) == 0);
    assert(SDL_SetRenderDrawColor(pRenderer, SDL_RED(colour), SDL_GREEN(colour), SDL_BLUE(colour), 0) == 0);
    assert(SDL_RenderFillRect(pRenderer, srcRect) == 0);
    assert(SDL_SetRenderTarget(pRenderer, nullptr) == 0);
}




#endif // !DRAWING_H
