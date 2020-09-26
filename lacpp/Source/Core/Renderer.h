#pragma once

#include "Singleton.h"
#include "Renderable.h"
#include <vector>
#include <set>
#include <functional>
#include <SDL_image.h>
#include <iostream>
#include <algorithm>

// Singleton instance of the renderer for the main window

class Renderer : public Singleton<Renderer>
{
    friend class Singleton<Renderer>;
public:

    void createRenderer(SDL_Window* pWindow) noexcept
    {
        m_renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
        assert(m_renderer != nullptr);
    }

    SDL_Renderer* getRenderer() const noexcept
    {
        return m_renderer;
    }
    void setRenderer(SDL_Renderer* pRenderer) noexcept
    {
        m_renderer = pRenderer;
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
        m_renderables.emplace(renderable);
    }

    void removeRenderable(Renderable* renderable) noexcept
    {
        auto iterator = std::find_if(m_renderables.begin(), m_renderables.end(), [renderable](const Renderable* r1) { return r1 == renderable; });
        if (iterator != m_renderables.end())
        {
            std::cout << "Removing renderable " << (*iterator)->name() << std::endl;
            m_renderables.erase(iterator);
        }
        else
        {
            // Attempting to remove something that wasn't in the renderable set
            assert(false);
        }
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