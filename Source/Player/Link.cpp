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
#include "Debug.h""
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

    m_position.x = 72;
    m_position.y = 32;
    m_boundingBox = { (int)m_position.x,(int)m_position.y, PLAYER_BOUNDING_BOX_WIDTH, PLAYER_BOUNDING_BOX_HEIGHT };

    m_health = 3;
    m_speed = 1;
    m_dir = Direction::DIRECTION_DOWN;

    // Set to Tail cave entrace
    /*
    m_currentCollisionMapX = 3;
    m_currentCollisionMapY = 5;
    m_collisionArea = m_collisionMap.m_tailCave[m_currentCollisionMapY][m_currentCollisionMapX];*/

    Renderer::getInstance().addRenderable(this);
    //Controller::getInstance().setController(this);

    m_upDownSpeedLimiter = 1;

    m_lerpPrevious = m_position;
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


void Link::update() noexcept
{
    // TODO: Fixed step update goes here
    if (m_currentTime == 0)
    {
        m_currentTime = SDL_GetTicks();
    }

    // TODO: Even this doesn't work although CPed from the example on FixedTimestep
    // It's inconsistent and jittery still
    auto const timeNow = SDL_GetTicks();
    auto frameTime = timeNow - m_currentTime;
    if (frameTime > m_maxFrameTime)
    {
        frameTime = m_maxFrameTime;
    }

    m_currentTime = timeNow;
    m_accumulator += frameTime;


    static float xSpeed = 0.5;
    static float ySpeed = 0;

    while (m_accumulator >= m_dt)
    {
        // Lerp
        m_lerpPrevious = m_position;

        if (Keyboard::getInstance().keyPushed(BUTTON_LEFT))
        {
            m_position.x -= 0.75;
        }
        if (Keyboard::getInstance().keyPushed(BUTTON_RIGHT))
        {
            m_position.x += 0.75;
        }
        if (Keyboard::getInstance().keyPushed(BUTTON_DOWN))
        {
            m_position.y += 0.75;
        }
        if (Keyboard::getInstance().keyPushed(BUTTON_UP))
        {
            m_position.y -= 0.75;
        }


        m_accumulator -= m_dt;
    }

    m_alphaTime = m_accumulator / m_dt;

    // (A * alpha) + B * (1.0 - alpha)

    //auto v = (m_lerpPrevious * m_alphaTime) + (m_position * (1.0 - m_alphaTime));

    m_drawPosition = Vector<float>::lerp(m_lerpPrevious, m_position, m_alphaTime);

    //std::cout << '(' << m_position.x << ',' << m_position.y << ')' << '\n';
    

}

void Link::render() noexcept
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
        m_drawPosition.x - Camera::getInstance().getX(),
        m_drawPosition.y - Camera::getInstance().getY(),
        static_cast<float>(m_width),
        static_cast<float>(m_height)
    };

    // Max frame controlled by the state
    m_endFrame = m_animations[m_state].endFrame;

    // Select correct animation
    m_animateXPos = m_animations[m_state].x;
    m_animateYPos = m_animations[m_state].y;

    m_texture.drawSpriteEx(Renderer::getInstance().getRenderer(), m_srcRect, m_dstRect, 0, SpriteFlip::FLIP_NONE);
    //SDL_ASSERT(SDL_RenderCopyExF(Renderer::getInstance().getRenderer(), m_texture, &m_srcRect, &m_dstRect, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE), SDL_ERROR_MESSAGE);

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

   /* if (Keyboard::getInstance().keyPushed(BUTTON_RIGHT))
    {
        m_position.x += 64.0 * (ts / 1000.0);
    }
    if (Keyboard::getInstance().keyPushed(BUTTON_LEFT))
    {
        m_position.x -= 64.0 * (ts / 1000.0);
    }
    if (Keyboard::getInstance().keyPushed(BUTTON_UP))
    {
        m_position.y -= 64.0 * (ts / 1000.0);
    }
    if (Keyboard::getInstance().keyPushed(BUTTON_DOWN))
    {
        m_position.y += 64.0 * (ts / 1000.0);
    }*/

#if 0
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
#endif
}

void Link::attack() noexcept
{
    if (Keyboard::getInstance()[BUTTON_A])
    {
        useWeapon(m_inventory.weaponA().first);
    }
    if (Keyboard::getInstance()[BUTTON_B])
    {
        useWeapon(m_inventory.weaponB().first);
    }


    if (Keyboard::getInstance().keyReleased(BUTTON_A))
    {
        if (m_inventory.weaponA().first == WPN_SHIELD)
        {
            m_useShield = false;
            updateState();
        }
    }
    if (Keyboard::getInstance().keyReleased(BUTTON_B))
    {
        if (m_inventory.weaponB().first == WPN_SHIELD)
        {
            m_useShield = false;
            updateState();
        }
    }
}

void Link::die() noexcept
{
    DEBUG(DBG_INFO, "Link died");
}

void Link::resetAnimation() noexcept
{
    m_currentFrame = m_animations[m_state].startFrame;
}

Vector<float> Link::position() const noexcept
{
    return m_position;
}

void Link::addPosition(float x, float y) noexcept
{
    m_position.x += x;
    m_position.y += y;
}

void Link::setPosition(float x, float y) noexcept
{
    m_position.x = x;
    m_position.y = y;
}

void Link::replenish(float hearts) noexcept
{
    m_health = std::min(m_health + hearts, m_healthMax);
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
                WeaponLevel shieldLevel = m_inventory.itemLevel(WPN_SHIELD);
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
            m_dir = Direction::DIRECTION_RIGHT;
        }

        if (!handleStaticCollisions(m_speedX, 0))
        {
            m_position.x += m_speedX;
        }
        else
        {
            // If collision with wall
            m_state = LINK_PUSH_RIGHT;
            m_dir = Direction::DIRECTION_RIGHT;
        }
    }
    else
    {
        if (m_state == LINK_PUSH_RIGHT && handleStaticCollisions(m_speedX, 0))
        {
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WeaponLevel shieldLevel = m_inventory.itemLevel(WPN_SHIELD);
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
            m_dir = Direction::DIRECTION_RIGHT;
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
                WeaponLevel shieldLevel = m_inventory.itemLevel(WPN_SHIELD);
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
            m_dir = Direction::DIRECTION_LEFT;
        }
        if (!handleStaticCollisions(m_speedX, 0))
        {
            m_position.x += m_speedX;
        }
        else
        {
            // If collision with wall
            m_state = LINK_PUSH_LEFT;
            m_dir = Direction::DIRECTION_LEFT;
        }
    }
    else
    {
        if (m_state == LINK_PUSH_LEFT && handleStaticCollisions(m_speedX, 0))
        {
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WeaponLevel shieldLevel = m_inventory.itemLevel(WPN_SHIELD);
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
            m_dir = Direction::DIRECTION_LEFT;
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
                WeaponLevel shieldLevel = m_inventory.itemLevel(WPN_SHIELD);
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
            m_dir = Direction::DIRECTION_UP;
        }

        if (!handleStaticCollisions(0, m_speedY))
        {
            m_position.y += m_speedY;
        }
        else
        {
            // If collision with wall
            m_state = LINK_PUSH_UP;
            m_dir = Direction::DIRECTION_UP;
        }
    }
    else
    {
        if (m_state == LINK_PUSH_UP && handleStaticCollisions(0, m_speedY))
        {
            // Show shield equipped sprite
            if (m_inventory.shieldEquipped())
            {
                WeaponLevel shieldLevel = m_inventory.itemLevel(WPN_SHIELD);
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
            m_dir = Direction::DIRECTION_UP;
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
                WeaponLevel shieldLevel = m_inventory.itemLevel(WPN_SHIELD);
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
            m_dir = Direction::DIRECTION_DOWN;
        }

        if (!handleStaticCollisions(0, m_speedY))
        {
            m_position.y += m_speedY;
        }
        else
        {
            // If collision with wall
            m_state = LINK_PUSH_DOWN;
            m_dir = Direction::DIRECTION_DOWN;
        }
    }
    else
    {
        if (m_state == LINK_PUSH_DOWN && handleStaticCollisions(0, m_speedY))
        {
            if (m_inventory.shieldEquipped())
            {
                WeaponLevel shieldLevel = m_inventory.itemLevel(WPN_SHIELD);
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
            m_dir = Direction::DIRECTION_DOWN;
        }
    }
}

// Update the player (visible state)
void Link::updateState() noexcept
{
    bool shieldEquipped = m_inventory.shieldEquipped();
    WeaponLevel shieldLevel = m_inventory.itemLevel(WPN_SHIELD);

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
    return m_dir;
}

void Link::useWeapon(WeaponItem weapon) noexcept
{
    WeaponLevel shieldLevel = m_inventory.itemLevel(WPN_SHIELD);

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
            m_sword->setDirection(m_dir);
            m_sword->setPosition(m_position);
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
        
        // When a new object is created, add it to the cullable list
        // Each frame, call cull() on each item in the cullable list
        // If it returns true then remove the item from the render list and free the memory

        // For bombs, it will get removed when it explodes or goes out of view
        // For arrows it will get removed when it goes out of view


            if (m_inventory.arrows() && m_canUseArrow)
            {
                auto arrow = std::make_unique<Arrow>();
                arrow->setDirection(m_dir);
                arrow->setPosition(m_position);
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
            m_boomerang->setDirection(m_dir);
            m_boomerang->setPosition(m_position);
        }
        
        break;
    case WPN_MAGIC_POWDER: break;
    case WPN_BOMBS:


        if (m_bomb == nullptr)
        {
            if (m_inventory.bombs())
            {
                m_bomb = std::make_unique<Bomb>();
                m_bomb->setDirection(m_dir);
                m_bomb->setPosition(m_position);
                m_inventory.useBombs();
            }

        }

        
        
        break;
    case WPN_POWER_BRACELET: break;
    case WPN_ROC_FEATHER: break;
    case WPN_HOOKSHOT: break;
    case WPN_OCARINA: break;
    case WPN_PEGASUS_BOOT: break;
    case WPN_SHOVEL: break;
    case WPN_FLAME_ROD:

        if (m_flameRod == nullptr)
        {
            m_flameRod = new FlameRod();
            m_flameRod->setDirection(m_dir);
            m_flameRod->setPosition(m_position);

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
        DEBUG(DBG_INFO, "Animating frame " + std::to_string(m_currentFrame) + " out of " + std::to_string(m_endFrame));
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