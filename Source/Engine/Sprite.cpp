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
constexpr Sprite::Sprite() : m_sprite(nullptr), m_width(0), m_height(0)
{
}

SDL_Texture* Sprite::data() const noexcept
{
    return m_sprite;
}

Sprite Sprite::operator=(SDL_Texture* texture) noexcept
{
    m_sprite = texture;
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


}