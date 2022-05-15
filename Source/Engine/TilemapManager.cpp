#include "TilemapManager.h"
#include "Renderer.h"
#include "Depth.h"
#include "Camera.h"
#include <cassert>

namespace Zelda
{

void TilemapManager::createTilemap(RoomName mapName, const Sprite& tilemap, const TileIndexArrays& mapEntries, const Tilemap::TilemapConfig& config)
{
    assert(m_tilemaps.count(mapName) == 0 && "Given mapName already exists");
    m_tilemaps[mapName] = Tilemap(tilemap, mapEntries, config);
}

void TilemapManager::useTilemap(RoomName mapName)
{
    assert(m_tilemaps.count(mapName) == 1 && "Given mapName does NOT exist");
    m_currentTilemapname = mapName;
}

void TilemapManager::setRoomPosition(const int x, const int y)
{
    m_roomX = x;
    m_roomY = y;
}

void TilemapManager::setNextRoomPosition(const int x, const int y)
{
    m_nextRoomX = x;
    m_nextRoomY = y;
}

void TilemapManager::setRoomLocation(const int roomLocation)
{
    assert(m_tilemaps.count(m_currentTilemapname) && "Invalid tilemap");
    assert(roomLocation < m_tilemaps[m_currentTilemapname].size() && "Invalid location");
    m_currentRoom = roomLocation;
}

void TilemapManager::setNextRoomLocation(const int nextLocation)
{
    assert(m_tilemaps.count(m_currentTilemapname) && "Invalid tilemap");
    assert(nextLocation < m_tilemaps[m_currentTilemapname].size() && "Invalid location");
    m_nextRoom = nextLocation;
}

int TilemapManager::roomLocation() const noexcept
{
    return m_currentRoom;
}

void TilemapManager::render() noexcept
{
    if (m_currentTilemapname == RoomName::RM_NONE)
    {
        return;
    }

    // Render the main canvas
    renderTileMap(Rect<int>
    {
        m_roomX,
        m_roomY,
        m_sprite->width(),
        m_sprite->height()
    }, *m_sprite, m_currentRoom);

    // Render the swap canvas
    renderTileMap(Rect<int>
    {
        m_nextRoomX,
        m_nextRoomY,
        m_swapCanvas.width(),
        m_swapCanvas.height()
    }, m_swapCanvas, m_nextRoom);
}

void TilemapManager::renderTileMap(const Rect<int>& dstRect, const Sprite& srcTexture, size_t roomIndex) noexcept
{
    assert(m_tilemaps.count(m_currentTilemapname) && "Invalid tilemap");

    // Tile the texture
    m_tilemaps[m_currentTilemapname].tile(Renderer::getInstance(), srcTexture, roomIndex);

    // Finally render the canvas
    srcTexture.drawSprite(Rect<int>{}, dstRect);
}

TilemapManager::TilemapManager() :
    Renderable("TilemapManager", Sprite(Renderer::getInstance().getRenderer(), CAMERA_WIDTH, CAMERA_HEIGHT), ZD_DEPTH_BACKGROUND),
    m_roomX(0),
    m_roomY(0),
    m_nextRoomX(0),
    m_nextRoomY(0),
    m_currentRoom(0),
    m_nextRoom(0),
    m_currentTilemapname(RoomName::RM_NONE),
    m_swapCanvas(Renderer::getInstance().getRenderer(), m_sprite->width(), m_sprite->height())
{
    // TODO: Free textures on shutdown
    assert(m_sprite->data());
    assert(m_swapCanvas.data());
    Renderer::getInstance().addRenderable(this);
}

};