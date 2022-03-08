#include "Camera.h"
#include "InputControl.h"
#include <assert.h>
#include "Link.h"
#include "Renderer.h"
#include "Depth.h"
#include "SDL_Assert.h"
#include "Engine.h"


namespace Zelda
{

Camera::Camera() :
    Renderable("Camera", Sprite(Renderer::getInstance().getRenderer(),CAMERA_WIDTH, CAMERA_HEIGHT), ZD_DEPTH_BACKGROUND),
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
    m_scrolled(0),
    m_nextRoomIndex(0)
{
    // TODO: Free textures on shutdown
    assert(m_sprite.data());
    m_swapCanvas = Sprite(Renderer::getInstance().getRenderer(), m_sprite.width(), m_sprite.height());
    assert(m_swapCanvas.data());
    Renderer::getInstance().addRenderable(this);
}

void Camera::setPosition(int x, int y) noexcept
{
    assert(x % CAMERA_WIDTH == 0);
    assert(y % CAMERA_HEIGHT == 0);
    m_x = x;
    m_y = y;
}

void Camera::renderTileMap(const Rect<int>& dstRect, const Sprite& srcTexture, uint16_t roomIndex) noexcept
{
    // Get the room tiles for the current room index
    // Calculate index into room array from co-ordinates
    auto const roomTiles = m_tilemap.getRoomTiles(roomIndex);

    // Get texture used
    auto const tilemapTexture = m_tilemap.getTilemap();

    auto const target = Renderer::getInstance().pushRenderingTarget(srcTexture);

    // Start painting the canvas with tiles
    for (int tileY = 0; tileY < ROOM_TILES_DOWN; tileY++)
    {
        for (int tileX = 0; tileX < ROOM_TILES_ACROSS; tileX++)
        {
            // The tile will be the ID in the image
            auto const tileID = roomTiles[tileY][tileX];

            // Calculate where to grab the tile from in the image
            auto const srcTileX = TILE_WIDTH * (tileID % TILE_MAP_TILES_ACROSS);
            auto const srcTileY = TILE_HEIGHT * (tileID / TILE_MAP_TILES_ACROSS);

            // Paste tile from tilemap
            tilemapTexture.drawSprite(Renderer::getInstance().getRenderer(),
                Rect<int>{ srcTileX, srcTileY, TILE_WIDTH, TILE_HEIGHT }, 
                Rect<int>{ tileX * TILE_WIDTH, tileY * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT });
        }
    }

    Renderer::getInstance().popRenderingTarget(target);

    // Finally render the canvas
    srcTexture.drawSprite(Renderer::getInstance().getRenderer(), 
        Rect<int>{0,0,srcTexture.width(), srcTexture.height()}, 
        dstRect);
}

void Camera::render() noexcept
{
    // We will only ever track the player
    Link* player = &Link::getInstance();

    Vector<float> position = player->position();
    auto x = position.x;
    auto y = position.y;

    // Calculate room index
    int roomIndex = ((m_y / CAMERA_HEIGHT) * m_tilemap.roomsAcross()) + (m_x / CAMERA_WIDTH);
    m_nextRoomIndex = roomIndex;


    // TODO: Decouple Tilemap from Camera class
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
        RoomManager::getInstance().roomDo(RoomAction::ROOM_LOAD, m_nextRoomIndex - 1);
        RoomManager::getInstance().transitionObjects(m_nextRoomIndex - 1, CAMERA_WIDTH, 0);

        // Put swap canvas in view
        m_swapX = -m_swapCanvas.width();
        m_swapY = 0;
    }
    else if (x > m_scrollX + CAMERA_WIDTH - SCROLL_RIGHT_EDGE && !m_scrollRight)
    {
        // Scroll right
        m_scrollRight = true;
        Controller::getInstance().setController(nullptr);

        // Pause engine
        Engine::getInstance().pause(true);

        // Load next room objects
        RoomManager::getInstance().roomDo(RoomAction::ROOM_LOAD, m_nextRoomIndex + 1);
        RoomManager::getInstance().transitionObjects(m_nextRoomIndex + 1, -CAMERA_WIDTH, 0);

        // Put swap canvas in view
        m_swapX = m_swapCanvas.width();
        m_swapY = 0;
    }
    else if (y < m_scrollY - SCROLL_UP_EDGE && !m_scrollUp)
    {
        // Scroll up
        m_scrollUp = true;
        Controller::getInstance().setController(nullptr);

        // Pause engine
        Engine::getInstance().pause(true);

        // Load next room objects
        RoomManager::getInstance().roomDo(RoomAction::ROOM_LOAD, m_nextRoomIndex - m_tilemap.roomsAcross());
        RoomManager::getInstance().transitionObjects(m_nextRoomIndex - m_tilemap.roomsAcross(), 0, CAMERA_HEIGHT);

        // Put swap canvas in view
        m_swapX = 0;
        m_swapY = -m_swapCanvas.height();

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
        RoomManager::getInstance().roomDo(RoomAction::ROOM_LOAD, m_nextRoomIndex + m_tilemap.roomsAcross());
        RoomManager::getInstance().transitionObjects(m_nextRoomIndex + m_tilemap.roomsAcross(), 0, -CAMERA_HEIGHT);

        // Put swap canvas in view
        m_swapX = 0;
        m_swapY = m_swapCanvas.height();
    }

    if (m_scrollLeft)
    {
        if (m_scrolled != CAMERA_WIDTH)
        {
            m_scrollX -= m_scrollSpeed;
            m_scrolled += m_scrollSpeed;

            // Load next room tiles
            m_nextRoomIndex--;
        }
        else
        {
            // Scrolling left complete

            // Clear previous room's objects
            // Shift previous object's out of view otherwise they will flicker on screen before disappearing
            RoomManager::getInstance().transitionObjects(roomIndex, -CAMERA_WIDTH, 0);
            RoomManager::getInstance().roomDo(RoomAction::ROOM_CLEAR, roomIndex);

            // Remove transition from loaded objects
            RoomManager::getInstance().transitionObjects(roomIndex - 1, 0, 0);

            // Update current view
            roomIndex--;
            m_x -= CAMERA_WIDTH;

             // Reset initial positions
            m_screenX = 0;
            m_screenY = 0;
            m_scrollX = 0;
            m_scrollY = 0;
            // Reset Link position
            player->setPosition(CAMERA_WIDTH + player->position().x, player->position().y);

            // Put swap canvas out of view
            m_swapX = m_swapCanvas.width();
            m_swapY = m_swapCanvas.height();

            // Unpause engine
            Engine::getInstance().pause(false);

            m_scrollLeft = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
            player->resetAnimation();
        }
    }
    else if (m_scrollRight)
    {
        if (m_scrolled != CAMERA_WIDTH)
        {
            m_scrollX += m_scrollSpeed;
            m_scrolled += m_scrollSpeed;

            // Load next room tiles
            m_nextRoomIndex++;
        }
        else
        {

            // Clear previous room's objects
            // Shift previous object's out of view otherwise they will flicker on screen before disappearing
            RoomManager::getInstance().transitionObjects(roomIndex, CAMERA_WIDTH, 0);
            RoomManager::getInstance().roomDo(RoomAction::ROOM_CLEAR, roomIndex);

            // Remove transition from loaded objects
            RoomManager::getInstance().transitionObjects(roomIndex + 1, 0, 0);

            roomIndex++;
            m_x += CAMERA_WIDTH;

            // Reset initial positions
            m_screenX = 0;
            m_screenY = 0;
            m_scrollX = 0;
            m_scrollY = 0;

            // Reset Link position
            player->setPosition(player->position().x - CAMERA_WIDTH, player->position().y);

            // Put swap canvas out of view
            m_swapX = m_swapCanvas.width();
            m_swapY = m_swapCanvas.height();

            // Unpause engine
            Engine::getInstance().pause(false);

            m_scrollRight = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
            player->resetAnimation();
        }
    }
    else if (m_scrollDown)
    {
        if (m_scrolled != CAMERA_HEIGHT)
        {
            m_scrollY += m_scrollSpeed;
            m_scrolled += m_scrollSpeed;

            // Load next room tiles
            m_nextRoomIndex += m_tilemap.roomsAcross();
        }
        else
        {
            // Unpause engine
            Engine::getInstance().pause(false);

            // Clear previous room's objects
            // Shift previous object's out of view otherwise they will flicker on screen before disappearing
            RoomManager::getInstance().transitionObjects(roomIndex, 0, CAMERA_HEIGHT);
            RoomManager::getInstance().roomDo(RoomAction::ROOM_CLEAR, roomIndex);

            // Remove transition from loaded objects
            RoomManager::getInstance().transitionObjects(roomIndex + m_tilemap.roomsAcross(), 0, 0);

            roomIndex += m_tilemap.roomsAcross();
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
            m_swapX = m_swapCanvas.width();
            m_swapY = m_swapCanvas.height();

            m_scrollDown = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
            player->resetAnimation();
        }
    }
    else if (m_scrollUp)
    {
        if (m_scrolled != CAMERA_HEIGHT)
        {
            m_scrollY -= m_scrollSpeed;
            m_scrolled += m_scrollSpeed;

            // Load next room tiles
            m_nextRoomIndex -= m_tilemap.roomsAcross();
        }
        else
        {
            // Clear previous room's objects
            // Shift previous object's out of view otherwise they will flicker on screen before disappearing
            RoomManager::getInstance().transitionObjects(roomIndex, 0, -CAMERA_HEIGHT);
            RoomManager::getInstance().roomDo(RoomAction::ROOM_CLEAR, roomIndex);

            // Remove transition from loaded objects
            RoomManager::getInstance().transitionObjects(roomIndex - m_tilemap.roomsAcross(), 0, 0);

            roomIndex -= m_tilemap.roomsAcross();
            m_y -= CAMERA_HEIGHT;

            // Reset initial positions
            m_screenX = 0;
            m_screenY = 0;
            m_scrollX = 0;
            m_scrollY = 0;
            // Reset Link position
            player->setPosition(player->position().x, CAMERA_HEIGHT + player->position().y);

            // Put swap canvas out of view
            m_swapX = m_swapCanvas.width();
            m_swapY = m_swapCanvas.height();

            // Unpause engine
            Engine::getInstance().pause(false);

            m_scrollUp = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
            player->resetAnimation();
        }
    }

    // Set position of dungeon marker if Link in dungeon
    int dx = roomIndex % m_tilemap.roomsAcross();
    // The y offset is calculated because we line the dungeon map array with 1s on the top and right
    // if roomsDown > 9 then we'll get assertion failure
    int dy = (DUNGEON_MAX_BLOCKS_Y - m_tilemap.roomsDown()) + (roomIndex / m_tilemap.roomsAcross());

    player->setDungeonMarkerLocation(dx, dy);

    // Render the main view
    renderTileMap(Rect<int>{ m_screenX - m_scrollX, m_screenY - m_scrollY, m_sprite.width(), m_sprite.height() }, m_sprite, roomIndex);

    // Render the swap canvas out of view 
    renderTileMap(Rect<int>{(m_screenX - m_scrollX) + m_swapX, (m_screenY - m_scrollY) + m_swapY, m_swapCanvas.width(), m_swapCanvas.height() }, m_swapCanvas, m_nextRoomIndex);
}

void Camera::update() noexcept
{

}

// Set the tilemap to use
void Camera::setTileMap(RoomName roomname) noexcept
{
    // Set the internal map to use
    m_tilemap.setTileMap(roomname);

    // And room to use
    RoomManager::getInstance().setRoom(roomname);

    // And load the current room objects
    int roomIndex = ((m_y / CAMERA_HEIGHT) * m_tilemap.roomsAcross()) + (m_x / CAMERA_WIDTH);
    RoomManager::getInstance().roomDo(RoomAction::ROOM_LOAD, roomIndex);
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