#pragma once

#include "Singleton.h"
#include "IRenderable.h"
#include "Sprite.h"
#include "Logger.h"
#include "Window.h"

#include <set>
#include <SDL_image.h>

// Singleton instance of the renderer for the main window

namespace zelda::engine
{

class Renderer : public Singleton<Renderer>
{
public:
    Renderer()
        : m_renderer(nullptr)
    {}
    ~Renderer();

    void createRenderer(const Window& window);

    void clearScreen(const Colour colour) const;

    void renderScreen() const;

    void setRendererScale(const float scaleX, const float scaleY) const;

    bool inRenderSet(IRenderable* renderable) const;

    void addRenderable(IRenderable* renderable);

    void removeRenderable(IRenderable* renderable);

    auto getRenderer() const
    {
        assert(m_renderer);
        return m_renderer;
    }

    auto getRenderSet() const { return m_renderables; }

private:
    // Global renderer
    SDL_Renderer* m_renderer;

    struct RendererComparator
    {
        bool operator()(const IRenderable* r1, const IRenderable* r2) const { return r1->depth() < r2->depth(); }
    };

    // Multiset of Renderable objects that will be drawn
    std::multiset<IRenderable*, RendererComparator> m_renderables;
};
} // namespace zelda::engine