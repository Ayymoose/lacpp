#include "Link.h"
#include "ResourceManager.h"
#include "Keyboard.h"
#include "InputControl.h"
#include "Controller.h"
#include "Renderer.h"
#include <set>
#include <chrono>

namespace Zelda
{

    void Link::setDungeonMarkerLocation(const int x, const int y)
    {
        m_inventory.setDungeonLocationMarker(x, y);
    }

    Vector<int> Link::dungeonMarkerLocation() const
    {
        return m_inventory.dungeonMarkerLocation();
    }

    Link::Link() : 
        Renderable("Link", *ResourceManager::getInstance()[SpriteResource::SPR_LINK], ZD_DEPTH_PLAYER),
        Controllable(m_name),
        m_healthMax(3),
        m_speedX(0),
        m_speedY(0),
        m_useShield(false),
        m_dirLockRight(false),
        m_dirLockUp(false),
        m_dirLockDown(false),
        m_dirLockLeft(false),
        m_canUseArrow(true),
        m_usingArrow(false),
        m_moveable(true),
        m_moving(false),
        m_usingSword(false),
        m_state(LINK_WALK_UP),
        m_useWeapon(false),
        m_usingWeapon(false)
    {

        // TODO: m_width/height is for the renderable element only so we do nned it
        m_width = 16;
        m_height = 16;

        m_position.x = 72;
        m_position.y = 32;

        m_health = 3;
        m_speed = 1;
        m_dir = Direction::DIRECTION_DOWN;

        // TODO: Superfluous header includes

        //m_inventory.addItem(DungeonItem::ITEM_MAP);

        //m_inventory.addItem(DungeonItem::ITEM_NIGHTMARE_KEY);

        Renderer::getInstance().addRenderable(this);
    }

    float Link::health() const
    {
        return m_health;
    }

    float Link::maxHealth() const
    {
        return m_healthMax;
    }

    void Link::update()
    {
        //////////////////////////////////////////////////
        /*if (Keyboard::getInstance().keyPushed(BUTTON_LEFT))
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
        }*/
        //////////////////////////////////////////////////


    }

    void Link::render()
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
            // TODO: Create method that returns the destRect in camera co-ordinates
            // e.g cameraCoordinate()
            m_position.x - Camera::getInstance().getX(),
            m_position.y - Camera::getInstance().getY(),
            static_cast<float>(m_width),
            static_cast<float>(m_height)
        };

        // Max frame controlled by the state
        m_endFrame = m_animations[m_state].endFrame;

        // Select correct animation
        m_animateXPos = m_animations[m_state].x;
        m_animateYPos = m_animations[m_state].y;

        m_sprite->drawSpriteEx(m_srcRect, m_dstRect, 0, SpriteFlip::FLIP_NONE);
    }

    void Link::cull()
    {
        // The owner of objects that can be culled must perform the culling to release the memory of the smart pointers

    }

    void Link::control()
    {
        if (Keyboard::getInstance().keyPushed(BUTTON_LEFT))
        {
            m_position.x -= 1;
        }
        if (Keyboard::getInstance().keyPushed(BUTTON_RIGHT))
        {
            m_position.x += 1;
        }
        if (Keyboard::getInstance().keyPushed(BUTTON_DOWN))
        {
            m_position.y += 1;
        }
        if (Keyboard::getInstance().keyPushed(BUTTON_UP))
        {
            m_position.y -= 1;
        }

        if (Keyboard::getInstance().keyPressed(BUTTON_SELECT))
        {
            m_inventory.inDungeon(true);
            m_inventory.open();
           // Controller::getInstance().setController();
            Controller::getInstance().pushController(&m_inventory);
        }
    }

    void Link::attack()
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

    void Link::die()
    {
        DEBUG(DBG_INFO, "Link died");
    }

    void Link::resetAnimation()
    {
        m_currentFrame = m_animations[m_state].startFrame;
    }

    Vector<float> Link::position() const
    {
        return m_position;
    }

    void Link::addPosition(float x, float y)
    {
        m_position.x += x;
        m_position.y += y;
    }

    void Link::setPosition(float x, float y)
    {
        m_position.x = x;
        m_position.y = y;
    }

    void Link::replenish(float hearts)
    {
        m_health = std::min(m_health + hearts, m_healthMax);
    }

    // Link control
    void Link::move()
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

        }
        else
        {
            if (m_state == LINK_PUSH_RIGHT)
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

        }
        else
        {
            if (m_state == LINK_PUSH_LEFT)
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

        }
        else
        {
            if (m_state == LINK_PUSH_UP)
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

        }
        else
        {
            if (m_state == LINK_PUSH_DOWN)
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
    void Link::updateState()
    {
        auto shieldEquipped = false;
        auto shieldLevel = WeaponLevel::WPN_LEVEL_NONE;
        //bool shieldEquipped = m_inventory.shieldEquipped();
        //WeaponLevel shieldLevel = m_inventory.itemLevel(WPN_SHIELD);

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

    bool Link::moving() const
    {
        return m_moving;
    }

    Direction Link::direction() const
    {
        return m_dir;
    }

    void Link::useWeapon(WeaponItem weapon)
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

        
            break;
        case WPN_BOOMERANG:


            break;
        case WPN_MAGIC_POWDER: break;
        case WPN_BOMBS:


       
        
        
            break;
        case WPN_POWER_BRACELET: break;
        case WPN_ROC_FEATHER: break;
        case WPN_HOOKSHOT: break;
        case WPN_OCARINA: break;
        case WPN_PEGASUS_BOOT: break;
        case WPN_SHOVEL: break;
        case WPN_FLAME_ROD:


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
        /*if (m_clockAnimation.elapsed(m_animations[m_state].animationFPS))
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
        }*/
    }

}