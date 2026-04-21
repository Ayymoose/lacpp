#pragma once

#include "IRenderable.h"
#include "core/Sprite.h"
#include "Tilemap.h"
#include "zelda_core/RoomName.h"

#include <unordered_map>

namespace zelda::core
{

using TileIndexArray = std::vector<std::vector<int>>;
using TileIndexArrays = std::vector<TileIndexArray>;
// This class is responsible for displaying the two canvas's on which we draw tiles too

class TilemapManager : IRenderable
{
public:
    // Associates the tilemap data provided with mapName
    void createTilemap(RoomName mapName, const engine::Sprite &tilemap, const TileIndexArrays &mapEntry,
                       const Tilemap::TilemapConfig &config);

    // Sets the current map to be mapName
    void setCurrentTilemap(RoomName mapName);

    // Sets position of the main and next room canvas on screen
    void setRoomPosition(const int x, const int y);
    void setNextRoomPosition(const int x, const int y);

    void setRoomLocation(const size_t roomLocation);
    void setNextRoomLocation(const size_t nextLocation);

    int roomLocation() const;

    void render() override;

    TilemapManager();

private:
    void renderTileMap(const engine::Rect<int> &dstRect, const engine::Sprite &srcTexture, const size_t roomIndex);

    int m_roomX;
    int m_roomY;

    int m_nextRoomX;
    int m_nextRoomY;

    size_t m_currentRoom;
    size_t m_nextRoom;

    RoomName m_currentTilemapname;
    engine::Sprite m_swapCanvas;
    std::unordered_map<RoomName, Tilemap> m_tilemaps;
};

} // namespace zelda::core