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
    m_Texture = nullptr;
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
    else if (x > m_scrollX + CAMERA_WIDTH)
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
    else if (y > m_scrollY + CAMERA_HEIGHT - 16)
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
            player->add(-1, 0);
            m_scrolled += m_scrollSpeed;
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
            player->add(1, 0);
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
            player->add(0, 1);
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
            player->add(0, -1);
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
    SDL_RenderCopy(pRenderer, m_Texture, &srcRect, &dstRect);
    
    trackCharacter();
}

void Camera::setCurrentBackground(SDL_Texture* currentBackground)
{
    m_Texture = currentBackground;
}

// Just for testing as the camera is not controllable
void Camera::control(const SDL_Event& event)
{
   /* switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case BUTTON_RIGHT: scroll(SCROLL_RIGHT); break;
        case BUTTON_LEFT: scroll(SCROLL_LEFT); break;
        case BUTTON_DOWN: scroll(SCROLL_DOWN); break;
        case BUTTON_UP: scroll(SCROLL_UP); break;
        }
    break;
    } */
}

void Camera::setScrollSpeed(int scrollSpeed)
{
    m_scrollSpeed = scrollSpeed;
}
