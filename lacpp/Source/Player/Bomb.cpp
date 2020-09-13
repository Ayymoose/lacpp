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

void Bomb::render(SDL_Renderer* pRenderer) noexcept
{
    SDL_Rect srcRect = m_weaponSpritesSrc[WPN_SPRITE_BOMB];
    srcRect.x = m_animateXPos + (m_currentFrame * (m_width + SPRITE_SPACING));

    SDL_Rect dstRect =
    {
        m_position.x - Camera::getInstance().getX(),
        m_position.y - Camera::getInstance().getY(),
        m_width,
        m_height
    };

    // Bomb frames
    // 0 - Inert
    // 1 - Ready to explode
    // 2 - Initial cloud
    // 3 - Explosion
    // 4 - After smoke

    m_boundingBox.x = m_position.x - Camera::getInstance().getX();
    m_boundingBox.y = m_position.y - Camera::getInstance().getY();

    // Draw the exploding parts superimposed on top
    switch (m_currentFrame)
    {

    case BOMB_SPRITE_INERT:
    case BOMB_SPRITE_FLASHING:
        ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());
        break;
    case BOMB_SPRITE_INITIAL_CLOUD:

        // Center the explosion
        dstRect.x -= 4;
        dstRect.y -= 4;
        m_boundingBox.x -= 4;
        m_boundingBox.y -= 4;

        ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());
        dstRect.x += 12;
        ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());
        dstRect.y += 8;
        ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());
        dstRect.x -= 12;
        ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());

        m_boundingBox.w = 28;
        m_boundingBox.h = 24;
    break;
    case BOMB_SPRITE_EXPLOSION:

        // Center the explosion
        dstRect.x -= 6;
        dstRect.y -= 6;
        m_boundingBox.x -= 6;
        m_boundingBox.y -= 6;

        ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());
        dstRect.x += 16;
        ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_HORIZONTAL) == 0, "SDL Error: " << SDL_GetError());
        dstRect.y += 16;
        ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, 270, nullptr, SDL_FLIP_VERTICAL) == 0, "SDL Error: " << SDL_GetError());
        dstRect.x -= 16;
        ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_VERTICAL) == 0, "SDL Error: " << SDL_GetError());

        m_boundingBox.w = 32;
        m_boundingBox.h = 32;
    break;
    case BOMB_SPRITE_AFTER_SMOKE:

        // Center the explosion
        dstRect.x -= 6;
        dstRect.y -= 6;
        m_boundingBox.x -= 6;
        m_boundingBox.y -= 6;

        ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());
        dstRect.x += 16;
        ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());
        dstRect.y += 16;
        ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());
        dstRect.x -= 16;
        ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());

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
    // ZD_ASSERT(SDL_RenderDrawRect(pRenderer, &boundingRect) == 0, "SDL Error: " << SDL_GetError());


    // When a bomb is placed
    // It is initially inert for 1 second then starts to flash then explodes
    // Frame
    // 0 -> 1 -> 0 -> 1 -> 0 -> 1 -> 0 -> 1 -> 0 -> 1 ... 2 -> 3 -> 4

    // Start flashing after 1 second
    // Keep flashing for 1 seconds
    // Then explode

    if (m_weaponTimer.update(BOMB_START_TIME) && !m_startBomb)
    {
        // Start the bomb
        m_startBomb = true;
    }

    if (m_startBomb && m_flashCount != BOMB_FLASH_MAX)
    {
        if (!m_flashBomb && m_weaponTimer.update(BOMB_EXPLODE_TIME))
        {
            m_currentFrame = 1;
            m_flashBomb = true;
            m_flashCount++;
        }
        else
        {
            if (m_weaponTimer.update(BOMB_EXPLODE_TIME))
            {
                m_currentFrame = 0;
                m_flashBomb = false;
            }
        }
    }
    else if (m_flashCount == BOMB_FLASH_MAX)
    {
        // Explode!
        if (m_animationTimer.update(BOMB_ANIMATION_TIME))
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

void Bomb::useWeapon()
{
    // Bomb starts as inert
    // After 2 seconds it starts flashing then explodes
    
}

void Bomb::setPosition(Vector<float> position)
{
    m_position = position;

    switch (m_direction)
    {
    case DIRECTION_LEFT: m_position.x -= m_width; break;
    case DIRECTION_RIGHT: m_position.x += m_width * 2; break;
    case DIRECTION_DOWN: m_position.y += m_height; break;
    case DIRECTION_UP: m_position.y -= m_height; break;
    }

}

bool Bomb::exploded() const
{
    return m_exploded;
}