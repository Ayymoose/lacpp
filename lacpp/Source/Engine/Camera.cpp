#include "Camera.h"
#include "InputControl.h"
#include <assert.h>
#include "Link.h"
#include "Renderer.h"
#include "Depth.h"
#include "ZD_Assert.h"
#include "Engine.h"
#include "Drawing.h"


using namespace Zelda;

Camera::Camera()
{
    m_x = 0;
    m_y = 0;
    m_scrollX = 0;
    m_scrollY = 0;
    m_scrollSpeed = 0;
    m_texture = nullptr;
    m_width = CAMERA_WIDTH;
    m_height = CAMERA_HEIGHT;
    m_scrollCamera = false;
    m_scrolled = 0;
    m_scrollLeft = false;
    m_scrollRight = false;
    m_scrollDown = false;
    m_scrollUp = false;
    m_tracker = nullptr;

    // Create a blank canvas for a the area
    m_texture = SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, m_width, m_height);
    assert(m_texture != nullptr);

    m_depth = ZD_DEPTH_BACKGROUND;
    m_name = "Camera";
    Renderer::getInstance().addRenderable(this);
}

void Camera::setPosition(int x, int y) noexcept
{
    assert(x % CAMERA_WIDTH == 0);
    assert(y % CAMERA_HEIGHT == 0);
    m_x = x;
    m_y = y;
}

void Camera::track(Character* character) noexcept
{
    m_tracker = character;
}

void Camera::trackCharacter() noexcept
{
    assert(m_tracker != nullptr);

    // We will only ever track the player
    Link* player = dynamic_cast<Link*>(m_tracker);
    assert(player != nullptr);

    Vector<float> position = player->position();
    auto x = position.x;
    auto y = position.y;

    // Transition the player if they move off the screen
    if (x < m_scrollX && !m_scrollLeft)
    {
        // Scroll left
        m_scrollLeft = true;
        Controller::getInstance().setController(nullptr);
        
        // Pause engine
        Engine::getInstance().pause(true);

        // TODO: Globalise
        player->m_currentCollisionMapX--;
        std::cout << "Scrolling left" << std::endl;
    }
    else if (x > m_scrollX + CAMERA_WIDTH - ScrollRightEdge && !m_scrollRight)
    {
        // Scroll right
        m_scrollRight = true;
        Controller::getInstance().setController(nullptr);

        // Pause engine
        Engine::getInstance().pause(true);

        // TODO: Globalise
        player->m_currentCollisionMapX++;
        std::cout << "Scrolling right" << std::endl;


    }
    else if (y < m_scrollY && !m_scrollUp)
    {
        // Scroll up
        m_scrollUp = true;
        Controller::getInstance().setController(nullptr);

        // Pause engine
        Engine::getInstance().pause(true);

        // TODO: Globalise
        player->m_currentCollisionMapY--;
        std::cout << "Scrolling up" << std::endl;

    }
    else if (y > m_scrollY + CAMERA_HEIGHT - HUD_HEIGHT /* HUD height because its on the bottom*/ && !m_scrollDown)
    {
        // Scroll down
        m_scrollDown = true;
        Controller::getInstance().setController(nullptr);

        // Pause engine
        Engine::getInstance().pause(true);

        // TODO: Globalise
        player->m_currentCollisionMapY++;
        std::cout << "Scrolling down" << std::endl;


    }
 
    if (m_scrollLeft)
    {
        if (m_scrolled != CAMERA_WIDTH)
        {
            m_scrollX -= m_scrollSpeed;
            m_scrolled += m_scrollSpeed;
            if (m_timerPlayerScroll.update(FPS_33))
            {
                player->addPosition(-PlayerScrollSpeed, 0);
            }
        }
        else
        {
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
            if (m_timerPlayerScroll.update(FPS_33))
            {
                player->addPosition(PlayerScrollSpeed, 0);
            }
        }
        else
        {
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
            if (m_timerPlayerScroll.update(FPS_33))
            {
                player->addPosition(0, PlayerScrollSpeed);
            }
        }
        else
        {
            // Unpause engine
            Engine::getInstance().pause(false);

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
            if (m_timerPlayerScroll.update(FPS_33))
            {
                player->addPosition(0, -PlayerScrollSpeed);
            }
        }
        else
        {
            // Unpause engine
            Engine::getInstance().pause(false);

            m_scrollUp = false;
            m_scrolled = 0;
            Controller::getInstance().setController(player);
            player->resetAnimation();
        }
    }

}

void Zelda::Camera::renderTileMap(SDL_Renderer* renderer) noexcept
{
    // Render the tilemap
    SDL_Rect dstRect = { 0, 0, m_width, m_height };

    // Get the room tiles for the current room index
    // Calculate index into room array from co-ordinates
  
    int roomX = (m_x / CAMERA_WIDTH);
    int roomY = (m_y / CAMERA_HEIGHT);

    auto roomIndex = (roomY * m_tilemap.roomWidth()) + roomX;
    auto roomTiles = m_tilemap.getRoomTiles(roomIndex);

    // Get texture used
    auto tilemapTexture = m_tilemap.getTilemapTexture();

    auto target = pushRenderingTarget(renderer, m_texture);

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

            SDL_Rect srcTile = { srcTileX , srcTileY ,TILE_WIDTH, TILE_HEIGHT};
            SDL_Rect dstTile = { tileX * TILE_WIDTH, tileY * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

            // Paste tile from tilemap
            ZD_ASSERT(SDL_RenderCopy(renderer, tilemapTexture, &srcTile, &dstTile) == 0, "SDL Error: " << SDL_GetError());
        }
    }
    popRenderingTarget(renderer, target);

    // Finally render the canvas
    ZD_ASSERT(SDL_RenderCopy(renderer, m_texture, nullptr, &dstRect) == 0, "SDL Error: " << SDL_GetError());
}

void Camera::render(SDL_Renderer* renderer) noexcept
{
    trackCharacter();
    renderTileMap(renderer);
}

// Set the tilemap to use
void Zelda::Camera::setTileMap(TilemapArea tilemap)
{
    // Set the internal map to use
    m_tilemap.setTileMap(tilemap);
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
    ZD_ASSERT(CAMERA_WIDTH % scrollSpeed == 0, "scrollSpeed not multiple of CAMERA_WIDTH");
    ZD_ASSERT(CAMERA_HEIGHT % scrollSpeed == 0, "scrollSpeed not multiple of CAMERA_HEIGHT");
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

Vector<float> Zelda::Camera::position() const noexcept
{
    return Vector<float>(m_scrollX, m_scrollY);
}
