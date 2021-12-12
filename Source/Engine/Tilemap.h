#pragma once

#include <vector>
#include <array>
#include <map>

#include "Resource.h"
#include "RoomManager.h"

namespace Zelda
{

// Tilemap array of room and room dimensions (WxH)
constexpr int TILE_WIDTH = 16;
constexpr int TILE_HEIGHT = 16;

constexpr int ROOM_TILES_ACROSS = 10;
constexpr int ROOM_TILES_DOWN = 8;

// Tilemap image will always be 128xH
constexpr int TILE_MAP_WIDTH = 128;
   
constexpr int TILE_MAP_TILES_ACROSS = (TILE_MAP_WIDTH / TILE_WIDTH);

using TileRoom = std::array<std::array<int, ROOM_TILES_ACROSS>, ROOM_TILES_DOWN>;
using TilemapArray = std::vector<TileRoom>;

typedef struct
{
	TilemapArray rooms;     // The 10x8 room
    int roomsAcross;   // Number of rooms across in tilemap
    int roomsDown;     // Number of rooms down in tilemap
	Graphic tilemap;       // Graphic constant of loaded tilemap
} TilemapInformation;

class Tilemap
{
public:
	// Sets the tilemap to use
    void setTileMap(RoomName roomname) noexcept;
	// Get current room dimensions of tilemap
    TileRoom getRoomTiles(size_t roomIndex) const noexcept;

    int roomsDown() const noexcept;
    int roomsAcross() const noexcept;

    // Tilemap texture used
    Sprite getTilemap() const noexcept;

    Tilemap();
private:

    // Scrolling tiles when moving out of view
    // Loading tiles when moving to next room

    TilemapInformation m_currentTileMap;
	std::map<RoomName, TilemapInformation> m_tileMaps;

};
}