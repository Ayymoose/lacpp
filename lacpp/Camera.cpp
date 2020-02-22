#include "Camera.h"
#include "InputControl.h"
#include <assert.h>

Camera::Camera()
{
    m_x = 0;
    m_y = 0;
    m_scrollX = 0;
    m_scrollY = 0;
    m_scrollSpeed = 0;
    m_Texture = nullptr;
}

void Camera::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

void Camera::render(SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect = { m_x + m_scrollX, m_y + m_scrollY,CAMERA_WIDTH ,CAMERA_HEIGHT };
    SDL_Rect dstRect = {0,0,CAMERA_WIDTH,CAMERA_HEIGHT};
    SDL_RenderCopy(pRenderer, m_Texture, &srcRect, &dstRect);
}

void Camera::setCurrentBackground(SDL_Texture* currentBackground)
{
    m_Texture = currentBackground;
}

void Camera::control(const SDL_Event& event)
{
    switch (event.type)
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
    } 
}

void Camera::setScrollSpeed(int scrollSpeed)
{
    m_scrollSpeed = scrollSpeed;
}

void Camera::scroll(SCROLL_DIRECTION scrollDirection)
{
    switch (scrollDirection)
    {
    case SCROLL_UP: 
        m_scrollY -=m_scrollSpeed;
        break;
    case SCROLL_RIGHT:
        m_scrollX += m_scrollSpeed;
        break;
    case SCROLL_LEFT: 
        m_scrollX -= m_scrollSpeed;
        break;
    case SCROLL_DOWN:
        m_scrollY += m_scrollSpeed;
        break;
    }
}
