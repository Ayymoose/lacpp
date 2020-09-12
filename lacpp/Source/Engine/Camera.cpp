#include "Camera.h"
#include "InputControl.h"
#include <assert.h>
#include "Link.h"
#include "Renderer.h"
#include "Depth.h"
#include "ZD_Assert.h"

using namespace Zelda;

Camera::Camera()
{
    m_x = 0;
    m_y = 0;
    m_scrollX = 0;
    m_scrollY = 0;
    m_scrollSpeed = 0;
    m_texture = nullptr;
    m_width = CameraWidth;
    m_height = CameraHeight;
    m_scrollCamera = false;
    m_scrolled = 0;
    m_scrollLeft = false;
    m_scrollRight = false;
    m_scrollDown = false;
    m_scrollUp = false;
    m_tracker = nullptr;

    m_depth = ZD_DEPTH_BACKGROUND;

    m_name = "Camera";
    Renderer::getInstance().addRenderable(this);
}

void Camera::setPosition(int x, int y) noexcept
{
    m_x = x;
    m_y = y;
}

void Camera::track(Character* character) noexcept
{
    m_tracker = character;
}

void Camera::trackCharacter() noexcept
{
    assert(m_tracker != nullptr);

    // We will only ever track the player
    Link* player = dynamic_cast<Link*>(m_tracker);
    assert(player != nullptr);

    Vector<float> position = player->position();
    float x = position.x;
    float y = position.y;

    // Transition the player if they move off the screen
    if (x < m_scrollX && !m_scrollLeft)
    {
        // Scroll left
        m_scrollLeft = true;
        Controller::getInstance().setController(nullptr);

        // TODO: Globalise
        player->m_currentCollisionMapX--;
        std::cout << "Scrolling left" << std::endl;
    }
    else if (x > m_scrollX + CameraWidth - ScrollRightEdge && !m_scrollRight)
    {
        // Scroll right
        m_scrollRight = true;
        Controller::getInstance().setController(nullptr);

        // TODO: Globalise
        player->m_currentCollisionMapX++;
        std::cout << "Scrolling right" << std::endl;


    }
    else if (y < m_scrollY && !m_scrollUp)
    {
        // Scroll up
        m_scrollUp = true;
        Controller::getInstance().setController(nullptr);

        // TODO: Globalise
        player->m_currentCollisionMapY--;
        std::cout << "Scrolling up" << std::endl;

    }
    else if (y > m_scrollY + CameraHeight - HUDHeight /* HUD height because its on the bottom*/ && !m_scrollDown)
    {
        // Scroll down
        m_scrollDown = true;
        Controller::getInstance().setController(nullptr);

        // TODO: Globalise
        player->m_currentCollisionMapY++;
        std::cout << "Scrolling down" << std::endl;


    }
 
    if (m_scrollLeft)
    {
        if (m_scrolled != CameraWidth)
        {
            m_scrollX -= m_scrollSpeed;
            m_scrolled += m_scrollSpeed;
            if (m_timerPlayerScroll.update(FPS_33))
            {
                player->addPosition(-PlayerScrollSpeed, 0);
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
        if (m_scrolled != CameraWidth)
        {
            m_scrollX += m_scrollSpeed;
            m_scrolled += m_scrollSpeed;
            if (m_timerPlayerScroll.update(FPS_33))
            {
                player->addPosition(PlayerScrollSpeed, 0);
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
        if (m_scrolled != CameraHeight)
        {
            m_scrollY += m_scrollSpeed;
            m_scrolled += m_scrollSpeed;
            if (m_timerPlayerScroll.update(FPS_33))
            {
                player->addPosition(0, PlayerScrollSpeed);
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
        if (m_scrolled != CameraHeight)
        {
            m_scrollY -= m_scrollSpeed;
            m_scrolled += m_scrollSpeed;
            if (m_timerPlayerScroll.update(FPS_33))
            {
                player->addPosition(0, -PlayerScrollSpeed);
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

void Camera::render(SDL_Renderer* pRenderer) noexcept
{
    trackCharacter();

    SDL_Rect srcRect = { m_x + m_scrollX, m_y + m_scrollY,m_width ,m_height };
    SDL_Rect dstRect = { 0, 0, m_width, m_height };
    ZD_ASSERT(SDL_RenderCopy(pRenderer, m_texture, &srcRect, &dstRect) == 0, "SDL Error: " << SDL_GetError());
    

}

void Camera::setCurrentBackground(SDL_Texture* currentBackground) noexcept
{
    m_texture = currentBackground;
}

bool Camera::visible(Vector<float> point) const noexcept
{
    float x = point.x;
    float y = point.y;

    if (x < m_scrollX)
    {
        return false;
    }
    else if (x > m_scrollX + CameraWidth)
    {
        return false;
    }
    else if (y < m_scrollY)
    {
        return false;
    }
    else if (y > m_scrollY + CameraHeight - HUDHeight /* HUD height because its on the bottom*/)
    {
        return false;
    }

    return true;
}

void Camera::setScrollSpeed(int scrollSpeed) noexcept
{
    ZD_ASSERT(CameraWidth % scrollSpeed == 0, "scrollSpeed not multiple of CameraWidth");
    ZD_ASSERT(CameraHeight % scrollSpeed == 0, "scrollSpeed not multiple of CameraHeight");
    m_scrollSpeed = scrollSpeed;
}



int Camera::getX() const noexcept
{
    return m_scrollX;
}
int Camera::getY() const noexcept
{
    return m_scrollY;
}