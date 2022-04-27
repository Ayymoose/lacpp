#include "Renderer.h"
#include "Colour.h"

// Singleton instance of the renderer for the main window

namespace Zelda
{

void Renderer::createRenderer(const Window& window) noexcept
{
    assert(window.getWindowHandle());
    auto const flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE;
    m_renderer = SDL_CreateRenderer(window.getWindowHandle(), -1, flags);
    assert(m_renderer);
    DEBUG(DBG_INFO, "Renderer created");
}

// TODO: Const all these parameters
void Renderer::clearScreen(int colour) const noexcept
{
    assert(m_renderer);
    SDL_ASSERT(SDL_SetRenderDrawColor(m_renderer, SDL_Red(colour), SDL_Green(colour), SDL_Blue(colour), 0));
    SDL_ASSERT(SDL_RenderClear(m_renderer));
}

void Renderer::renderScreen() const noexcept
{
    assert(m_renderer);
    SDL_RenderPresent(m_renderer);
}

void Renderer::setRendererScale(float scaleX, float scaleY) const noexcept
{
    assert(m_renderer);
    assert(scaleX > 0 && scaleY > 0);
    SDL_ASSERT(SDL_RenderSetScale(m_renderer,scaleX,scaleY));
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
    DEBUG(DBG_INFO, "Renderer destroyed");
}

bool Renderer::inRenderSet(Renderable* renderable) const noexcept
{
    auto iterator = std::find_if(m_renderables.cbegin(), m_renderables.cend(), [renderable](const Renderable* r1)
    {
        return r1 == renderable;
    });
    return iterator != m_renderables.cend();
}

void Renderer::addRenderable(Renderable* renderable) noexcept
{
    assert(renderable);
    if (inRenderSet(renderable))
    {
        assert(false && "Can't add same object to render set");
    }
    else
    {
        m_renderables.emplace(renderable);
    }

}

void Renderer::removeRenderable(Renderable* renderable) noexcept
{
    assert(renderable);
    auto iterator = std::find_if(m_renderables.cbegin(), m_renderables.cend(), [renderable](const Renderable* r1)
    {
        return r1 == renderable;
    });
    if (iterator != m_renderables.cend())
    {
        m_renderables.erase(iterator);
    }
    else
    {
        assert(false && "Trying to remove non-existent renderable");
    }
}

void Renderer::popRenderingTarget(SDL_Texture* srcTexture) const noexcept
{
    assert(m_renderer);
    SDL_ASSERT(SDL_SetRenderTarget(m_renderer, srcTexture));
}


}