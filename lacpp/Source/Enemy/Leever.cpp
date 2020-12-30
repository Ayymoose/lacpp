#include "Leever.h"
#include "Common.h"

Leever::Leever(int x, int y) : Enemy(x, y)
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_ENEMY];
    m_direction = Direction::DIRECTION_DOWN;

    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;

    m_health = 5;
    m_speed = 0.75f;

    m_moving = true;
    m_emerging = true;
    m_burrowing = false;

    // Set it off in a random direction
    m_directionVector = { 0, m_speed };

    m_name = "Leever";
    m_depth = ZD_DEPTH_ENEMY;
    Renderer::getInstance().addRenderable(this);
}

void Leever::render(SDL_Renderer* renderer) noexcept
{
    auto animation = m_enemy[static_cast<size_t>(EnemySprite::ENEMY_LEEVER)];

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

    if (m_emerging || m_moving || m_burrowing)
    {
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


}

float Leever::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> Leever::position() const noexcept
{
    return m_positionVector;
}

void Leever::die() noexcept
{


}

void Leever::attack() noexcept
{
    // Emerges from the ground from a random place and moves towards Link for a while
    // Then burrows back in and appears at a random place again
    
    if (m_emerging)
    {
        // If emerging, we will play the emerging frame for 2 frames
        if (m_currentFrame == 1)
        {
            m_auxiliaryFrame = 2;
            m_emerging = false;
        }
        m_enemyTimer.reset();
    }
    else
    {
        if (!m_burrowing && m_enemyTimer.elapsed(3.0f))
        {
            // Burrow back in the ground again
            m_burrowing = true;
            m_enemyTimer.reset();
        }
    }
    
    if (m_burrowing)
    {
        m_auxiliaryFrame = 4;
        if (m_currentFrame == 1)
        {
            m_burrowing = false;
            m_moving = false;
        }
    }

    if (!m_burrowing && !m_moving && !m_emerging)
    {
        if (m_emergeTimer.elapsed(8.0f))
        {
            // Appear at a random place within sand area only!
            m_positionVector.x = random(0, CAMERA_WIDTH) - Camera::getInstance().getX();
            m_positionVector.y = random(0, CAMERA_HEIGHT - m_height) - Camera::getInstance().getY();

            m_emerging = true;
            m_moving = true;
            m_emergeTimer.reset();
        }
    }

    if (m_moving && !m_emerging && !m_burrowing)
    {
        Vector<float> linkPositionVector = Link::getInstance().position();
        m_directionVector = linkPositionVector - m_positionVector;
        // Can't remember what this 0.01 was for
        // Ah yes, prevent division by 0 if they are at the same position
        if (m_directionVector.length() > 0.1f)
        {
            m_directionVector.normalise();
            m_positionVector += m_directionVector * m_speed;
        }
    }
}
