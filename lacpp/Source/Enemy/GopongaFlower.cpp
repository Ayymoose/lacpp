#include "GopongaFlower.h"

GopongaFlower::GopongaFlower(int x, int y) : Enemy(x, y)
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_ENEMY];
    m_direction = Direction::DIRECTION_DOWN;

    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 3;

    m_name = "Goponga Flower";
    m_depth = ZD_DEPTH_ENEMY;
    Renderer::getInstance().addRenderable(this);
}

void GopongaFlower::render(SDL_Renderer* renderer) noexcept
{
    auto animation = m_enemy[static_cast<size_t>(EnemySprite::ENEMY_GOPONGA_FLOWER)];

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
        m_positionVector.x - Camera::getInstance().getX(),
        m_positionVector.y - Camera::getInstance().getY(),
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

float GopongaFlower::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> GopongaFlower::position() const noexcept
{
    return m_positionVector;
}

void GopongaFlower::attack() noexcept
{

}

void GopongaFlower::die() noexcept
{
    
}