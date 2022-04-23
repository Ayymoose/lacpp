#include "Camera.h"
#include "InputControl.h"
#include <cassert>
#include "Link.h"
#include "Renderer.h"
#include "Depth.h"
#include "SDL_Assert.h"
#include "Engine.h"
#include "TilemapManager.h"
#include "RoomLinkManager.h"


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
    // TODO: Free textures on shutdown
    assert(m_sprite.data());
    // TODO: Remove Camera from Renderable
    Renderer::getInstance().addRenderable(this);
}

void Camera::setPosition(int x, int y) noexcept
{
    assert(x % CAMERA_WIDTH == 0);
    assert(y % CAMERA_HEIGHT == 0);
    m_x = x;
    m_y = y;
}

void Camera::updateNextRoomLocation(const int nextRoomIndex) const noexcept
{
    if (nextRoomIndex == -1)
    {
        assert(false && "Invalid next room index");
    }
    else
    {
        TilemapManager::getInstance().setNextRoomLocation(nextRoomIndex);
        RoomLinkManager::getInstance().setRoomLocation(nextRoomIndex);
    }
}

void Camera::updateCurrentRoomLocation() const noexcept
{
    // Update room information
    auto const currentRoomIndex = RoomLinkManager::getInstance().currentRoom();
    TilemapManager::getInstance().setRoomLocation(currentRoomIndex);
}

void Camera::render() noexcept
{
    // We will only ever track the player
    // TODO: Decouple this
    Link* player = &Link::getInstance();

    Vector<float> position = player->position();
    auto x = position.x;
    auto y = position.y;



    // TODO: Algorithm to move Link x pixels across when scrolling 

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
        updateNextRoomLocation(RoomLinkManager::getInstance().roomLink().left);

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
        updateNextRoomLocation(RoomLinkManager::getInstance().roomLink().right);
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
        m_swapX = 0;
        m_swapY = -CAMERA_HEIGHT;

        // Find out if we can scroll up
        updateNextRoomLocation(RoomLinkManager::getInstance().roomLink().up);
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
        updateNextRoomLocation(RoomLinkManager::getInstance().roomLink().down);
    }

    if (m_scrollLeft)
    {
        if (m_scrolled != CAMERA_WIDTH)
        {
            m_scrollX -= m_scrollSpeed;
            m_scrolled += m_scrollSpeed;
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
            // Reset Link position
            player->setPosition(CAMERA_WIDTH + player->position().x, player->position().y);

            // Put swap canvas out of view
            //m_swapX = m_swapCanvas.width();
            //m_swapY = m_swapCanvas.height();

            // Unpause engine
            Engine::getInstance().pause(false);

            m_scrollLeft = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
            player->resetAnimation();

            // Update room information
            updateCurrentRoomLocation();

        }
    }
    else if (m_scrollRight)
    {
        if (m_scrolled != CAMERA_WIDTH)
        {
            m_scrollX += m_scrollSpeed;
            m_scrolled += m_scrollSpeed;
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

            // Reset Link position
            player->setPosition(player->position().x - CAMERA_WIDTH, player->position().y);

            // Put swap canvas out of view
            //m_swapX = m_swapCanvas.width();
            //m_swapY = m_swapCanvas.height();

            // Unpause engine
            Engine::getInstance().pause(false);

            m_scrollRight = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
            player->resetAnimation();

            // Update room information
            updateCurrentRoomLocation();
        }
    }
    else if (m_scrollDown)
    {
        if (m_scrolled != CAMERA_HEIGHT)
        {
            m_scrollY += m_scrollSpeed;
            m_scrolled += m_scrollSpeed;
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
            // Reset Link position
            player->setPosition(player->position().x, player->position().y - CAMERA_HEIGHT);

            // Take a snapshot of the canvas and use that for display
            // Clear the current room objects
            // Set offsetX / offsetY to scroll 

            // Put swap canvas out of view
            //m_swapX = m_swapCanvas.width();
            //m_swapY = m_swapCanvas.height();

            m_scrollDown = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
            player->resetAnimation();

            // Update room information
            updateCurrentRoomLocation();
        }
    }
    else if (m_scrollUp)
    {
        if (m_scrolled != CAMERA_HEIGHT)
        {
            m_scrollY -= m_scrollSpeed;
            m_scrolled += m_scrollSpeed;
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
            // Reset Link position
            player->setPosition(player->position().x, CAMERA_HEIGHT + player->position().y);

            // Put swap canvas out of view
            //m_swapX = m_swapCanvas.width();
            //m_swapY = m_swapCanvas.height();

            // Unpause engine
            Engine::getInstance().pause(false);

            m_scrollUp = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
            player->resetAnimation();

            // Update room information
            updateCurrentRoomLocation();
        }
    }

    // Set position of dungeon marker if Link in dungeon
    int dx = 0;// roomIndex;//% m_tilemap.roomsAcross();
    // The y offset is calculated because we line the dungeon map array with 1s on the top and right
    // if roomsDown > 9 then we'll get assertion failure
    int dy = 0;// (DUNGEON_MAX_BLOCKS_Y - m_tilemap.roomsDown()) + (roomIndex / m_tilemap.roomsAcross());

    //player->setDungeonMarkerLocation(dx, dy);

    // Render the main view

    // TODO: Wrap in RoomManager class which will handle the tilemap and roomlink positions
	TilemapManager::getInstance().setRoomPosition(m_screenX - m_scrollX, m_screenY - m_scrollY);
	TilemapManager::getInstance().setNextRoomPosition((m_screenX - m_scrollX) + m_swapX, (m_screenY - m_scrollY) + m_swapY);

}

void Camera::update() noexcept
{

}

void Camera::setScrollSpeed(int scrollSpeed) noexcept
{
    assert((CAMERA_WIDTH % scrollSpeed == 0) && "scrollSpeed not multiple of CAMERA_WIDTH");
    assert((CAMERA_HEIGHT % scrollSpeed == 0) && "scrollSpeed not multiple of CAMERA_HEIGHT");
    m_scrollSpeed = scrollSpeed;
}

int Camera::getX() const noexcept
{
    return m_scrollX;
}
int Camera::getY() const noexcept
{
    return m_scrollY;
}

Vector<float> Camera::position() const noexcept
{
    return Vector<float>(m_scrollX, m_scrollY);
}

}