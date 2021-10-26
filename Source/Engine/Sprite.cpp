#pragma once

#include "Sprite.h"

// Wrapper class around an SDL_Texture
namespace Zelda
{

Sprite::Sprite(SDL_Texture* texture) : m_sprite(texture), m_width(0), m_height(0)
{
    assert(texture);
    SDL_ASSERT(SDL_QueryTexture(m_sprite, nullptr, nullptr, &m_width, &m_height), SDL_ERROR_MESSAGE);
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