#include "Bomb.h"
#include "Camera.h"
#include "Resource.h"
#include "MyAssert.h"
#include "Player.h"

Bomb::Bomb()
{
    m_texture = ResourceManager::getInstance()[RSC_WEAPON];
    m_name = "Bomb";
    m_width = m_weaponSpritesSrc[WPN_SPRITE_BOMB].w;
    m_height = m_weaponSpritesSrc[WPN_SPRITE_BOMB].h;
    m_boundingBox.w = m_width;
    m_boundingBox.h = m_height;
    m_exploded = false;
    m_animateXPos = m_weaponSpritesSrc[WPN_SPRITE_BOMB].x;

}

void Bomb::render(SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect = m_weaponSpritesSrc[WPN_SPRITE_BOMB];
    srcRect.x = m_animateXPos + (m_currentFrame * m_width);

    SDL_Rect dstRect =
    {
        m_position.x - Camera::getInstance().getX(),
        m_position.y - Camera::getInstance().getY(),
        m_width,
        m_height
    };

    DASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, SDL_GetError());

    m_boundingBox.x = m_position.x - Camera::getInstance().getX();
    m_boundingBox.y = m_position.y - Camera::getInstance().getY();

    // Bounding Box rect
    // DASSERT(SDL_RenderDrawRect(pRenderer, &dstRect) == 0, SDL_GetError());

    if (m_weaponTimer.update(BOMB_START_TIME) && !m_exploded)
    {
        // Start the animation
        if (m_animationTimer.update(BOMB_EXPLODE_TIME))
        {
            m_currentFrame = 1;
        }
        else
        {
            m_currentFrame = 0;
        }
        


        //m_exploded = true;
    }

    // TODO: Rotate the boomerang bounding box
    // TODO: Correct the boomerang rotating sprite
    // TODO: Return to player after distance travelled
    // TODO: Collisions with walls
    // TODO: Correct positioning
    // TODO: Collision with player after moving screen
}

void Bomb::useWeapon()
{
    // Bomb starts as inert
    // After 2 seconds it starts flashing then explodes
    
}

void Bomb::setPosition(Vec2<float> position)
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

bool Bomb::exploded() const
{
    return m_exploded;
}
