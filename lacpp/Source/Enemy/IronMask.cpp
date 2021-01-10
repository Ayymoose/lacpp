#include "IronMask.h"
#include "Common.h"

IronMask::IronMask(float x, float y) : Enemy(x, y)
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_ENEMY];
    m_direction = Direction::DIRECTION_DOWN;

    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 5;
    m_moving = false;
    m_speed = 1;
    m_exposed = true;

    // Set it off in a random direction
    m_directionVector = { 0, m_speed };

    m_name = "Iron Mask";
    m_depth = ZD_DEPTH_ENEMY;
}

void IronMask::render(SDL_Renderer* renderer) noexcept
{
    auto animation = m_enemy[static_cast<size_t>(EnemySprite::ENEMY_IRON_MASK)];

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
        m_positionVector.x - m_xTransition - static_cast<float>(Camera::getInstance().getX()),
        m_positionVector.y - m_yTransition - static_cast<float>(Camera::getInstance().getY()),
        static_cast<float>(m_width),
        static_cast<float>(m_height)
    };

    SDL_ASSERT(SDL_RenderCopyF(renderer, m_texture, &m_srcRect, &m_dstRect), SDL_ERROR_MESSAGE);

    if (m_animationTimer.elapsed(m_animationFPS) && !Engine::getInstance().paused())
    {
        if (m_moving)
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

float IronMask::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> IronMask::position() const noexcept
{
    return m_positionVector;
}

void IronMask::die() noexcept
{


}

void IronMask::attack() noexcept
{
    // Move's randomly in 4 directions only
    
    // Basic AI movement
    // Walks in one direction for a random amount of steps
    // Then thinks for a while
    // Then repeats
    
    if (m_enemyTimer.elapsed(0.5f) && !m_moving)
    {
        // Try to change direction
        auto chance = random(1, 2);
        if (chance == 2)
        {
            auto dir = random(0, 3);
            const Direction dirs[4] =
            {
                Direction::DIRECTION_UP, Direction::DIRECTION_DOWN, Direction::DIRECTION_LEFT, Direction::DIRECTION_RIGHT
            };

            if (!m_exposed)
            {
                switch (dirs[dir])
                {
                case Direction::DIRECTION_DOWN: 
                    m_auxiliaryFrame = 0; 
                    m_directionVector = { 0, m_speed };
                    break;
                case Direction::DIRECTION_UP: 
                    m_auxiliaryFrame = 2; 
                    m_directionVector = { 0, -m_speed };
                    break;
                case Direction::DIRECTION_LEFT: 
                    m_auxiliaryFrame = 4; 
                    m_directionVector = { -m_speed, 0 };
                    break;
                case Direction::DIRECTION_RIGHT: 
                    m_auxiliaryFrame = 6; 
                    m_directionVector = { m_speed, 0 };
                    break;
                }
            }
            else
            {
                // TODO: Pick a random direction
                const Vector<float> dirs[4] =
                {
                    {m_speed, 0}, {0, m_speed}, {-m_speed, 0}, {0, -m_speed}
                };
                m_directionVector = dirs[dir];
                m_auxiliaryFrame = 8;
            }
            m_moving = true;
        }
    }
    else if (m_moving)
    {
        // Walk a random amount of steps
        static auto steps = random(8, 24);
        if (m_steps < steps)
        {
            m_positionVector += m_directionVector;
            m_steps++;
        }
        else
        {
            m_steps = 0;
            m_moving = false;
        }
    }
}
