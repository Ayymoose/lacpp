#include "RoomManager.h"
#include "Renderer.h"

#include <cassert>


namespace Zelda
{

RoomManager::RoomManager()
{
    // Tail Cave room objects
    /*Room tc =

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
            // TODO: Create EnemyFactory class
           // new AnimatedObject(AnimatedClass::AN_TORCH,144,32,0,90),
           // new AnimatedObject(AnimatedClass::AN_TORCH,144,80,0,90),
        },
        { 
           // new ShyGuy(64,64),
           // new AnimatedObject(AnimatedClass::AN_CANDLE,16,96,0,0),
           // new AnimatedObject(AnimatedClass::AN_CANDLE,128,96,0,0),
        },
        {
           // new AnimatedObject(AnimatedClass::AN_CANDLE,48,16,0,0),
           // new AnimatedObject(AnimatedClass::AN_CANDLE,96,16,0,0),
        },
        {},
        {},
        {},
        {
           // new AnimatedObject(AnimatedClass::AN_CANDLE,16,16,0,0),
           // new AnimatedObject(AnimatedClass::AN_CANDLE,80,16,0,0),
           // new AnimatedObject(AnimatedClass::AN_CANDLE,16,96,0,0),
           // new AnimatedObject(AnimatedClass::AN_CANDLE,80,96,0,0),
        },
        { 
           // new Gibdo(32,32), 
           // new Gibdo(64,32),
           // new AnimatedObject(AnimatedClass::AN_TORCH,0,32,0,-90),
           // new AnimatedObject(AnimatedClass::AN_TORCH,0,80,0,-90)
        },
        {   // Starting room Tail Cave
            // Better yet, one allocation with variable arguments of positions
            new AnimatedObject(AnimatedClass::AN_CANDLE,16,16,0,0),
            new AnimatedObject(AnimatedClass::AN_CANDLE,128,16,0,0),
            new AnimatedObject(AnimatedClass::AN_CANDLE,16,96,0,0),
            new AnimatedObject(AnimatedClass::AN_CANDLE,128,96,0,0),
            new Octorok(EnemyType::Basic,80,80),
            new IronMask(64,64),
            new PigWarrior(EnemyType::Basic, 48,32),
            new Moblin(EnemyType::Basic, 48,32),
            new Darknut(EnemyType::Basic, 64,64),
            new ShroudedStalfos(EnemyType::Basic, 64,64),
        },
        {},
        {},
        {}
    };

    m_rooms[RM_TAIL_CAVE] = tc;*/
}

void RoomManager::useRoom(RoomName room)
{
    m_tilemapManager.useTilemap(room);
    m_tilemapManager.setRoomLocation(0);

    m_roomLinkManager.useRoomLink(room);
    m_roomLinkManager.setRoomLocation(0);
}

void RoomManager::setRoomLocation(const int roomLocation)
{
    m_tilemapManager.setRoomLocation(roomLocation);
    m_roomLinkManager.setRoomLocation(roomLocation);
}

void RoomManager::createRoom(RoomName roomName, const Sprite& tilemap, const TileIndexArrays& tileIndexArrays, const Tilemap::TilemapConfig& tilemapConfig, const RoomLinkMap& roomLinkMap)
{
    m_tilemapManager.createTilemap(roomName, tilemap, tileIndexArrays, tilemapConfig);
    m_roomLinkManager.createRoomLink(roomName, roomLinkMap);
}

// Loads the room objects for the current room at roomIndex
void RoomManager::roomDo(RoomAction action, size_t roomIndex)
{
    // Check we have a room
    /*assert(m_currentRoom.size() && roomIndex < m_currentRoom.size() && "Invalid room access");

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
    }*/
}

void RoomManager::transitionObjects(const size_t roomIndex, const int xTransition, const int yTransition)
{
    // Check we have a room
    /*assert(m_currentRoom.size() && roomIndex < m_currentRoom.size() && "Invalid room access");

    // Add or remove objects depending on action
    for (auto const& roomObject : m_currentRoom[roomIndex])
    {
        assert(roomObject);
        roomObject->transition(xTransition, yTransition);
    }*/
}

void RoomManager::updateNextRoomLocation(RoomDirection direction)
{
    int nextRoomIndex;
    switch (direction)
    {
    case RoomDirection::LEFT: 
        nextRoomIndex = m_roomLinkManager.roomLink().left;
        break;
    case RoomDirection::RIGHT: 
        nextRoomIndex = m_roomLinkManager.roomLink().right;
        break;
    case RoomDirection::UP:
        nextRoomIndex = m_roomLinkManager.roomLink().up;
        break;
    case RoomDirection::DOWN:
        nextRoomIndex = m_roomLinkManager.roomLink().down;
        break;
    default: 
        nextRoomIndex = -1; 
        assert(false);
    }
    if (nextRoomIndex == -1)
    {
        assert(false && "Invalid next room index");
    }
    else
    {
        m_tilemapManager.setNextRoomLocation(nextRoomIndex);
        m_roomLinkManager.setRoomLocation(nextRoomIndex);
    }
}

void RoomManager::updateCurrentRoomPosition(const int x, const int y)
{
    m_tilemapManager.setRoomPosition(x, y);
}

void RoomManager::updateNextRoomPosition(const int x, const int y)
{
    m_tilemapManager.setNextRoomPosition(x, y);
}

void RoomManager::updateCurrentRoomLocation()
{
    // Update room information
    auto const currentRoomIndex = m_roomLinkManager.currentRoom();
    m_tilemapManager.setRoomLocation(currentRoomIndex);
}

RoomManager::~RoomManager()
{
    // Free all newed objects in each room
   /* for (auto const& [roomName, room] : m_rooms)
    {
        for (auto const& roomObjects : room)
        {
            for (auto const& roomObject : roomObjects)
            {
                delete roomObject;
            }
        }
    }*/
    // m_currentRoom is now dangling!
}

}

