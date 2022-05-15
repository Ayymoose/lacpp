#pragma once

#include "RoomName.h"

#include <unordered_map>

namespace Zelda
{

// This class is responsible for linking rooms together

using RoomIndex = int;

struct RoomLink
{
    RoomIndex left;
    RoomIndex right;
    RoomIndex up;
    RoomIndex down;
};

using RoomLinkMap = std::unordered_map<RoomIndex, RoomLink>;

class RoomLinkManager
{
public:
    void createRoomLink(RoomName roomLinkName, const RoomLinkMap& roomLinkMap);
    void useRoomLink(RoomName roomLinkName);
    void setRoomLocation(const int roomLocation);
    RoomIndex currentRoom() const noexcept;
    RoomLink roomLink() noexcept;
    RoomLinkManager();

private:
    RoomIndex m_currentRoom;
    RoomName m_currentRoomLink;
    std::unordered_map<RoomName, RoomLinkMap> m_roomLinkMap;
};

};