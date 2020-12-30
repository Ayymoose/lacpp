#include "Vacuum.h"

Vacuum::Vacuum(int x, int y) : Enemy(x, y)
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_ENEMY];
    m_direction = Direction::DIRECTION_DOWN;

    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 5;


    m_name = "Vacuum";
    m_depth = ZD_DEPTH_ENEMY;
    Renderer::getInstance().addRenderable(this);
}

void Vacuum::render(SDL_Renderer* renderer) noexcept
{
    auto animation = m_enemy[static_cast<size_t>(EnemySprite::ENEMY_VACUUM)];

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
            
            m_animationTimer.reset();
            m_enemyTimer.reset();
        }
    }
    else
    {
        m_currentFrame = animation.startFrame;
        // Wait 2 seconds then reset
        if (m_enemyTimer.elapsed(2.0f))
        {
            m_vacuums = 0;
            m_enemyTimer.reset();
        }
    }

}

float Vacuum::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> Vacuum::position() const noexcept
{
    return m_positionVector;
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