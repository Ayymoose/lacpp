#include "RoomManager.h"
#include "Peahat.h"
#include "Gibdo.h"

namespace Zelda
{

RoomManager::RoomManager()
{
    // Tail Cave room objects
    Room tc =

    {
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        { new Gibdo(32,32), new Gibdo(64,32) },
        { new Peahat(32,32), new Peahat(64,32), new Peahat(80,80)/* Starting room Tail Cave*/},
        {},
        {},
        {}
    };

    m_rooms[RM_TAIL_CAVE] = tc;
}

void RoomManager::setRoom(RoomName room) noexcept
{
    assert(room > RM_NONE && room < RM_COUNT);
    m_currentRoom = m_rooms[room];


    // Load all the objects for this room under it's current index

}

// Loads the room objects for the current room at roomIndex
void RoomManager::roomOjects(RoomAction action, size_t roomIndex) noexcept
{
    // Check we have a room
    assert(m_currentRoom.size() && roomIndex < m_currentRoom.size());

    // Add or remove objects depending on action
    for (auto const& roomObject : m_currentRoom[roomIndex])
    {
        assert(roomObject);
        if (action == RoomAction::ROOM_LOAD)
        {
            std::cout << "[ROOM_MANAGER] Adding " << roomObject->name() << " at index " << roomIndex << "\n";
            Renderer::getInstance().addRenderable(roomObject);
        }
        else
        {
            std::cout << "[ROOM_MANAGER] Removing " << roomObject->name() << " at index " << roomIndex << "\n";
            Renderer::getInstance().removeRenderable(roomObject);
        }
    }
}

RoomManager::~RoomManager()
{
    // TODO: Free object memory
}

}

