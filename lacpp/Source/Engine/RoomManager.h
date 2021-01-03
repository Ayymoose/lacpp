#pragma once

#include "Singleton.h"
#include "Renderable.h"

#include <map>
#include <vector>


namespace Zelda
{
    using RoomObjects = std::vector<Renderable*>;
    using Room = std::vector<RoomObjects>;

    enum RoomName
    {
        RM_NONE = -1,
        RM_TAIL_CAVE,
        RM_BOTTLE_GROTTO,
        RM_KEY_CAVERN,
        RM_ANGLER_TUNNEL,
        RM_CATFISH_MAW,
        RM_FACE_SHRINE,
        RM_EAGLE_TOWER,
        RM_TURTLE_ROCK,
        RM_WIND_FISH_EGG,
        RM_KANALET_CASTLE,
        RM_COLOUR_DUNGEON,
        RM_DREAM_SHRINE,
        RM_UNDERWORLD,
        RM_OVERWORLD,
        RM_COUNT
    };

    enum class RoomAction
    {
        ROOM_LOAD,
        ROOM_CLEAR
    };

    class RoomManager : public Singleton<RoomManager>
    {
        friend class Singleton<RoomManager>;
    public:
        // Sets the room to use
        void setRoom(RoomName room) noexcept;

        // Load or clear room objects from the current room
        void roomOjects(RoomAction action, size_t roomIndex) noexcept;
    private:
        RoomManager();
        ~RoomManager();

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

        Room m_currentRoom;
        std::map<RoomName, Room> m_rooms;
    };
}