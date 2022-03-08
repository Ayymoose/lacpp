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

    ~Renderer();

    void createRenderer(const Window& window) noexcept;

    void clearScreen(int colour) const noexcept;

    void renderScreen() const noexcept;

    void setRendererScale(float scaleX, float scaleY) const noexcept;

    bool inRenderSet(Renderable* renderable) const noexcept;

    void addRenderable(Renderable* renderable) noexcept;

    void removeRenderable(Renderable* renderable) noexcept;

    auto getRenderer() const noexcept
    {
        assert(m_renderer);
        return m_renderer;
    }

    auto getRenderSet() const noexcept
    {
        return m_renderables;
    }

    auto pushRenderingTarget(const Sprite& dstTexture) const noexcept
    {
        assert(m_renderer);
        assert(dstTexture.data());
        auto const currentRenderingTarget = SDL_GetRenderTarget(m_renderer);
        SDL_ASSERT(SDL_SetRenderTarget(m_renderer, dstTexture.data()));
        return currentRenderingTarget;
    }

    void popRenderingTarget(SDL_Texture* srcTexture) const noexcept;

private:
    Renderer() : m_renderer(nullptr) {}

    // Global renderer
    SDL_Renderer* m_renderer;

    struct RendererComparator
    {
        bool operator ()(const Renderable* r1, const Renderable* r2) const noexcept
        {
            return r1->depth() < r2->depth();
        }
    };

    // Multiset of Renderable objects that will be drawn
    std::multiset<Renderable*, RendererComparator> m_renderables;

};
}