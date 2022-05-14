#include "Sword.h"
#include "Camera.h"
#include "Resource.h"
#include "SDL_Assert.h"
#include "Link.h"

namespace Zelda
{

Sword::Sword()
{
   // m_sprite = ResourceManager::getInstance()[SpriteResource::SPR_WEAPON];
    m_name = "Sword";
    m_animateXPos = 0;
    m_animateYPos = 16;
    m_endFrame = 2;
    m_width = m_weaponSpritesSrc[WPN_SPRITE_SWORD].w;
    m_height = m_weaponSpritesSrc[WPN_SPRITE_SWORD].h;
    m_depth = ZD_DEPTH_BACKGROUND;
}

void Sword::render() noexcept
{
    Rect<int> srcRect =
    {
        m_animateXPos + (m_currentFrame * m_width),
        m_animateYPos,
        m_width,
        m_height
    };

    Rect<int> dstRect =
    {
        static_cast<int>(m_position.x - Camera::getInstance().getX()),
        static_cast<int>(m_position.y - Camera::getInstance().getY()),
        m_width,
        m_height
    };

    switch (m_direction)
    {
    case Direction::DIRECTION_DOWN:

        switch (m_currentFrame)
        {
        case 0:
            m_orientation = 270;
            dstRect.y += 3;
            dstRect.x -= 17;
            break;
        case 1:
            m_orientation = 180;
            dstRect.y += 14;
            dstRect.x -= 13;
            break;
        case 2:
            m_orientation = 90;
            dstRect.y += 15;
            dstRect.x += 4;
            break;
        }
        break;
    case Direction::DIRECTION_RIGHT:
        m_orientation = 0;
        switch (m_currentFrame)
        {
        case 0:
            dstRect.y -= 16;
            dstRect.x += 2;
            break;
        case 1:
            dstRect.y -= 12;
            dstRect.x += 10;
            break;
        case 2:
            dstRect.y += 3;
            dstRect.x += 15;
            break;
        }
        break;
    case Direction::DIRECTION_LEFT:
        switch (m_currentFrame)
        {
        case 0:
            m_orientation = 0;
            dstRect.y -= 15;
            dstRect.x -= 1;
            break;
        case 1:
            m_orientation = 270;
            dstRect.y -= 12;
            dstRect.x -= 10;
            break;
        case 2:
            m_orientation = 180;
            dstRect.y += 5;
            dstRect.x -= 15;
            break;
        }
        break;
    case Direction::DIRECTION_UP:
        switch (m_currentFrame)
        {
        case 0:
            m_orientation = 90;
            dstRect.x += 16;
            break;
        case 1:
            m_orientation = 0;
            dstRect.y -= 12;
            dstRect.x += 13;
            break;
        case 2:
            m_orientation = 270;
            dstRect.y -= 15;
            dstRect.x -= 5;
            break;
        }
        break;
    }

    //m_animationTimer.start();
    if (m_animationTimer.elapsed(SWORD_ATTACK_FPS))
    {
        if (m_currentFrame + 1 > m_endFrame)
        {
            m_animationComplete = true;
        }
        else
        {
            m_currentFrame++;
            m_animationComplete = false;
        }
        //m_animationTimer.reset();
    }
}

void Sword::update() noexcept
{
}

void Sword::setPosition(Vector<float> position)
{
    m_position = position;
}

}