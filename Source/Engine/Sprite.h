#pragma once

#include "SDL_render.h"
#include "ZD_Assert.h"
#include <cassert>
#include "Rect.h"

// Wrapper class around an SDL_Texture
namespace Zelda
{

//     b        g        r 
// 00000000 00000000 00000000 
#define SDL_RGB(r,g,b) ((r) | ((g) << 8) | ((b) << 16))
#define SDL_RED(colour) ((colour) & 0x0000FF)
#define SDL_GREEN(colour) (((colour) >> 8) & 0x0000FF)
#define SDL_BLUE(colour) (((colour) >> 16) & 0x0000FF)

enum class SpriteFlip
{
    FLIP_NONE,
    FLIP_HORIZONTAL,
    FLIP_VERTICAL
};


class Sprite
{
public:
    Sprite(SDL_Texture* texture);
    constexpr Sprite() : m_sprite(nullptr), m_width(0), m_height(0)
    {
    }

    Sprite(SDL_Renderer* renderer, int width, int height);
    
    SDL_Texture* data() const noexcept;
    Sprite& operator=(SDL_Texture* texture) noexcept;

    int width() const noexcept;
    int height() const noexcept;
    void free() noexcept;

    // Copies srcTexture to dstTexture using srcRect for srcTexture and dstRect for dstRect
    // The dstRect co-ordinates are relative to the srcRect!
    template<typename R1, typename R2>
    static void copySprite(SDL_Renderer* renderer, const Sprite& srcTexture, const Sprite& dstTexture, const Rect<R1>& srcRect, const Rect<R2>& dstRect) noexcept
    {
        // Push rendering target
        auto const currentRenderingTarget = SDL_GetRenderTarget(renderer);
        SDL_ASSERT(SDL_SetRenderTarget(renderer, dstTexture.data()), SDL_ERROR_MESSAGE);

        assert(srcRect != Rect<R1>());
        assert(dstRect != Rect<R2>());
        auto rectSrc = rectToSDLRect(srcRect);
        auto rectDst = rectToSDLRect(dstRect);
        SDL_ASSERT(SDL_RenderCopy(renderer, srcTexture.data(), &rectSrc, &rectDst), SDL_ERROR_MESSAGE);

        // Pop rendering target
        SDL_ASSERT(SDL_SetRenderTarget(renderer, currentRenderingTarget), SDL_ERROR_MESSAGE);
    }

    // Colours a part of a texture (or whole use nullptr with a given colour 
    template<typename R>
    static void colourSprite(SDL_Renderer* renderer, const Sprite& srcTexture, const Rect<R>& srcRect, uint32_t colour)
    {
        // Push rendering target
        auto const currentRenderingTarget = SDL_GetRenderTarget(renderer);

        SDL_ASSERT(SDL_SetRenderTarget(renderer, srcTexture.data()), SDL_ERROR_MESSAGE);
        SDL_ASSERT(SDL_SetRenderDrawColor(renderer, SDL_RED(colour), SDL_GREEN(colour), SDL_BLUE(colour), 0), SDL_ERROR_MESSAGE);

        // assert rect boundaries
        assert(srcRect != Rect<R>());
        auto const rectSrc = rectToSDLRect(srcRect);

        SDL_ASSERT(SDL_RenderFillRect(renderer, &rectSrc), SDL_ERROR_MESSAGE);

        // Pop rendering target
        SDL_ASSERT(SDL_SetRenderTarget(renderer, currentRenderingTarget), SDL_ERROR_MESSAGE);
    }

    // Draw a sprite on screen
    template<typename R1, typename R2>
    void drawSprite(SDL_Renderer* renderer, const Rect<R1>& srcRect, const Rect<R2>& dstRect) const noexcept
    {
        assert(m_sprite);
        assert(srcRect != Rect<R1>());
        assert(dstRect != Rect<R2>());

        auto rectSrc = rectToSDLRect(srcRect);
        auto rectDst = rectToSDLRect(dstRect);

        SDL_ASSERT(SDL_RenderCopy(renderer, m_sprite, &rectSrc, &rectDst), SDL_ERROR_MESSAGE);
    }

    template<typename R1, typename R2>
    void drawSpriteEx(SDL_Renderer* renderer, const Rect<R1>& srcRect, const Rect<R2>& dstRect, double angle, SpriteFlip flip) const noexcept
    {
        assert(m_sprite);
        assert(srcRect != Rect<R1>());
        assert(dstRect != Rect<R2>());

        auto rectSrc = rectToSDLRect(srcRect);
        auto rectDst = rectToSDLRect(dstRect);

        SDL_ASSERT(SDL_RenderCopyEx(renderer, m_sprite, &rectSrc, &rectDst, angle, nullptr, flipToSDLRendererFlip(flip)), SDL_ERROR_MESSAGE);
    }

private:
    SDL_Texture* m_sprite;
    int m_width;
    int m_height;

    static SDL_RendererFlip flipToSDLRendererFlip(SpriteFlip flip) noexcept;

};


}