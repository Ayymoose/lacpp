#if 0


#include "Zombie.h"
#include "Common.h"

namespace Zelda
{

Zombie::Zombie(float x, float y) :
    Renderable("Zombie", ResourceManager::getInstance()[Graphic::GFX_ENEMY], ZD_DEPTH_ENEMY),
    Enemy(x, y),
    m_emerging(true),
    m_burrowing(false)
{
    m_dir = Direction::DIRECTION_DOWN;

    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 5;
    m_speed = 0.75f;
    m_moving = true;

    // Set it off in a random direction
    m_direction = { 0, m_speed };
}

void Zombie::render() noexcept
{
    auto animation = m_enemy[ENEMY_ZOMBIE];

    m_animateXPos = animation.x;
    m_animateYPos = animation.y;
    m_endFrame = animation.endFrame;
    m_animationFPS = animation.animationFPS;

    m_srcRect =
    {
        m_animateXPos + ((m_currentFrame + m_auxiliaryFrame) * m_width),
        m_animateYPos,
        m_width,
        m_height
    };

    // Where to draw on screen
    m_dstRect =
    {
        m_position.x - m_xTransition - static_cast<float>(Camera::getInstance().getX()),
        m_position.y - m_yTransition - static_cast<float>(Camera::getInstance().getY()),
        static_cast<float>(m_width),
        static_cast<float>(m_height)
    };

    if (m_emerging || m_moving || m_burrowing)
    {
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


}

void Zombie::update() noexcept
{
}

float Zombie::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> Zombie::position() const noexcept
{
    return m_position;
}

void Zombie::die() noexcept
{


}

void Zombie::attack() noexcept
{
    // Emerges from the ground from a random place and moves towards Link for a while
    // Then burrows back in and appears at a random place again

    if (m_emerging)
    {
        // If emerging, we will play the emerging frame for 2 frames
        if (m_currentFrame == 1)
        {
            m_auxiliaryFrame = 2;
            m_emerging = false;
        }
    }
    else
    {
        if (!m_burrowing && m_enemyTimer.elapsed(1.0f))
        {
            // Burrow back in the ground again
            m_burrowing = true;
        }
    }

    if (m_burrowing)
    {
        m_auxiliaryFrame = 4;
        if (m_currentFrame == 1)
        {
            m_burrowing = false;
            m_moving = false;
        }
    }

    if (!m_burrowing && !m_moving && !m_emerging)
    {
        if (m_emergeTimer.elapsed(3.0f))
        {
            // Appear at a random place within sand area only!
            m_position.x = random(0, CAMERA_WIDTH) - Camera::getInstance().getX();
            m_position.y = random(0, CAMERA_HEIGHT - m_height) - Camera::getInstance().getY();

            m_emerging = true;
            m_moving = true;
        }
    }

    if (m_moving && !m_emerging && !m_burrowing)
    {
        Vector<float> linkPositionVector = Link::getInstance().position();
        m_direction = linkPositionVector - m_position;
        // Can't remember what this 0.01 was for
        // Ah yes, prevent division by 0 if they are at the same position
        if (m_direction.length() > 0.1f)
        {
            m_direction.normalise();
            m_position += m_direction * m_speed;
        }
    }
}

}

#endif