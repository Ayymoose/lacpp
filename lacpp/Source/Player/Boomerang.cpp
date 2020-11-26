#include "Boomerang.h"
#include "Camera.h"
#include "Resource.h"
#include "ZD_Assert.h"
#include "Link.h"

Boomerang::Boomerang()
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_WEAPON];
    m_speed = 2;
    m_name = "Boomerang";
    m_width = m_weaponSpritesSrc[WPN_SPRITE_BOOMERANG].w;
    m_height = m_weaponSpritesSrc[WPN_SPRITE_BOOMERANG].h;
    m_boundingBox.w = m_width;
    m_boundingBox.h = m_height;
    m_return = false;
}

void Boomerang::render(SDL_Renderer* renderer) noexcept
{

    SDL_Rect srcRect = m_weaponSpritesSrc[WPN_SPRITE_BOOMERANG];

    SDL_Rect dstRect =
    {
        m_positionVector.x - Camera::getInstance().getX(),
        m_positionVector.y - Camera::getInstance().getY(),
        m_width,
        m_height
    };

    ZD_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());

    m_boundingBox.x = m_positionVector.x - Camera::getInstance().getX();
    m_boundingBox.y = m_positionVector.y - Camera::getInstance().getY();

    // Bounding Box rect
    // ZD_ASSERT(SDL_RenderDrawRect(renderer, &dstRect) == 0, "SDL Error: " << SDL_GetError());

    // Return to the player
    if (m_return)
    {
        // Get vector from player to here and repeatedly add position till we return to player
        Vector<float> positionVector = Link::getInstance().position();
        Vector<float> returnVector = positionVector - m_positionVector;
        if (returnVector.length() > 0.01f)
        {
            returnVector.normalise();
        }
        m_positionVector += returnVector * m_speed;
    }
    else
    {
        // Throw the boomerang
        m_positionVector += m_dirVec;
    }

    // Rotate the boomerang
    if (m_weaponTimer.update(BOOMERANG_ROTATION_FPS))
    {
        m_orientation += 90;
        m_orientation = static_cast<int>(m_orientation) % 360;
    }

    // TODO: Rotate the boomerang bounding box
    // TODO: Correct the boomerang rotating sprite
    // TODO: Return to player after distance travelled
    // TODO: Collisions with walls
    // TODO: Correct positioning
    // TODO: Collision with player after moving screen
}

/*void Boomerang::useWeapon()
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

void Boomerang::returnToPlayer()
{
    m_return = true;
}

void Boomerang::setPosition(Vector<float> position)
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
