#include "Arrow.h"
#include "Camera.h"
#include "Resource.h"
#include "ZD_Assert.h"

namespace Zelda
{

Arrow::Arrow()
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_WEAPON];
    m_speed = 2;
    m_name = "Arrow";
    m_width = m_weaponSpritesSrc[WPN_SPRITE_BOW].w;
    m_height = m_weaponSpritesSrc[WPN_SPRITE_BOW].h;
    m_boundingBox.w = m_width;
    m_boundingBox.h = m_height;
}

void Arrow::render(SDL_Renderer* renderer) noexcept
{

    SDL_Rect srcRect = m_weaponSpritesSrc[WPN_SPRITE_BOW];

    SDL_Rect dstRect =
    {
        m_positionVector.x - Camera::getInstance().getX(),
        m_positionVector.y - Camera::getInstance().getY(),
        m_width,
        m_height
    };

    switch (m_direction)
    {
    case Direction::DIRECTION_LEFT:
        m_orientation = 270;
        m_dirVec.x = -m_speed;
        dstRect.x -= 12;
        dstRect.y += 4;
        break;
    case Direction::DIRECTION_RIGHT:
        m_orientation = 90;
        m_dirVec.x = m_speed;
        dstRect.x += 20;
        dstRect.y += 4;
        break;
    case Direction::DIRECTION_DOWN:
        m_orientation = 180;
        m_dirVec.y = m_speed;
        dstRect.x += 7;
        dstRect.y += 16;
        break;
    case Direction::DIRECTION_UP:
        m_orientation = 0;
        m_dirVec.y = -m_speed;
        dstRect.y -= 16;
        break;
    }

    SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE), SDL_ERROR_MESSAGE);

    m_boundingBox.x = m_positionVector.x - Camera::getInstance().getX();
    m_boundingBox.y = m_positionVector.y - Camera::getInstance().getY();

    // Fire the arrow
    m_positionVector += m_dirVec;

}

void Arrow::setPosition(Vector<float> position)
{
    m_positionVector = position;
}

}