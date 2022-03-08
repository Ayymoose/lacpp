#if 0


#include "Peahat.h"
#include "Common.h"
#include "Drawing.h"

namespace Zelda
{

Peahat::Peahat(float x, float y) :
    Renderable("Peahat", ResourceManager::getInstance()[SpriteResource::SPR_ENEMY], ZD_DEPTH_ENEMY),
    Enemy(x, y),
    m_startingUp(true),
    m_coolDown(false),
    m_risen(0)
{
    m_dir = Direction::DIRECTION_DOWN;
    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;
    m_health = 5;
    m_speed = 0.5f;
}

void Peahat::render() noexcept
{
    auto animation = m_enemy[ENEMY_PEAHAT];

    m_animateXPos = animation.x;
    m_animateYPos = animation.y;
    m_endFrame = animation.endFrame;
    if (m_startingUp || m_coolDown)
    {
        m_animationFPS = animation.animationFPS * 2.0f;
    }
    else
    {
        m_animationFPS = animation.animationFPS;
    }

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

    if (m_animationTimer.elapsed(m_animationFPS) && !Engine::getInstance().paused())
    {
        if (m_moving || m_startingUp || m_coolDown)
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

void Peahat::update() noexcept
{
}

float Peahat::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> Peahat::position() const noexcept
{
    return m_position;
}

void Peahat::die() noexcept
{


}

void Peahat::attack() noexcept
{
    // Stays stationary for a while then
    // Starts spinning then rises up and once risen, moves around before settling back
    // on the ground again
    if (m_startingUp)
    {
        if (m_enemyTimer.elapsed(0.25f))
        {
            if (m_risen < 8)
            {
                m_risen++;
                m_position.y--;
            }
            else
            {
                m_startingUp = false;
                m_moving = true;
                m_risen = 0;
            }
        }
    }
    else if (m_moving)
    {
        if (m_enemyTimer.elapsed(0.25f))
        {
            // Try to change direction
            auto chance = random(1, 3);
            if (chance == 2)
            {
                auto dir = random(0, 7);
                const Vector<float> dirs[8] =
                {
                    {m_speed,0},
                    {-m_speed, 0},
                    {0, -m_speed},
                    {0, m_speed},
                    {m_speed,m_speed},
                    {-m_speed, m_speed},
                    {m_speed, -m_speed},
                    {-m_speed, -m_speed}
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

        if (m_cooldownTimer.elapsed(8.0f))
        {
            m_coolDown = true;
            m_moving = false;
            //m_cooldownTimer.reset();
        }
    }
    else if (m_coolDown)
    {
        if (m_enemyTimer.elapsed(0.25f))
        {
            if (m_risen < 8)
            {
                m_risen++;
                m_position.y++;
            }
            else
            {
                m_coolDown = false;
                m_risen = 0;
            }
        }
    }

}

}

#endif