#include "Bow.h"
#include "Camera.h"
#include "Resource.h"

Bow::Bow() : Weapon(WPN_BOW)
{
    m_texture = ResourceManager::getInstance()[RSC_ARROW];
    m_speed = 2;
    m_boundingBox.w = m_width;
    m_boundingBox.h = m_height;

}

void Bow::render(SDL_Renderer* pRenderer)
{
    SDL_Rect dstRect =
    {
        m_position.x - Camera::getInstance().getX(),
        m_position.y - Camera::getInstance().getY(),
        m_width,
        m_height
    };
    auto res = SDL_RenderCopyEx(pRenderer, m_texture, nullptr, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE);
    if (res != 0)
    {
        std::cerr << SDL_GetError() << std::endl;
        assert(false);
    }
    //assert(SDL_RenderCopyEx(pRenderer, m_texture, nullptr, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0);

    m_boundingBox.x = m_position.x - Camera::getInstance().getX();
    m_boundingBox.y = m_position.y - Camera::getInstance().getY();

    // Move the arrow
    if (m_weaponTimer.update(ARROW_SPEED_FPS))
    {
        m_position += m_dirVec;
    }

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

bool Bow::perished()
{
    int x = m_position.x - Camera::getInstance().getX();
    int y = m_position.y - Camera::getInstance().getY();

    return false;
}
