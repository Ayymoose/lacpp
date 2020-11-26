#pragma once

#include <SDL.h>
#include "Assert.h"
#include <vector>
#include <utility>

//     b        g        r 
// 00000000 00000000 00000000 
#define SDL_RGB(r,g,b) ((r) | (g << 8) | (b << 16))
#define SDL_RED(colour) (colour & 0x0000FF)
#define SDL_GREEN(colour) ((colour >> 8) & 0x0000FF)
#define SDL_BLUE(colour) ((colour >> 16) & 0x0000FF)

// Copies srcTexture to dstTexture using srcRect for srcTexture and dstRect for dstRect
// The dstRect co-ordinates are relative to the srcRect!
void copyToTexture(SDL_Renderer* renderer, SDL_Texture* srcTexture, SDL_Texture* dstTexture, SDL_Rect* srcRect, SDL_Rect* dstRect);

// Colours a part of a texture (or whole use nullptr for srcRect with a given colour)
void colourTexture(SDL_Renderer* renderer, SDL_Texture* srcTexture, SDL_Rect* srcRect, uint32_t colour);

void palleteSwap(SDL_Renderer* renderer, SDL_Texture* srcTexture, const std::vector<std::pair<int,int>>& palletes);