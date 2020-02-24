#include "Camera.h"
#include "InputControl.h"
#include <assert.h>
#include "Player.h"

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

    Vec2 position = player->position();
    int x = position.x();
    int y = position.y();

    if (x < m_scrollX)
    {
        // Scroll left
        m_scrollLeft = true;
        Controller::getInstance().setController(nullptr);
    }
    else if (x > m_scrollX + CAMERA_WIDTH - SCROLL_X_RIGHT_EDGE)
    {
        // Scroll right
        m_scrollRight = true;
        Controller::getInstance().setController(nullptr);
    }
    else if (y < m_scrollY)
    {
        // Scroll up
        m_scrollUp = true;
        Controller::getInstance().setController(nullptr);
    }
    else if (y > m_scrollY + CAMERA_HEIGHT - 16 /* HUD height because its on the bottom*/)
    {
        // Scroll down
        m_scrollDown = true;
        Controller::getInstance().setController(nullptr);
    }

 
    if (m_scrollLeft)
    {
        if (m_scrolled != CAMERA_WIDTH)
        {
            m_scrollX -= m_scrollSpeed;
            m_scrolled += m_scrollSpeed;
            if (m_scrolled % PLAYER_SCROLL_FACTOR == 0)
            {
                player->add(-PLAYER_SCROLL, 0);
            }
        }
        else
        {
            m_scrollLeft = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
        }
    }
    else if (m_scrollRight)
    {
        if (m_scrolled != CAMERA_WIDTH)
        {
            m_scrollX += m_scrollSpeed;
            m_scrolled += m_scrollSpeed;
            if (m_scrolled % PLAYER_SCROLL_FACTOR == 0)
            {
                player->add(PLAYER_SCROLL, 0);
            }
        }
        else
        {
            m_scrollRight = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
        }
    }
    else if (m_scrollDown)
    {
        if (m_scrolled != CAMERA_HEIGHT)
        {
            m_scrollY += m_scrollSpeed;
            m_scrolled += m_scrollSpeed;
            if (m_scrolled % PLAYER_SCROLL_FACTOR == 0)
            {
                player->add(0, PLAYER_SCROLL);
            }
        }
        else
        {
            m_scrollDown = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
        }
    }
    else if (m_scrollUp)
    {
        if (m_scrolled != CAMERA_HEIGHT)
        {
            m_scrollY -= m_scrollSpeed;
            m_scrolled += m_scrollSpeed;
            if (m_scrolled % PLAYER_SCROLL_FACTOR == 0)
            {
                player->add(0, -PLAYER_SCROLL);
            }
        }
        else
        {
            m_scrollUp = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
        }
    }

}

void Camera::render(SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect = { m_x + m_scrollX, m_y + m_scrollY,m_width ,m_height };
    SDL_Rect dstRect = {0,0,m_width,m_height };
    SDL_RenderCopy(pRenderer, m_texture, &srcRect, &dstRect);
    
    trackCharacter();
}

void Camera::setCurrentBackground(SDL_Texture* currentBackground)
{
    m_texture = currentBackground;
}

// Just for testing as the camera is not controllable
void Camera::control()
{


}

void Camera::setScrollSpeed(int scrollSpeed)
{
    m_scrollSpeed = scrollSpeed;
}
