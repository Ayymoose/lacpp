#include "Renderer.h"
#include "Colour.h"
#include "SDL_Check.h"

#include <algorithm>

// Singleton instance of the renderer for the main window

namespace zelda::engine
{

void Renderer::create(const Window& window)
{
    assert(window.getHandle());
    assert(!m_renderer);
    m_renderer = SDL_CreateRenderer(window.getHandle(),
                                    -1,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    SDL_ASSERT(m_renderer);
}

void Renderer::clearScreen(Colour::colour colour) const
{
    assert(m_renderer);
    SDL_CHECK(SDL_SetRenderDrawColor(m_renderer,
                                     Colour::makeRed(colour),
                                     Colour::makeGreen(colour),
                                     Colour::makeBlue(colour),
                                     0));
    SDL_CHECK(SDL_RenderClear(m_renderer));
}

void Renderer::renderScreen() const
{
    assert(m_renderer);
    SDL_RenderPresent(m_renderer);
}

void Renderer::setRendererScale(float scaleX, float scaleY) const
{
    assert(m_renderer);
    assert(scaleX > 0 && scaleY > 0);
    SDL_CHECK(SDL_RenderSetScale(m_renderer, scaleX, scaleY));
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_CHECK_NO_ERROR();
}

bool Renderer::inRenderSet(Renderable* renderable) const
{
    return std::ranges::find(m_renderables, renderable) != m_renderables.cend();
}

void Renderer::addRenderable(Renderable* renderable)
{
    assert(renderable);
    if (!inRenderSet(renderable))
    {
        m_renderables.emplace(renderable);
    }
}

void Renderer::removeRenderable(Renderable* renderable)
{
    assert(renderable);
    const auto it = std::ranges::find(m_renderables, renderable);
    assert(it != m_renderables.cend() && "Trying to remove non-existent renderable");
    m_renderables.erase(it);
}

} // namespace zelda::engine