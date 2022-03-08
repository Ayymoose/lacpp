#pragma once

#include <string>
#include "Sprite.h"
#include "Colour.h"
#include <cassert>
#include <SDL_image.h>
#include "Renderer.h"
#include "SDL_Assert.h"

namespace Zelda
{

class Resource
{
public:
    // Load a texture and specify the transparent colour
    static Sprite loadSprite(const Renderer& renderer, const std::string& path, Colour transparency) noexcept;
};


}