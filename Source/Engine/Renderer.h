#pragma once

#include "Singleton.h"
#include "Renderable.h"
#include "Sprite.h"
#include "Debug.h"
#include "Window.h"

#include <set>
#include <SDL_image.h>

// Singleton instance of the renderer for the main window

namespace Zelda
{

class Renderer : public Singleton<Renderer>
{
    friend class Singleton<Renderer>;
public:

    ~Renderer();

    void createRenderer(const Window& window);

    void clearScreen(const Colour colour) const;

    void renderScreen() const;

    void setRendererScale(const float scaleX, const float scaleY) const;

    bool inRenderSet(Renderable* renderable) const;

    void addRenderable(Renderable* renderable);

    void removeRenderable(Renderable* renderable);

    auto getRenderer() const
    {
        assert(m_renderer);
        return m_renderer;
    }

    auto getRenderSet() const
    {
        return m_renderables;
    }

    auto pushRenderingTarget(const Sprite& dstTexture) const
    {
        assert(m_renderer);
        assert(dstTexture.data());
        auto const currentRenderingTarget = SDL_GetRenderTarget(m_renderer);
        SDL_ASSERT(SDL_SetRenderTarget(m_renderer, dstTexture.data()));
        return currentRenderingTarget;
    }

    void popRenderingTarget(SDL_Texture* srcTexture) const;

private:
    Renderer() : m_renderer(nullptr) {}

    // Global renderer
    SDL_Renderer* m_renderer;

    struct RendererComparator
    {
        bool operator ()(const Renderable* r1, const Renderable* r2) const
        {
            return r1->depth() < r2->depth();
        }
    };

    // Multiset of Renderable objects that will be drawn
    std::multiset<Renderable*, RendererComparator> m_renderables;

};
}