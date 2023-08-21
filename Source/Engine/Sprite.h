#pragma once

#include <SDL_surface.h>
#include <SDL_render.h>
#include <type_traits>
#include <cassert>

#include "SDL_Assert.h"
#include "Rect.h"
#include "Colour.h"


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
        Sprite() = delete;

        Sprite(const Sprite& sprite);
        Sprite& operator=(Sprite sprite);
        Sprite(Sprite&& sprite) noexcept;
        ~Sprite() noexcept;

        int width() const;
        int height() const;
        SDL_Texture* data() const;
        SDL_Renderer* renderer() const;

        // Copies source to dest using srcRect for srcTexture and dstRect for dstRect
        // The dstRect co-ordinates are relative to the srcRect!
        template<typename R1, typename R2>
        static void copySprite(const Sprite& source, const Sprite& dest, const Rect<R1>& srcRect, const Rect<R2>& dstRect, const Colour colourMod = 0)
        {
            assert(dest.m_renderer == source.m_renderer);
            if (dest.m_renderer)
            {
                // Push rendering target
                auto const currentRenderingTarget = SDL_GetRenderTarget(dest.m_renderer);
                SDL_ASSERT(SDL_SetRenderTarget(dest.m_renderer, dest.data()));

                // Check rects within boundaries of sprite if need be
                if (srcRect != Rect<R1>())
                {
                    assert(srcRect.x >= 0 && srcRect.x + srcRect.w <= source.width());
                    assert(srcRect.y >= 0 && srcRect.y + srcRect.h <= source.height());
                }

                auto sdlRectSrc = rectToSDLRect(srcRect);
                auto sdlRectDst = rectToSDLRect(dstRect);

                auto rectSrc = (srcRect != Rect<R1>() ? &sdlRectSrc : nullptr);
                auto rectDst = (dstRect != Rect<R2>() ? &sdlRectDst : nullptr);

                if (colourMod)
                {
                    SDL_ASSERT(SDL_SetTextureColorMod(source.data(), makeRed(colourMod), makeGreen(colourMod), makeBlue(colourMod)));
                }

                SDL_ASSERT(SDL_RenderCopy(dest.m_renderer, source.data(), rectSrc, rectDst));

                // Pop rendering target
                SDL_ASSERT(SDL_SetRenderTarget(dest.m_renderer, currentRenderingTarget));
            }
        }

        // Colours a part of a sprite (or whole use nullptr with a given colour) 
        template<typename R>
        void colourSprite(const Rect<R>& srcRect, Colour colour, const int opacity=255)
        {
            if (m_renderer)
            {
                // Push rendering target
                auto const currentRenderingTarget = SDL_GetRenderTarget(m_renderer);

                SDL_ASSERT(SDL_SetRenderTarget(m_renderer, m_sprite));
                SDL_ASSERT(SDL_SetRenderDrawColor(m_renderer, makeRed(colour), makeGreen(colour), makeBlue(colour), opacity));

                if (srcRect != Rect<R>())
                {
                    // Check srcRect within boundaries of sprite
                    assert(srcRect.x >= 0 && srcRect.x + srcRect.w <= m_width);
                    assert(srcRect.y >= 0 && srcRect.y + srcRect.h <= m_height);

                }

                auto sdlRectSrc = rectToSDLRect(srcRect);
                auto rectSrc = (srcRect != Rect<R>() ? &sdlRectSrc : nullptr);

                SDL_ASSERT(SDL_RenderFillRect(m_renderer, rectSrc));

                // Pop rendering target
                SDL_ASSERT(SDL_SetRenderTarget(m_renderer, currentRenderingTarget));
            }
        }

        // Draw a sprite on screen
        template<typename R1, typename R2>
        void drawSprite(const Rect<R1>& srcRect, const Rect<R2>& dstRect) const
        {
            if (m_renderer)
            {
                assert(m_sprite);

                if (srcRect != Rect<R1>())
                {
                    // Check srcRect within boundaries of sprite
                    assert(srcRect.x >= 0 && srcRect.x + srcRect.w <= m_width);
                    assert(srcRect.y >= 0 && srcRect.y + srcRect.h <= m_height);
                }

                auto sdlRectSrc = rectToSDLRect(srcRect);
                auto sdlRectDst = rectToSDLRect(dstRect);

                auto rectSrc = (srcRect != Rect<R1>() ? &sdlRectSrc : nullptr);
                auto rectDst = (dstRect != Rect<R2>() ? &sdlRectDst : nullptr);

                SDL_ASSERT(SDL_RenderCopy(m_renderer, m_sprite, rectSrc, rectDst));
            }
        }

        template<typename R1, typename R2>
        void drawSpriteEx(const Rect<R1>& srcRect, const Rect<R2>& dstRect, const double angle, SpriteFlip flip) const
        {
            if (m_renderer)
            {
                assert(m_sprite);
                if (srcRect != Rect<R1>())
                {
                    // Check srcRect within boundaries of sprite
                    assert(srcRect.x >= 0 && srcRect.x + srcRect.w <= m_width);
                    assert(srcRect.y >= 0 && srcRect.y + srcRect.h <= m_height);
                }

                auto sdlRectSrc = rectToSDLRect(srcRect);
                auto sdlRectDst = rectToSDLRect(dstRect);

                auto rectSrc = (srcRect != Rect<R1>() ? &sdlRectSrc : nullptr);
                auto rectDst = (dstRect != Rect<R2>() ? &sdlRectDst : nullptr);

                if constexpr (std::is_integral_v<R2>)
                {
                    SDL_ASSERT(SDL_RenderCopyEx(m_renderer, m_sprite, rectSrc, rectDst, angle, nullptr, flipToSDLRendererFlip(flip)));
                }
                else
                {
                    SDL_ASSERT(SDL_RenderCopyExF(m_renderer, m_sprite, rectSrc, rectDst, angle, nullptr, flipToSDLRendererFlip(flip)));
                }
            }
        }

        friend void swap(Sprite& sprite1, Sprite& sprite2);

    private:
        SDL_Renderer* m_renderer;
        SDL_Texture* m_sprite;
        SDL_BlendMode m_blendMode;
        int m_width;
        int m_height;

        static SDL_RendererFlip flipToSDLRendererFlip(SpriteFlip flip);
    };


}