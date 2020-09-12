#include "Bow.h"
#include "Camera.h"
#include "Resource.h"
#include "ZD_Assert.h"

Bow::Bow()
{
    m_texture = ResourceManager::getInstance()[RSC_WEAPON];
    m_speed = 2;
    m_name = "Bow";
    m_width = m_weaponSpritesSrc[WPN_SPRITE_BOW].w;
    m_height = m_weaponSpritesSrc[WPN_SPRITE_BOW].h;
    m_boundingBox.w = m_width;
    m_boundingBox.h = m_height;
}

void Bow::render(SDL_Renderer* pRenderer)
{

    SDL_Rect srcRect = m_weaponSpritesSrc[WPN_SPRITE_BOW];

    SDL_Rect dstRect =
    {
        m_position.x - Camera::getInstance().getX(),
        m_position.y - Camera::getInstance().getY(),
        m_width,
        m_height
    };

    ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());

    m_boundingBox.x = m_position.x - Camera::getInstance().getX();
    m_boundingBox.y = m_position.y - Camera::getInstance().getY();

    // Fire the arrow
    m_position += m_dirVec;

}

void Bow::useWeapon()
{
    // Rotate to direction
    switch (m_direction)
    {
    case DIRECTION_LEFT: m_orientation = 270; m_dirVec.x = -m_speed; break;
    case DIRECTION_RIGHT: m_orientation = 90; m_dirVec.x = m_speed; break;
    case DIRECTION_DOWN: m_orientation = 180; m_dirVec.y = m_speed; break;
    case DIRECTION_UP: m_orientation = 0; m_dirVec.y = -m_speed; break;
    }
}

void Bow::setPosition(Vector<float> position)
{
    m_position = position;
}
