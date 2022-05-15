#pragma once

#include <cstring>

#include "Sprite.h"

// Wrapper class around an SDL_Texture
namespace Zelda
{

Sprite::Sprite(SDL_Renderer* renderer, const int width, const int height)
{
    m_width = width;
    m_height = height;
    m_renderer = renderer;
    m_blendMode = SDL_BLENDMODE_NONE;
    
    if (m_renderer)
    {
        assert(m_width);
        assert(m_height);
        m_sprite = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, m_width, m_height);
        assert(m_sprite);
        SDL_ASSERT(SDL_SetTextureBlendMode(m_sprite, m_blendMode));
    }
    else
    {
        assert(!m_width);
        assert(!m_height);
        m_sprite = nullptr;
    }
}

Sprite::Sprite(SDL_Renderer* renderer, SDL_Surface* surface)
{
    assert(renderer);
    m_renderer = renderer;
    assert(surface);

    // Create a new texture from this surface
    auto const textureCreatedFromSurface = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);

    // Query dimensions
    SDL_ASSERT(SDL_QueryTexture(textureCreatedFromSurface, nullptr, nullptr, &m_width, &m_height));
    assert(m_width);
    assert(m_height);

    // Create the main texture onto which we copy the texture created from the surface
    m_sprite = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, m_width, m_height);
    assert(m_sprite);

    // Copy texture created from surface to one we can draw on
    auto const currentRenderingTarget = SDL_GetRenderTarget(m_renderer);
    SDL_ASSERT(SDL_SetRenderTarget(m_renderer, m_sprite));
    SDL_ASSERT(SDL_RenderCopy(m_renderer, textureCreatedFromSurface, nullptr, nullptr));
    SDL_ASSERT(SDL_SetRenderTarget(m_renderer, currentRenderingTarget));

    // Default is to blend
    m_blendMode = SDL_BLENDMODE_BLEND;
    SDL_ASSERT(SDL_SetTextureBlendMode(m_sprite, m_blendMode));

    SDL_DestroyTexture(textureCreatedFromSurface);
}

SDL_Texture* Sprite::data() const noexcept
{
    return m_sprite;
}

SDL_Renderer* Sprite::renderer() const noexcept
{
    return m_renderer;
}

Sprite::Sprite(const Sprite& sprite) noexcept
{
    m_width = sprite.m_width;
    m_height = sprite.m_height;
    m_renderer = sprite.m_renderer;
    m_blendMode = sprite.m_blendMode;

    // Free existing texture
    SDL_DestroyTexture(m_sprite);

    // Create new texture
    m_sprite = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, m_width, m_height);
    assert(m_sprite);

    // Paste sprite texture onto here
    auto const currentRenderingTarget = SDL_GetRenderTarget(m_renderer);
    SDL_ASSERT(SDL_SetRenderTarget(m_renderer, m_sprite));
    SDL_ASSERT(SDL_RenderCopy(m_renderer, sprite.m_sprite, nullptr, nullptr));
    SDL_ASSERT(SDL_SetRenderTarget(m_renderer, currentRenderingTarget));

    SDL_ASSERT(SDL_SetTextureBlendMode(m_sprite, m_blendMode));
}

Sprite& Sprite::operator=(Sprite sprite) noexcept
{
    swap(*this, sprite);
    return *this;
}

Sprite::Sprite(Sprite&& sprite) noexcept : 
    Sprite(nullptr, 0, 0)
{
    swap(*this, sprite);
}

Sprite::~Sprite() noexcept
{
    SDL_DestroyTexture(m_sprite);
    m_sprite = nullptr;
}

int Sprite::width() const noexcept
{
    return m_width;
}

int Sprite::height() const noexcept
{
    return m_height;
}

SDL_RendererFlip Sprite::flipToSDLRendererFlip(SpriteFlip flip) noexcept
{
    switch (flip)
    {
    case SpriteFlip::FLIP_HORIZONTAL: 
        return SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
    case SpriteFlip::FLIP_VERTICAL:
        return SDL_RendererFlip::SDL_FLIP_VERTICAL;
    case SpriteFlip::FLIP_NONE:
        return SDL_RendererFlip::SDL_FLIP_NONE;
    default:
        assert(false && "Unknown flip");
        return SDL_RendererFlip::SDL_FLIP_NONE;
    }
}

void swap(Sprite& sprite1, Sprite& sprite2) noexcept
{
    std::swap(sprite1.m_height, sprite2.m_height);
    std::swap(sprite1.m_width, sprite2.m_width);
    std::swap(sprite1.m_renderer, sprite2.m_renderer);
    std::swap(sprite1.m_sprite, sprite2.m_sprite);
    std::swap(sprite1.m_blendMode, sprite2.m_blendMode);
}


}