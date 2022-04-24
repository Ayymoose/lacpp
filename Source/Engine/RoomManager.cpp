#include "RoomManager.h"
#include "TilemapManager.h"
#include "RoomLinkManager.h"
#include "Renderer.h"

#include <cassert>

//#include "AnimatedObject.h"

// All enemies
/*#include "Pairodd.h"
#include "Gibdo.h"
#include "Shyguy.h"
//#include "Goomba.h"
#include "Octorok.h"
#include "ArmMimic.h"
#include "SeaUrchin.h"
#include "Beamos.h"
#include "GopongaFlower.h"
#include "Gibdo.h"
#include "LikeLike.h"
#include "HardhatBeetle.h"
#include "Bubble.h"
#include "Star.h"
#include "Vacuum.h"
#include "BladeTrap.h"
#include "ShyGuy.h"
#include "WaterTektite.h"
#include "IronMask.h"
#include "ThreeOfAKind.h"
//#include "Spark.h"
#include "Leever.h"
#include "SandCrab.h"
#include "BuzzBlob.h"
#include "Zombie.h"
#include "Peahat.h"
#include "PigWarrior.h"
#include "Moblin.h"
#include "Darknut.h"
#include "ShroudedStalfos.h"*/

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

void RoomManager::useRoom(RoomName room) noexcept
{
    TilemapManager::getInstance().useTilemap(room);
    TilemapManager::getInstance().setRoomLocation(0);

    RoomLinkManager::getInstance().useRoomLink(room);
    RoomLinkManager::getInstance().setRoomLocation(0);
}

void RoomManager::setRoomLocation(const int roomLocation) noexcept
{
    TilemapManager::getInstance().setRoomLocation(roomLocation);
    RoomLinkManager::getInstance().setRoomLocation(roomLocation);
}

// Loads the room objects for the current room at roomIndex
void RoomManager::roomDo(RoomAction action, size_t roomIndex) noexcept
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

void RoomManager::transitionObjects(size_t roomIndex, int xTransition, int yTransition) noexcept
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

void RoomManager::updateNextRoomLocation(RoomDirection direction) const noexcept
{
    int nextRoomIndex;
    switch (direction)
    {
    case RoomDirection::LEFT: 
        nextRoomIndex = RoomLinkManager::getInstance().roomLink().left;
        break;
    case RoomDirection::RIGHT: 
        nextRoomIndex = RoomLinkManager::getInstance().roomLink().right;
        break;
    case RoomDirection::UP:
        nextRoomIndex = RoomLinkManager::getInstance().roomLink().up;
        break;
    case RoomDirection::DOWN:
        nextRoomIndex = RoomLinkManager::getInstance().roomLink().down;
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
        TilemapManager::getInstance().setNextRoomLocation(nextRoomIndex);
        RoomLinkManager::getInstance().setRoomLocation(nextRoomIndex);
    }
}

void RoomManager::updateCurrentRoomPosition(const int x, const int y) const noexcept
{
    TilemapManager::getInstance().setRoomPosition(x, y);
}

void RoomManager::updateNextRoomPosition(const int x, const int y) const noexcept
{
    TilemapManager::getInstance().setNextRoomPosition(x, y);
}

void RoomManager::updateCurrentRoomLocation() const noexcept
{
    // Update room information
    auto const currentRoomIndex = RoomLinkManager::getInstance().currentRoom();
    TilemapManager::getInstance().setRoomLocation(currentRoomIndex);
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

