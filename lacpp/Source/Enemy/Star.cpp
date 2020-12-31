#include "Star.h"

Star::Star(int x, int y) : Enemy(x, y)
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_ENEMY];
    m_direction = Direction::DIRECTION_DOWN;

    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 5;

    m_speed = 1;

    // Set it off in a random direction
    m_directionVector = { 1, 1 };

    m_name = "Star";
    m_depth = ZD_DEPTH_ENEMY;
    Renderer::getInstance().addRenderable(this);
}

void Star::render(SDL_Renderer* renderer) noexcept
{
    auto animation = m_enemy[static_cast<size_t>(EnemySprite::ENEMY_STAR)];

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
        m_positionVector.x - static_cast<float>(Camera::getInstance().getX()),
        m_positionVector.y - static_cast<float>(Camera::getInstance().getY()),
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
        //m_animationTimer.reset();
    }
}

float Star::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> Star::position() const noexcept
{
    return m_positionVector;
}

void Star::die() noexcept
{
    // Can't remember if it dies or not
}

void Star::attack() noexcept
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
