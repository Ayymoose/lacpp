#if 0


#include "Bubble.h"

namespace Zelda
{

Bubble::Bubble(float x, float y) :
    Renderable("Bubble", ResourceManager::getInstance()[Graphic::GFX_ENEMY], ZD_DEPTH_ENEMY),
    Enemy(x, y)
{
    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 5;

    m_speed = 1;

    // Set it off in a random direction
    m_direction = { 1, 1 };
}

void Bubble::render() noexcept
{
    auto animation = m_enemy[ENEMY_BUBBLE];

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
        m_position.x - m_xTransition - static_cast<float>(Camera::getInstance().getX()),
        m_position.y - m_yTransition - static_cast<float>(Camera::getInstance().getY()),
        static_cast<float>(m_width),
        static_cast<float>(m_height)
    };

    SDL_ASSERT(SDL_RenderCopyF(Renderer::getInstance().getRenderer(), m_texture, &m_srcRect, &m_dstRect), SDL_ERROR_MESSAGE);

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

void Bubble::update() noexcept
{
}

float Bubble::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> Bubble::position() const noexcept
{
    return m_position;
}

void Bubble::die() noexcept
{
    // Can't remember if it dies or not
}

void Bubble::attack() noexcept
{
    // Bounces diagonally off the walls/screen
    // Change direction as if bouncing off a wall
    if (m_position.x < 0)
    {
        m_direction.x = -m_direction.x;
    }
    else if (m_position.x > (Camera::getInstance().getX() + CAMERA_WIDTH) - m_width)
    {
        m_direction.x = -m_direction.x;
    }

    if (m_position.y < 0)
    {
        m_direction.y = -m_direction.y;
    }
    else if (m_position.y > (Camera::getInstance().getY() + CAMERA_HEIGHT) - m_height)
    {
        m_direction.y = -m_direction.y;
    }

    m_position += m_direction * m_speed;
}

}

#endif