#pragma once

#include "Singleton.h"
#include "Renderable.h"
#include "Sprite.h"
#include "Window.h"

#include <set>

// Singleton instance of the renderer for the main window

namespace zelda::engine
{

class Renderer : public Singleton<Renderer>
{
public:
    Renderer() = default;

    ~Renderer();

    void create(const Window& window);

    void clearScreen(Colour::colour colour) const;

    void renderScreen() const;

    void setRendererScale(float scaleX, float scaleY) const;

    [[nodiscard]] bool inRenderSet(Renderable* renderable) const;

    void addRenderable(Renderable* renderable);

    void removeRenderable(Renderable* renderable);

    [[nodiscard]] SDL_Renderer* getRenderer() const
    {
        assert(m_renderer);
        return m_renderer;
    }

    [[nodiscard]] auto getRenderSet() const { return m_renderables; }

private:
    // Global renderer
    SDL_Renderer* m_renderer = nullptr;

    struct RendererComparator
    {
        bool operator()(const Renderable* r1, const Renderable* r2) const { return r1->depth() < r2->depth(); }
    };

    // Multiset of Renderable objects that will be drawn
    std::multiset<Renderable*, RendererComparator> m_renderables;
};
} // namespace zelda::engine