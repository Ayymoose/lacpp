#pragma once

#include "Singleton.h"
#include "Renderable.h"
#include <set>
#include <SDL_image.h>
#include "Sprite.h"

// Singleton instance of the renderer for the main window

namespace Zelda
{

class Renderer : public Singleton<Renderer>
{
    friend class Singleton<Renderer>;
public:

    void createRenderer(SDL_Window* window) noexcept
    {
        assert(window);

        auto const flags = SDL_RENDERER_ACCELERATED |
            SDL_RENDERER_PRESENTVSYNC |
            SDL_RENDERER_TARGETTEXTURE;
        m_renderer = SDL_CreateRenderer(window, -1, flags);
        assert(m_renderer);
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

    virtual ~Renderer()
    {
        SDL_DestroyRenderer(m_renderer);
    }

    auto getRenderSet() const noexcept
    {
        return m_renderables;
    }

    void addRenderable(Renderable* renderable) noexcept
    {
        assert(renderable);
        auto iterator = std::find_if(m_renderables.begin(), m_renderables.end(), [renderable](const Renderable* r1)
        {
            return r1 == renderable;
        });

        if (iterator != m_renderables.end())
        {
            // No adding the same object to the render set
            assert(false && "Can't add same object to render set");
        }
        //std::cout << "Adding renderable " << renderable->name() << std::endl;
        m_renderables.emplace(renderable);
    }

    void removeRenderable(Renderable* renderable) noexcept
    {
        assert(renderable);
        auto iterator = std::find_if(m_renderables.begin(), m_renderables.end(), [renderable](const Renderable* r1)
        {
            return r1 == renderable;
        });
        if (iterator != m_renderables.end())
        {
            //std::cout << "Removing renderable " << (*iterator)->name() << std::endl;
            m_renderables.erase(iterator);
        }
        else
        {
            // Attempting to remove something that wasn't in the renderable set
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

    void popRenderingTarget(SDL_Texture* srcTexture)  const noexcept
    {
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