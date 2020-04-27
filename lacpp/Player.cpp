#include "Player.h"
#include "Resource.h"
#include "InputControl.h"
#include "Vec2.h"
#include "Camera.h"
#include "Renderer.h"
#include "Bow.h"
#include "Depth.h"
#include "MyAssert.h"
#include <set>

Player::Player()
{
    m_texture = ResourceManager::getInstance()[RSC_LINK];
    m_width = 16;
    m_height = 16;
    m_speed = 1;


    m_position.x = 72; m_position.y = 88;
    m_boundingBox.x = m_position.x; m_boundingBox.y = m_position.y;

    m_boundingBox.w = PLAYER_BOUNDING_BOX_WIDTH;
    m_boundingBox.h = PLAYER_BOUNDING_BOX_HEIGHT;

    m_health = 3;
    m_healthMax = 3;

    m_depth = PLAYER_DEPTH;
    m_state = LINK_WALK_DOWN;
    m_direction = DIRECTION_DOWN;

    m_animateXPos = 0;      // Initial X-position in sprite sheet for this animation
    m_animateYPos = 0;      // Initial Y-position in sprite sheet for this animation
    m_currentFrame = 0;     // Initial frame in this animation
    m_maxFrame = 0;         // Maximum frame number for this animation
    m_animationFPS = 0;     // Animation rate in FPS

    m_dirLockRight = false;
    m_dirLockUp = false;
    m_dirLockDown = false;
    m_dirLockLeft = false;

    m_useShield = false;

    // Collision related stuff
    m_speed_x = 0;
    m_speed_y = 0;

    // Weapon tests
    m_arrow = nullptr;
    m_boomerang = nullptr;
    m_bomb = nullptr;

    //
    // Set to Tail cave entrace
    m_currentCollisionMapX = 3;
    m_currentCollisionMapY = 5;
    m_collisionArea = m_collisionMap.m_tailCave[m_currentCollisionMapY][m_currentCollisionMapX];


    //
    m_boundingBox.w = PLAYER_BOUNDING_BOX_WIDTH;
    m_boundingBox.h = PLAYER_BOUNDING_BOX_HEIGHT;

    m_name = "Player";
    Renderer::getInstance().addRenderable(this);
    Controller::getInstance().setController(this);
}

float Player::health() const
{
    return m_health;
}

float Player::maxHealth() const
{
    return m_healthMax;
}

bool Player::handleStaticCollisions(int horizontalSpeed, int verticalSpeed)
{

    // When moving in a direction
    // If our position + speed encounters a wall, stop
    // else keep moving in that direction
    bool topLeftLeftToRight = false;
    bool bottomLeftLeftToRight = false;
    bool topRightRightToLeft = false;
    bool bottomRightRightToLeft = false;
    bool bottomLeftBottomToTop = false;
    bool bottomRightBottomToTop = false;
    bool topLeftTopToBottom = false;
    bool topRightTopToBottom = false;

    m_boundingBox.x = m_position.x + PLAYER_BOUNDING_BOX_WIDTH_OFFSET;
    m_boundingBox.y = m_position.y + PLAYER_BOUNDING_BOX_HEIGHT;

    // Copy box
    BoundingBox testBox = m_boundingBox;
    testBox.x += horizontalSpeed;
    testBox.y += verticalSpeed;

    // Handle static collisions
    bool collision = false;
    std::vector<BoundingBox> bbs = m_collisionMap.collisionMap(m_collisionArea);
    for (BoundingBox& box : bbs)
    {
        // Transform the bounding box co-ordinates as we offset from the count
        // Why does this have to be negative?
        box.x -= -Camera::getInstance().getX();
        box.y -= -Camera::getInstance().getY();

        if (BoundingBox::intersects(testBox, box))
        {
            // Either horizontal or vertical speed will be non-zero, never both
            // Do corner cutting
            collision = true;
            topLeftLeftToRight = (((m_boundingBox.y + m_boundingBox.h) - box.y) >= 0 && ((m_boundingBox.y + m_boundingBox.h) - box.y) <= PLAYER_CORNER_CUTTING_BOUNDARY) && (m_boundingBox.x + m_boundingBox.w <= box.x);  // Push player UP when going right
            topLeftTopToBottom = (((m_boundingBox.x + m_boundingBox.w) - box.x) >= 0 && ((m_boundingBox.x + m_boundingBox.w) - box.x) <= PLAYER_CORNER_CUTTING_BOUNDARY) && (m_boundingBox.y + m_boundingBox.h <= box.y);  // push player DOWN when going down
            topRightTopToBottom = (((box.x + box.w) - m_boundingBox.x) >= 0 && ((box.x + box.w) - m_boundingBox.x) <= PLAYER_CORNER_CUTTING_BOUNDARY) && (m_boundingBox.y + m_boundingBox.h <= box.y);
            topRightRightToLeft = (((m_boundingBox.y + m_boundingBox.h) - box.y) >= 0 && ((m_boundingBox.y + m_boundingBox.h) - box.y) <= PLAYER_CORNER_CUTTING_BOUNDARY) && (box.x + box.w <= m_boundingBox.x);
            bottomRightRightToLeft = (((box.y + box.h) - m_boundingBox.y) >= 0 && ((box.y + box.h) - m_boundingBox.y) <= PLAYER_CORNER_CUTTING_BOUNDARY) && (box.x + box.w <= m_boundingBox.x);
            bottomRightBottomToTop = (((box.x + box.w) - m_boundingBox.x) >= 0 && ((box.x + box.w) - m_boundingBox.x) <= PLAYER_CORNER_CUTTING_BOUNDARY) && (box.y + box.h <= m_boundingBox.y);
            bottomLeftBottomToTop = (((m_boundingBox.x + m_boundingBox.w) - box.x) >= 0 && ((m_boundingBox.x + m_boundingBox.w) - box.x) <= PLAYER_CORNER_CUTTING_BOUNDARY) && (box.y + box.h <= m_boundingBox.y);
            bottomLeftLeftToRight = (((box.y + box.h) - m_boundingBox.y) >= 0 && ((box.y + box.h) - m_boundingBox.y) <= PLAYER_CORNER_CUTTING_BOUNDARY) && (m_boundingBox.x + m_boundingBox.w <= box.x);
            break;
        }
    }

    // TODO: Check whether there is space or not before pushing the player
    // Don't get stuck on a corner or increase speed when gliding along the wall
    if (topLeftLeftToRight && !(m_speed_x == m_speed && m_speed_y == m_speed) && !(m_speed_x == m_speed && m_speed_y == -m_speed))
    {
        m_position.y-= m_speed;
    }
    if (topLeftTopToBottom && !(m_speed_x == m_speed && m_speed_y == m_speed) && !(m_speed_x == -m_speed && m_speed_y == m_speed))
    {
        m_position.x-= m_speed;
    }
    if (topRightTopToBottom && !(m_speed_x == m_speed && m_speed_y == m_speed) && !(m_speed_x == -m_speed && m_speed_y == m_speed))
    {
        m_position.x+= m_speed;
    }
    if (topRightRightToLeft && !(m_speed_x == -m_speed && m_speed_y == m_speed) && !(m_speed_x == -m_speed && m_speed_y == -m_speed))
    {
        m_position.y-= m_speed;
    }
    if (bottomRightRightToLeft && !(m_speed_x == -m_speed && m_speed_y == -m_speed) && !(m_speed_x == -m_speed && m_speed_y == m_speed))
    {
        m_position.y+= m_speed;
    }
    if (bottomRightBottomToTop && !(m_speed_x == -m_speed && m_speed_y == -m_speed) && !(m_speed_x == m_speed && m_speed_y == -m_speed))
    {
        m_position.x+= m_speed;
    }
    if (bottomLeftBottomToTop && !(m_speed_x == -m_speed && m_speed_y == -m_speed) && !(m_speed_x == m_speed && m_speed_y == -m_speed))
    {
        m_position.x-= m_speed;
    }
    if (bottomLeftLeftToRight && !(m_speed_x == m_speed && m_speed_y == m_speed) && !(m_speed_x == m_speed && m_speed_y == -m_speed))
    {
        m_position.y+= m_speed;
    }

    return collision;
}

Player::~Player()
{

}

void Player::render(SDL_Renderer* pRenderer)
{

    // Get clock, if elapsed, increase frame counter
    SDL_Rect srcRect = { m_animateXPos + (m_currentFrame * m_width) , m_animateYPos, m_width ,m_height };
    SDL_Rect dstRect = {
        m_position.x - Camera::getInstance().getX(),
        m_position.y - Camera::getInstance().getY(),
        m_width, m_height 
                       };
    DASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, m_animations[m_state].flip) == 0, SDL_GetError());


    // Drawing bounding boxes for testing
    m_collisionArea = m_collisionMap.m_tailCave[m_currentCollisionMapY][m_currentCollisionMapX];
    
    SDL_Rect playerRect =
    {
        m_boundingBox.x - Camera::getInstance().getX(),
        m_boundingBox.y - Camera::getInstance().getY(),
        m_boundingBox.w, m_boundingBox.h
    };
    //DASSERT(SDL_RenderDrawRect(pRenderer, &playerRect) == 0, SDL_GetError());

    /* std::vector<BoundingBox> bbs = m_collisionMap.collisionMap(m_collisionArea);
    for (const BoundingBox& box : bbs)
    {

        SDL_Rect bbRect = { box.x , box.y, box.w, box.h };

        DASSERT(SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 0) == 0);
        DASSERT(SDL_RenderDrawRect(pRenderer, &bbRect) == 0);
    }
    
    */

    // Perishable weapons
    // Weapons that go offscreen are culled
    if (m_arrow)
    {
        auto arrowPos = m_arrow->position();
        if (!Camera::getInstance().visible(arrowPos))
        {
            Renderer::getInstance().removeRenderable(m_arrow);
            delete m_arrow;
            m_arrow = nullptr;
        }
    }

    if (m_boomerang)
    {
        auto boomerangPos = m_boomerang->position();
        if (!Camera::getInstance().visible(boomerangPos))
        {
            m_boomerang->returnToPlayer();
        }
        BoundingBox box;
        box.x = m_boundingBox.x - Camera::getInstance().getX();
        box.y = m_boundingBox.y - Camera::getInstance().getY();

        if (BoundingBox::intersects(box, m_boomerang->boundingBox()))
        {
            Renderer::getInstance().removeRenderable(m_boomerang);
            delete m_boomerang;
            m_boomerang = nullptr;
        }
    }

    if (m_bomb)
    {
        if (m_bomb->exploded() || !Camera::getInstance().visible(m_bomb->position()))
        {
            Renderer::getInstance().removeRenderable(m_bomb);
            delete m_bomb;
            m_bomb = nullptr;
        }
    }

}

void Player::control()
{
    m_keyboardState = SDL_GetKeyboardState(nullptr);

    // Open the inventory
    if (m_keyboardState[BUTTON_SELECT])
    {
        m_inventory.open();
        Controller::getInstance().pushController(this, &m_inventory);
    }

    // Max frame controlled by the state
    m_maxFrame = m_animations[m_state].maxFrame;

    // Sprite orientation
    m_orientation = m_animations[m_state].orientation;

    // If we are holding left and we press up or down, we don't want to change the state whatever it is...
    // Same applies to other directions 
    move();

    // Select correct animation
    m_animateXPos = m_animations[m_state].x;
    m_animateYPos = m_animations[m_state].y;

    // Only animate if moving
    if (IS_MOVING(m_keyboardState))
    {
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

    // Player attack
    attack();

}

void Player::attack()
{
    if (m_keyboardState[BUTTON_A])
    {
        useWeapon(m_inventory.weaponA());
    }
    else if (!m_keyboardState[BUTTON_B])
    {
        m_useShield = false;
        updateState();
    }
    if (m_keyboardState[BUTTON_B])
    {
        useWeapon(m_inventory.weaponB());
    }
    else if (!m_keyboardState[BUTTON_A])
    {
        m_useShield = false;
        updateState();
    }
}

void Player::die()
{
    std::cout << "Player died" << std::endl;
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
    else
    {
        die();
    }
}

DIRECTION Player::direction() const
{
    return m_direction;
}

void Player::replenish(float hearts)
{
    if (m_health + hearts <= m_healthMax)
    {
        m_health += hearts;
    }
}

// Player control
void Player::move()
{
    if (m_keyboardState[BUTTON_RIGHT])
    {
        m_speed_x = m_speed;
        m_speed_y = m_speed * (m_keyboardState[BUTTON_DOWN] - m_keyboardState[BUTTON_UP]);

        if (!m_dirLockUp && !m_dirLockDown)
        {
            m_dirLockRight = true;
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WEAPON_LEVEL shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WPN_LEVEL_1)
                {
                    if (m_useShield)
                    {
                        m_state = LINK_BLOCK_RIGHT_SMALL_SHIELD;
                    }
                    else
                    {
                        m_state = LINK_WALK_RIGHT_SMALL_SHIELD;
                    }
                }
                else if (shieldLevel == WPN_LEVEL_2)
                {
                    if (m_useShield)
                    {
                        m_state = LINK_BLOCK_RIGHT_BIG_SHIELD;
                    }
                    else
                    {
                        m_state = LINK_WALK_RIGHT_BIG_SHIELD;
                    }
                }
            }
            else
            {
                m_state = LINK_WALK_RIGHT;
            }
            m_direction = DIRECTION_RIGHT;
        }

        if (!handleStaticCollisions(m_speed_x, 0))
        {
            m_position.x += m_speed_x;
        }
        else
        {
            // If collision with wall
            m_state = LINK_PUSH_RIGHT;
            m_direction = DIRECTION_RIGHT;
        }
    }
    else
    {
        if (m_state == LINK_PUSH_RIGHT && handleStaticCollisions(m_speed_x, 0))
        {
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WEAPON_LEVEL shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WPN_LEVEL_1)
                {
                    m_state = LINK_WALK_RIGHT_SMALL_SHIELD;
                }
                else if (shieldLevel == WPN_LEVEL_2)
                {
                    m_state = LINK_WALK_RIGHT_BIG_SHIELD;
                }
            }
            else
            {
                m_state = LINK_WALK_RIGHT;
            }
            m_direction = DIRECTION_RIGHT;
        }
    }

    if (m_keyboardState[BUTTON_LEFT])
    {
        m_speed_x = -m_speed;
        m_speed_y = m_speed * (m_keyboardState[BUTTON_DOWN] - m_keyboardState[BUTTON_UP]);

        if (!m_dirLockUp && !m_dirLockDown)
        {
            m_dirLockLeft = true;
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WEAPON_LEVEL shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WPN_LEVEL_1)
                {
                    if (m_useShield)
                    {
                        m_state = LINK_BLOCK_LEFT_SMALL_SHIELD;
                    }
                    else
                    {
                        m_state = LINK_WALK_LEFT_SMALL_SHIELD;
                    }
                }
                else if (shieldLevel == WPN_LEVEL_2)
                {
                    if (m_useShield)
                    {
                        m_state = LINK_BLOCK_LEFT_BIG_SHIELD;
                    }
                    else
                    {
                        m_state = LINK_WALK_LEFT_BIG_SHIELD;
                    }
                }
            }
            else
            {
                m_state = LINK_WALK_LEFT;
            }
            m_direction = DIRECTION_LEFT;
        }
        if (!handleStaticCollisions(m_speed_x, 0))
        {
            m_position.x += m_speed_x;
        }
        else
        {
            // If collision with wall
            m_state = LINK_PUSH_LEFT;
            m_direction = DIRECTION_LEFT;
        }
    }
    else
    {
        if (m_state == LINK_PUSH_LEFT && handleStaticCollisions(m_speed_x, 0))
        {
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WEAPON_LEVEL shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WPN_LEVEL_1)
                {
                    m_state = LINK_WALK_LEFT_SMALL_SHIELD;
                }
                else if (shieldLevel == WPN_LEVEL_2)
                {
                    m_state = LINK_WALK_LEFT_BIG_SHIELD;
                }
            }
            else
            {
                m_state = LINK_WALK_LEFT;
            }
            m_direction = DIRECTION_LEFT;
        }
    }
    if (m_keyboardState[BUTTON_UP])
    {
        m_speed_x = m_speed * (m_keyboardState[BUTTON_RIGHT] - m_keyboardState[BUTTON_LEFT]);
        m_speed_y = -m_speed;

        if (!m_dirLockRight && !m_dirLockLeft)
        {
            m_dirLockUp = true;
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WEAPON_LEVEL shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WPN_LEVEL_1)
                {
                    if (m_useShield)
                    {
                        m_state = LINK_BLOCK_UP_SMALL_SHIELD;
                    }
                    else
                    {
                        m_state = LINK_WALK_UP_SMALL_SHIELD;
                    }
                }
                else if (shieldLevel == WPN_LEVEL_2)
                {
                    if (m_useShield)
                    {
                        m_state = LINK_BLOCK_UP_BIG_SHIELD;
                    }
                    else
                    {
                        m_state = LINK_WALK_UP_BIG_SHIELD;
                    }
                }
            }
            else
            {
                m_state = LINK_WALK_UP;
            }
            m_direction = DIRECTION_UP;
        }

        if (!handleStaticCollisions(0, m_speed_y))
        {
            m_position.y += m_speed_y;
        }
        else
        {
            // If collision with wall
            m_state = LINK_PUSH_UP;
            m_direction = DIRECTION_UP;
        }
    }
    else
    {
        if (m_state == LINK_PUSH_UP && handleStaticCollisions(0, m_speed_y))
        {
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WEAPON_LEVEL shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WPN_LEVEL_1)
                {
                    m_state = LINK_WALK_UP_SMALL_SHIELD;
                }
                else if (shieldLevel == WPN_LEVEL_2)
                {
                    m_state = LINK_WALK_UP_BIG_SHIELD;
                }
            }
            else
            {
                m_state = LINK_WALK_UP;
            }
            m_direction = DIRECTION_UP;
        }
    }
    if (m_keyboardState[BUTTON_DOWN])
    {
        m_speed_x = m_speed * (m_keyboardState[BUTTON_RIGHT] - m_keyboardState[BUTTON_LEFT]);
        m_speed_y = m_speed;

        if (!m_dirLockRight && !m_dirLockLeft)
        {
            m_dirLockDown = true;
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WEAPON_LEVEL shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WPN_LEVEL_1)
                {
                    if (m_useShield)
                    {
                        m_state = LINK_BLOCK_DOWN_SMALL_SHIELD;
                    }
                    else
                    {
                        m_state = LINK_WALK_DOWN_SMALL_SHIELD;
                    }
                }
                else if (shieldLevel == WPN_LEVEL_2)
                {
                    if (m_useShield)
                    {
                        m_state = LINK_BLOCK_DOWN_BIG_SHIELD;
                    }
                    else
                    {
                        m_state = LINK_WALK_DOWN_BIG_SHIELD;
                    }
                }
            }
            else
            {
                m_state = LINK_WALK_DOWN;
            }
            m_direction = DIRECTION_DOWN;
        }

        if (!handleStaticCollisions(0, m_speed_y))
        {
            m_position.y += m_speed_y;
        }
        else
        {
            // If collision with wall
            m_state = LINK_PUSH_DOWN;
            m_direction = DIRECTION_DOWN;
        }
    }
    else
    {
        if (m_state == LINK_PUSH_DOWN && handleStaticCollisions(0, m_speed_y))
        {
            if (m_inventory.shieldEquipped())
            {
                WEAPON_LEVEL shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WPN_LEVEL_1)
                {
                    m_state = LINK_WALK_DOWN_SMALL_SHIELD;
                }
                else if (shieldLevel == WPN_LEVEL_2)
                {
                    m_state = LINK_WALK_DOWN_BIG_SHIELD;
                }
            }
            else
            {
                m_state = LINK_WALK_DOWN;
            }
            m_direction = DIRECTION_DOWN;
        }
    }
}

// Update the player (visible state)
void Player::updateState()
{
    bool shieldEquipped = m_inventory.shieldEquipped();
    WEAPON_LEVEL shieldLevel = m_inventory.shieldLevel();

    switch (m_state)
    {
    case LINK_WALK_DOWN:
        if (shieldEquipped)
        {
            if (shieldLevel == WPN_LEVEL_1)
            {
                m_state = LINK_WALK_DOWN_SMALL_SHIELD;
            }
            else if (shieldLevel == WPN_LEVEL_2)
            {
                m_state = LINK_WALK_DOWN_BIG_SHIELD;
            }
        }
    break;
    case LINK_WALK_UP:
        if (shieldEquipped)
        {
            if (shieldLevel == WPN_LEVEL_1)
            {
                m_state = LINK_WALK_UP_SMALL_SHIELD;
            }
            else if (shieldLevel == WPN_LEVEL_2)
            {
                m_state = LINK_WALK_UP_BIG_SHIELD;
            }
        }
    break;
    case LINK_WALK_LEFT:
        if (shieldEquipped)
        {
            if (shieldLevel == WPN_LEVEL_1)
            {
                m_state = LINK_WALK_LEFT_SMALL_SHIELD;
            }
            else if (shieldLevel == WPN_LEVEL_2)
            {
                m_state = LINK_WALK_LEFT_BIG_SHIELD;
            }
        }
    break;
    case LINK_WALK_RIGHT:
        if (shieldEquipped)
        {
            if (shieldLevel == WPN_LEVEL_1)
            {
                m_state = LINK_WALK_RIGHT_SMALL_SHIELD;
            }
            else if (shieldLevel == WPN_LEVEL_2)
            {
                m_state = LINK_WALK_RIGHT_BIG_SHIELD;
            }
        }
    break;
    case LINK_WALK_DOWN_BIG_SHIELD:
    case LINK_WALK_DOWN_SMALL_SHIELD:
        if (!shieldEquipped)
        {
            m_state = LINK_WALK_DOWN;
        }
    break;
    case LINK_WALK_UP_BIG_SHIELD:
    case LINK_WALK_UP_SMALL_SHIELD:
        if (!shieldEquipped)
        {
            m_state = LINK_WALK_UP;
        }
    break;
    case LINK_WALK_LEFT_BIG_SHIELD:
    case LINK_WALK_LEFT_SMALL_SHIELD:
        if (!shieldEquipped)
        {
            m_state = LINK_WALK_LEFT;
        }
    break;
    case LINK_WALK_RIGHT_BIG_SHIELD:
    case LINK_WALK_RIGHT_SMALL_SHIELD:
        if (!shieldEquipped)
        {
            m_state = LINK_WALK_RIGHT;
        }
    break;

    case LINK_BLOCK_LEFT_SMALL_SHIELD:
        m_state = LINK_WALK_LEFT_SMALL_SHIELD;
        break;
    case LINK_BLOCK_RIGHT_SMALL_SHIELD:
        m_state = LINK_WALK_RIGHT_SMALL_SHIELD;
        break;
    case LINK_BLOCK_UP_SMALL_SHIELD:
        m_state = LINK_WALK_UP_SMALL_SHIELD;
        break;
    case LINK_BLOCK_DOWN_SMALL_SHIELD:
        m_state = LINK_WALK_DOWN_SMALL_SHIELD;
        break;

    case LINK_BLOCK_LEFT_BIG_SHIELD:
        m_state = LINK_WALK_LEFT_BIG_SHIELD;
        break;
    case LINK_BLOCK_RIGHT_BIG_SHIELD:
        m_state = LINK_WALK_RIGHT_BIG_SHIELD;
        break;
    case LINK_BLOCK_UP_BIG_SHIELD:
        m_state = LINK_WALK_UP_BIG_SHIELD;
        break;
    case LINK_BLOCK_DOWN_BIG_SHIELD:
        m_state = LINK_WALK_DOWN_BIG_SHIELD;
        break;
    }
}

void Player::useWeapon(WEAPON weapon)
{
    std::string wpn;
    WEAPON_LEVEL shieldLevel = m_inventory.shieldLevel();

    switch (weapon)
    {
    case WPN_NONE: wpn = "None"; break;
    case WPN_SWORD: wpn = "Sword"; break;
    case WPN_SHIELD:
        wpn = "Shield";
        switch (m_state)
        {
        case LINK_WALK_LEFT_BIG_SHIELD:
        case LINK_WALK_LEFT_SMALL_SHIELD:
        case LINK_WALK_LEFT:
            if (shieldLevel == WPN_LEVEL_1)
            {
                m_state = LINK_BLOCK_LEFT_SMALL_SHIELD;
            }
            else if (shieldLevel == WPN_LEVEL_2)
            {
                m_state = LINK_BLOCK_LEFT_BIG_SHIELD;
            }
            break;
        case LINK_WALK_RIGHT_BIG_SHIELD:
        case LINK_WALK_RIGHT_SMALL_SHIELD:
        case LINK_WALK_RIGHT:
            if (shieldLevel == WPN_LEVEL_1)
            {
                m_state = LINK_BLOCK_RIGHT_SMALL_SHIELD;
            }
            else if (shieldLevel == WPN_LEVEL_2)
            {
                m_state = LINK_BLOCK_RIGHT_BIG_SHIELD;
            }
            break;
        case LINK_WALK_UP_BIG_SHIELD:
        case LINK_WALK_UP_SMALL_SHIELD:
        case LINK_WALK_UP:
            if (shieldLevel == WPN_LEVEL_1)
            {
                m_state = LINK_BLOCK_UP_SMALL_SHIELD;
            }
            else if (shieldLevel == WPN_LEVEL_2)
            {
                m_state = LINK_BLOCK_UP_BIG_SHIELD;
            }
            break;
        case LINK_WALK_DOWN_BIG_SHIELD:
        case LINK_WALK_DOWN_SMALL_SHIELD:
        case LINK_WALK_DOWN:
            if (shieldLevel == WPN_LEVEL_1)
            {
                m_state = LINK_BLOCK_DOWN_SMALL_SHIELD;
            }
            else if (shieldLevel == WPN_LEVEL_2)
            {
                m_state = LINK_BLOCK_DOWN_BIG_SHIELD;
            }
            break;
        }
        m_useShield = true;

        break;
    case WPN_BOW:
        wpn = "Bow";


        // We can fire multiple arrows
        // An arrow that hits an enemy disappears
        // An arrow that goes off screen disappears
        // An arrow that hits an object deflects and disappears

        if (m_arrow == nullptr)
        {
            if (m_inventory.bowAndArrowAvailable())
            {
                m_arrow = new Bow();
                m_arrow->setDirection(m_direction);
                m_arrow->setPosition(m_position);
                m_arrow->useWeapon();
                m_inventory.useBowAndArrow();
            }
        }

        
        break;
    case WPN_BOOMERANG:
        wpn = "Boomerang";

        // A boomerang can only be thrown once
        // A boomerang that hits an enemy stuns it and returns to the player
        // A boomerang that goes off screen returns to the player
        // A boomerang that hits an object deflects and returns

        if (m_boomerang == nullptr)
        {
            m_boomerang = new Boomerang();
            m_boomerang->setDirection(m_direction);
            m_boomerang->setPosition(m_position);
            m_boomerang->useWeapon();
        }
        
        break;
    case WPN_MAGIC_POWDER: wpn = "Magic Powder"; break;
    case WPN_BOMBS:
        wpn = "Bombs";
        
        if (m_bomb == nullptr)
        {
            if (m_inventory.bombsAvailable())
            {
                m_bomb = new Bomb();
                m_bomb->setDirection(m_direction);
                m_bomb->setPosition(m_position);
                m_bomb->useWeapon();
                m_inventory.useBombs();
            }

        }
        
        
        break;
    case WPN_POWER_BRACELET_1: wpn = "Power Bracelet 1"; break;
    case WPN_POWER_BRACELET_2: wpn = "Power Bracelet 2"; break;
    case WPN_ROC_FEATHER: wpn = "Roc Feather"; break;
    case WPN_HOOKSHOT: wpn = "Hookshot"; break;
    case WPN_OCARINA: wpn = "Ocarina"; break;
    case WPN_PEGASUS_BOOT: wpn = "Pegasus Boot"; break;
    case WPN_SHOVEL: wpn = "Shovel"; break;
    case WPN_FLAME_ROD: wpn = "Flame rod"; break;
    }
    std::cout << "Using weapon: " << wpn << std::endl;


}