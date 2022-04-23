#include "RoomLinkManager.h"
#include <cassert>

namespace Zelda
{
void RoomLinkManager::createRoomLink(const RoomLinkName& roomLinkName, const RoomLinkMap& roomLinkMap)
{
    assert(m_roomLinkMap.count(roomLinkName) == 0 && "Invalid roomLinkName");
    m_roomLinkMap[roomLinkName] = roomLinkMap;
}

void RoomLinkManager::useRoomLink(const RoomLinkName& roomLinkName)
{
    assert(m_roomLinkMap.count(roomLinkName) == 1 && "Given roomLinkName does NOT exist");
    m_currentRoomLink = roomLinkName;
}

void RoomLinkManager::setRoomLocation(const int roomLocation)
{
    m_currentRoom = roomLocation;
}

RoomIndex RoomLinkManager::currentRoom() const noexcept
{
    return m_currentRoom;
}

RoomLink RoomLinkManager::roomLink() noexcept
{
    assert(m_roomLinkMap.count(m_currentRoomLink) == 1 && "Given roomLinkName does NOT exist");
    assert(m_currentRoom < m_roomLinkMap[m_currentRoomLink].size() && "Invalid room location");
    return m_roomLinkMap[m_currentRoomLink][m_currentRoom];
}

RoomLinkManager::RoomLinkManager() : m_currentRoom(0)
{
}

};