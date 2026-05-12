#include "RoomManager.h"
#include "RoomName.h"

namespace zelda::core
{

RoomManager::RoomManager()
    : m_currentRoom(RoomName::NONE)
    , m_currentRoomArea(-1)
{
    m_rooms.resize(std::to_underlying(RoomName::COUNT));
}

void RoomManager::setRoom(RoomName room)
{
    m_currentRoom = room;
}

void RoomManager::setRoomArea(int index)
{
    m_currentRoomArea = index;
}

int RoomManager::getRoomArea() const
{
    return m_currentRoomArea;
}

void RoomManager::addRoom(RoomName name, const std::vector<RoomArea>& areas)
{
    const auto index = std::to_underlying(name);
    m_rooms[index].name = name;
    m_rooms[index].areas = areas;
}

} // namespace zelda::core
