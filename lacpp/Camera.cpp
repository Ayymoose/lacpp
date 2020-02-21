#include "Camera.h"
#include "InputControl.h"
#include <assert.h>

Camera::Camera()
{
    m_x = 0;
    m_y = 0;
    m_scrollSpeed = 0;
    m_Texture = nullptr;
    m_cameraWidth = 0;
    m_cameraHeight = 0;
}

void Camera::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

void Camera::render(SDL_Renderer* pRenderer)
{
    SDL_Rect rect = {m_x,m_y,160,128};
    SDL_RenderCopyEx(pRenderer, m_Texture, &rect, nullptr,0, nullptr, SDL_FLIP_NONE);
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
    case SCROLL_UP: m_y-=m_scrollSpeed;  break;
    case SCROLL_RIGHT: m_x+= m_scrollSpeed;  break;
    case SCROLL_LEFT: m_x-= m_scrollSpeed; break;
    case SCROLL_DOWN: m_y+= m_scrollSpeed; break;
    }
}
