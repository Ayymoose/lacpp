#include "RoomManager.h"
#include "Peahat.h"
#include "Gibdo.h"
#include "Shyguy.h"
#include "AnimatedObject.h"


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
        {
            new AnimatedObject(AnimatedClass::AN_TORCH,144,32,0,90),
            new AnimatedObject(AnimatedClass::AN_TORCH,144,80,0,90),
        },
        { 
            new ShyGuy(64,64),
            new AnimatedObject(AnimatedClass::AN_CANDLE,16,96,0,0),
            new AnimatedObject(AnimatedClass::AN_CANDLE,128,96,0,0),
        },
        {
            new AnimatedObject(AnimatedClass::AN_CANDLE,48,16,0,0),
            new AnimatedObject(AnimatedClass::AN_CANDLE,96,16,0,0),
        },
        {},
        {},
        {},
        {
            new AnimatedObject(AnimatedClass::AN_CANDLE,16,16,0,0),
            new AnimatedObject(AnimatedClass::AN_CANDLE,80,16,0,0),
            new AnimatedObject(AnimatedClass::AN_CANDLE,16,96,0,0),
            new AnimatedObject(AnimatedClass::AN_CANDLE,80,96,0,0),
        },
        { 
            new Gibdo(32,32), 
            new Gibdo(64,32),
            new AnimatedObject(AnimatedClass::AN_TORCH,0,32,0,-90),
            new AnimatedObject(AnimatedClass::AN_TORCH,0,80,0,-90)
        },
        { 
            new AnimatedObject(AnimatedClass::AN_CANDLE,16,16,0,0),
            new AnimatedObject(AnimatedClass::AN_CANDLE,128,16,0,0),
            new AnimatedObject(AnimatedClass::AN_CANDLE,16,96,0,0),
            new AnimatedObject(AnimatedClass::AN_CANDLE,128,96,0,0),
            new Peahat(32,32), 
            new Peahat(64,32), 
            new Peahat(80,80)/* Starting room Tail Cave*/
        },
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
void RoomManager::roomObjects(RoomAction action, size_t roomIndex) noexcept
{
    // Check we have a room
    assert(m_currentRoom.size() && roomIndex < m_currentRoom.size());

    // Add or remove objects depending on action
    for (auto const& roomObject : m_currentRoom[roomIndex])
    {
        assert(roomObject);
        if (action == RoomAction::ROOM_LOAD)
        {
            Renderer::getInstance().addRenderable(roomObject);
        }
        else
        {
            Renderer::getInstance().removeRenderable(roomObject);
        }
    }
}

void RoomManager::transitionObjects(size_t roomIndex, int xTransition, int yTransition) noexcept
{
    // Check we have a room
    assert(m_currentRoom.size() && roomIndex < m_currentRoom.size());

    // Add or remove objects depending on action
    for (auto const& roomObject : m_currentRoom[roomIndex])
    {
        assert(roomObject);
        roomObject->transition(xTransition, yTransition);
    }
}

RoomManager::~RoomManager()
{
    // TODO: Free object memory
}

}

