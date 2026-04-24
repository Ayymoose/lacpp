#include "Sprite.h"

// Wrapper class around an SDL_Texture
namespace zelda::engine
{

Sprite::Sprite(SDL_Renderer* renderer, int width, int height)
    : m_renderer(renderer)
    , m_width(width)
    , m_height(height)
{
    if (m_renderer)
    {
        assert(m_width);
        assert(m_height);
        m_sprite = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, m_width, m_height);
        SDL_ASSERT(m_sprite);
        SDL_CHECK(SDL_SetTextureBlendMode(m_sprite, m_blendMode));
    }
}

Sprite::Sprite(SDL_Renderer* renderer, SDL_Surface* surface)
    : m_renderer(renderer)
    , m_blendMode(SDL_BLENDMODE_BLEND)
{
    assert(m_renderer);
    assert(surface);

    // Create a new texture from this surface
    const auto textureCreatedFromSurface = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);

    // Query dimensions
    SDL_CHECK(SDL_QueryTexture(textureCreatedFromSurface, nullptr, nullptr, &m_width, &m_height));
    assert(m_width);
    assert(m_height);

    // Create the main texture onto which we copy the texture created from the surface
    m_sprite = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, m_width, m_height);
    SDL_ASSERT(m_sprite);

    // Copy texture created from surface to one we can draw on
    {
        RenderTarget target(m_renderer, m_sprite);
        SDL_CHECK(SDL_RenderCopy(m_renderer, textureCreatedFromSurface, nullptr, nullptr));
    }

    SDL_CHECK(SDL_SetTextureBlendMode(m_sprite, m_blendMode));

    SDL_DestroyTexture(textureCreatedFromSurface);
    SDL_CHECK_NO_ERROR();
}

Sprite::Sprite(const Sprite& sprite)
    : m_renderer(sprite.m_renderer)
    , m_blendMode(sprite.m_blendMode)
    , m_width(sprite.m_width)
    , m_height(sprite.m_height)
{
    m_sprite = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, m_width, m_height);
    SDL_ASSERT(m_sprite);

    // Paste sprite texture onto here
    {
        RenderTarget target(m_renderer, m_sprite);
        SDL_CHECK(SDL_RenderCopy(m_renderer, sprite.m_sprite, nullptr, nullptr));
    }

    SDL_CHECK(SDL_SetTextureBlendMode(m_sprite, m_blendMode));
}

Sprite& Sprite::operator=(const Sprite& sprite)
{
    if (this != &sprite)
    {
        Sprite temp(sprite);
        swap(*this, temp);
    }
    return *this;
}

Sprite& Sprite::operator=(Sprite&& sprite) noexcept
{
    swap(*this, sprite);
    return *this;
}

Sprite::Sprite(Sprite&& sprite) noexcept
    : Sprite(nullptr, 0, 0)
{
    swap(*this, sprite);
}

Sprite::~Sprite() noexcept
{
    if (m_sprite)
    {
        SDL_DestroyTexture(m_sprite);
        SDL_CHECK_NO_ERROR();
    }
}

int Sprite::width() const
{
    return m_width;
}

int Sprite::height() const
{
    return m_height;
}

SDL_Texture* Sprite::data() const
{
    return m_sprite;
}

SDL_Renderer* Sprite::renderer() const
{
    return m_renderer;
}

void swap(Sprite& sprite1, Sprite& sprite2) noexcept
{
    std::swap(sprite1.m_height, sprite2.m_height);
    std::swap(sprite1.m_width, sprite2.m_width);
    std::swap(sprite1.m_renderer, sprite2.m_renderer);
    std::swap(sprite1.m_sprite, sprite2.m_sprite);
    std::swap(sprite1.m_blendMode, sprite2.m_blendMode);
}


} // namespace zelda::engine
