#include "ResourceManager.h"
#include "DataManager.h"
#include "zelda_core/RoomLinkManager.h"
#include "Colour.h"

#include "zelda_core/RoomManager.h"


// TODO: Remove when defaults are set
#include "zelda_core/Link.h"
#include "Controller.h"

namespace zelda::engine
{

void DataManager::loadData() const
{
    // TODO: Load data from file
    loadSprites();
    loadRooms();
}

void DataManager::loadSprites()
{
    constexpr Colour::colour TRANSPARENCY_COLOUR = Colour::makeRGB(255, 0, 128);
    ResourceManager::instance().loadSprite(SpriteResource::TAIL_CAVE,
                                              RESOURCE_DUNGEONS_PATH / "dungeon_tail_cave.png",
                                              TRANSPARENCY_COLOUR);
    ResourceManager::instance().loadSprite(SpriteResource::WORLD_MAP,
                                              RESOURCE_MISC_PATH / "tm_worldmap.png",
                                              TRANSPARENCY_COLOUR);
    ResourceManager::instance().loadSprite(SpriteResource::LINK,
                                              RESOURCE_SPRITE_LINK_PATH / "link.png",
                                              TRANSPARENCY_COLOUR);
    ResourceManager::instance().loadSprite(SpriteResource::INVENTORY,
                                              RESOURCE_OBJECT_PATH / "inventory.png",
                                              TRANSPARENCY_COLOUR);
    ResourceManager::instance().loadSprite(SpriteResource::WEAPON,
                                              RESOURCE_OBJECT_PATH / "weapons.png",
                                              TRANSPARENCY_COLOUR);
    ResourceManager::instance().loadSprite(SpriteResource::TEXT,
                                              RESOURCE_MISC_PATH / "dialogue.png",
                                              TRANSPARENCY_COLOUR);
    ResourceManager::instance().loadSprite(SpriteResource::ENEMY,
                                              RESOURCE_ENEMY_PATH / "enemy.png",
                                              TRANSPARENCY_COLOUR);
}

void DataManager::loadTailCave()
{
    core::RoomLinkMap roomLinkMap = {
        {0, {-1, 1, -1, 6}},    {1, {0, 2, -1, 7}},     {2, {1, -1, -1, 8}},    {3, {-1, 4, -1, -1}},
        {4, {3, 5, -1, 10}},    {5, {4, 6, -1, 11}},    {6, {5, 7, 0, 12}},     {7, {6, 8, 1, 13}},
        {8, {7, -1, 2, 14}},    {9, {-1, -1, -1, 15}},  {10, {-1, 11, 4, 17}},  {11, {10, 12, 5, 18}},
        {12, {11, 13, 6, 19}},  {13, {12, 14, 7, 20}},  {14, {13, -1, 8, 21}},  {15, {-1, 16, 9, 22}},
        {16, {15, 17, -1, -1}}, {17, {16, 18, 10, 23}}, {18, {17, 19, 11, 24}}, {19, {18, 20, 12, 25}},
        {20, {19, 21, 13, -1}}, {21, {20, -1, 14, -1}}, {22, {-1, -1, 15, -1}}, {23, {-1, 24, 17, 27}},
        {24, {23, 25, 18, 28}}, {25, {24, -1, 19, -1}}, {26, {-1, 27, -1, -1}}, {27, {26, 28, 23, -1}},
        {28, {27, -1, 24, -1}},
    };

    // TODO: Load collision data
    // TODO: Load enemies/room objects at some point

    core::RoomManager::instance().createRoom(core::RoomName::TAIL_CAVE, roomLinkMap);
}

void DataManager::loadRooms() const
{
    loadTailCave();


    // TODO: Setup initial starting positions somewhere
    // e.g GameManager
    core::RoomManager::instance().useRoom(core::RoomName::TAIL_CAVE);
    core::RoomManager::instance().setRoomLocation(28);
    // Link::getInstance().setDungeonMarkerLocation(3, 8);
    Controller::instance().setController(&core::Link::instance());
    Camera::instance().setScrollSpeed(CAMERA_SCROLL_SPEED);


    // Dialogue::getInstance().question("Our colors are  ""never the same! ""If
    // I am red, he ""is blue! If he  ""is red, I am    ""blue! What color""is my cloth?", "Red", "Blue",0);

    // Dialogue::getInstance().message("Level 1--       ""     Tail Cave",0);
}


}; // namespace zelda::engine