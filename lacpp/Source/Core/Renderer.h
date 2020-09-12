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
        m_pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
        assert(m_pRenderer != nullptr);
    }

    SDL_Renderer* getRenderer() const noexcept
    {
        return m_pRenderer;
    }
    void setRenderer(SDL_Renderer* pRenderer) noexcept
    {
        m_pRenderer = pRenderer;
    }

    virtual ~Renderer()
    {
        SDL_DestroyRenderer(m_pRenderer);
    }

    auto getRenderSet() const noexcept
    {
        return m_Renderables;
    }

    void addRenderable(Renderable* renderable) noexcept
    {
        m_Renderables.emplace(renderable);
    }

    void removeRenderable(Renderable* renderable) noexcept
    {
        auto iterator = std::find_if(m_Renderables.begin(), m_Renderables.end(), [renderable](const Renderable* r1) { return r1 == renderable; });
        if (iterator != m_Renderables.end())
        {
            std::cout << "[removeRenderable] Removing " << (*iterator)->friendlyName() << std::endl;
            m_Renderables.erase(iterator);
        }
        else
        {
            assert(false);
        }
    }

private:
    Renderer() : m_pRenderer(nullptr) {}
    // Global renderer
    SDL_Renderer* m_pRenderer;

    struct rendererComparator
    {
        bool operator ()(const Renderable* r1, const Renderable* r2) const noexcept
        {
            return r1->depth() < r2->depth();
        }
    };
  
    // Multiset of Renderable objects that will be drawn
    std::multiset<Renderable*, rendererComparator> m_Renderables;

};