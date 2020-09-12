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

void Boomerang::render(SDL_Renderer* pRenderer) noexcept
{

    SDL_Rect srcRect = m_weaponSpritesSrc[WPN_SPRITE_BOOMERANG];

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

    // Bounding Box rect
    // ZD_ASSERT(SDL_RenderDrawRect(pRenderer, &dstRect) == 0, "SDL Error: " << SDL_GetError());

    // Return to the player
    if (m_return)
    {
        // Get vector from player to here and repeatedly add position till we return to player
        Vector<float> positionVector = Link::getInstance().position();
        Vector<float> returnVector = positionVector - m_position;
        if (returnVector.length() > 0.01)
        {
            returnVector.normalise();
        }
        m_position += returnVector * m_speed;
    }
    else
    {
        // Throw the boomerang
        m_position += m_dirVec;
    }

    // Rotate the boomerang
    if (m_weaponTimer.update(BOOMERANG_ROTATION_FPS))
    {
        m_orientation += 90;
        m_orientation = (int)m_orientation % 360;
    }

    // TODO: Rotate the boomerang bounding box
    // TODO: Correct the boomerang rotating sprite
    // TODO: Return to player after distance travelled
    // TODO: Collisions with walls
    // TODO: Correct positioning
    // TODO: Collision with player after moving screen
}

void Boomerang::useWeapon()
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

void Boomerang::returnToPlayer()
{
    m_return = true;
}

void Boomerang::setPosition(Vector<float> position)
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
