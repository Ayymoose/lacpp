#include "Player.h"
#include "Resource.h"
#include "InputControl.h"
#include "Vec2.h"
#include "Camera.h"
#include "Renderer.h"
#include <set>
#include "Depth.h"

Player::Player()
{
    m_texture = ResourceManager::getInstance()[RSC_LINK];
    //m_position.set(64, 64);
    //m_jumpVector.set(0, 0);
    m_width = 16;
    m_height = 16;
    m_speed = 1;

    m_health = 3;
    m_healthMax = 3;

    m_depth = PLAYER_DEPTH;
    m_state = LINK_WALK_DOWN;

    m_animateXPos = 0;   // Initial X-position in sprite sheet for this animation
    m_animateYPos = 0;   // Initial Y-position in sprite sheet for this animation
    m_currentFrame = 0;  // Initial frame in this animation
    m_maxFrame = 0;      // Maximum frame number for this animation
    m_animationFPS = 0; // Animation rate in FPS

    m_dirLockRight = false;
    m_dirLockUp = false;
    m_dirLockDown = false;
    m_dirLockLeft = false;
    
    Renderer::getInstance().addRenderable(this);
 
    m_inventory.open();
    Controller::getInstance().setController(&m_inventory);

}

float Player::health() const
{
    return m_health;
}

float Player::maxHealth() const
{
    return m_healthMax;
}

Player::~Player()
{

}

void Player::render(SDL_Renderer* pRenderer)
{
    // Get clock, if elapsed, increase frame counter
    SDL_Rect srcRect = { m_animateXPos + (m_currentFrame * m_width) , m_animateYPos, m_width ,m_height };
    SDL_Rect dstRect = { m_position.x /*+ m_jumpVector.x*/ - Camera::getInstance().getX(),
                         m_position.y /*+ m_jumpVector.y*/ - Camera::getInstance().getY(),
                         m_width,m_height 
                       };
    SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, m_animations[m_state].flip);
}

void Player::control()
{
    m_keyboardState = SDL_GetKeyboardState(nullptr);

    // Open the inventory
    if (m_keyboardState[BUTTON_SELECT])
    {
     //   m_inventory.open();
     //   Controller::getInstance().setController(&m_inventory);
    }

    /*

    1. Render texture with transparent colour (DONE)
    2. Array for sprite indices (DONE)
    3. Correct diagonal movement
    4. Reset current frame to 0 when no key pressed or finished scrolling (DONE)
    5. Single animation timer for player (DONE)
    6. Pressing oposing keys to not stop movement (DONE)
    7. Holding combination of left/right and up or left/right and down keeps current sprite effect (DONE)

    */

    // Max frame controlled by the state
    m_maxFrame = m_animations[m_state].maxFrame;

    // Sprite orientation
    m_orientation = m_animations[m_state].orientation;

    if (IS_MOVING(m_keyboardState))
    {

        int m_speed_x = 0;
        int m_speed_y = 0;


        // If we are holding left and we press up or down, we don't want to change the state whatever it is...
        // Same applies to other directions 

        if (m_keyboardState[BUTTON_RIGHT])
        {
            if (!m_dirLockUp && !m_dirLockDown)
            {
                m_dirLockRight = true;
                m_state = LINK_WALK_RIGHT;
            }
            m_speed_x = m_speed;
            m_speed_y = -m_keyboardState[BUTTON_UP] + m_keyboardState[BUTTON_DOWN];
        }
        if (m_keyboardState[BUTTON_LEFT])
        {
            if (!m_dirLockUp && !m_dirLockDown)
            {
                m_dirLockLeft = true;
                m_state = LINK_WALK_LEFT;
            }
            m_speed_x = -m_speed;
            m_speed_y = - m_keyboardState[BUTTON_UP] + m_keyboardState[BUTTON_DOWN];
        }
        if (m_keyboardState[BUTTON_UP])
        {
            if (!m_dirLockRight && !m_dirLockLeft)
            {
                m_dirLockUp = true;
                m_state = LINK_WALK_UP;
            }
            m_speed_x = - m_keyboardState[BUTTON_LEFT] + m_keyboardState[BUTTON_RIGHT];
            m_speed_y = -m_speed;
        }
        if (m_keyboardState[BUTTON_DOWN])
        {
            if (!m_dirLockRight && !m_dirLockLeft)
            {
                m_dirLockDown = true;
                m_state = LINK_WALK_DOWN;
            }
            m_speed_x = - m_keyboardState[BUTTON_LEFT] + m_keyboardState[BUTTON_RIGHT];
            m_speed_y = m_speed;
        }

        // Select correct animation
        m_animateXPos = m_animations[m_state].x;
        m_animateYPos = m_animations[m_state].y;

        /// Move player
        if (m_movementTimer.update(FPS_66))
        {
            m_position.x += m_speed_x;
            m_position.y += m_speed_y;
        }

        // Animation
        if (m_currentFrame <= m_maxFrame)
        {
            if (m_animationTimer.update(m_animations[m_state].animationFPS))
            {
                m_currentFrame++;
                if (m_currentFrame > m_maxFrame)
                {
                    m_currentFrame = 0;
                }
            }
        }
    }

    // If no key is pressed (reset the animation)
    SDL_PumpEvents();
    if (!IS_GAMEPAD_PRESSED(m_keyboardState))
    {
        // TODO: Current frame has to be reset to intial frame
        m_currentFrame = 0;
        m_dirLockRight = false;
        m_dirLockUp = false;
        m_dirLockLeft = false;
        m_dirLockDown = false;
    }


    // If any directional keys are released
    // Release the direction lock
    if (!m_keyboardState[BUTTON_RIGHT])
    {
        m_dirLockRight = false;
    }
    if (!m_keyboardState[BUTTON_LEFT])
    {
        m_dirLockLeft = false;
    }
    if (!m_keyboardState[BUTTON_UP])
    {
        m_dirLockUp = false;
    }
    if (!m_keyboardState[BUTTON_DOWN])
    {
        m_dirLockDown = false;
    }

}

void Player::attack()
{

}

void Player::die()
{
}

void Player::resetAnimation()
{
    m_currentFrame = m_animations[m_state].currentFrame;
}

Vec2<float> Player::position() const
{
    return m_position;
}

void Player::addPosition(int x, int y)
{
    m_position.x += x;
    m_position.y += y;
}

void Player::damage(float damage)
{
    if (m_health - damage >= 0)
    {
        m_health -= damage;
    }
}

void Player::replenish(float hearts)
{
    if (m_health + hearts <= m_healthMax)
    {
        m_health += hearts;
    }
}
