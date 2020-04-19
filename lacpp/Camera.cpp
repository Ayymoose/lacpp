#include "Camera.h"
#include "InputControl.h"
#include <assert.h>
#include "Player.h"
#include "Renderer.h"
#include "Depth.h"

Camera::Camera()
{
    m_x = 0;
    m_y = 0;
    m_scrollX = 0;
    m_scrollY = 0;
    m_scrollSpeed = 0;
    m_texture = nullptr;
    m_width = CAMERA_WIDTH;
    m_height = CAMERA_HEIGHT;
    m_scrollCamera = false;
    m_scrolled = 0;
    m_scrollLeft = false;
    m_scrollRight = false;
    m_scrollDown = false;
    m_scrollUp = false;
    m_tracker = nullptr;

    m_depth = BACKGROUND_DEPTH;

    Renderer::getInstance().addRenderable(this);
}

void Camera::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

void Camera::track(Character* character)
{
    m_tracker = character;
}

void Camera::trackCharacter()
{
    assert(m_tracker != nullptr);

    // We will only ever track the player
    Player* player = dynamic_cast<Player*>(m_tracker);
    assert(player != nullptr);

    Vec2<float> position = player->position();
    float x = position.x; float y = position.y;

    if (x < m_scrollX)
    {
        // Scroll left
        m_scrollLeft = true;
        player->m_currentCollisionMapX--;
        Controller::getInstance().setController(nullptr);
    }
    else if (x > m_scrollX + CAMERA_WIDTH - SCROLL_RIGHT_EDGE)
    {
        // Scroll right
        m_scrollRight = true;
        player->m_currentCollisionMapX++;
        Controller::getInstance().setController(nullptr);
    }
    else if (y < m_scrollY)
    {
        // Scroll up
        m_scrollUp = true;
        player->m_currentCollisionMapY--;
        Controller::getInstance().setController(nullptr);
    }
    else if (y > m_scrollY + CAMERA_HEIGHT - 16 /* HUD height because its on the bottom*/)
    {
        // Scroll down
        m_scrollDown = true;
        player->m_currentCollisionMapY++;
        Controller::getInstance().setController(nullptr);
    }

 
    if (m_scrollLeft)
    {
        if (m_scrolled != CAMERA_WIDTH)
        {
            if (m_timerCameraScroll.update(FPS_66))
            {
                m_scrollX -= m_scrollSpeed;
                m_scrolled += m_scrollSpeed;
                if (m_timerPlayerScroll.update(FPS_33))
                {
                    player->addPosition(-PLAYER_SCROLL_SPEED, 0);
                }
            }

        }
        else
        {
            m_scrollLeft = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
            player->resetAnimation();
        }
    }
    else if (m_scrollRight)
    {
        if (m_scrolled != CAMERA_WIDTH)
        {
            if (m_timerCameraScroll.update(FPS_66))
            {
                m_scrollX += m_scrollSpeed;
                m_scrolled += m_scrollSpeed;
                if (m_timerPlayerScroll.update(FPS_33))
                {
                    player->addPosition(PLAYER_SCROLL_SPEED, 0);
                }
            }
        }
        else
        {
            m_scrollRight = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
            player->resetAnimation();
        }
    }
    else if (m_scrollDown)
    {
        if (m_scrolled != CAMERA_HEIGHT)
        {
            if (m_timerCameraScroll.update(FPS_66))
            {
                m_scrollY += m_scrollSpeed;
                m_scrolled += m_scrollSpeed;
                if (m_timerPlayerScroll.update(FPS_33))
                {
                    player->addPosition(0, PLAYER_SCROLL_SPEED);
                }
            }
        }
        else
        {
            m_scrollDown = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
            player->resetAnimation();
        }
    }
    else if (m_scrollUp)
    {
        if (m_scrolled != CAMERA_HEIGHT)
        {
            if (m_timerCameraScroll.update(FPS_66))
            {
                m_scrollY -= m_scrollSpeed;
                m_scrolled += m_scrollSpeed;
                if (m_timerPlayerScroll.update(FPS_33))
                {
                    player->addPosition(0, -PLAYER_SCROLL_SPEED);
                }
            }
        }
        else
        {
            m_scrollUp = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
            player->resetAnimation();
        }
    }

}

void Camera::render(SDL_Renderer* pRenderer)
{
    if (m_tracker)
    {
        trackCharacter();
    }

    SDL_Rect srcRect = { m_x + m_scrollX, m_y + m_scrollY,m_width ,m_height };
    SDL_Rect dstRect = { 0, 0, m_width, m_height };
    assert(SDL_RenderCopy(pRenderer, m_texture, &srcRect, &dstRect) == 0);
    

}

void Camera::setCurrentBackground(SDL_Texture* currentBackground)
{
    m_texture = currentBackground;
}

void Camera::control()
{
    m_keyboardState = SDL_GetKeyboardState(nullptr);
    if (m_keyboardState[BUTTON_RIGHT])
    {
        if (m_timerCameraScroll.update(FPS_66))
        {
            m_scrollX += m_scrollSpeed;
        }
    }
    if (m_keyboardState[BUTTON_LEFT])
    {
        if (m_timerCameraScroll.update(FPS_66))
        {
            m_scrollX -= m_scrollSpeed;
        }
    }
    if (m_keyboardState[BUTTON_UP])
    {
        if (m_timerCameraScroll.update(FPS_66))
        {
            m_scrollY -= m_scrollSpeed;
        }
    }
    if (m_keyboardState[BUTTON_DOWN])
    {
        if (m_timerCameraScroll.update(FPS_66))
        {
            m_scrollY += m_scrollSpeed;
        }
    }

}

void Camera::setScrollSpeed(int scrollSpeed)
{
    m_scrollSpeed = scrollSpeed;
}

int Camera::getX() const
{
    return m_scrollX;
}
int Camera::getY() const
{
    return m_scrollY;
}