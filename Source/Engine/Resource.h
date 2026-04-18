#pragma once

#include <string>
#include <memory>
#include <SDL_surface.h>

#include "Colour.h"
#include "Renderer.h"

namespace Zelda
{

    class Resource
    {
    public:
        // Load a texture and specify the transparent colour
        static std::unique_ptr<Sprite> loadSprite(const Renderer& renderer, const std::string& path, const Colour transparency);
    
        static SDL_Surface* loadSprite(const std::string& path, const Colour transparency);
    };


}