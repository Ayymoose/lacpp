#include "RoomManager.h"

#include "AnimatedObject.h"

#include "Renderer.h"

// All enemies
#include "Pairodd.h"
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
#include "ShroudedStalfos.h"

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
        {   /* Starting room Tail Cave*/
            // Better yet, one allocation with variable arguments of positions
           /* new AnimatedObject(AnimatedClass::AN_CANDLE,16,16,0,0),
            new AnimatedObject(AnimatedClass::AN_CANDLE,128,16,0,0),
            new AnimatedObject(AnimatedClass::AN_CANDLE,16,96,0,0),
            new AnimatedObject(AnimatedClass::AN_CANDLE,128,96,0,0),
            new Octorok(EnemyType::Basic,80,80),
            new IronMask(64,64),
            new PigWarrior(EnemyType::Basic, 48,32),
            new Moblin(EnemyType::Basic, 48,32),
            new Darknut(EnemyType::Basic, 64,64),
            new ShroudedStalfos(EnemyType::Basic, 64,64),*/
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
void RoomManager::roomDo(RoomAction action, size_t roomIndex) noexcept
{
    // Check we have a room
    assert(m_currentRoom.size() && roomIndex < m_currentRoom.size() && "Invalid room access");

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
    assert(m_currentRoom.size() && roomIndex < m_currentRoom.size() && "Invalid room access");

    // Add or remove objects depending on action
    for (auto const& roomObject : m_currentRoom[roomIndex])
    {
        assert(roomObject);
        roomObject->transition(xTransition, yTransition);
    }
}

RoomManager::~RoomManager()
{
    // Free all newed objects in each room
    for (auto const& [roomName, room] : m_rooms)
    {
        for (auto const& roomObjects : room)
        {
            for (auto const& roomObject : roomObjects)
            {
                delete roomObject;
            }
        }
    }
    // m_currentRoom is now dangling!
}

}

