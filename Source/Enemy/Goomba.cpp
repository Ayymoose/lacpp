#if 0


#include "Goomba.h"
#include "Common.h"

namespace Zelda
{

Goomba::Goomba(float x, float y) :
    Renderable("Goomba", ResourceManager::getInstance()[Graphic::GFX_ENEMY], ZD_DEPTH_ENEMY),
    Enemy(x, y)
{
    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 1;
    m_speed = 0.5f;
}

void Goomba::render() noexcept
{
    auto animation = m_enemy[ENEMY_GOOMBA];

    m_animateXPos = animation.x;
    m_animateYPos = animation.y;
    m_endFrame = animation.endFrame;
    m_animationFPS = animation.animationFPS;

    m_srcRect =
    {
        m_animateXPos + (m_currentFrame * m_width),
        m_animateYPos,
        m_width,
        m_height
    };

    // Where to draw on screen
    m_dstRect =
    {
        m_position.x - m_xTransition - Camera::getInstance().getX(),
        m_position.y - m_yTransition - Camera::getInstance().getY(),
        static_cast<float>(m_width),
        static_cast<float>(m_height)
    };

    SDL_ASSERT(SDL_RenderCopyF(Renderer::getInstance().getRenderer(), m_texture, &m_srcRect, &m_dstRect));

    if (m_animationTimer.elapsed(m_animationFPS) && !Engine::getInstance().paused())
    {
        if (m_currentFrame < m_endFrame)
        {
            m_currentFrame++;
        }
        else
        {
            m_currentFrame = animation.startFrame;
        }
    }
}

void Goomba::update() noexcept
{
}

float Goomba::health() const noexcept
{
    return m_health;
}

Vector<float> Goomba::position() const noexcept
{
    return m_position;
}

void Goomba::attack() noexcept
{
    // This enemy doesn't move and doesn't do anything except animate

        // Move's randomly in 4 directions only
    // Bouncing off objects
    // Any attempt to move out of the camera will flip it's direction
    // If pushed out the camera by Link, will reach the edge only

    // Basic AI movement
    // Every second, if we hit 1/4 then change direction to a new direction
    // The new direction must not be the same direction and can't be the opposite of the last direction 

    // BUG: The enemy can still get stuck at the border between the camera edge it seems and "vibrate"
    if (m_enemyTimer.elapsed(0.25f))
    {
        // Try to change direction
        auto chance = random(1, 3);
        if (chance == 2)
        {
            auto dir = random(0, 3);
            const Vector<float> dirs[4] =
            {
                {m_speed,0}, {-m_speed, 0}, {0, -m_speed}, {0, m_speed}
            };
            m_direction = dirs[dir];
        }
    }

    // If attempt to move out of view, flip direction
    if (!Camera::getInstance().visible({ m_position.x, m_position.y, static_cast<float>(m_width), static_cast<float>(m_height) }))
    {
        m_direction = -m_direction;
    }

    m_position += m_direction;
}

void Goomba::die() noexcept
{
    // TODO: If stepped on turn into flat sprite

}

}

#endif