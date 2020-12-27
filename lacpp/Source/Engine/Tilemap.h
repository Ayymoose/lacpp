#pragma once

#include <cstdint>
#include <vector>
#include <array>
#include <map>

#include "Resource.h"

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

    using Room = std::array<std::array<uint16_t, ROOM_TILES_ACROSS>, ROOM_TILES_DOWN>;
    using TilemapArray = std::vector<Room>;

    enum TilemapArea
    {
        TM_NONE = -1,
        TM_TAIL_CAVE,
        TM_BOTTLE_GROTTO,
        TM_KEY_CAVERN,
        TM_ANGLER_TUNNEL,
        TM_CATFISH_MAW,
        TM_FACE_SHRINE,
        TM_EAGLE_TOWER,
        TM_TURTLE_ROCK,
        TM_WIND_FISH_EGG,
        TM_KANALET_CASTLE,
        TM_COLOUR_DUNGEON,
        TM_OVERWORLD,
        TM_COUNT
    };

	typedef struct
	{
		TilemapArray rooms;     // The 10x8 room
		uint16_t roomsAcross;   // Number of rooms across in tilemap
		uint16_t roomsDown;     // Number of rooms down in tilemap
		Graphic tilemap;       // Graphic constant of loaded tilemap
	} TilemapInformation;

    class Tilemap
	{
    public:
		// Sets the tilemap to use
        void setTileMap(TilemapArea tilemap) noexcept;
		// Get current room dimensions of tilemap
		Room getRoomTiles(int roomIndex) const noexcept;

        uint16_t roomWidth() const noexcept;

        // Tilemap texture used
        SDL_Texture* getTilemapTexture() const noexcept;

        Tilemap();
    private:

        // Scrolling tiles when moving out of view
        // Loading tiles when moving to next room

        TilemapInformation m_currentTileMap;
		std::map<TilemapArea, TilemapInformation> m_tileMaps;

    };
}