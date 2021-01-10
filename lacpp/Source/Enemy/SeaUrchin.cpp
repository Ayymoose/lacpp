#include "SeaUrchin.h"

SeaUrchin::SeaUrchin(float x, float y) : 
    Renderable("Sea Urchin", ResourceManager::getInstance()[Graphic::GFX_ENEMY], ZD_DEPTH_ENEMY),
    Enemy(x, y)
{
    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;
 
    m_health = 3;
}

void SeaUrchin::render(SDL_Renderer* renderer) noexcept
{
    auto animation = m_enemy[ENEMY_SEA_URCHIN];
    
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
        m_positionVector.x - m_xTransition - Camera::getInstance().getX(),
        m_positionVector.y - m_yTransition - Camera::getInstance().getY(),
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
    }
}

float SeaUrchin::health() const noexcept
{
    return m_health;
}

Vector<float> SeaUrchin::position() const noexcept
{
    return m_positionVector;
}

void SeaUrchin::attack() noexcept
{
    // This enemy doesn't move and doesn't do anything except animate
}

void SeaUrchin::die() noexcept
{
}