#include "FlameRod.h"
#include "Camera.h"
#include "Resource.h"
#include "ZD_Assert.h"
#include "Link.h"

FlameRod::FlameRod()
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_WEAPON];
    m_speed = 2;
    m_name = "Flamerod";
    m_width = m_weaponSpritesSrc[WPN_SPRITE_FLAMEROD_FLAME].w;
    m_height = m_weaponSpritesSrc[WPN_SPRITE_FLAMEROD_FLAME].h;
    m_boundingBox.w = m_width;
    m_boundingBox.h = m_height;
    m_flameRodOrientation = 0;
    m_flameRodWidth = m_weaponSpritesSrc[WPN_SPRITE_FLAMEROD].w;
    m_flameRodHeight = m_weaponSpritesSrc[WPN_SPRITE_FLAMEROD].h;
    //m_depth = ZD_DEPTH_BACKGROUND;
    m_display = true;
}

void FlameRod::render(SDL_Renderer* renderer) noexcept
{

    SDL_Rect flameSrcRect = m_weaponSpritesSrc[WPN_SPRITE_FLAMEROD_FLAME];

    SDL_Rect flameDstRect =
    {
        m_positionVector.x - Camera::getInstance().getX(),
        m_positionVector.y - Camera::getInstance().getY(),
        m_width,
        m_height
    };

    // The flame
    SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &flameSrcRect, &flameDstRect, m_orientation, nullptr, SDL_FLIP_NONE), SDL_ERROR_MESSAGE);


    SDL_Rect flameRodSrcRect = m_weaponSpritesSrc[WPN_SPRITE_FLAMEROD];

    SDL_Rect flameRodDstRect =
    {
        m_flameRodPosition.x - Camera::getInstance().getX(),
        m_flameRodPosition.y - Camera::getInstance().getY(),
        m_flameRodWidth,
        m_flameRodHeight
    };


    m_boundingBox.x = m_positionVector.x - Camera::getInstance().getX();
    m_boundingBox.y = m_positionVector.y - Camera::getInstance().getY();

    // The flame rod
    if (m_display)
    SDL_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &flameRodSrcRect, &flameRodDstRect, m_flameRodOrientation, nullptr, SDL_FLIP_NONE), SDL_ERROR_MESSAGE);


    // Animate the flame rod
    if (m_weaponTimer.elapsed(1.0 / 8.0f) && m_currentFrame++ < 1)
    {
        switch (m_direction)
        {
        case Direction::DIRECTION_LEFT:
            m_flameRodOrientation = 270;
            m_flameRodPosition.x -= (m_flameRodHeight / 2) + 2;
            m_flameRodPosition.y += m_flameRodHeight;
            break;
        case Direction::DIRECTION_RIGHT:
            m_flameRodOrientation = 90;
            m_flameRodPosition.x += (m_flameRodHeight / 2) + 2;
            m_flameRodPosition.y += m_flameRodHeight + 2;
            break;
        case Direction::DIRECTION_DOWN:
            m_flameRodOrientation = 180;
            m_flameRodPosition.x += m_flameRodHeight - 1;
            m_flameRodPosition.y += m_flameRodHeight - 5;
            break;
        case Direction::DIRECTION_UP:
            m_flameRodOrientation = 0;
            m_flameRodPosition.y -= m_height;
            m_flameRodPosition.x -= m_width;
            break;
        }      
    }
    else if (m_currentFrame > 1)
    {
        m_display = false;
    }


    // Throw the flame
    m_positionVector += m_dirVec;
    
    // TODO: How to make it that the flamerod stays when the flame goes out?
    // TODO: Use player position for offset
}

/*void FlameRod::useWeapon()
{
    // Rotate to direction
    switch (m_direction)
    {
    case Direction::DIRECTION_LEFT: m_orientation = 270; m_dirVec.x = -m_speed; break;
    case Direction::DIRECTION_RIGHT: m_orientation = 90; m_dirVec.x = m_speed; break;
    case Direction::DIRECTION_DOWN: m_orientation = 180; m_dirVec.y = m_speed; break;
    case Direction::DIRECTION_UP: m_orientation = 0; m_dirVec.y = -m_speed; break;
    }
}*/

void FlameRod::setPosition(Vector<float> position)
{
    m_positionVector = position;
    m_flameRodPosition = position;

    switch (m_direction)
    {
    case Direction::DIRECTION_LEFT:
        m_positionVector.x -= m_width;

        m_flameRodOrientation = 0;
        m_flameRodPosition.x -= (m_flameRodWidth / 2) - 4;
        m_flameRodPosition.y -= m_flameRodHeight - 4;

        break;
    case Direction::DIRECTION_RIGHT:
        m_positionVector.x += m_width;

        m_flameRodOrientation = 0;
        m_flameRodPosition.x += (m_flameRodHeight / 2);
        m_flameRodPosition.y -= m_flameRodHeight - 2;
        break;
    case Direction::DIRECTION_DOWN:
        m_positionVector.y += m_height;

        m_flameRodOrientation = 270;
        m_flameRodPosition.x -= m_flameRodWidth;
        m_flameRodPosition.y += m_flameRodWidth / 2;

        break;
    case Direction::DIRECTION_UP:
        m_positionVector.y -= m_height;

        m_flameRodOrientation = 90;
        m_flameRodPosition.x += m_width;
        break;
    }

}