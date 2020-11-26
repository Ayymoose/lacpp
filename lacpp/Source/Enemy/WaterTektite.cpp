#include "WaterTektite.h"
#include "Common.h"

WaterTektite::WaterTektite(int x, int y) : Enemy(x, y)
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_ENEMY];
    m_direction = Direction::DIRECTION_DOWN;

    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 5;

    m_speed = 1;
    m_strideLength = 48;
    m_strided = 0;
    m_stride = false;
    m_directionVector = { 1,-1 };

    m_name = "Water Tektite";
    m_depth = ZD_DEPTH_ENEMY;
    Renderer::getInstance().addRenderable(this);
}

void WaterTektite::render(SDL_Renderer* renderer) noexcept
{
    auto animation = m_enemy[static_cast<size_t>(EnemySprite::ENEMY_WATER_TEKTITE)];

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

    ZD_ASSERT(SDL_RenderCopyF(renderer, m_texture, &m_srcRect, &m_dstRect) == 0, "SDL Error: " << SDL_GetError());

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
        m_animationTimer.reset();
    }
}

float WaterTektite::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> WaterTektite::position() const noexcept
{
    return m_positionVector;
}

void WaterTektite::attack() noexcept
{
    // This enemy doesn't attack
}

void WaterTektite::die() noexcept
{
    // Can't remember if it dies or not
}

void WaterTektite::move() noexcept
{
    // Moves in random diagnoal strides
    if (!m_stride)
    {
        auto dir = random(0, 3);
        const Vector<float> dirs[4] =
        {
            {m_speed,m_speed}, {-m_speed, m_speed}, {m_speed, -m_speed}, {-m_speed, -m_speed}
        };
        m_directionVector = dirs[dir];
        m_stride = true;
    }
    else if (m_stride)
    {
        if (m_strided < m_strideLength)
        {
            // Keep within camera region
            auto nextPositionVector = m_positionVector + m_directionVector * m_speed;
            if (Camera::getInstance().visible({ nextPositionVector.x, nextPositionVector.y, static_cast<float>(m_width), static_cast<float>(m_height)}))
            {
                m_positionVector += m_directionVector * m_speed;
                m_strided += (m_directionVector * m_speed).length();
                
            }
            else
            {
                m_strided = m_strideLength;
            }
            m_enemyTimer.reset();
        }
        else
        {
            if (m_enemyTimer.elapsed(0.5f))
            {
                m_strided = 0;
                m_stride = false;
                m_enemyTimer.reset();
            }

        }
    }
}
