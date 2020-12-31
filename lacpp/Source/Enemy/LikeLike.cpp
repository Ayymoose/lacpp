#include "LikeLike.h"
#include "Common.h"

LikeLike::LikeLike(int x, int y) : Enemy(x, y)
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_ENEMY];
    m_direction = Direction::DIRECTION_DOWN;

    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 5;

    m_speed = 0.5f;

    // Set it off in a random direction
    m_directionVector = { 0, m_speed };

    m_name = "Like Like";
    m_depth = ZD_DEPTH_ENEMY;
    Renderer::getInstance().addRenderable(this);
}

// Common functionality across all it seems
void LikeLike::render(SDL_Renderer* renderer) noexcept
{
    auto animation = m_enemy[static_cast<size_t>(EnemySprite::ENEMY_LIKE_LIKE)];

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

float LikeLike::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> LikeLike::position() const noexcept
{
    return m_positionVector;
}

void LikeLike::die() noexcept
{


}

void LikeLike::attack() noexcept
{
    // Move's randomly in 4 directions only
    // Bouncing off objects
    // Any attempt to move out of the camera will flip it's direction
    // If pushed out the camera by Link, will reach the edge only

    // Basic AI movement
    // Every second, if we hit 1/4 then change direction to a new direction
    // The new direction must not be the same direction and can't be the opposite of the last direction    
    if (m_enemyTimer.elapsed(0.25f))
    {
        // Try to change direction
        auto chance = random(1, 3);
        if (chance == 2)
        {
            auto dir = random(0, 3);
            const Vector<float> dirs[4] =
            {
                {m_speed,0}, {-m_speed, 0}, {0, -m_speed}, {0, m_speed}
            };
            m_directionVector = dirs[dir];
        }
        //m_enemyTimer.reset();
    }

    // If attempt to move out of view, flip direction
    if (!Camera::getInstance().visible({ m_positionVector.x, m_positionVector.y, static_cast<float>(m_width), static_cast<float>(m_height) }))
    {
        m_directionVector = -m_directionVector;
    }

    m_positionVector += m_directionVector;
}
