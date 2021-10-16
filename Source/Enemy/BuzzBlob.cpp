#include "BuzzBlob.h"
#include "Common.h"

namespace Zelda
{

BuzzBlob::BuzzBlob(float x, float y) :
    Renderable("Buzz Blob", ResourceManager::getInstance()[Graphic::GFX_ENEMY], ZD_DEPTH_ENEMY),
    Enemy(x, y),
    m_bigEyes(true)
{
    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 5;

    m_speed = 0.5f;

    // Set it off in a random direction
    m_direction = { 0, m_speed };

}

void BuzzBlob::render() noexcept
{
    auto animation = m_enemy[ENEMY_BUZZ_BLOB];

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

    SDL_ASSERT(SDL_RenderCopyExF(Renderer::getInstance().getRenderer(), m_texture, &m_srcRect, &m_dstRect, 0, nullptr, m_flip), SDL_ERROR_MESSAGE);

    if (m_animationTimer.elapsed(m_animationFPS) && !Engine::getInstance().paused())
    {
        if (m_currentFrame < m_endFrame)
        {
            m_currentFrame++;
        }
        else
        {
            m_currentFrame = animation.startFrame;
            if (m_flip == SDL_RendererFlip::SDL_FLIP_NONE)
            {
                m_flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
            }
            else
            {
                m_flip = SDL_RendererFlip::SDL_FLIP_NONE;
            }
        }
    }

    // Cukeman
    if (m_bigEyes)
    {
        m_auxiliaryFrame = 3;
    }
}

void BuzzBlob::update() noexcept
{
}

float BuzzBlob::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> BuzzBlob::position() const noexcept
{
    return m_position;
}

void BuzzBlob::die() noexcept
{


}

void BuzzBlob::attack() noexcept
{
    // Move's randomly in 4 directions only
    // Bouncing off objects
    // Any attempt to move out of the camera will flip it's direction
    // If pushed out the camera by Link, will reach the edge only

    // Basic AI movement
    // Every second, if we hit 1/4 then change direction to a new direction
    // The new direction must not be the same direction and can't be the opposite of the last direction 

    // BUG: The enemy can still get stuck at the border between the camera edge it seems and "vibrate"
    if (m_enemyTimer.elapsed(0.5f))
    {
        // Try to change direction
        auto chance = random(1, 3);
        if (chance == 2)
        {
            auto dir = random(0, 7);
            const Vector<float> dirs[8] =
            {
                {m_speed,0},
                {-m_speed, 0},
                {0, -m_speed},
                {0, m_speed},
                {m_speed,m_speed},
                {-m_speed, m_speed},
                {m_speed, -m_speed},
                {m_speed, m_speed}
            };
            m_direction = dirs[dir];
        }
    }

    // If attempt to move out of view, flip direction
    if (!Camera::getInstance().visible({ m_position.x, m_position.y, static_cast<float>(m_width), static_cast<float>(m_height) }))
    {
        m_direction = -m_direction;
    }

    m_position += m_direction;
}

}