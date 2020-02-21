#ifndef RENDERER_H
#define RENDERER_H

#include "Singleton.h"
#include "Renderable.h"
#include <vector>
#include <SDL_image.h>

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

    std::vector<Renderable*> renderableObjects() const
    {
        return m_RenderableObjects;
    }

    void addRenderable(Renderable* renderable)
    {
        m_RenderableObjects.emplace_back(renderable);
    }

    void removeRenderable(Renderable* renderable)
    {
        //TODO: Implement
    }

private:
    Renderer()
    {
        m_pRenderer = nullptr;
    }
    // Global renderer
    SDL_Renderer* m_pRenderer;
    // List of Renderable objects that will be drawn
    std::vector<Renderable*> m_RenderableObjects;
};

#endif
