#if 0


#include "ThreeOfAKind.h"
#include "Common.h"

namespace Zelda
{

ThreeOfAKind::ThreeOfAKind(float x, float y) :
    Renderable("Three Of A Kind", ResourceManager::getInstance()[SpriteResource::SPR_ENEMY], ZD_DEPTH_ENEMY),
    Enemy(x, y)
{
    m_dir = Direction::DIRECTION_DOWN;

    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 5;
    m_moving = false;
    m_speed = 1;
    // Set it off in a random direction
    m_direction = { 0, m_speed };

}

void ThreeOfAKind::render() noexcept
{
    auto animation = m_enemy[ENEMY_THREE_OF_A_KIND];

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
        m_position.x - m_xTransition - static_cast<float>(Camera::getInstance().getX()),
        m_position.y - m_yTransition - static_cast<float>(Camera::getInstance().getY()),
        static_cast<float>(m_width),
        static_cast<float>(m_height)
    };

    SDL_ASSERT(SDL_RenderCopyExF(Renderer::getInstance().getRenderer(), m_texture, &m_srcRect, &m_dstRect, m_orientation, nullptr, m_flip));

    if (m_animationTimer.elapsed(m_animationFPS) && !Engine::getInstance().paused())
    {
        if (m_currentFrame < m_endFrame)
        {
            m_currentFrame++;
            // Flip sprite every odd frame index when moving
            if (m_moving)
            {
                if (m_currentFrame & 1)
                {
                    m_flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
                }
                else
                {
                    m_flip = SDL_RendererFlip::SDL_FLIP_NONE;
                }
            }
        }
        else
        {
            m_currentFrame = animation.startFrame;
        }
    }
}

void ThreeOfAKind::update() noexcept
{
}

float ThreeOfAKind::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> ThreeOfAKind::position() const noexcept
{
    return m_position;
}

void ThreeOfAKind::die() noexcept
{


}

void ThreeOfAKind::attack() noexcept
{
    // Move's randomly in 4 directions only

    // Basic AI movement
    // Walks in one direction for a random amount of steps
    // Then thinks for a while
    // Then repeats

    if (m_enemyTimer.elapsed(0.5f) && !m_moving)
    {
        // Try to change direction
        auto chance = random(1, 2);
        if (chance == 2)
        {
            auto dir = random(0, 3);

            // TODO: Pick a random direction
            const Vector<float> dirs[4] =
            {
                {m_speed, 0}, {0, m_speed}, {-m_speed, 0}, {0, -m_speed}
            };
            m_direction = dirs[dir];

            m_moving = true;
        }
    }
    else if (m_moving)
    {
        // Walk a random amount of steps
        static auto steps = random(48, 96);
        if (m_steps < steps)
        {
            m_position += m_direction;
            m_steps++;
        }
        else
        {
            m_steps = 0;
            m_moving = false;
        }
    }
}

}

#endif