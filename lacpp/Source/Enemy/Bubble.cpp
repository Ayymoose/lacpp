#include "Bubble.h"

Bubble::Bubble(float x, float y) : 
    Renderable("Bubble", ResourceManager::getInstance()[Graphic::GFX_ENEMY], ZD_DEPTH_ENEMY),
    Enemy(x, y)
{
    m_direction = Direction::DIRECTION_DOWN;

    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 5;

    m_speed = 1;

    // Set it off in a random direction
    m_directionVector = { 1, 1 };
}

void Bubble::render(SDL_Renderer* renderer) noexcept
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
        m_positionVector.x - m_xTransition - static_cast<float>(Camera::getInstance().getX()),
        m_positionVector.y - m_yTransition - static_cast<float>(Camera::getInstance().getY()),
        static_cast<float>(m_width),
        static_cast<float>(m_height)
    };

    SDL_ASSERT(SDL_RenderCopyF(renderer, m_texture, &m_srcRect, &m_dstRect), SDL_ERROR_MESSAGE);

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

float Bubble::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> Bubble::position() const noexcept
{
    return m_positionVector;
}

void Bubble::die() noexcept
{
    // Can't remember if it dies or not
}

void Bubble::attack() noexcept
{
    // Bounces diagonally off the walls/screen
    // Change direction as if bouncing off a wall
    if (m_positionVector.x < 0)
    {
        m_directionVector.x = -m_directionVector.x;
    }
    else if (m_positionVector.x > (Camera::getInstance().getX() + CAMERA_WIDTH) - m_width)
    {
        m_directionVector.x = -m_directionVector.x;
    }

    if (m_positionVector.y < 0)
    {
        m_directionVector.y = -m_directionVector.y;
    }
    else if (m_positionVector.y > (Camera::getInstance().getY() + CAMERA_HEIGHT) - m_height)
    {
        m_directionVector.y = -m_directionVector.y;
    }
    
    m_positionVector += m_directionVector * m_speed;
}
