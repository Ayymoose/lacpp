#include "Bomb.h"
#include "Camera.h"
#include "Resource.h"
#include "SDL_Assert.h"
#include "Link.h"

namespace Zelda
{

Bomb::Bomb()
{
    m_sprite = ResourceManager::getInstance()[SpriteResource::SPR_WEAPON];
    m_name = "Bomb";
    m_width = m_weaponSpritesSrc[WPN_SPRITE_BOMB].w;
    m_height = m_weaponSpritesSrc[WPN_SPRITE_BOMB].h;
    m_exploded = false;
    m_animateXPos = m_weaponSpritesSrc[WPN_SPRITE_BOMB].x;
    m_startBomb = false;
    m_flashBomb = false;
    m_flashCount = 0;
}

void Bomb::render() noexcept
{
    auto srcRect = m_weaponSpritesSrc[WPN_SPRITE_BOMB];
    srcRect.x = m_animateXPos + (m_currentFrame * (m_width + SPRITE_SPACING));

    Rect<int> dstRect =
    {
        static_cast<int>(m_position.x - Camera::getInstance().getX()),
        static_cast<int>(m_position.y - Camera::getInstance().getY()),
        m_width,
        m_height
    };

    // Bomb frames
    // 0 - Inert
    // 1 - Ready to explode
    // 2 - Initial cloud
    // 3 - Explosion
    // 4 - After smoke

    // Draw the exploding parts superimposed on top
    switch (m_currentFrame)
    {

    case BOMB_SPRITE_INERT:
    case BOMB_SPRITE_FLASHING:
        m_sprite.drawSpriteEx(Renderer::getInstance().getRenderer(), srcRect, dstRect, m_orientation, SpriteFlip::FLIP_NONE);
        break;
    case BOMB_SPRITE_INITIAL_CLOUD:

        // Center the explosion
        dstRect.x -= 4;
        dstRect.y -= 4;
        
        m_sprite.drawSpriteEx(Renderer::getInstance().getRenderer(), srcRect, dstRect, m_orientation, SpriteFlip::FLIP_NONE);
        dstRect.x += 12;
        m_sprite.drawSpriteEx(Renderer::getInstance().getRenderer(), srcRect, dstRect, m_orientation, SpriteFlip::FLIP_NONE);

        dstRect.y += 8;
        m_sprite.drawSpriteEx(Renderer::getInstance().getRenderer(), srcRect, dstRect, m_orientation, SpriteFlip::FLIP_NONE);

        dstRect.x -= 12;
        m_sprite.drawSpriteEx(Renderer::getInstance().getRenderer(), srcRect, dstRect, m_orientation, SpriteFlip::FLIP_NONE);

        break;
    case BOMB_SPRITE_EXPLOSION:

        // Center the explosion
        dstRect.x -= 6;
        dstRect.y -= 6;

        m_sprite.drawSpriteEx(Renderer::getInstance().getRenderer(), srcRect, dstRect, m_orientation, SpriteFlip::FLIP_NONE);

        dstRect.x += 16;
        m_sprite.drawSpriteEx(Renderer::getInstance().getRenderer(), srcRect, dstRect, m_orientation, SpriteFlip::FLIP_HORIZONTAL);

        dstRect.y += 16;
        m_sprite.drawSpriteEx(Renderer::getInstance().getRenderer(), srcRect, dstRect, 270, SpriteFlip::FLIP_VERTICAL);

        dstRect.x -= 16;
        m_sprite.drawSpriteEx(Renderer::getInstance().getRenderer(), srcRect, dstRect, m_orientation, SpriteFlip::FLIP_VERTICAL);

        break;
    case BOMB_SPRITE_AFTER_SMOKE:

        // Center the explosion
        dstRect.x -= 6;
        dstRect.y -= 6;

        m_sprite.drawSpriteEx(Renderer::getInstance().getRenderer(), srcRect, dstRect, m_orientation, SpriteFlip::FLIP_NONE);

        dstRect.x += 16;
        m_sprite.drawSpriteEx(Renderer::getInstance().getRenderer(), srcRect, dstRect, m_orientation, SpriteFlip::FLIP_NONE);

        dstRect.y += 16;
        m_sprite.drawSpriteEx(Renderer::getInstance().getRenderer(), srcRect, dstRect, m_orientation, SpriteFlip::FLIP_NONE);

        dstRect.x -= 16;
        m_sprite.drawSpriteEx(Renderer::getInstance().getRenderer(), srcRect, dstRect, m_orientation, SpriteFlip::FLIP_NONE);

        break;
    }

    // When a bomb is placed
    // It is initially inert for 1 second then starts to flash then explodes
    // Frame
    // 0 -> 1 -> 0 -> 1 -> 0 -> 1 -> 0 -> 1 -> 0 -> 1 ... 2 -> 3 -> 4

    // Start flashing after 1 second
    // Keep flashing for 1 seconds
    // Then explode

    if (m_weaponTimer.elapsed(BOMB_START_TIME) && !m_startBomb)
    {
        // Start the bomb
        m_startBomb = true;
    }

    if (m_startBomb && m_flashCount != BOMB_FLASH_MAX)
    {
        if (!m_flashBomb && m_weaponTimer.elapsed(BOMB_EXPLODE_TIME))
        {
            m_currentFrame = 1;
            m_flashBomb = true;
            m_flashCount++;
        }
        else
        {
            if (m_weaponTimer.elapsed(BOMB_EXPLODE_TIME))
            {
                m_currentFrame = 0;
                m_flashBomb = false;
            }
        }
    }
    else if (m_flashCount == BOMB_FLASH_MAX)
    {
        // Explode!
        if (m_animationTimer.elapsed(BOMB_ANIMATION_TIME))
        {
            if (m_currentFrame < BOMB_FRAMES - 1)
            {
                m_currentFrame++;
            }
            else
            {
                m_exploded = true;
            }
        }
    }
}

void Bomb::update() noexcept
{
}

void Bomb::setPosition(Vector<float> position)
{
    m_position = position;

    switch (m_direction)
    {
    case Direction::DIRECTION_LEFT: m_position.x -= m_width; break;
    case Direction::DIRECTION_RIGHT: m_position.x += m_width * 2; break;
    case Direction::DIRECTION_DOWN: m_position.y += m_height; break;
    case Direction::DIRECTION_UP: m_position.y -= m_height; break;
    }

}

bool Bomb::exploded() const
{
    return m_exploded;
}

bool Bomb::cull() noexcept
{
    return m_exploded || !Camera::getInstance().visible(Rect<float>{ m_position.x, m_position.y, static_cast<float>(m_width), static_cast<float>(m_height) });
}

}