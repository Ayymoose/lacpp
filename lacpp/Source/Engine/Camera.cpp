#include "Camera.h"
#include "InputControl.h"
#include <assert.h>
#include "Link.h"
#include "Renderer.h"
#include "Depth.h"
#include "ZD_Assert.h"
#include "Engine.h"
#include "Drawing.h"


namespace Zelda
{

Camera::Camera() :
    Renderable("Camera", SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, CAMERA_WIDTH, CAMERA_HEIGHT), ZD_DEPTH_BACKGROUND),
    m_scrollX(0),
    m_scrollY(0),
    m_offScrollX(0),
    m_offScrollY(0),
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
    assert(m_texture);
    m_swapCanvas = SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, m_width, m_height);
    assert(m_swapCanvas);
    Renderer::getInstance().addRenderable(this);
}

void Camera::setPosition(int x, int y) noexcept
{
    assert(x % CAMERA_WIDTH == 0);
    assert(y % CAMERA_HEIGHT == 0);
    m_x = x;
    m_y = y;
}

void Camera::renderTileMap(SDL_Renderer* renderer, SDL_Rect dstRect, SDL_Texture* srcTexture, uint16_t roomIndex) noexcept
{
    // Get the room tiles for the current room index
    // Calculate index into room array from co-ordinates
    auto roomTiles = m_tilemap.getRoomTiles(roomIndex);

    // Get texture used
    auto tilemapTexture = m_tilemap.getTilemapTexture();

    auto target = pushRenderingTarget(renderer, srcTexture);

    // Start painting the canvas with tiles
    for (int tileY = 0; tileY < ROOM_TILES_DOWN; tileY++)
    {
        for (int tileX = 0; tileX < ROOM_TILES_ACROSS; tileX++)
        {
            // The tile will be the ID in the image
            auto tileID = roomTiles[tileY][tileX];

            // Calculate where to grab the tile from in the image
            auto srcTileX = TILE_WIDTH * (tileID % TILE_MAP_TILES_ACROSS);
            auto srcTileY = TILE_HEIGHT * (tileID / TILE_MAP_TILES_ACROSS);

            SDL_Rect srcTile = { srcTileX , srcTileY ,TILE_WIDTH, TILE_HEIGHT };
            SDL_Rect dstTile = { tileX * TILE_WIDTH, tileY * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

            // Paste tile from tilemap
            SDL_ASSERT(SDL_RenderCopy(renderer, tilemapTexture, &srcTile, &dstTile), SDL_ERROR_MESSAGE);
        }
    }
    popRenderingTarget(renderer, target);

    // Finally render the canvas
    SDL_ASSERT(SDL_RenderCopy(renderer, srcTexture, nullptr, &dstRect), SDL_ERROR_MESSAGE);
}

void Camera::render(SDL_Renderer* renderer) noexcept
{
    // We will only ever track the player
    Link* player = &Link::getInstance();

    Vector<float> position = player->position();
    auto x = position.x;
    auto y = position.y;

    // Calculate room index
    int roomIndex = ((m_y / CAMERA_HEIGHT) * m_tilemap.roomsAcross()) + (m_x / CAMERA_WIDTH);
    m_nextRoomIndex = roomIndex;


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
        RoomManager::getInstance().roomObjects(RoomAction::ROOM_LOAD, m_nextRoomIndex - 1);
        RoomManager::getInstance().transitionObjects(m_nextRoomIndex - 1, CAMERA_WIDTH, 0);

        // Put swap canvas in view
        m_swapX = -m_width;
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
        RoomManager::getInstance().roomObjects(RoomAction::ROOM_LOAD, m_nextRoomIndex + 1);
        RoomManager::getInstance().transitionObjects(m_nextRoomIndex + 1, -CAMERA_WIDTH, 0);

        // Put swap canvas in view
        m_swapX = m_width;
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
        RoomManager::getInstance().roomObjects(RoomAction::ROOM_LOAD, m_nextRoomIndex - m_tilemap.roomsAcross());
        RoomManager::getInstance().transitionObjects(m_nextRoomIndex - m_tilemap.roomsAcross(), 0, CAMERA_HEIGHT);


        // Put swap canvas in view
        m_swapX = 0;
        m_swapY = -m_height;

    }
    else if (y > m_scrollY + CAMERA_HEIGHT - HUD_HEIGHT - SCROLL_DOWN_EDGE && !m_scrollDown)
    {
        // -HUD height because its on the bottom

        // Scroll down
        m_scrollDown = true;
        Controller::getInstance().setController(nullptr);

        // Pause engine
        Engine::getInstance().pause(true);

        // Load next room objects
        RoomManager::getInstance().roomObjects(RoomAction::ROOM_LOAD, m_nextRoomIndex + m_tilemap.roomsAcross());
        RoomManager::getInstance().transitionObjects(m_nextRoomIndex + m_tilemap.roomsAcross(), 0, -CAMERA_HEIGHT);

        // Put swap canvas in view
        m_swapX = 0;
        m_swapY = m_height;
    }

    if (m_scrollLeft)
    {
        if (m_scrolled != CAMERA_WIDTH)
        {
            m_scrollX -= m_scrollSpeed;
            m_scrolled += m_scrollSpeed;

            if (m_timerPlayerScroll.elapsed(1.0f / 25.0f))
            {
                player->addPosition(-PLAYER_SCROLL_SPEED, 0);
            }
            // Load next room tiles
            m_nextRoomIndex--;
        }
        else
        {

            // Scrolling left complete

            // Clear previous room's objects
            // Shift previous object's out of view otherwise they will flicker on screen before disappearing
            RoomManager::getInstance().transitionObjects(roomIndex, -CAMERA_WIDTH, 0);
            RoomManager::getInstance().roomObjects(RoomAction::ROOM_CLEAR, roomIndex);

            // Remove transition from loaded objects
            RoomManager::getInstance().transitionObjects(roomIndex - 1, 0, 0);

            // Update current view
            roomIndex--;
            m_x -= CAMERA_WIDTH;


            // m_screenX -= CAMERA_WIDTH;

             // Reset initial positions
            m_screenX = 0;
            m_screenY = 0;
            m_scrollX = 0;
            m_scrollY = 0;
            // Reset Link position
            player->setPosition(CAMERA_WIDTH + player->position().x, player->position().y);


            // Put swap canvas out of view
            m_swapX = m_width;
            m_swapY = m_height;

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

            if (m_timerPlayerScroll.elapsed(1.0f / 25.0f))
            {
                player->addPosition(PLAYER_SCROLL_SPEED, 0);
            }

            // Load next room tiles
            m_nextRoomIndex++;
        }
        else
        {


            // Clear previous room's objects
            // Shift previous object's out of view otherwise they will flicker on screen before disappearing
            RoomManager::getInstance().transitionObjects(roomIndex, CAMERA_WIDTH, 0);
            RoomManager::getInstance().roomObjects(RoomAction::ROOM_CLEAR, roomIndex);

            // Remove transition from loaded objects
            RoomManager::getInstance().transitionObjects(roomIndex + 1, 0, 0);

            roomIndex++;
            m_x += CAMERA_WIDTH;

            //m_screenX += CAMERA_WIDTH;
            // Reset initial positions
            m_screenX = 0;
            m_screenY = 0;
            m_scrollX = 0;
            m_scrollY = 0;
            // Reset Link position
            //std::cout << "Player X : " << player->position().x << "\n";
            player->setPosition(player->position().x - CAMERA_WIDTH, player->position().y);



            // Put swap canvas out of view
            m_swapX = m_width;
            m_swapY = m_height;

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

            if (m_timerPlayerScroll.elapsed(1.0f / 30.0f))
            {
                player->addPosition(0, PLAYER_SCROLL_SPEED);
            }

            // Load next room tiles
            m_nextRoomIndex += m_tilemap.roomsAcross();
        }
        else
        {
            // Player will be 1 pixel off so move back
            // Hacky code
            player->addPosition(0, -1.0f);

            // Unpause engine
            Engine::getInstance().pause(false);

            // Clear previous room's objects
            // Shift previous object's out of view otherwise they will flicker on screen before disappearing
            RoomManager::getInstance().transitionObjects(roomIndex, 0, CAMERA_HEIGHT);
            RoomManager::getInstance().roomObjects(RoomAction::ROOM_CLEAR, roomIndex);

            // Remove transition from loaded objects
            RoomManager::getInstance().transitionObjects(roomIndex + m_tilemap.roomsAcross(), 0, 0);

            roomIndex += m_tilemap.roomsAcross();
            m_y += CAMERA_HEIGHT;

            //m_screenY += CAMERA_HEIGHT;

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
            m_swapX = m_width;
            m_swapY = m_height;

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

            // More hacky code to assure the player is 1 pixel above the HUD
            player->addPosition(0, -0.40625f);

            // Load next room tiles
            m_nextRoomIndex -= m_tilemap.roomsAcross();
        }
        else
        {

            // Clear previous room's objects
            // Shift previous object's out of view otherwise they will flicker on screen before disappearing
            RoomManager::getInstance().transitionObjects(roomIndex, 0, -CAMERA_HEIGHT);
            RoomManager::getInstance().roomObjects(RoomAction::ROOM_CLEAR, roomIndex);

            // Remove transition from loaded objects
            RoomManager::getInstance().transitionObjects(roomIndex - m_tilemap.roomsAcross(), 0, 0);

            roomIndex -= m_tilemap.roomsAcross();
            m_y -= CAMERA_HEIGHT;

            //m_screenY -= CAMERA_HEIGHT;


            // Reset initial positions
            m_screenX = 0;
            m_screenY = 0;
            m_scrollX = 0;
            m_scrollY = 0;
            // Reset Link position
            player->setPosition(player->position().x, CAMERA_HEIGHT + player->position().y);

            // Put swap canvas out of view
            m_swapX = m_width;
            m_swapY = m_height;

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
    SDL_Rect dstRect = { m_screenX - m_scrollX, m_screenY - m_scrollY, m_width, m_height };
    renderTileMap(renderer, dstRect, m_texture, roomIndex);

    // Render the swap canvas out of view 
    SDL_Rect dstSwapRect = { (m_screenX - m_scrollX) + m_swapX, (m_screenY - m_scrollY) + m_swapY, m_width, m_height };
    renderTileMap(renderer, dstSwapRect, m_swapCanvas, m_nextRoomIndex);
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
    RoomManager::getInstance().roomObjects(RoomAction::ROOM_LOAD, roomIndex);
}

bool Camera::visible(SDL_FRect&& rectangle) const noexcept
{
    if (rectangle.x > (m_scrollX + CAMERA_WIDTH) - rectangle.w)
    {
        return false;
    }
    else if (rectangle.x < m_scrollX)
    {
        return false;
    }
    else if (rectangle.y < m_scrollY)
    {
        return false;
    }
    else if (rectangle.y > (m_scrollY + CAMERA_HEIGHT) - rectangle.h)
    {
        return false;
    }
    return true;
}

void Camera::setScrollSpeed(int scrollSpeed) noexcept
{
    SDL_ASSERT(CAMERA_WIDTH % scrollSpeed, "scrollSpeed not multiple of CAMERA_WIDTH");
    SDL_ASSERT(CAMERA_HEIGHT % scrollSpeed, "scrollSpeed not multiple of CAMERA_HEIGHT");
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

int Camera::offScrollX() const noexcept
{
    return m_offScrollX;
}

int Camera::offScrollY() const noexcept
{
    return m_offScrollY;
}

Vector<float> Camera::position() const noexcept
{
    return Vector<float>(m_scrollX, m_scrollY);
}

}