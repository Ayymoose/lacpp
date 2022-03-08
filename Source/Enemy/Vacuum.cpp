#if 0


#include "Vacuum.h"

// TODO: Boolean for suck or push Link in/away

namespace Zelda
{

Vacuum::Vacuum(float x, float y) :
    Renderable("Vacuum", ResourceManager::getInstance()[SpriteResource::SPR_ENEMY], ZD_DEPTH_ENEMY),
    Enemy(x, y),
    m_vacuums(0)
{
    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 5;

}

void Vacuum::render() noexcept
{
    auto animation = m_enemy[ENEMY_VACUUM];

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

    SDL_ASSERT(SDL_RenderCopyF(Renderer::getInstance().getRenderer(), m_texture, &m_srcRect, &m_dstRect));

    if (m_vacuums < MAX_VACUUMS)
    {
        if (m_animationTimer.elapsed(m_animationFPS) && !Engine::getInstance().paused())
        {
            if (m_currentFrame < m_endFrame)
            {
                m_currentFrame++;
            }
            else
            {
                m_currentFrame = animation.startFrame;
                m_vacuums++;
            }
        }
    }
    else
    {
        m_currentFrame = animation.startFrame;
        // Wait 2 seconds then reset
        if (m_enemyTimer.elapsed(2.0f))
        {
            m_vacuums = 0;
        }
    }

}

void Vacuum::update() noexcept
{
}

float Vacuum::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> Vacuum::position() const noexcept
{
    return m_position;
}

void Vacuum::attack() noexcept
{
    // "Vacuums" 8 times with a 2 second pause in between
    // Attacking when m_vacuums < MAX_VACUUMS
}

void Vacuum::die() noexcept
{
    // Can't remember if it dies or not
}

}

#endif