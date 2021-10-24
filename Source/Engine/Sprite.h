#pragma once

#include "SDL_render.h"
#include "ZD_Assert.h"
#include <cassert>

// Wrapper class around an SDL_Texture
namespace Zelda
{

enum /*class*/ SpriteFlip
{
    FLIP_NONE,
    FLIP_HORIZONTAL,
    FLIP_VERTICAL
};


class Sprite
{
public:
    Sprite(SDL_Texture* texture);
    constexpr Sprite();
    SDL_Texture* data() const noexcept;
    Sprite operator=(SDL_Texture* texture) noexcept;
    int width() const noexcept;
    int height() const noexcept;

private:
    SDL_Texture* m_sprite;
    int m_width;
    int m_height;

};


}