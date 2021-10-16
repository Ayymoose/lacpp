#include "GopongaFlower.h"

namespace Zelda
{

GopongaFlower::GopongaFlower(float x, float y) :
    Renderable("Goponga Flower", ResourceManager::getInstance()[Graphic::GFX_ENEMY], ZD_DEPTH_ENEMY),
    Enemy(x, y)
{
    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 3;
}

void GopongaFlower::render() noexcept
{
    auto animation = m_enemy[ENEMY_GOPONGA_FLOWER];

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
        m_position.x - m_xTransition - Camera::getInstance().getX(),
        m_position.y - m_yTransition - Camera::getInstance().getY(),
        static_cast<float>(m_width),
        static_cast<float>(m_height)
    };

    SDL_ASSERT(SDL_RenderCopyF(Renderer::getInstance().getRenderer(), m_texture, &m_srcRect, &m_dstRect), SDL_ERROR_MESSAGE);

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

void GopongaFlower::update() noexcept
{
}

float GopongaFlower::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> GopongaFlower::position() const noexcept
{
    return m_position;
}

void GopongaFlower::attack() noexcept
{

}

void GopongaFlower::die() noexcept
{

}

}