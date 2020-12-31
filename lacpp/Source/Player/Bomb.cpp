#include "Bomb.h"
#include "Camera.h"
#include "Resource.h"
#include "ZD_Assert.h"
#include "Link.h"

Bomb::Bomb()
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_WEAPON];
    m_name = "Bomb";
    m_width = m_weaponSpritesSrc[WPN_SPRITE_BOMB].w;
    m_height = m_weaponSpritesSrc[WPN_SPRITE_BOMB].h;
    m_boundingBox.w = m_width;
    m_boundingBox.h = m_height;
    m_exploded = false;
    m_animateXPos = m_weaponSpritesSrc[WPN_SPRITE_BOMB].x;
    m_startBomb = false;
    m_flashBomb = false;
    m_flashCount = 0;
}

void Bomb::render(SDL_Renderer* renderer) noexcept
{
    SDL_Rect srcRect = m_weaponSpritesSrc[WPN_SPRITE_BOMB];
    srcRect.x = m_animateXPos + (m_currentFrame * (m_width + SPRITE_SPACING));

    SDL_Rect dstRect =
    {
        m_positionVector.x - Camera::getInstance().getX(),
        m_positionVector.y - Camera::getInstance().getY(),
        m_width,
        m_height
    };

    // Bomb frames
    // 0 - Inert
    // 1 - Ready to explode
    // 2 - Initial cloud
    // 3 - Explosion
    // 4 - After smoke

    m_boundingBox.x = m_positionVector.x - Camera::getInstance().getX();
    m_boundingBox.y = m_positionVector.y - Camera::getInstance().getY();

    // Draw the exploding parts superimposed on top
    switch (m_currentFrame)
    {

    case BOMB_SPRITE_INERT:
    case BOMB_SPRITE_FLASHING:
        SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE), SDL_ERROR_MESSAGE);
        break;
    case BOMB_SPRITE_INITIAL_CLOUD:

        // Center the explosion
        dstRect.x -= 4;
        dstRect.y -= 4;
        m_boundingBox.x -= 4;
        m_boundingBox.y -= 4;

        SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE), SDL_ERROR_MESSAGE);
        dstRect.x += 12;
        SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE), SDL_ERROR_MESSAGE);
        dstRect.y += 8;
        SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE), SDL_ERROR_MESSAGE);
        dstRect.x -= 12;
        SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE), SDL_ERROR_MESSAGE);

        m_boundingBox.w = 28;
        m_boundingBox.h = 24;
    break;
    case BOMB_SPRITE_EXPLOSION:

        // Center the explosion
        dstRect.x -= 6;
        dstRect.y -= 6;
        m_boundingBox.x -= 6;
        m_boundingBox.y -= 6;

        SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE), SDL_ERROR_MESSAGE);
        dstRect.x += 16;
        SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_HORIZONTAL), SDL_ERROR_MESSAGE);
        dstRect.y += 16;
        SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, 270, nullptr, SDL_FLIP_VERTICAL), SDL_ERROR_MESSAGE);
        dstRect.x -= 16;
        SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_VERTICAL), SDL_ERROR_MESSAGE);

        m_boundingBox.w = 32;
        m_boundingBox.h = 32;
    break;
    case BOMB_SPRITE_AFTER_SMOKE:

        // Center the explosion
        dstRect.x -= 6;
        dstRect.y -= 6;
        m_boundingBox.x -= 6;
        m_boundingBox.y -= 6;

        SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE), SDL_ERROR_MESSAGE);
        dstRect.x += 16;
        SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE), SDL_ERROR_MESSAGE);
        dstRect.y += 16;
        SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE), SDL_ERROR_MESSAGE);
        dstRect.x -= 16;
        SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE), SDL_ERROR_MESSAGE);

        m_boundingBox.w = 32;
        m_boundingBox.h = 32;
    break;
    }

    SDL_Rect boundingRect = 
    {
        m_boundingBox.x,
        m_boundingBox.y,
        m_boundingBox.w,
        m_boundingBox.h
    };

    // Bounding Box rect
    // SDL_ASSERT(SDL_RenderDrawRect(renderer, &boundingRect), SDL_ERROR_MESSAGE);


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
            if (m_currentFrame < BOMB_FRAMES-1)
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

void Bomb::setPosition(Vector<float> position)
{
    m_positionVector = position;

    switch (m_direction)
    {
    case Direction::DIRECTION_LEFT: m_positionVector.x -= m_width; break;
    case Direction::DIRECTION_RIGHT: m_positionVector.x += m_width * 2; break;
    case Direction::DIRECTION_DOWN: m_positionVector.y += m_height; break;
    case Direction::DIRECTION_UP: m_positionVector.y -= m_height; break;
    }

}

bool Bomb::exploded() const
{
    return m_exploded;
}

bool Bomb::cull() noexcept
{
    return m_exploded || !Camera::getInstance().visible({m_positionVector.x, m_positionVector.y, static_cast<float>(m_width), static_cast<float>(m_height)});
}
