#pragma once

#include "Renderable.h"
#include "Sprite.h"
#include "Tilemap.h"
#include "RoomName.h"

#include <unordered_map>

namespace Zelda
{


using TileIndexArray = std::vector<std::vector<int>>;
using TileIndexArrays = std::vector<TileIndexArray>;
// This class is responsible for displaying the two canvas's on which we draw tiles too

class TilemapManager : Renderable
{
public:
    // Associates the tilemap data provided with mapName
    void createTilemap(RoomName mapName, const Sprite& tilemap, const TileIndexArrays& mapEntry, const Tilemap::TilemapConfig& config);

    // Sets the current map to be mapName
    void useTilemap(RoomName mapName);

    // Sets position of the main and next room canvas on screen
    void setRoomPosition(const int x, const int y);
    void setNextRoomPosition(const int x, const int y);

    void setRoomLocation(const int roomLocation);
    void setNextRoomLocation(const int nextLocation);

    int roomLocation() const noexcept;

    void render() noexcept override;

    TilemapManager();

private:

    void renderTileMap(const Rect<int>& dstRect, const Sprite& srcTexture, size_t roomIndex) noexcept;

    int m_roomX;
    int m_roomY;

    int m_nextRoomX;
    int m_nextRoomY;

    size_t m_currentRoom;
    size_t m_nextRoom;

    RoomName m_currentTilemapname;
    Sprite m_swapCanvas;
    std::unordered_map<RoomName, Tilemap> m_tilemaps;
};

};