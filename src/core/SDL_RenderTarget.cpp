#include "SDL_RenderTarget.h"
#include "SDL_Check.h"

namespace zelda::engine
{

RenderTarget::RenderTarget(SDL_Renderer* renderer, SDL_Texture* target)
    : m_renderer(renderer)
    , m_texture(SDL_GetRenderTarget(renderer))
{
    SDL_CHECK(SDL_SetRenderTarget(m_renderer, target));
}

RenderTarget::~RenderTarget()
{
    SDL_CHECK(SDL_SetRenderTarget(m_renderer, m_texture));
}

} // namespace zelda::engine