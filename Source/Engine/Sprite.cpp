#pragma once

#include "Sprite.h"

// Wrapper class around an SDL_Texture
namespace Zelda
{

Sprite::Sprite(SDL_Texture* texture) : m_sprite(texture), m_width(0), m_height(0)
{
    assert(texture);
    SDL_ASSERT(SDL_QueryTexture(m_sprite, nullptr, nullptr, &m_width, &m_height), SDL_ERROR_MESSAGE);
    assert(m_width);
    assert(m_height);
}

Sprite::Sprite(SDL_Renderer* renderer, int width, int height) :
    m_sprite(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, width, height)),
    m_width(width),
    m_height(height)
{
    assert(width);
    assert(height);
    assert(m_sprite);
}

SDL_Texture* Sprite::data() const noexcept
{
    return m_sprite;
}

// SDL_Texture assignment operator
Sprite& Sprite::operator=(SDL_Texture* texture) noexcept
{
    m_sprite = texture; 
    if (m_sprite)
    {
        SDL_ASSERT(SDL_QueryTexture(m_sprite, nullptr, nullptr, &m_width, &m_height), SDL_ERROR_MESSAGE);
    }
    return *this;
}

int Sprite::width() const noexcept
{
    return m_width;
}

int Sprite::height() const noexcept
{
    return m_height;
}

void Sprite::free() noexcept
{
    SDL_DestroyTexture(m_sprite);
    m_sprite = nullptr;
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

}