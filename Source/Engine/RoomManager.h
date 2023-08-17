#pragma once

#include "Singleton.h"
#include "Renderable.h"
#include "RoomName.h"
#include "RoomLinkManager.h"
#include "TilemapManager.h"

#include <unordered_map>
#include <vector>


namespace Zelda
{
    //using RoomObjects = std::vector<Renderable*>;
    //using Room = std::vector<RoomObjects>;

    enum class RoomAction
    {
        ROOM_LOAD,
        ROOM_CLEAR
    };

    enum class RoomDirection
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    class RoomManager : public Singleton<RoomManager>
    {
        friend class Singleton<RoomManager>;
    public:

        // Sets the room to use
        void useRoom(RoomName roomName);
        void setRoomLocation(const int roomLocation);

        void createRoom(RoomName roomName, const Sprite& tilemap, const TileIndexArrays& tileIndexArrays,
            const Tilemap::TilemapConfig& tilemapConfig, const RoomLinkMap& roomLinkMap);

        // Load or clear room objects from the current room
        void roomDo(RoomAction action, const size_t roomIndex);
        void transitionObjects(size_t roomIndex, const int xTransition, const int yTransition);


        // Room transition related functions
        void updateCurrentRoomLocation();
        void updateNextRoomLocation(RoomDirection direction);
        void updateCurrentRoomPosition(const int x, const int y);
        void updateNextRoomPosition(const int x, const int y);

    private:
        RoomManager();
        ~RoomManager();

        RoomLinkManager m_roomLinkManager;
        TilemapManager m_tilemapManager;

        // [RoomName][Room][std::vector<Rendereable*>]

        // Loads animated tiles
        // Room objects (Enemies, Objects, NPC etc)

        // 10 tiles across of animated water starting at (32,32) rotated 90 degrees 
        // AnimatedObject(LIGHT_WATER, 32, 32, 10, ROTATE_90)

        // One object with list of positions of this object
        // OR
        // Many objects with different positions

        // When a room is loaded, add objects to the render set
        // Remove them from the render set when new room is loaded 

        //Room m_currentRoom;
        //std::unordered_map<RoomName, Room> m_rooms;
    };
}