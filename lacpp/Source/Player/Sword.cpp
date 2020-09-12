#include "Sword.h"
#include "Camera.h"
#include "Resource.h"
#include "ZD_Assert.h"
#include "Link.h"

Sword::Sword()
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_WEAPON];
    m_name = "Sword";
    m_width = m_weaponSpritesSrc[WPN_SPRITE_SWORD].w;
    m_height = m_weaponSpritesSrc[WPN_SPRITE_SWORD].h;
    m_boundingBox.w = m_width;
    m_boundingBox.h = m_height;
    m_depth = ZD_DEPTH_BACKGROUND;
}

void Sword::render(SDL_Renderer* pRenderer) noexcept
{
    SDL_Rect srcRect = m_weaponSpritesSrc[WPN_SPRITE_SWORD];
    SDL_Rect dstRect =
    {
        m_position.x - Camera::getInstance().getX(),
        m_position.y - Camera::getInstance().getY(),
        m_width,
        m_height
    };

    m_boundingBox.x = m_position.x - Camera::getInstance().getX();
    m_boundingBox.y = m_position.y - Camera::getInstance().getY();

    ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());

}

void Sword::useWeapon()
{
    // Rotate to direction
    switch (m_direction)
    {
    case DIRECTION_LEFT: m_orientation = 270; break;
    case DIRECTION_RIGHT: m_orientation = 90; break;
    case DIRECTION_DOWN: m_orientation = 180; break;
    case DIRECTION_UP: m_orientation = 0; break;
    }
}

void Sword::setPosition(Vector<float> position)
{
    m_position = position;

    switch (m_direction)
    {
    case DIRECTION_LEFT:
        m_position.x -= m_width;
        break;
    case DIRECTION_RIGHT:
        m_position.x += m_width;
        break;
    case DIRECTION_DOWN:
        m_position.y += m_height;
        break;
    case DIRECTION_UP:
        m_position.y -= m_height;
        break;
    }
}
