#include "Camera.h"
#include "Depth.h"
#include "Renderer.h"
#include "Link.h"
#include "RoomManager.h"
#include "Engine.h"
#include "Controller.h"

namespace Zelda
{

    Camera::Camera() :
        Renderable("Camera", Sprite(Renderer::getInstance().getRenderer(), CAMERA_WIDTH, CAMERA_HEIGHT), ZD_DEPTH_BACKGROUND),
        m_scrollX(0),
        m_scrollY(0),
        m_x(0),
        m_y(0),
        m_screenX(0),
        m_screenY(0),
        m_swapX(CAMERA_WIDTH),
        m_swapY(CAMERA_HEIGHT),
        m_scrollSpeed(0),
        m_scrollLeft(false),
        m_scrollRight(false),
        m_scrollDown(false),
        m_scrollUp(false),
        m_scrolled(0)
    {
        assert(m_sprite->data());
        // TODO: Remove Camera from Renderable
        Renderer::getInstance().addRenderable(this);
    }

    void Camera::setPosition(const int x, const int y)
    {
        assert(x % CAMERA_WIDTH == 0);
        assert(y % CAMERA_HEIGHT == 0);
        m_x = x;
        m_y = y;
    }

    void Camera::render()
    {
        // We will only ever track the player
        auto player = &Link::getInstance();
        auto const position = player->position();
        auto const x = position.x;
        auto const y = position.y;

        // Camera scrolling is implemented by using two canvases
        // One main canvas and a swap canvas
        // The main canvas is the one we always see on the screen
        // The swap canvas is the canvas that we see when scrolling to the next area
        // usually it is hidden offscreen

        // Once scrolling is complete, we reset the main canvas position and player position
        // This just makes it easier to position solids and enemies within one screen

        // Transition the player if they move off the screen
        if (x < m_scrollX - SCROLL_LEFT_EDGE && !m_scrollLeft)
        {
            // Scroll left
            m_scrollLeft = true;
            Controller::getInstance().setController(nullptr);

            // Pause engine
            Engine::getInstance().pause(true);

            // Load next room objects
           // RoomManager::getInstance().roomDo(RoomAction::ROOM_LOAD, m_nextRoomIndex - 1);
           // RoomManager::getInstance().transitionObjects(m_nextRoomIndex - 1, CAMERA_WIDTH, 0);

            // Put swap canvas in view
            m_swapX = -CAMERA_WIDTH;
            m_swapY = 0;

            // Find out if we can scroll left
            RoomManager::getInstance().updateNextRoomLocation(RoomDirection::LEFT);

        }
        else if (x > m_scrollX + CAMERA_WIDTH - SCROLL_RIGHT_EDGE && !m_scrollRight)
        {
            // Scroll right
            m_scrollRight = true;
            Controller::getInstance().setController(nullptr);

            // Pause engine
            Engine::getInstance().pause(true);

            // Load next room objects
            //RoomManager::getInstance().roomDo(RoomAction::ROOM_LOAD, m_nextRoomIndex + 1);
            //RoomManager::getInstance().transitionObjects(m_nextRoomIndex + 1, -CAMERA_WIDTH, 0);

            // Put swap canvas in view
            m_swapX = CAMERA_WIDTH;
            m_swapY = 0;

            // Find out if we can scroll right
            RoomManager::getInstance().updateNextRoomLocation(RoomDirection::RIGHT);
        }
        else if (y < m_scrollY - SCROLL_UP_EDGE && !m_scrollUp)
        {
            // Scroll up
            m_scrollUp = true;
            Controller::getInstance().setController(nullptr);

            // Pause engine
            Engine::getInstance().pause(true);

            // Load next room objects
            //RoomManager::getInstance().roomDo(RoomAction::ROOM_LOAD, m_nextRoomIndex /*- m_tilemap.roomsAcross()*/);
            //RoomManager::getInstance().transitionObjects(m_nextRoomIndex/* - m_tilemap.roomsAcross()*/, 0, CAMERA_HEIGHT);

            // Put swap canvas in view
            // TODO: Black area shown when moving in the corner
            m_swapX = 0;
            m_swapY = -CAMERA_HEIGHT;

            // Find out if we can scroll up
            RoomManager::getInstance().updateNextRoomLocation(RoomDirection::UP);
        }
        else if (y > m_scrollY + CAMERA_HEIGHT - SCROLL_DOWN_EDGE && !m_scrollDown)
        {
            // -HUD height because its on the bottom

            // Scroll down
            m_scrollDown = true;
            Controller::getInstance().setController(nullptr);

            // Pause engine
            Engine::getInstance().pause(true);

            // Load next room objects
            //RoomManager::getInstance().roomDo(RoomAction::ROOM_LOAD, m_nextRoomIndex /*+ m_tilemap.roomsAcross()*/);
            //RoomManager::getInstance().transitionObjects(m_nextRoomIndex /*+ m_tilemap.roomsAcross()*/, 0, -CAMERA_HEIGHT);

            // Put swap canvas in view
            m_swapX = 0;
            m_swapY = CAMERA_HEIGHT;

            // Find out if we can scroll down
            RoomManager::getInstance().updateNextRoomLocation(RoomDirection::DOWN);
        }

        auto dungeonMarker = player->dungeonMarkerLocation();
    

        if (m_scrollLeft)
        {
            if (m_scrolled != CAMERA_WIDTH)
            {
                m_scrollX -= m_scrollSpeed;
                m_scrolled += m_scrollSpeed;

                // Move player slowly with camera
                constexpr float leftSteps = 14.0f;
                auto const cameraSteps = CAMERA_WIDTH / m_scrollSpeed;
                auto const pushSteps = leftSteps / cameraSteps;
                player->setPosition(player->position().x - pushSteps, player->position().y);
            }
            else
            {
                // Scrolling left complete

                // Clear previous room's objects
                // Shift previous object's out of view otherwise they will flicker on screen before disappearing
                //RoomManager::getInstance().transitionObjects(roomIndex, -CAMERA_WIDTH, 0);
                //RoomManager::getInstance().roomDo(RoomAction::ROOM_CLEAR, roomIndex);

                // Remove transition from loaded objects
                //RoomManager::getInstance().transitionObjects(roomIndex - 1, 0, 0);

                // Update current view
                m_x -= CAMERA_WIDTH;

                 // Reset initial positions
                m_screenX = 0;
                m_screenY = 0;
                m_scrollX = 0;
                m_scrollY = 0;

                player->setPosition(CAMERA_WIDTH + player->position().x, player->position().y);

                // Unpause engine
                Engine::getInstance().pause(false);

                m_scrollLeft = false;
                m_scrolled = 0;
                Controller::getInstance().setController(player);
                player->resetAnimation();

                // Update room information
                RoomManager::getInstance().updateCurrentRoomLocation();

                dungeonMarker.x--;

            }
        }
        else if (m_scrollRight)
        {
            if (m_scrolled != CAMERA_WIDTH)
            {
                m_scrollX += m_scrollSpeed;
                m_scrolled += m_scrollSpeed;

                // Move player slowly with camera
                constexpr float rightSteps = 14.0f;
                auto const cameraSteps = CAMERA_WIDTH / m_scrollSpeed;
                auto const pushSteps = rightSteps / cameraSteps;
                player->setPosition(player->position().x + pushSteps, player->position().y);
            }
            else
            {

                // Clear previous room's objects
                // Shift previous object's out of view otherwise they will flicker on screen before disappearing
                //RoomManager::getInstance().transitionObjects(roomIndex, CAMERA_WIDTH, 0);
                //RoomManager::getInstance().roomDo(RoomAction::ROOM_CLEAR, roomIndex);

                // Remove transition from loaded objects
                //RoomManager::getInstance().transitionObjects(roomIndex + 1, 0, 0);

                m_x += CAMERA_WIDTH;

                // Reset initial positions
                m_screenX = 0;
                m_screenY = 0;
                m_scrollX = 0;
                m_scrollY = 0;

                player->setPosition(player->position().x - CAMERA_WIDTH, player->position().y);

                // Unpause engine
                Engine::getInstance().pause(false);

                m_scrollRight = false;
                m_scrolled = 0;
                Controller::getInstance().setController(player);
                player->resetAnimation();

                // Update room information
                RoomManager::getInstance().updateCurrentRoomLocation();

                dungeonMarker.x++;
            }
        }
        else if (m_scrollDown)
        {
            if (m_scrolled != CAMERA_HEIGHT)
            {
                m_scrollY += m_scrollSpeed;
                m_scrolled += m_scrollSpeed;

                // Move player slowly with camera
                constexpr float downSteps = 12.0f;
                auto const cameraSteps = CAMERA_HEIGHT / m_scrollSpeed;
                auto const pushSteps = downSteps / cameraSteps;
                player->setPosition(player->position().x, player->position().y + pushSteps);
            }
            else
            {
                // Unpause engine
                Engine::getInstance().pause(false);

                // Clear previous room's objects
                // Shift previous object's out of view otherwise they will flicker on screen before disappearing
               // RoomManager::getInstance().transitionObjects(roomIndex, 0, CAMERA_HEIGHT);
               // RoomManager::getInstance().roomDo(RoomAction::ROOM_CLEAR, roomIndex);

                // Remove transition from loaded objects
               // RoomManager::getInstance().transitionObjects(roomIndex /*+ m_tilemap.roomsAcross()*/, 0, 0);

                m_y += CAMERA_HEIGHT;

                // Reset initial positions
                m_screenX = 0;
                m_screenY = 0;
                m_scrollX = 0;
                m_scrollY = 0;

                player->setPosition(player->position().x, player->position().y - CAMERA_HEIGHT);
           
                m_scrollDown = false;
                m_scrolled = 0;
                Controller::getInstance().setController(player);
                player->resetAnimation();

                // Update room information
                RoomManager::getInstance().updateCurrentRoomLocation();

                dungeonMarker.y++;
            }
        }
        else if (m_scrollUp)
        {
            if (m_scrolled != CAMERA_HEIGHT)
            {
                m_scrollY -= m_scrollSpeed;
                m_scrolled += m_scrollSpeed;

                // Move player slowly with camera
                constexpr float upSteps = 12.0f;
                auto const cameraSteps = CAMERA_HEIGHT / m_scrollSpeed;
                auto const pushSteps = upSteps / cameraSteps;
                player->setPosition(player->position().x, player->position().y - pushSteps);
            }
            else
            {
                // Clear previous room's objects
                // Shift previous object's out of view otherwise they will flicker on screen before disappearing
               // RoomManager::getInstance().transitionObjects(roomIndex, 0, -CAMERA_HEIGHT);
               // RoomManager::getInstance().roomDo(RoomAction::ROOM_CLEAR, roomIndex);

                // Remove transition from loaded objects
               // RoomManager::getInstance().transitionObjects(roomIndex /*- m_tilemap.roomsAcross()*/, 0, 0);

                m_y -= CAMERA_HEIGHT;

                // Reset initial positions
                m_screenX = 0;
                m_screenY = 0;
                m_scrollX = 0;
                m_scrollY = 0;

                player->setPosition(player->position().x, CAMERA_HEIGHT + player->position().y);

                // Unpause engine
                Engine::getInstance().pause(false);

                m_scrollUp = false;
                m_scrolled = 0;
                Controller::getInstance().setController(player);
                player->resetAnimation();

                // Update room information
                RoomManager::getInstance().updateCurrentRoomLocation();

                // TODO: This needs a mapping from the room position as with looping rooms, this will just keep decrementing
                dungeonMarker.y--;
            }
        }

        // Set position of dungeon marker if Link in dungeon
        player->setDungeonMarkerLocation(dungeonMarker.x, dungeonMarker.y);

        RoomManager::getInstance().updateCurrentRoomPosition(m_screenX - m_scrollX, m_screenY - m_scrollY);
        RoomManager::getInstance().updateNextRoomPosition((m_screenX - m_scrollX) + m_swapX, (m_screenY - m_scrollY) + m_swapY);

    }

    void Camera::update()
    {

    }

    void Camera::setScrollSpeed(const int scrollSpeed)
    {
        assert((CAMERA_WIDTH % scrollSpeed == 0) && "scrollSpeed not multiple of CAMERA_WIDTH");
        assert((CAMERA_HEIGHT % scrollSpeed == 0) && "scrollSpeed not multiple of CAMERA_HEIGHT");
        m_scrollSpeed = scrollSpeed;
    }

    int Camera::getX() const
    {
        return m_scrollX;
    }

    int Camera::getY() const
    {
        return m_scrollY;
    }

    Vector<float> Camera::position() const
    {
        return Vector<float>(m_scrollX, m_scrollY);
    }

}