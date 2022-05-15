#pragma once

#include "SDL_surface.h"
#include "SDL_render.h"
#include "SDL_Assert.h"
#include "Rect.h"
#include "Colour.h"

#include <cassert>
#include <type_traits>

// Wrapper class around an SDL_Texture
namespace Zelda
{

enum class SpriteFlip
{
    FLIP_NONE,
    FLIP_HORIZONTAL,
    FLIP_VERTICAL
};

class Sprite
{
public:
    Sprite(SDL_Renderer* renderer, const int width, const int height);
    Sprite(SDL_Renderer* renderer, SDL_Surface* surface);

    // All Sprites must be tied to a renderer
    Sprite() noexcept = delete;

    Sprite(const Sprite& sprite) noexcept;
    Sprite& operator=(Sprite sprite) noexcept;
    Sprite(Sprite&& sprite) noexcept;
    ~Sprite() noexcept;

    int width() const noexcept;
    int height() const noexcept;
    SDL_Texture* data() const noexcept;
    SDL_Renderer* renderer() const noexcept;

    // Copies srcTexture to dstTexture using srcRect for srcTexture and dstRect for dstRect
    // The dstRect co-ordinates are relative to the srcRect!
    template<typename R1, typename R2>
    static void copySprite(const Sprite& srcTexture, const Sprite& dstTexture, const Rect<R1>& srcRect, const Rect<R2>& dstRect) noexcept
    {
        assert(dstTexture.m_renderer == srcTexture.m_renderer);
        if (dstTexture.m_renderer)
        {
            // Push rendering target
            auto const currentRenderingTarget = SDL_GetRenderTarget(dstTexture.m_renderer);
            SDL_ASSERT(SDL_SetRenderTarget(dstTexture.m_renderer, dstTexture.data()));

            // TODO: Allow use of empty rect to specify whole sprite for copying
            assert(srcRect != Rect<R1>());
            assert(dstRect != Rect<R2>());

            // Check rects within boundaries of sprite
            assert(srcRect.x >= 0 && srcRect.x + srcRect.w <= srcTexture.width());
            assert(srcRect.y >= 0 && srcRect.y + srcRect.h <= srcTexture.height());
            assert(dstRect.x >= 0 && dstRect.x + dstRect.w <= dstTexture.width());
            assert(dstRect.y >= 0 && dstRect.y + dstRect.h <= dstTexture.height());

            auto rectSrc = rectToSDLRect(srcRect);
            auto rectDst = rectToSDLRect(dstRect);

            SDL_ASSERT(SDL_RenderCopy(dstTexture.m_renderer, srcTexture.data(), &rectSrc, &rectDst));

            // Pop rendering target
            SDL_ASSERT(SDL_SetRenderTarget(dstTexture.m_renderer, currentRenderingTarget));
        }
    }

    // Colours a part of a texture (or whole use nullptr with a given colour 
    template<typename R>
    void colourSprite(const Rect<R>& srcRect, Colour colour)
    {
        if (m_renderer)
        {
            // Push rendering target
            auto const currentRenderingTarget = SDL_GetRenderTarget(m_renderer);

            SDL_ASSERT(SDL_SetRenderTarget(m_renderer, m_sprite));
            // TODO: Add parameter here for opacity with default
            SDL_ASSERT(SDL_SetRenderDrawColor(m_renderer, make_red(colour), make_green(colour), make_blue(colour), 255));

            assert(srcRect != Rect<R>());

            // Check srcRect within boundaries of sprite
            assert(srcRect.x >= 0 && srcRect.x + srcRect.w <= m_width);
            assert(srcRect.y >= 0 && srcRect.y + srcRect.h <= m_height);

            auto const rectSrc = rectToSDLRect(srcRect);

            SDL_ASSERT(SDL_RenderFillRect(m_renderer, &rectSrc));

            // Pop rendering target
            SDL_ASSERT(SDL_SetRenderTarget(m_renderer, currentRenderingTarget));
        }
    }

    // Draw a sprite on screen
    template<typename R1, typename R2>
    void drawSprite(const Rect<R1>& srcRect, const Rect<R2>& dstRect) const noexcept
    {
        if (m_renderer)
        {
            assert(m_sprite);
            assert(srcRect != Rect<R1>());
            assert(dstRect != Rect<R2>());

            // Check srcRect within boundaries of sprite
            assert(srcRect.x >= 0 && srcRect.x + srcRect.w <= m_width);
            assert(srcRect.y >= 0 && srcRect.y + srcRect.h <= m_height);

            auto rectSrc = rectToSDLRect(srcRect);
            auto rectDst = rectToSDLRect(dstRect);

            SDL_ASSERT(SDL_RenderCopy(m_renderer, m_sprite, &rectSrc, &rectDst));
        }
    }

    template<typename R1, typename R2>
    void drawSpriteEx(const Rect<R1>& srcRect, const Rect<R2>& dstRect, const double angle, SpriteFlip flip) const noexcept
    {
        if (m_renderer)
        {
            assert(m_sprite);
            assert(srcRect != Rect<R1>());
            assert(dstRect != Rect<R2>());

            // Check srcRect within boundaries of sprite
            assert(srcRect.x >= 0 && srcRect.x + srcRect.w <= m_width);
            assert(srcRect.y >= 0 && srcRect.y + srcRect.h <= m_height);

            auto rectSrc = rectToSDLRect(srcRect);
            auto rectDst = rectToSDLRect(dstRect);

            if constexpr (std::is_integral_v<R2>)
            {
                SDL_ASSERT(SDL_RenderCopyEx(m_renderer, m_sprite, &rectSrc, &rectDst, angle, nullptr, flipToSDLRendererFlip(flip)));
            }
            else
            {
                SDL_ASSERT(SDL_RenderCopyExF(m_renderer, m_sprite, &rectSrc, &rectDst, angle, nullptr, flipToSDLRendererFlip(flip)));
            }
        }
    }

    // TODO: Why is this friend?
    friend void swap(Sprite& sprite1, Sprite& sprite2) noexcept;

private:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_sprite;
    SDL_BlendMode m_blendMode;
    int m_width;
    int m_height;

    static SDL_RendererFlip flipToSDLRendererFlip(SpriteFlip flip) noexcept;
};


}