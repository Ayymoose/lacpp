#pragma once

#include <SDL_surface.h>
#include <SDL_render.h>
#include <concepts>
#include <cassert>

#include "SDL_Assert.h"
#include "Rect.h"
#include "Colour.h"

namespace zelda::engine
{

class Sprite final
{
public:
    enum class Flip
    {
        NONE,
        HORIZONTAL,
        VERTICAL
    };

    Sprite(SDL_Renderer* renderer, int width, int height);
    Sprite(SDL_Renderer* renderer, SDL_Surface* surface);

    // All Sprites must be tied to a renderer
    Sprite() = delete;

    Sprite(const Sprite& sprite);
    Sprite& operator=(const Sprite& sprite);
    Sprite(Sprite&& sprite) noexcept;
    Sprite& operator=(Sprite&& sprite) noexcept;
    ~Sprite() noexcept;

    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;
    [[nodiscard]] SDL_Texture* data() const;
    [[nodiscard]] SDL_Renderer* renderer() const;

    // Copies source to dest using srcRect for srcTexture and dstRect for dstRect.
    // The dstRect co-ordinates are relative to the srcRect.
    template <typename R1, typename R2>
    static void copy(const Sprite& source, const Sprite& dest, const Rect<R1>& srcRect, const Rect<R2>& dstRect,
                     const Colour colourMod = 0)
    {
        assert(dest.m_renderer == source.m_renderer);
        if (dest.m_renderer)
        {
            const auto currentRenderingTarget = SDL_GetRenderTarget(dest.m_renderer);
            SDL_ASSERT(SDL_SetRenderTarget(dest.m_renderer, dest.data()));

            assert(srcRect.x >= 0 && srcRect.x + srcRect.w <= source.width());
            assert(srcRect.y >= 0 && srcRect.y + srcRect.h <= source.height());

            auto sdlRectSrc = rectToSDLRect(srcRect);
            auto sdlRectDst = rectToSDLRect(dstRect);

            auto rectSrc = (srcRect != Rect<R1>() ? &sdlRectSrc : nullptr);
            auto rectDst = (dstRect != Rect<R2>() ? &sdlRectDst : nullptr);

            if (colourMod)
            {
                SDL_ASSERT(SDL_SetTextureColorMod(source.data(),
                                                  makeRed(colourMod),
                                                  makeGreen(colourMod),
                                                  makeBlue(colourMod)));
            }

            SDL_ASSERT(SDL_RenderCopy(dest.m_renderer, source.data(), rectSrc, rectDst));

            SDL_ASSERT(SDL_SetRenderTarget(dest.m_renderer, currentRenderingTarget));
        }
    }

    // Colours a part of a sprite (or whole use nullptr) with a given colour
    template <typename R>
    void colour(const Rect<R>& srcRect, Colour colour, const int opacity = 255)
    {
        if (m_renderer)
        {
            const auto currentRenderingTarget = SDL_GetRenderTarget(m_renderer);

            SDL_ASSERT(SDL_SetRenderTarget(m_renderer, m_sprite));
            SDL_ASSERT(
                SDL_SetRenderDrawColor(m_renderer, makeRed(colour), makeGreen(colour), makeBlue(colour), opacity));

            assert(srcRect.x >= 0 && srcRect.x + srcRect.w <= m_width);
            assert(srcRect.y >= 0 && srcRect.y + srcRect.h <= m_height);

            auto sdlRectSrc = rectToSDLRect(srcRect);
            auto rectSrc = (srcRect != Rect<R>() ? &sdlRectSrc : nullptr);

            SDL_ASSERT(SDL_RenderFillRect(m_renderer, rectSrc));

            SDL_ASSERT(SDL_SetRenderTarget(m_renderer, currentRenderingTarget));
        }
    }

    // Draw a sprite on screen
    template <typename R1, typename R2>
    void draw(const Rect<R1>& srcRect, const Rect<R2>& dstRect, double angle = 0, Flip flip = Flip::NONE) const
    {
        if (m_renderer)
        {
            assert(m_sprite);

            assert(srcRect.x >= 0 && static_cast<long long>(srcRect.x + srcRect.w) <= static_cast<long long>(m_width));
            assert(srcRect.y >= 0 && static_cast<long long>(srcRect.y + srcRect.h) <= static_cast<long long>(m_height));

            auto sdlRectSrc = rectToSDLRect(srcRect);
            auto sdlRectDst = rectToSDLRect(dstRect);

            auto rectSrc = (srcRect != Rect<R1>() ? &sdlRectSrc : nullptr);
            auto rectDst = (dstRect != Rect<R2>() ? &sdlRectDst : nullptr);

            if constexpr (std::integral<R2>)
            {
                SDL_ASSERT(SDL_RenderCopyEx(m_renderer,
                                            m_sprite,
                                            rectSrc,
                                            rectDst,
                                            angle,
                                            nullptr,
                                            flipToSDLRendererFlip(flip)));
            }
            else
            {
                SDL_ASSERT(SDL_RenderCopyExF(m_renderer,
                                             m_sprite,
                                             rectSrc,
                                             rectDst,
                                             angle,
                                             nullptr,
                                             flipToSDLRendererFlip(flip)));
            }
        }
    }

    friend void swap(Sprite& sprite1, Sprite& sprite2) noexcept;

private:
    SDL_Renderer* m_renderer = nullptr;
    SDL_Texture* m_sprite = nullptr;
    SDL_BlendMode m_blendMode = SDL_BLENDMODE_NONE;
    int m_width = 0;
    int m_height = 0;

    static SDL_RendererFlip flipToSDLRendererFlip(Flip flip);
};


} // namespace zelda::engine
