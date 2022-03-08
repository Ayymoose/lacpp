#include "Boomerang.h"
#include "Camera.h"
#include "Resource.h"
#include "SDL_Assert.h"
#include "Link.h"

namespace Zelda
{

Boomerang::Boomerang()
{
    m_sprite = ResourceManager::getInstance()[SpriteResource::SPR_WEAPON];
    m_speed = 2;
    m_name = "Boomerang";
    m_width = m_weaponSpritesSrc[WPN_SPRITE_BOOMERANG].w;
    m_height = m_weaponSpritesSrc[WPN_SPRITE_BOOMERANG].h;
    m_return = false;
}

void Boomerang::render() noexcept
{

    auto srcRect = m_weaponSpritesSrc[WPN_SPRITE_BOOMERANG];

    Rect<int> dstRect =
    {
        static_cast<int>(m_position.x - Camera::getInstance().getX()),
        static_cast<int>(m_position.y - Camera::getInstance().getY()),
        m_width,
        m_height
    };

    m_sprite.drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

    // Return to the player
    if (m_return)
    {
        // Get vector from player to here and repeatedly add position till we return to player
       /* Vector<float> positionVector = Link::getInstance().position();
        Vector<float> returnVector = positionVector - m_position;
        if (returnVector.length() > 0.01f)
        {
            returnVector.normalise();
        }
        m_position += returnVector * m_speed;*/
    }
    else
    {
        // Throw the boomerang
        m_position += m_dirVec;
    }

    // Rotate the boomerang
    if (m_weaponTimer.elapsed(BOOMERANG_ROTATION_FPS))
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

void Boomerang::update() noexcept
{
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
    m_position = position;

    switch (m_direction)
    {
    case Direction::DIRECTION_LEFT: m_position.x -= m_width; break;
    case Direction::DIRECTION_RIGHT: m_position.x += m_width * 2; break;
    case Direction::DIRECTION_DOWN: m_position.y += m_height; break;
    case Direction::DIRECTION_UP: m_position.y -= m_height; break;
    }

}

}