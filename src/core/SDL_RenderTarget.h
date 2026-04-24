#pragma once

#include <SDL_render.h>

namespace zelda::engine
{

class RenderTarget
{
public:
    RenderTarget(SDL_Renderer* renderer, SDL_Texture* target);
    ~RenderTarget();

private:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;

};

}