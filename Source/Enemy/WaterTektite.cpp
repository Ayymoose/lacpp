#if 0


#include "WaterTektite.h"
#include "Common.h"

namespace Zelda
{

WaterTektite::WaterTektite(float x, float y) :
    Renderable("Water Tektite", ResourceManager::getInstance()[Graphic::GFX_ENEMY], ZD_DEPTH_ENEMY),
    Enemy(x, y),
    m_strideLength(48),
    m_strided(0),
    m_stride(false)
{
    m_dir = Direction::DIRECTION_DOWN;

    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;
    m_health = 5;
    m_speed = 1;
    m_direction = { 1,-1 };
}

void WaterTektite::render() noexcept
{
    auto animation = m_enemy[ENEMY_WATER_TEKTITE];

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

void WaterTektite::update() noexcept
{
}

float WaterTektite::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> WaterTektite::position() const noexcept
{
    return m_position;
}

void WaterTektite::die() noexcept
{
    // Can't remember if it dies or not
}

void WaterTektite::attack() noexcept
{
    // Moves in random diagnoal strides
    if (!m_stride)
    {
        auto dir = random(0, 3);
        const Vector<float> dirs[4] =
        {
            {m_speed,m_speed}, {-m_speed, m_speed}, {m_speed, -m_speed}, {-m_speed, -m_speed}
        };
        m_direction = dirs[dir];
        m_stride = true;
    }
    else if (m_stride)
    {
        if (m_strided < m_strideLength)
        {
            // Keep within camera region
            auto nextPositionVector = m_position + m_direction * m_speed;
            if (Camera::getInstance().visible({ nextPositionVector.x, nextPositionVector.y, static_cast<float>(m_width), static_cast<float>(m_height) }))
            {
                m_position += m_direction * m_speed;
                m_strided += (m_direction * m_speed).length();

            }
            else
            {
                m_strided = m_strideLength;
            }
        }
        else
        {
            if (m_enemyTimer.elapsed(0.5f))
            {
                m_strided = 0;
                m_stride = false;
            }

        }
    }
}

}

#endif