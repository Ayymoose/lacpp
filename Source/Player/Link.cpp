#include "Link.h"
#include "Resource.h"
#include "InputControl.h"
#include "Vector.h"
#include "Camera.h"
#include "Renderer.h"
#include "Arrow.h"
#include "Depth.h"
#include "ZD_Assert.h"
#include "Keyboard.h"
#include "Engine.h"
#include <set>

namespace Zelda
{

void Link::setDungeonMarkerLocation(int x, int y) noexcept
{
    m_inventory.setDungeonLocationMarker(x, y);
}

Link::Link() : 
    Renderable("Link", ResourceManager::getInstance()[Graphic::GFX_LINK], ZD_DEPTH_PLAYER),
    Controllable(m_name),
    m_healthMax(3),
    m_speedX(0),
    m_speedY(0),
    m_useShield(false),
    m_dirLockRight(false),
    m_dirLockUp(false),
    m_dirLockDown(false),
    m_dirLockLeft(false),
    m_boomerang(nullptr),
    m_flameRod(nullptr),
    m_canUseArrow(true),
    m_usingArrow(false),
    m_moveable(true),
    m_moving(false),
    m_usingSword(false),
    m_state(LINK_WALK_UP),
    m_useWeapon(false),
    m_usingWeapon(false)
{
    m_width = 16;
    m_height = 16;

    m_positionVector.x = 72;
    m_positionVector.y = 32;
    m_boundingBox = { (int)m_positionVector.x,(int)m_positionVector.y, PLAYER_BOUNDING_BOX_WIDTH, PLAYER_BOUNDING_BOX_HEIGHT };

    m_health = 3;
    m_speed = 1;
    m_direction = Direction::DIRECTION_DOWN;

    // Set to Tail cave entrace
    /*
    m_currentCollisionMapX = 3;
    m_currentCollisionMapY = 5;
    m_collisionArea = m_collisionMap.m_tailCave[m_currentCollisionMapY][m_currentCollisionMapX];*/

    Renderer::getInstance().addRenderable(this);
    Controller::getInstance().setController(this);

    m_upDownSpeedLimiter = 1;

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
    return false;

#if 0
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

    m_boundingBox.x = m_positionVector.x + PLAYER_BOUNDING_BOX_WIDTH_OFFSET;
    m_boundingBox.y = m_positionVector.y + PLAYER_BOUNDING_BOX_HEIGHT;

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
        m_positionVector.y-= m_speed;
    }
    if (topLeftTopToBottom && !(m_speedX == m_speed && m_speedY == m_speed) && !(m_speedX == -m_speed && m_speedY == m_speed))
    {
        m_positionVector.x-= m_speed;
    }
    if (topRightTopToBottom && !(m_speedX == m_speed && m_speedY == m_speed) && !(m_speedX == -m_speed && m_speedY == m_speed))
    {
        m_positionVector.x+= m_speed;
    }
    if (topRightRightToLeft && !(m_speedX == -m_speed && m_speedY == m_speed) && !(m_speedX == -m_speed && m_speedY == -m_speed))
    {
        m_positionVector.y-= m_speed;
    }
    if (bottomRightRightToLeft && !(m_speedX == -m_speed && m_speedY == -m_speed) && !(m_speedX == -m_speed && m_speedY == m_speed))
    {
        m_positionVector.y+= m_speed;
    }
    if (bottomRightBottomToTop && !(m_speedX == -m_speed && m_speedY == -m_speed) && !(m_speedX == m_speed && m_speedY == -m_speed))
    {
        m_positionVector.x+= m_speed;
    }
    if (bottomLeftBottomToTop && !(m_speedX == -m_speed && m_speedY == -m_speed) && !(m_speedX == m_speed && m_speedY == -m_speed))
    {
        m_positionVector.x-= m_speed;
    }
    if (bottomLeftLeftToRight && !(m_speedX == m_speed && m_speedY == m_speed) && !(m_speedX == m_speed && m_speedY == -m_speed))
    {
        m_positionVector.y+= m_speed;
    }

    return collision;
#endif
}

void Link::render(SDL_Renderer* renderer) noexcept
{

    // The render loop calls render() every frame
    // But there are special cases of animation

    // Walking - Holding movement keys will play the same animation over and over unless the user has the sword out



    // Get clock, if elapsed, increase frame counter
    // Source rect to pull from sprite sheet
    m_srcRect =
    {
        m_animateXPos + (m_currentFrame * m_width),
        m_animateYPos,
        m_width,
        m_height
    };

    // Where to draw on screen
    m_dstRect =
    {
        m_positionVector.x - Camera::getInstance().getX(),
        m_positionVector.y - Camera::getInstance().getY(),
        static_cast<float>(m_width),
        static_cast<float>(m_height)
    };

    // Max frame controlled by the state
    m_endFrame = m_animations[m_state].endFrame;

    // Select correct animation
    m_animateXPos = m_animations[m_state].x;
    m_animateYPos = m_animations[m_state].y;

    SDL_ASSERT(SDL_RenderCopyExF(renderer, m_texture, &m_srcRect, &m_dstRect, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE), SDL_ERROR_MESSAGE);


    // Drawing bounding boxes for testing
    //m_collisionArea = m_collisionMap.m_tailCave[m_currentCollisionMapY][m_currentCollisionMapX];
    
    SDL_Rect playerRect =
    {
        m_boundingBox.x - Camera::getInstance().getX(),
        m_boundingBox.y - Camera::getInstance().getY(),
        m_boundingBox.w,
        m_boundingBox.h
    };

    //SDL_ASSERT(SDL_RenderDrawRect(renderer, &playerRect), SDL_ERROR_MESSAGE);

    /* std::vector<BoundingBox> bbs = m_collisionMap.collisionMap(m_collisionArea);
    for (const BoundingBox& box : bbs)
    {

        SDL_Rect bbRect = { box.x , box.y, box.w, box.h };

        SDL_ASSERT(SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0), SDL_ERROR_MESSAGE);
        SDL_ASSERT(SDL_RenderDrawRect(renderer, &bbRect), SDL_ERROR_MESSAGE);
    }
    
    */

    // Perishable weapons
    // Weapons that go offscreen are culled
    /*

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
    }*/

}

void Link::cull() noexcept
{
    // The owner of objects that can be culled must perform the culling to release the memory of the smart pointers
    if (m_bomb && m_bomb->cull())
    {
        m_bomb.reset();
    }
    
}

void Link::control() noexcept
{
    // Open the inventory
    if (Keyboard::getInstance().keyPushed(BUTTON_SELECT))
    {
        m_inventory.open();
        // Give control to the inventory and pause the engine
        Controller::getInstance().pushController(this, &m_inventory);
        Engine::getInstance().pause(true);
        std::cout << "Inventory opened!\n";
    }

    // TODO: Open worldmap only if inventory not open
    // Open worldmap
    /*if (Keyboard::getInstance().keyPushed(BUTTON_START))
    {
        m_worldmap.open();
        // Give control to the inventory and pause the engine
        Controller::getInstance().pushController(this, &m_worldmap);
        Engine::getInstance().pause(true);
        std::cout << "Worldmap opened!\n";
    }*/

    // Only animate if moving
    if (m_moveable && (Keyboard::getInstance().keyPushed(BUTTON_RIGHT) || Keyboard::getInstance().keyPushed(BUTTON_LEFT) || Keyboard::getInstance().keyPushed(BUTTON_DOWN) || Keyboard::getInstance().keyPushed(BUTTON_UP)))
    {
        // Animation
        animate();

        // If we are holding left and we press up or down, we don't want to change the state whatever it is...
        // Same applies to other directions 
        move();

        m_moving = true;
    }
    else
    {
        m_moving = false;
        // TODO: Current frame has to be reset to intial frame
        if (!m_usingSword && !m_usingArrow)
        {
            resetAnimation();
        }
        else
        {
            m_moveable = false;
            if (!m_animationComplete)
            {
                animate();
            }
            else
            {
                updateState();
                m_animationComplete = false;
                m_moveable = true;

                if (m_usingSword)
                {
                    m_usingSword = false;
                    m_sword.reset();
                }
                else if (m_usingArrow)
                {
                    m_usingArrow = false;
                    //m_quiver.erase(m_quiver.begin());
                    m_canUseArrow = true;
                }

            }
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
    if (Keyboard::getInstance()[BUTTON_B])
    {
        useWeapon(m_inventory.weaponB());
    }


    if (Keyboard::getInstance().keyReleased(BUTTON_A))
    {
        if (m_inventory.weaponA() == WPN_SHIELD)
        {
            m_useShield = false;
            updateState();
        }
    }
    if (Keyboard::getInstance().keyReleased(BUTTON_B))
    {
        if (m_inventory.weaponB() == WPN_SHIELD)
        {
            m_useShield = false;
            updateState();
        }
    }
}

void Link::die() noexcept
{
    std::cout << "Link died" << std::endl;
}

void Link::resetAnimation() noexcept
{
    m_currentFrame = m_animations[m_state].startFrame;
}

Vector<float> Link::position() const noexcept
{
    return m_positionVector;
}

void Link::addPosition(float x, float y) noexcept
{
    m_positionVector.x += x;
    m_positionVector.y += y;
}

void Link::setPosition(float x, float y) noexcept
{
    m_positionVector.x = x;
    m_positionVector.y = y;
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

        // TODO: Diagonal speed lock
        m_speedX = m_speed;

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
            m_direction = Direction::DIRECTION_RIGHT;
        }

        if (!handleStaticCollisions(m_speedX, 0))
        {
            m_positionVector.x += m_speedX;
        }
        else
        {
            // If collision with wall
            m_state = LINK_PUSH_RIGHT;
            m_direction = Direction::DIRECTION_RIGHT;
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
            m_direction = Direction::DIRECTION_RIGHT;
        }
    }

    if (Keyboard::getInstance().keyPushed(BUTTON_LEFT))
    {
        m_speedX = -m_speed;
        m_upDownSpeedLimiter = 0.70710678118654752440084436210485f;

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
            m_direction = Direction::DIRECTION_LEFT;
        }
        if (!handleStaticCollisions(m_speedX, 0))
        {
            m_positionVector.x += m_speedX;
        }
        else
        {
            // If collision with wall
            m_state = LINK_PUSH_LEFT;
            m_direction = Direction::DIRECTION_LEFT;
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
            m_direction = Direction::DIRECTION_LEFT;
        }
    }
    if (Keyboard::getInstance().keyPushed(BUTTON_UP))
    {
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
            m_direction = Direction::DIRECTION_UP;
        }

        if (!handleStaticCollisions(0, m_speedY))
        {
            m_positionVector.y += m_speedY;
        }
        else
        {
            // If collision with wall
            m_state = LINK_PUSH_UP;
            m_direction = Direction::DIRECTION_UP;
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
            m_direction = Direction::DIRECTION_UP;
        }
    }
    if (Keyboard::getInstance().keyPushed(BUTTON_DOWN))
    {
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
            m_direction = Direction::DIRECTION_DOWN;
        }

        if (!handleStaticCollisions(0, m_speedY))
        {
            m_positionVector.y += m_speedY;
        }
        else
        {
            // If collision with wall
            m_state = LINK_PUSH_DOWN;
            m_direction = Direction::DIRECTION_DOWN;
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
            m_direction = Direction::DIRECTION_DOWN;
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

    case LINK_SWORD_DOWN:
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
        else
        {
            m_state = LINK_WALK_DOWN;
        }
        break;
    case LINK_SWORD_RIGHT:
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
        else
        {
            m_state = LINK_WALK_RIGHT;
        }
        break;
    case LINK_SWORD_LEFT:
        m_state = LINK_WALK_LEFT;
        break;
    case LINK_SWORD_UP:
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
        else
        {
            m_state = LINK_WALK_UP;
        }
        break;
    }
}

bool Link::moving() const noexcept
{
    return m_moving;
}

Direction Link::direction() const noexcept
{
    return m_direction;
}

void Link::useWeapon(WEAPON weapon) noexcept
{
    WeaponLevel shieldLevel = m_inventory.shieldLevel();

    switch (weapon)
    {
    case WPN_NONE: break;
    case WPN_SWORD:
        
        // Create a single sword object

        // If the sword is held after the animation ends
        // Remain in the last state and charge up the sword
        // Otherwise destroy

        switch (m_state)
        {
        case LINK_WALK_DOWN_BIG_SHIELD:
        case LINK_WALK_DOWN_SMALL_SHIELD:
        case LINK_WALK_DOWN:
            m_state = LINK_SWORD_DOWN;
            break;
        case LINK_WALK_RIGHT_BIG_SHIELD:
        case LINK_WALK_RIGHT_SMALL_SHIELD:
        case LINK_WALK_RIGHT:
            m_state = LINK_SWORD_RIGHT;
            break;
        case LINK_WALK_LEFT_BIG_SHIELD:
        case LINK_WALK_LEFT_SMALL_SHIELD:
        case LINK_WALK_LEFT:
            m_state = LINK_SWORD_LEFT;
            break;
        case LINK_WALK_UP_BIG_SHIELD:
        case LINK_WALK_UP_SMALL_SHIELD:
        case LINK_WALK_UP:
            m_state = LINK_SWORD_UP;
            break;
        }

        if (m_sword == nullptr)
        {
            m_sword = std::make_unique<Sword>();
            m_sword->setDirection(m_direction);
            m_sword->setPosition(m_positionVector);
            m_usingSword = true;
        }
        
        
        
        break;
    case WPN_SHIELD:
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

        // We can fire multiple arrows
        // An arrow that hits an enemy disappears
        // An arrow that goes off screen disappears
        // An arrow that hits an object deflects and disappears

        switch (m_state)
        {
        case LINK_WALK_DOWN_BIG_SHIELD:
        case LINK_WALK_DOWN_SMALL_SHIELD:
        case LINK_WALK_DOWN:
            m_state = LINK_HOOK_DOWN;
            break;
        case LINK_WALK_RIGHT_BIG_SHIELD:
        case LINK_WALK_RIGHT_SMALL_SHIELD:
        case LINK_WALK_RIGHT:
            m_state = LINK_HOOK_RIGHT;
            break;
        case LINK_WALK_LEFT_BIG_SHIELD:
        case LINK_WALK_LEFT_SMALL_SHIELD:
        case LINK_WALK_LEFT:
            m_state = LINK_HOOK_LEFT;
            break;
        case LINK_WALK_UP_BIG_SHIELD:
        case LINK_WALK_UP_SMALL_SHIELD:
        case LINK_WALK_UP:
            m_state = LINK_HOOK_UP;
            break;
        }
        

        // std::vector<std::shared_ptr> cullables;
// for (auto cullable : cullables)
// if (cullable->cull())
// {
//     cullable->reset();
//     cullables.remove(this it);
// }
// 
        // When a new object is created, add it to the cullable list
        // Each frame, call cull() on each item in the cullable list
        // If it returns true then remove the item from the render list and free the memory

        // For bombs, it will get removed when it explodes or goes out of view
        // For arrows it will get removed when it goes out of view


            if (m_inventory.bowAndArrowAvailable() && m_canUseArrow)
            {
                auto arrow = std::make_unique<Arrow>();
                arrow->setDirection(m_direction);
                arrow->setPosition(m_positionVector);
                m_inventory.useBowAndArrow();
                m_quiver.emplace_back(std::move(arrow));
                m_canUseArrow = false;
                m_usingArrow = true;
            }

        
        break;
    case WPN_BOOMERANG:

        // A boomerang can only be thrown once
        // A boomerang that hits an enemy stuns it and returns to the player
        // A boomerang that goes off screen returns to the player
        // A boomerang that hits an object deflects and returns

        if (m_boomerang == nullptr)
        {
            m_boomerang = new Boomerang();
            m_boomerang->setDirection(m_direction);
            m_boomerang->setPosition(m_positionVector);
        }
        
        break;
    case WPN_MAGIC_POWDER: break;
    case WPN_BOMBS:


        if (m_bomb == nullptr)
        {
            if (m_inventory.bombsAvailable())
            {
                m_bomb = std::make_unique<Bomb>();
                m_bomb->setDirection(m_direction);
                m_bomb->setPosition(m_positionVector);
                m_inventory.useBombs();
            }

        }

        
        
        break;
    case WPN_POWER_BRACELET_1: break;
    case WPN_POWER_BRACELET_2: break;
    case WPN_ROC_FEATHER: break;
    case WPN_HOOKSHOT: break;
    case WPN_OCARINA: break;
    case WPN_PEGASUS_BOOT: break;
    case WPN_SHOVEL: break;
    case WPN_FLAME_ROD:

        if (m_flameRod == nullptr)
        {
            m_flameRod = new FlameRod();
            m_flameRod->setDirection(m_direction);
            m_flameRod->setPosition(m_positionVector);

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
    //m_clockAnimation.start();
    if (m_clockAnimation.elapsed(m_animations[m_state].animationFPS))
    {
        std::cout << "Animating frame " << m_currentFrame << " out of " << m_endFrame << '\n';
        if (m_currentFrame+1 > m_endFrame)
        {
            // Reset to the initial frame
            if (!m_usingSword)
            {
                m_currentFrame = m_animations[m_state].startFrame;
            }
            m_animationComplete = true;
        }
        else
        {
            m_currentFrame++;
            m_animationComplete = false;
        }
    }
}

}