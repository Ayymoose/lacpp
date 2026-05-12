#pragma once

#include "core/Singleton.h"
#include "RoomName.h"
#include "core/Direction.h"
#include "core/Renderable.h"
#include "core/Renderer.h"

#include <cassert>
#include <vector>

namespace zelda::core
{

class RoomManager : public engine::Singleton<RoomManager>
{
public:
    RoomManager();

    enum class Action
    {
        LOAD,
        CLEAR
    };

    struct RoomLink
    {
        // -1 is a hard error - no room in that direction
        int left{-1};
        int right{-1};
        int up{-1};
        int down{-1};
    };

    struct RoomArea
    {
        RoomLink link;
        std::vector<engine::Renderable*> objects;
    };

    struct Room
    {
        RoomName name{RoomName::NONE};
        std::vector<RoomArea> areas;
    };


    // Sets the room to use
    void setRoom(RoomName name);

    // And the room area within that room
    void setRoomArea(int index);

    int getRoomArea() const;

    // Add a room
    void addRoom(RoomName name, const std::vector<RoomArea>& areas);

    // Load or clear room objects from the current room area
    template <Action action>
    void roomDo(size_t roomIndex)
    {
        assert(m_currentRoom != RoomName::NONE);
        const auto& areas = m_rooms[std::to_underlying(m_currentRoom)].areas;

        assert(roomIndex < areas.size());
        for (const auto object : areas[roomIndex].objects)
        {
            if constexpr (action == Action::LOAD)
            {
                engine::Renderer::instance().addRenderable(object);
            }
            else if constexpr (action == Action::CLEAR)
            {
                engine::Renderer::instance().removeRenderable(object);
            }
        }
    }

    template <engine::Direction direction>
    [[nodiscard]] int moveRoomArea()
    {
        // When moving room areas, we need to load the next room area first
        int oldRoomArea = m_currentRoomArea;
        const auto& link = m_rooms[std::to_underlying(m_currentRoom)].areas[m_currentRoomArea].link;
        if constexpr (direction == engine::Direction::LEFT)
        {
            assert(link.left != -1);
            m_currentRoomArea = link.left;
        }
        else if constexpr (direction == engine::Direction::RIGHT)
        {
            assert(link.right != -1);
            m_currentRoomArea = link.right;
        }
        else if constexpr (direction == engine::Direction::UP)
        {
            assert(link.up != -1);
            m_currentRoomArea = link.up;
        }
        else if constexpr (direction == engine::Direction::DOWN)
        {
            assert(link.down != -1);
            m_currentRoomArea = link.down;
        }
        // Then clear the old one
        return oldRoomArea;
    }

private:
    RoomName m_currentRoom;

    int m_currentRoomArea;

    std::vector<Room> m_rooms;
};
} // namespace zelda::core