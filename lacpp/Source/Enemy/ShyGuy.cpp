#include "ShyGuy.h"
#include "Common.h"

ShyGuy::ShyGuy(int x, int y) : Enemy(x, y)
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_ENEMY];
    m_direction = Direction::DIRECTION_DOWN;

    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 5;

    m_speed = 1;

    m_name = "Shy Guy";
    m_depth = ZD_DEPTH_ENEMY;
    Renderer::getInstance().addRenderable(this);
}

void ShyGuy::render(SDL_Renderer* renderer) noexcept
{
    auto animation = m_enemy[static_cast<size_t>(EnemySprite::ENEMY_SHY_GUY)];

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
        m_positionVector.x - static_cast<float>(Camera::getInstance().getX()),
        m_positionVector.y - static_cast<float>(Camera::getInstance().getY()),
        static_cast<float>(m_width),
        static_cast<float>(m_height)
    };

    ZD_ASSERT(SDL_RenderCopyF(renderer, m_texture, &m_srcRect, &m_dstRect) == 0, "SDL Error: " << SDL_GetError());

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
                m_animationTimer.reset();
            }
        }
        else
        {
            m_currentFrame = animation.startFrame;
        }

    }

}

float ShyGuy::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> ShyGuy::position() const noexcept
{
    return m_positionVector;
}

void ShyGuy::attack() noexcept
{
    // This enemy doesn't attack
}

void ShyGuy::die() noexcept
{


}

void ShyGuy::move() noexcept
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
            m_directionVector = { 0,-1 };
            break;
        case Direction::DIRECTION_UP:
            m_auxiliaryFrame = 0;
            // Move down
            m_directionVector = { 0,1 };
            break;
        case Direction::DIRECTION_LEFT:
            m_auxiliaryFrame = 6;
            // Move right
            m_directionVector = { 1,0 };
            break;
        case Direction::DIRECTION_RIGHT:
            m_auxiliaryFrame = 4;
            // Move left
            m_directionVector = { -1,0 };
            break;

        }
        m_positionVector += m_directionVector * m_speed;
    }
}
