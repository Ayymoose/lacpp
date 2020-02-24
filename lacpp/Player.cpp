#include "Player.h"
#include "Resource.h"
#include "InputControl.h"
#include "Vec2.h"

Player::Player()
{
    m_Texture = ResourceManager::getInstance()[RSC_LINK];
    m_position.set(64, 64);
    m_jumpVector.set(0, 0);
    m_width = 16;
    m_height = 16;

    m_health = 3;

    currentTicks = SDL_GetTicks();
    currentFrame = 0;
    max_frame = 1;
    m_camera = nullptr;
}

Player::~Player()
{
}

void Player::render(SDL_Renderer* pRenderer)
{
    // Get clock, if elapsed, increase frame counter
    SDL_Rect srcRect = { 1 + (currentFrame*m_width), 2, m_width ,m_height };
    SDL_Rect dstRect = { m_position.x() + m_jumpVector.x() - m_camera->getX(),
                         m_position.y() + m_jumpVector.y() - m_camera->getY(),
                         m_width,m_height 
                       };
    SDL_RenderCopy(pRenderer, m_Texture, &srcRect, &dstRect);
}

void Player::control()
{
    m_keyboardState = SDL_GetKeyboardState(nullptr);

    if (m_keyboardState[BUTTON_RIGHT])
    {
        m_position.add(2, 0);
    }
    if (m_keyboardState[BUTTON_LEFT])
    {
        m_position.add(-2, 0);
    }
    if (m_keyboardState[BUTTON_UP])
    {
        m_position.add(0, -2);
    }
    if (m_keyboardState[BUTTON_DOWN])
    {
        m_position.add(0, 2);
    }
    /*if (m_keyboardState[BUTTON_LEFT] && m_keyboardState[BUTTON_UP])
    {
        m_position.add(-1, -1);
    }*/
}

void Player::attack()
{
}

void Player::die()
{
}