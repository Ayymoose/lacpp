#if 0


#include "ShyGuy.h"
#include "Common.h"

namespace Zelda
{

ShyGuy::ShyGuy(float x, float y) :
    Renderable("Shy Guy", ResourceManager::getInstance()[Graphic::GFX_ENEMY], ZD_DEPTH_ENEMY),
    Enemy(x, y)
{
    m_dir = Direction::DIRECTION_DOWN;

    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 5;
    m_speed = 1;
}

void ShyGuy::render() noexcept
{
    auto animation = m_enemy[ENEMY_SHY_GUY];

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

    SDL_ASSERT(SDL_RenderCopyF(Renderer::getInstance().getRenderer(), m_texture, &m_srcRect, &m_dstRect));

    if (!Engine::getInstance().paused())
    {
        if (Link::getInstance().moving())
        {
            if (m_animationTimer.elapsed(m_animationFPS))
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
        else
        {
            m_currentFrame = animation.startFrame;
        }

    }

}

void ShyGuy::update() noexcept
{
}

float ShyGuy::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> ShyGuy::position() const noexcept
{
    return m_position;
}

void ShyGuy::die() noexcept
{


}

void ShyGuy::attack() noexcept
{
    // Moves in the opposite direction to Link
    // If Link moves left, we move right
    // If Link moves up, we move down
    if (Link::getInstance().moving())
    {
        switch (Link::getInstance().direction())
        {
        case Direction::DIRECTION_DOWN:
            m_auxiliaryFrame = 2;
            // Move up
            m_direction = { 0,-1 };
            break;
        case Direction::DIRECTION_UP:
            m_auxiliaryFrame = 0;
            // Move down
            m_direction = { 0,1 };
            break;
        case Direction::DIRECTION_LEFT:
            m_auxiliaryFrame = 6;
            // Move right
            m_direction = { 1,0 };
            break;
        case Direction::DIRECTION_RIGHT:
            m_auxiliaryFrame = 4;
            // Move left
            m_direction = { -1,0 };
            break;

        }
        m_position += m_direction * m_speed;
    }
}


}

#endif