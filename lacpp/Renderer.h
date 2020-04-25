#ifndef RENDERER_H
#define RENDERER_H

#include "Singleton.h"
#include "Renderable.h"
#include <vector>
#include <set>
#include <functional>
#include <SDL_image.h>
#include <iostream>

// Singleton instance of the renderer for the main window

class Renderer : public Singleton<Renderer>
{
    friend class Singleton<Renderer>;
public:

    void createRenderer(SDL_Window* pWindow)
    {
        m_pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        assert(m_pRenderer != nullptr);
    }

    SDL_Renderer* getRenderer() const
    {
        return m_pRenderer;
    }
    void setRenderer(SDL_Renderer* pRenderer)
    {
        m_pRenderer = pRenderer;
    }

    virtual ~Renderer()
    {
        SDL_DestroyRenderer(m_pRenderer);
    }

    auto getRenderSet() const
    {
        return m_Renderables;
    }

    void addRenderable(Renderable* renderable)
    {
        std::cout << "[Renderer::addRenderable] Adding " << renderable->friendlyName() << " with unique ID: " << renderable->uniqueID() << std::endl;
        m_Renderables.insert(renderable);
    }

    void removeRenderable(Renderable* renderable)
    {

    }

private:
    Renderer()
    {
        m_pRenderer = nullptr;
    }
    // Global renderer
    SDL_Renderer* m_pRenderer;

    struct rendererComparator
    {
        bool operator ()(const Renderable* r1, const Renderable* r2) const
        {
            return r1->getDepth() < r2->getDepth();
        }
    };
  
    // Multiset of Renderable objects that will be drawn
    std::multiset<Renderable*, rendererComparator> m_Renderables;

};


#endif
