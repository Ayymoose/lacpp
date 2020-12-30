#include "HardhatBeetle.h"
#include "Link.h"

HardhatBeetle::HardhatBeetle(int x, int y) : Enemy(x, y)
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

    m_name = "Hardhat Beetle";
    m_depth = ZD_DEPTH_ENEMY;
    Renderer::getInstance().addRenderable(this);
}

void HardhatBeetle::render(SDL_Renderer* renderer) noexcept
{
    auto animation = m_enemy[static_cast<size_t>(EnemySprite::ENEMY_HARDHAT_BEETLE)];

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
        m_animationTimer.reset();
    }
}

float HardhatBeetle::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> HardhatBeetle::position() const noexcept
{
    return m_positionVector;
}

void HardhatBeetle::die() noexcept
{


}

void HardhatBeetle::attack() noexcept
{
    // Moves towards Link
    Vector<float> linkPositionVector = Link::getInstance().position();
    m_directionVector = linkPositionVector - m_positionVector;
    
    // Can't remember what this 0.01 was for
    // Ah yes, prevent division by 0 if they are at the same position
    if (m_directionVector.length() > 0.01f)
    {
        m_directionVector.normalise();
    }
    m_positionVector += m_directionVector * m_speed;
}
