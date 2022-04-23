#pragma once

#include "Singleton.h"
#include <unordered_map>
#include <string>

namespace Zelda
{

// This class is responsible for linking rooms together

using RoomLinkName = std::string;
using RoomIndex = int;

struct RoomLink
{
    RoomIndex left;
    RoomIndex right;
    RoomIndex up;
    RoomIndex down;
};

using RoomLinkMap = std::unordered_map<RoomIndex, RoomLink>;

class RoomLinkManager : public Singleton<RoomLinkManager>
{
    friend class Singleton<RoomLinkManager>;
public:
    void createRoomLink(const RoomLinkName& roomLinkName, const RoomLinkMap& roomLinkMap);
    void useRoomLink(const RoomLinkName& roomLinkName);
    void setRoomLocation(const int roomLocation);
    RoomIndex currentRoom() const noexcept;
    RoomLink roomLink() noexcept;

private:
    RoomLinkManager();
    RoomIndex m_currentRoom;
    RoomLinkName m_currentRoomLink;
    std::unordered_map<RoomLinkName, RoomLinkMap> m_roomLinkMap;
};

};