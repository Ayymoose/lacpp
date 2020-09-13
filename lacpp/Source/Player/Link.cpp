#include "Link.h"
#include "Resource.h"
#include "InputControl.h"
#include "Vector.h"
#include "Camera.h"
#include "Renderer.h"
#include "Bow.h"
#include "Depth.h"
#include "ZD_Assert.h"
#include "Keyboard.h"
#include "Engine.h"

#include <set>

Link::Link()
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_LINK];
    m_width = 16;
    m_height = 16;
    m_speed = 1;

    m_position.x = 72;
    m_position.y = 32;
    m_boundingBox.x = m_position.x;
    m_boundingBox.y = m_position.y;

    m_boundingBox.w = PLAYER_BOUNDING_BOX_WIDTH;
    m_boundingBox.h = PLAYER_BOUNDING_BOX_HEIGHT;

    m_health = 3;
    m_healthMax = 3;

    m_depth = ZD_DEPTH_PLAYER;
    m_state = LINK_WALK_DOWN;
    m_direction = DIRECTION_DOWN;

    m_animateXPos = 0;              // Initial X-position in sprite sheet for this animation
    m_animateYPos = 0;              // Initial Y-position in sprite sheet for this animation
    m_currentFrame = 0;             // Initial frame in this animation
    m_endFrame = 0;                 // Maximum frame number for this animation
    m_animationFPS = 0;             // Animation rate in FPS
    m_animationComplete = false;    // Set to true when animation complete

    m_dirLockRight = false;
    m_dirLockUp = false;
    m_dirLockDown = false;
    m_dirLockLeft = false;

    m_useShield = false;

    // Collision related stuff
    m_speedX = 0;
    m_speedY = 0;

    // Weapon tests
    m_arrow = nullptr;
    m_boomerang = nullptr;
    m_bomb = nullptr;
    m_flameRod = nullptr;
    m_sword = nullptr;
    //

    m_moveable = true;
    // Set to Tail cave entrace
    m_currentCollisionMapX = 3;
    m_currentCollisionMapY = 5;
    m_collisionArea = m_collisionMap.m_tailCave[m_currentCollisionMapY][m_currentCollisionMapX];

    m_usingWeapon = false;
    m_useWeapon = false;
    //
    m_boundingBox.w = PLAYER_BOUNDING_BOX_WIDTH;
    m_boundingBox.h = PLAYER_BOUNDING_BOX_HEIGHT;

    m_name = "Link";
    Renderer::getInstance().addRenderable(this);
    Controller::getInstance().setController(this);
}

float Link::health() const noexcept
{
    return m_health;
}

float Link::maxHealth() const noexcept
{
    return m_healthMax;
}

bool Link::handleStaticCollisions(int horizontalSpeed, int verticalSpeed) noexcept
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
    if (topLeftLeftToRight && !(m_speedX == m_speed && m_speedY == m_speed) && !(m_speedX == m_speed && m_speedY == -m_speed))
    {
        m_position.y-= m_speed;
    }
    if (topLeftTopToBottom && !(m_speedX == m_speed && m_speedY == m_speed) && !(m_speedX == -m_speed && m_speedY == m_speed))
    {
        m_position.x-= m_speed;
    }
    if (topRightTopToBottom && !(m_speedX == m_speed && m_speedY == m_speed) && !(m_speedX == -m_speed && m_speedY == m_speed))
    {
        m_position.x+= m_speed;
    }
    if (topRightRightToLeft && !(m_speedX == -m_speed && m_speedY == m_speed) && !(m_speedX == -m_speed && m_speedY == -m_speed))
    {
        m_position.y-= m_speed;
    }
    if (bottomRightRightToLeft && !(m_speedX == -m_speed && m_speedY == -m_speed) && !(m_speedX == -m_speed && m_speedY == m_speed))
    {
        m_position.y+= m_speed;
    }
    if (bottomRightBottomToTop && !(m_speedX == -m_speed && m_speedY == -m_speed) && !(m_speedX == m_speed && m_speedY == -m_speed))
    {
        m_position.x+= m_speed;
    }
    if (bottomLeftBottomToTop && !(m_speedX == -m_speed && m_speedY == -m_speed) && !(m_speedX == m_speed && m_speedY == -m_speed))
    {
        m_position.x-= m_speed;
    }
    if (bottomLeftLeftToRight && !(m_speedX == m_speed && m_speedY == m_speed) && !(m_speedX == m_speed && m_speedY == -m_speed))
    {
        m_position.y+= m_speed;
    }

    return collision;
}

void Link::render(SDL_Renderer* pRenderer) noexcept
{

    // Get clock, if elapsed, increase frame counter
    SDL_Rect srcRect =
    {
        m_animateXPos + (m_currentFrame * m_width),
        m_animateYPos,
        m_width,
        m_height
    };

    SDL_Rect dstRect =
    {
        m_position.x - Camera::getInstance().getX(),
        m_position.y - Camera::getInstance().getY(),
        m_width, m_height
    };

    // Max frame controlled by the state
    m_endFrame = m_animations[m_state].endFrame;

    // Sprite orientation
    m_orientation = m_animations[m_state].orientation;

    // Select correct animation
    m_animateXPos = m_animations[m_state].x;
    m_animateYPos = m_animations[m_state].y;

    ZD_ASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, m_animations[m_state].flip) == 0, "SDL Error: " << SDL_GetError());


    // Drawing bounding boxes for testing
    m_collisionArea = m_collisionMap.m_tailCave[m_currentCollisionMapY][m_currentCollisionMapX];
    
    SDL_Rect playerRect =
    {
        m_boundingBox.x - Camera::getInstance().getX(),
        m_boundingBox.y - Camera::getInstance().getY(),
        m_boundingBox.w, m_boundingBox.h
    };

    //ZD_ASSERT(SDL_RenderDrawRect(pRenderer, &playerRect) == 0, "SDL Error: " << SDL_GetError());

    /* std::vector<BoundingBox> bbs = m_collisionMap.collisionMap(m_collisionArea);
    for (const BoundingBox& box : bbs)
    {

        SDL_Rect bbRect = { box.x , box.y, box.w, box.h };

        ZD_ASSERT(SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 0) == 0, "SDL Error: " << SDL_GetError());
        ZD_ASSERT(SDL_RenderDrawRect(pRenderer, &bbRect) == 0, "SDL Error: " << SDL_GetError());
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

    if (m_flameRod)
    {
        if (!Camera::getInstance().visible(m_flameRod->position()))
        {
            Renderer::getInstance().removeRenderable(m_flameRod);
            delete m_flameRod;
            m_flameRod = nullptr;
        }

        // Animate link
        animate();
    }

    if (m_sword)
    {
        if (!Camera::getInstance().visible(m_sword->position()))
        {
            Renderer::getInstance().removeRenderable(m_sword);
            delete m_sword;
            m_sword = nullptr;
        }

        // Animate link
        //animate();

    }

}

void Link::control() noexcept
{
    // Open the inventory
    if (Keyboard::getInstance().keyPushed(BUTTON_SELECT))
    {
        m_inventory.open();
        Controller::getInstance().pushController(this, &m_inventory);
        Engine::getInstance().pauseEngine(true);
        //Keyboard::getInstance().clearKeyStates();
        std::cout << "Inventory opened!\n";
    }

    // If we are holding left and we press up or down, we don't want to change the state whatever it is...
    // Same applies to other directions 
    move();

    // Only animate if moving
    if (Keyboard::getInstance().keyPushed(BUTTON_RIGHT) ||
        Keyboard::getInstance().keyPushed(BUTTON_LEFT) ||
        Keyboard::getInstance().keyPushed(BUTTON_DOWN) ||
        Keyboard::getInstance().keyPushed(BUTTON_UP))
    {
        // Animation
        animate();
    }

    // If no key is pressed (reset the animation)

    if (!(Keyboard::getInstance().keyPushed(BUTTON_RIGHT) ||
        Keyboard::getInstance().keyPushed(BUTTON_LEFT) ||
        Keyboard::getInstance().keyPushed(BUTTON_DOWN) ||
        Keyboard::getInstance().keyPushed(BUTTON_UP)))
    {
        // TODO: Current frame has to be reset to intial frame
        
        if (!m_usingWeapon)
        {
            resetAnimation();
        }

        m_dirLockRight = false;
        m_dirLockUp = false;
        m_dirLockLeft = false;
        m_dirLockDown = false;
    }

    // If any directional keys are released
    // Release the direction lock
    if (Keyboard::getInstance().keyReleased(BUTTON_RIGHT))
    {
        m_dirLockRight = false;
    }
    if (Keyboard::getInstance().keyReleased(BUTTON_LEFT))
    {
        m_dirLockLeft = false;
    }
    if (Keyboard::getInstance().keyReleased(BUTTON_UP))
    {
        m_dirLockUp = false;
    }
    if (Keyboard::getInstance().keyReleased(BUTTON_DOWN))
    {
        m_dirLockDown = false;
    }

    // Link attack
    // Only attack if a key is actually pressed
    attack();
    
}

void Link::attack() noexcept
{
    if (Keyboard::getInstance()[BUTTON_A])
    {
        useWeapon(m_inventory.weaponA());
    }
    else if (!Keyboard::getInstance()[BUTTON_B])
    {
        m_useShield = false;
        if (!m_usingWeapon)
        updateState();
    }
    if (Keyboard::getInstance()[BUTTON_B])
    {
        useWeapon(m_inventory.weaponB());
    }
    else if (!Keyboard::getInstance()[BUTTON_A])
    {
        m_useShield = false;
        if (!m_usingWeapon)
        updateState();
    }
}

void Link::die() noexcept
{
    std::cout << "Link died" << std::endl;
}

void Link::resetAnimation() noexcept
{
    m_currentFrame = m_animations[m_state].startFrame;
    m_clockAnimation.reset();
}

Vector<float> Link::position() const noexcept
{
    return m_position;
}

void Link::addPosition(int x, int y) noexcept
{
    m_position.x += x;
    m_position.y += y;
}

void Link::damage(float damage) noexcept
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

Direction Link::direction() const noexcept
{
    return m_direction;
}

void Link::replenish(float hearts) noexcept
{
    if (m_health + hearts <= m_healthMax)
    {
        m_health += hearts;
    }
}

// Link control
void Link::move() noexcept
{
    if (Keyboard::getInstance().keyPushed(BUTTON_RIGHT))
    {
        m_speedX = m_speed;
        m_speedY = m_speed * (Keyboard::getInstance()[BUTTON_DOWN] - Keyboard::getInstance()[BUTTON_UP]);

        if (!m_dirLockUp && !m_dirLockDown)
        {
            m_dirLockRight = true;
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WeaponLevel shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
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
                else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
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

        if (!handleStaticCollisions(m_speedX, 0))
        {
            m_position.x += m_speedX;
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
        if (m_state == LINK_PUSH_RIGHT && handleStaticCollisions(m_speedX, 0))
        {
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WeaponLevel shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
                {
                    m_state = LINK_WALK_RIGHT_SMALL_SHIELD;
                }
                else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
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

    if (Keyboard::getInstance().keyPushed(BUTTON_LEFT))
    {
        m_speedX = -m_speed;
        m_speedY = m_speed * (Keyboard::getInstance()[BUTTON_DOWN] - Keyboard::getInstance()[BUTTON_UP]);

        if (!m_dirLockUp && !m_dirLockDown)
        {
            m_dirLockLeft = true;
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WeaponLevel shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
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
                else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
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
        if (!handleStaticCollisions(m_speedX, 0))
        {
            m_position.x += m_speedX;
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
        if (m_state == LINK_PUSH_LEFT && handleStaticCollisions(m_speedX, 0))
        {
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WeaponLevel shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
                {
                    m_state = LINK_WALK_LEFT_SMALL_SHIELD;
                }
                else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
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
    if (Keyboard::getInstance().keyPushed(BUTTON_UP))
    {
        m_speedX = m_speed * (Keyboard::getInstance()[BUTTON_RIGHT] - Keyboard::getInstance()[BUTTON_LEFT]);
        m_speedY = -m_speed;

        if (!m_dirLockRight && !m_dirLockLeft)
        {
            m_dirLockUp = true;
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WeaponLevel shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
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
                else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
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

        if (!handleStaticCollisions(0, m_speedY))
        {
            m_position.y += m_speedY;
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
        if (m_state == LINK_PUSH_UP && handleStaticCollisions(0, m_speedY))
        {
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WeaponLevel shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
                {
                    m_state = LINK_WALK_UP_SMALL_SHIELD;
                }
                else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
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
    if (Keyboard::getInstance().keyPushed(BUTTON_DOWN))
    {
        m_speedX = m_speed * (Keyboard::getInstance()[BUTTON_RIGHT] - Keyboard::getInstance()[BUTTON_LEFT]);
        m_speedY = m_speed;

        if (!m_dirLockRight && !m_dirLockLeft)
        {
            m_dirLockDown = true;
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WeaponLevel shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
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
                else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
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

        if (!handleStaticCollisions(0, m_speedY))
        {
            m_position.y += m_speedY;
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
        if (m_state == LINK_PUSH_DOWN && handleStaticCollisions(0, m_speedY))
        {
            if (m_inventory.shieldEquipped())
            {
                WeaponLevel shieldLevel = m_inventory.shieldLevel();
                if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
                {
                    m_state = LINK_WALK_DOWN_SMALL_SHIELD;
                }
                else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
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
void Link::updateState() noexcept
{
    bool shieldEquipped = m_inventory.shieldEquipped();
    WeaponLevel shieldLevel = m_inventory.shieldLevel();

    switch (m_state)
    {

    case LINK_HOOK_DOWN:
        m_state = LINK_WALK_DOWN;
        break;

    case LINK_HOOK_RIGHT:
        m_state = LINK_WALK_RIGHT;
        break;

    case LINK_HOOK_LEFT:
        m_state = LINK_WALK_LEFT;
        break;

    case LINK_HOOK_UP:
        m_state = LINK_WALK_UP;
        break;

    case LINK_WALK_DOWN:
        if (shieldEquipped)
        {
            if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
            {
                m_state = LINK_WALK_DOWN_SMALL_SHIELD;
            }
            else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
            {
                m_state = LINK_WALK_DOWN_BIG_SHIELD;
            }
        }
    break;
    case LINK_WALK_UP:
        if (shieldEquipped)
        {
            if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
            {
                m_state = LINK_WALK_UP_SMALL_SHIELD;
            }
            else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
            {
                m_state = LINK_WALK_UP_BIG_SHIELD;
            }
        }
    break;
    case LINK_WALK_LEFT:
        if (shieldEquipped)
        {
            if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
            {
                m_state = LINK_WALK_LEFT_SMALL_SHIELD;
            }
            else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
            {
                m_state = LINK_WALK_LEFT_BIG_SHIELD;
            }
        }
    break;
    case LINK_WALK_RIGHT:
        if (shieldEquipped)
        {
            if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
            {
                m_state = LINK_WALK_RIGHT_SMALL_SHIELD;
            }
            else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
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

void Link::useWeapon(WEAPON weapon) noexcept
{
    std::string wpn;
    WeaponLevel shieldLevel = m_inventory.shieldLevel();

    switch (weapon)
    {
    case WPN_NONE: wpn = "None"; break;
    case WPN_SWORD:
        wpn = "Sword";
        
        if (m_sword == nullptr)
        {
            m_sword = new Sword;
            m_sword->setDirection(m_direction);
            m_sword->setPosition(m_position);
            m_sword->useWeapon();
        }
        
        
        
        break;
    case WPN_SHIELD:
        wpn = "Shield";
        switch (m_state)
        {
        case LINK_WALK_LEFT_BIG_SHIELD:
        case LINK_WALK_LEFT_SMALL_SHIELD:
        case LINK_WALK_LEFT:
            if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
            {
                m_state = LINK_BLOCK_LEFT_SMALL_SHIELD;
            }
            else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
            {
                m_state = LINK_BLOCK_LEFT_BIG_SHIELD;
            }
            break;
        case LINK_WALK_RIGHT_BIG_SHIELD:
        case LINK_WALK_RIGHT_SMALL_SHIELD:
        case LINK_WALK_RIGHT:
            if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
            {
                m_state = LINK_BLOCK_RIGHT_SMALL_SHIELD;
            }
            else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
            {
                m_state = LINK_BLOCK_RIGHT_BIG_SHIELD;
            }
            break;
        case LINK_WALK_UP_BIG_SHIELD:
        case LINK_WALK_UP_SMALL_SHIELD:
        case LINK_WALK_UP:
            if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
            {
                m_state = LINK_BLOCK_UP_SMALL_SHIELD;
            }
            else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
            {
                m_state = LINK_BLOCK_UP_BIG_SHIELD;
            }
            break;
        case LINK_WALK_DOWN_BIG_SHIELD:
        case LINK_WALK_DOWN_SMALL_SHIELD:
        case LINK_WALK_DOWN:
            if (shieldLevel == WeaponLevel::WPN_LEVEL_1)
            {
                m_state = LINK_BLOCK_DOWN_SMALL_SHIELD;
            }
            else if (shieldLevel == WeaponLevel::WPN_LEVEL_2)
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
        
        if (Keyboard::getInstance().keyPushed(BUTTON_A) || Keyboard::getInstance().keyPushed(BUTTON_B))
        {
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
    case WPN_FLAME_ROD:
        wpn = "Flame rod";
        
        if (m_flameRod == nullptr)
        {
            m_flameRod = new FlameRod();
            m_flameRod->setDirection(m_direction);
            m_flameRod->setPosition(m_position);
            m_flameRod->useWeapon();

            switch (m_state)
            {
            case LINK_WALK_LEFT_BIG_SHIELD:
            case LINK_WALK_LEFT_SMALL_SHIELD:
            case LINK_WALK_LEFT:
                m_state = LINK_HOOK_LEFT;
                break;
            case LINK_WALK_RIGHT_BIG_SHIELD:
            case LINK_WALK_RIGHT_SMALL_SHIELD:
            case LINK_WALK_RIGHT:
                m_state = LINK_HOOK_RIGHT;
                break;
            case LINK_WALK_UP_BIG_SHIELD:
            case LINK_WALK_UP_SMALL_SHIELD:
            case LINK_WALK_UP:
                m_state = LINK_HOOK_UP;
                break;
            case LINK_WALK_DOWN_BIG_SHIELD:
            case LINK_WALK_DOWN_SMALL_SHIELD:
            case LINK_WALK_DOWN:
                m_state = LINK_HOOK_DOWN;
                break;
            }
            std::cout << "Using weapon: " << wpn << std::endl;
            m_useWeapon = true;
            m_usingWeapon = true;
        }
        
        break;
    }



}

void Link::animate()
{
    // When animate() is called
    // There are two types of animation
    // - Key controlled animation
    //  - When the key is held, the player is animated and when released, resets to the initial frame
    // - One press animation
    //  - An animation is carried out and when finished, resets to the initial frame

    //std::cout << "State: " << m_state << " Current frame: " << m_currentFrame << " Max frame: " << m_endFrame << std::endl;

    m_clockAnimation.start();
    if (m_clockAnimation.elapsed(m_animations[m_state].animationFPS))
    {
        if (++m_currentFrame > m_endFrame)
        {
            // Reset to the initial frame
            m_currentFrame = m_animations[m_state].startFrame;
            if (m_usingWeapon)
            {
                m_useWeapon = false;
                m_usingWeapon = false;
            }
        }
        m_clockAnimation.reset();
    }
}