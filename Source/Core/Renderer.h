#pragma once

#include "Singleton.h"
#include "Renderable.h"
#include <set>
#include <SDL_image.h>
#include "Sprite.h"
#include "Debug.h"
#include "Window.h"

// Singleton instance of the renderer for the main window

namespace Zelda
{

class Renderer : public Singleton<Renderer>
{
    friend class Singleton<Renderer>;
public:

    void createRenderer(const Window& window) noexcept
    {
        assert(window.getWindowHandle());
        auto const flags = SDL_RENDERER_ACCELERATED |
            SDL_RENDERER_PRESENTVSYNC |
            SDL_RENDERER_TARGETTEXTURE;
        m_renderer = SDL_CreateRenderer(window.getWindowHandle(), -1, flags);
        assert(m_renderer);
        DEBUG(DBG_INFO, "Renderer created");
    }

    auto getRenderer() const noexcept
    {
        assert(m_renderer);
        return m_renderer;
    }
    void setRenderer(SDL_Renderer* renderer) noexcept
    {
        assert(renderer);
        m_renderer = renderer;
    }

    void clearScreen(int colour) const noexcept
    {
        assert(m_renderer);
        SDL_ASSERT(SDL_SetRenderDrawColor(m_renderer, SDL_RED(colour), SDL_GREEN(colour), SDL_BLUE(colour), 0), SDL_ERROR_MESSAGE);
        SDL_ASSERT(SDL_RenderClear(m_renderer), SDL_ERROR_MESSAGE);
    }

    void renderScreen() const noexcept
    {
        assert(m_renderer);
        // Represent to the screen
        SDL_RenderPresent(m_renderer);
    }

    void setRendererScale(float scaleX, float scaleY) const noexcept
    {
        assert(m_renderer);
        SDL_ASSERT(SDL_RenderSetScale(m_renderer,scaleX,scaleY), SDL_ERROR_MESSAGE);
    }

    virtual ~Renderer()
    {
        SDL_DestroyRenderer(m_renderer);
        DEBUG(DBG_INFO, "Renderer destroyed");
    }

    auto getRenderSet() const noexcept
    {
        return m_renderables;
    }

    bool inRenderSet(Renderable* renderable) const noexcept
    {
        auto iterator = std::find_if(m_renderables.cbegin(), m_renderables.cend(), [renderable](const Renderable* r1)
        {
            return r1 == renderable;
        });
        return iterator != m_renderables.cend();
    }

    void addRenderable(Renderable* renderable) noexcept
    {
        assert(renderable);
        if (inRenderSet(renderable))
        {
            assert(false && "Can't add same object to render set");
        }
        else
        {
            //std::cout << "Adding renderable " << renderable->name() << std::endl;
            m_renderables.emplace(renderable);
        }

    }

    void removeRenderable(Renderable* renderable) noexcept
    {
        assert(renderable);
        auto iterator = std::find_if(m_renderables.cbegin(), m_renderables.cend(), [renderable](const Renderable* r1)
        {
            return r1 == renderable;
        });
        if (iterator != m_renderables.cend())
        {
            //std::cout << "Removing renderable " << (*iterator)->name() << std::endl;
            m_renderables.erase(iterator);
        }
        else
        {
            assert(false && "Trying to remove non-existent renderable");
        }
    }

    SDL_Texture* pushRenderingTarget(const Sprite& dstTexture) const noexcept
    {
        assert(m_renderer);
        auto const currentRenderingTarget = SDL_GetRenderTarget(m_renderer);
        SDL_ASSERT(SDL_SetRenderTarget(m_renderer, dstTexture.data()), SDL_ERROR_MESSAGE);
        return currentRenderingTarget;
    }

    void popRenderingTarget(SDL_Texture* srcTexture) const noexcept
    {
        //auto const currentRenderingTarget = SDL_GetRenderTarget(m_renderer);
       
        assert(m_renderer);
        SDL_ASSERT(SDL_SetRenderTarget(m_renderer, srcTexture), SDL_ERROR_MESSAGE);
    }

private:
    Renderer() : m_renderer(nullptr)
    {

    }
    // Global renderer
    SDL_Renderer* m_renderer;

    struct rendererComparator
    {
        bool operator ()(const Renderable* r1, const Renderable* r2) const noexcept
        {
            return r1->depth() < r2->depth();
        }
    };

    // Multiset of Renderable objects that will be drawn
    std::multiset<Renderable*, rendererComparator> m_renderables;

};
}