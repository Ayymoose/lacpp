#include "Arrow.h"
#include "Camera.h"
#include "Resource.h"
#include "SDL_Assert.h"

namespace Zelda
{

Arrow::Arrow()
{
    m_sprite = ResourceManager::getInstance()[Graphic::GFX_WEAPON];
    m_speed = 2;
    m_name = "Arrow";
    m_width = m_weaponSpritesSrc[WPN_SPRITE_BOW].w;
    m_height = m_weaponSpritesSrc[WPN_SPRITE_BOW].h;
}

void Arrow::render() noexcept
{

    auto srcRect = m_weaponSpritesSrc[WPN_SPRITE_BOW];

    Rect<int> dstRect =
    {
        static_cast<int>(m_position.x - Camera::getInstance().getX()),
        static_cast<int>(m_position.y - Camera::getInstance().getY()),
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

    m_sprite.drawSpriteEx(Renderer::getInstance().getRenderer(), srcRect, dstRect, m_orientation, SpriteFlip::FLIP_NONE);

    // Fire the arrow
    m_position += m_dirVec;
}

void Arrow::update() noexcept
{
}

void Arrow::setPosition(Vector<float> position)
{
    m_position = position;
}

}