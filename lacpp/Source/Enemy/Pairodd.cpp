#include "Pairodd.h"
#include "Common.h"

namespace Zelda
{

Pairodd::Pairodd(float x, float y) :
    Renderable("Pairodd", ResourceManager::getInstance()[Graphic::GFX_ENEMY], ZD_DEPTH_ENEMY),
    Enemy(x, y),
    m_idle(true),
    m_disappear(false),
    m_appear(false)
{
    // Values likely to be different per enemy
    m_width = 16;
    m_height = 16;
    m_health = 3;
}

void Pairodd::render(SDL_Renderer* renderer) noexcept
{
    auto animation = m_enemy[EnemySprite::ENEMY_PAIRODD];

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
        m_positionVector.x - m_xTransition - static_cast<float>(Camera::getInstance().getX()),
        m_positionVector.y - m_yTransition - static_cast<float>(Camera::getInstance().getY()),
        static_cast<float>(m_width),
        static_cast<float>(m_height)
    };



    // Draw the second part of the vanish
    if ((!m_idle && m_currentFrame == 2) || (m_appear == true && m_currentFrame == 2))
    {
        m_dstRect.x -= 8;
        SDL_ASSERT(SDL_RenderCopyExF(renderer, m_texture, &m_srcRect, &m_dstRect, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE), SDL_ERROR_MESSAGE);
        m_dstRect.x += 16;
        SDL_ASSERT(SDL_RenderCopyExF(renderer, m_texture, &m_srcRect, &m_dstRect, 0, nullptr, SDL_RendererFlip::SDL_FLIP_HORIZONTAL), SDL_ERROR_MESSAGE);
    }
    else
    {
        if (!m_disappear || m_appear)
        {
            SDL_ASSERT(SDL_RenderCopyExF(renderer, m_texture, &m_srcRect, &m_dstRect, 0, nullptr, m_flip), SDL_ERROR_MESSAGE);
        }
        else
        {
            if (m_enemyTimer.elapsed(2.5f))
            {
                m_appear = true;

                // TODO: Appear at random place alligned to 16 by 16
                // Appear at place 32 pixels away from Link usually on other side
                m_positionVector.x = random(0, CAMERA_WIDTH);
                m_positionVector.y = random(0, CAMERA_HEIGHT);

                // TODO: Fire something at Link
            }
        }
    }

    if (m_animationTimer.elapsed(m_animationFPS) && !Engine::getInstance().paused())
    {
        // If idle, flip first frame back and forth
        // If player comes close enough, idle is false and run to end of frame
        // At end of frame, disappear for a few seconds (2?) 
        // Appear in a random place (tile alligned)
        // Reverse the frame to first frame and set idle to true and fire bolt(?) at Link

        if (m_idle)
        {
            if (m_flip == SDL_RendererFlip::SDL_FLIP_NONE)
            {
                m_flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
            }
            else
            {
                m_flip = SDL_RendererFlip::SDL_FLIP_NONE;
            }
        }
        else if (!m_disappear)
        {
            // Link got too close, disappear
            if (m_currentFrame < m_endFrame)
            {
                m_currentFrame++;
            }
            else
            {
                // Disappear for 1 second and reverse the frame
                m_disappear = true;
            }
        }
        else if (m_appear)
        {
            if (m_currentFrame > animation.startFrame)
            {
                m_currentFrame--;
            }
            else
            {
                // Disappear for 1 second and reverse the frame
                m_disappear = false;
                m_appear = false;
                m_idle = true;
            }
        }


    }

    // TODO: Check what distance 
    float distToLink = Vector<float>::distanceBetween(m_positionVector, Link::getInstance().position());
    if (distToLink < 32)
    {
        m_idle = false;
    }
}

float Pairodd::health() const noexcept
{
    // TODO: Return -1 for enemys that can't be killed
    return m_health;
}

Vector<float> Pairodd::position() const noexcept
{
    return m_positionVector;
}

void Pairodd::attack() noexcept
{

}

void Pairodd::die() noexcept
{
}

}