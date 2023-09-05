#include "TilemapManager.h"
#include "ResourceManager.h"
#include "DataManager.h"
#include "RoomLinkManager.h"
#include "Colour.h"

#include "RoomManager.h"


// TODO: Remove when defaults are set
#include "Link.h"
#include "Controller.h"
#include "Dialogue.h"

namespace Zelda
{

	void DataManager::loadData() const
	{
		// TODO: Load data from file
		loadSprites();
		loadRooms();
	}

	void DataManager::loadSprites() const
	{
		constexpr Colour TRANSPARENCY_COLOUR = makeRGB(255, 0, 128);
		ResourceManager::getInstance().loadSprite(SpriteResource::SPR_DUNGEON_1_TAIL_CAVE, RESOURCE_DUNGEONS_PATH + "tail-cave.png", TRANSPARENCY_COLOUR);
		ResourceManager::getInstance().loadSprite(SpriteResource::SPR_WORLD_MAP, RESOURCE_MISC_PATH + "tm_worldmap.png", TRANSPARENCY_COLOUR);
		ResourceManager::getInstance().loadSprite(SpriteResource::SPR_LINK, RESOURCE_SPRITE_LINK_PATH + "link.png", TRANSPARENCY_COLOUR);
		ResourceManager::getInstance().loadSprite(SpriteResource::SPR_INVENTORY, RESOURCE_OBJECT_PATH + "inventory.png", TRANSPARENCY_COLOUR);
		ResourceManager::getInstance().loadSprite(SpriteResource::SPR_WEAPON, RESOURCE_OBJECT_PATH + "weapons.png", TRANSPARENCY_COLOUR);
		ResourceManager::getInstance().loadSprite(SpriteResource::SPR_TEXT, RESOURCE_MISC_PATH + "dialogue.png", TRANSPARENCY_COLOUR);
		ResourceManager::getInstance().loadSprite(SpriteResource::SPR_ENEMY,  RESOURCE_ENEMY_PATH + "enemy.png", TRANSPARENCY_COLOUR);

	}

	void DataManager::loadTailCave() const
	{

		// TODO: const this (constexpr?)
		Tilemap::TilemapConfig tilemapConfig;
		tilemapConfig.tileHeight = 16;
		tilemapConfig.tileWidth = 16;
		tilemapConfig.tilesAcross = 10;
		tilemapConfig.tilesDown = 8;

		const TileIndexArrays tileIndexArrays =
		{
			{
				{
					{0,0,1,0,0,0,0,0,0,0},
					{2,3,4,3,3,3,5,6,5,3},
					{2,3,4,3,3,3,6,7,6,3},
					{2,3,4,3,3,3,3,3,3,3},
					{8,8,4,8,8,3,8,8,4,8},
					{9,10,4,3,3,3,3,3,4,2},
					{9,10,4,3,3,3,3,3,4,2},
					{9,9,11,11,11,11,11,11,11,11},
				}
			},
			{
				{
					{0,0,0,0,0,0,0,1,0,0},
					{3,5,6,5,3,3,3,4,3,2},
					{3,6,7,6,3,3,3,4,3,2},
					{3,3,3,3,3,3,8,4,8,8},
					{8,4,3,8,8,3,3,4,12,9},
					{2,4,3,3,3,3,3,4,12,9},
					{2,4,3,3,3,3,3,4,12,9},
					{11,11,11,11,11,11,11,11,9,9},
				}
			},
			{
				{
					{13,14,15,16,14,14,17,18,14,15},
					{19,20,21,22,23,23,22,24,20,21},
					{19,20,21,23,23,23,23,24,20,21},
					{19,20,21,22,23,23,22,24,20,21},
					{19,20,16,14,25,25,14,17,20,21},
					{19,20,20,20,23,23,20,20,20,21},
					{19,20,20,20,23,23,20,20,20,21},
					{26,27,27,27,28,29,27,27,27,30},
				}
			},
			{
				{
					{18,14,14,14,14,31,14,14,14,15},
					{24,20,20,32,20,33,32,20,34,21},
					{24,20,32,20,20,20,20,32,20,35},
					{24,20,20,20,20,20,20,20,20,36},
					{24,20,20,20,20,20,20,20,20,21},
					{24,20,20,20,20,20,20,20,20,21},
					{37,38,20,20,20,20,20,20,39,30},
					{40,37,27,27,27,27,27,27,30,40},
				}
			},
			{
				{
					{18,14,14,31,14,14,14,14,14,14},
					{24,20,20,33,20,20,20,20,20,20},
					{41,23,23,23,42,23,42,23,23,23},
					{43,23,42,23,23,42,23,42,23,23},
					{24,20,20,20,20,20,20,20,20,20},
					{24,44,32,32,44,44,44,44,44,44},
					{24,20,20,20,23,23,23,23,23,23},
					{37,27,27,27,45,46,27,27,27,27},
				}
			},
			{
				{
					{14,14,14,14,14,14,14,14,14,15},
					{20,20,20,20,20,20,20,20,20,21},
					{23,23,23,42,23,23,42,23,20,21},
					{23,23,42,23,23,42,23,23,20,21},
					{20,20,20,20,42,20,23,42,20,21},
					{44,44,44,42,20,20,42,23,20,21},
					{23,23,23,23,23,23,23,23,20,21},
					{27,27,27,27,27,27,27,27,27,30},
				}
			},
			{
				{
					{2,3,47,3,3,47,3,3,47,3},
					{2,3,48,3,3,47,3,3,48,3},
					{2,3,49,3,3,48,3,3,49,3},
					{8,8,5,6,5,49,5,6,5,3},
					{2,3,6,7,6,3,6,7,6,3},
					{2,3,3,3,3,3,3,3,3,3},
					{2,50,50,3,50,3,3,3,3,3},
					{8,8,8,8,8,8,8,8,8,8},
				}
			},
			{
				{
					{3,3,3,3,3,8,8,4,8,8},
					{3,3,3,3,3,2,3,4,3,2},
					{3,3,3,3,3,2,3,4,3,2},
					{3,5,6,5,3,8,8,4,8,8},
					{3,6,7,6,3,3,3,4,3,2},
					{3,3,3,3,3,3,3,4,3,2},
					{3,3,3,3,50,3,50,4,50,2},
					{8,8,8,8,8,8,8,8,8,8},
				}
			},
			{
				{
					{13,14,14,14,51,52,14,14,14,15},
					{19,53,54,23,23,23,23,54,53,21},
					{19,53,23,23,23,23,23,23,53,21},
					{19,53,23,23,23,23,23,23,53,21},
					{19,53,23,23,23,23,23,23,53,21},
					{19,53,23,23,23,23,23,23,53,21},
					{19,53,55,23,23,23,23,55,53,21},
					{26,27,27,27,28,29,27,27,27,30},
				}
			},
			{
				{
					{18,14,14,14,14,14,14,14,14,15},
					{24,3,20,23,23,23,20,3,3,21},
					{24,3,20,23,20,23,20,3,3,21},
					{24,3,20,23,23,23,20,3,3,21},
					{24,56,32,32,20,32,32,56,56,21},
					{24,20,20,20,20,20,20,20,20,21},
					{24,20,20,20,20,20,20,20,20,21},
					{37,27,27,38,20,39,27,27,27,30},
				}
			},
			{
				{
					{57,57,18,14,51,52,14,15,58,44},
					{57,18,17,20,20,20,59,21,60,20},
					{18,17,32,20,20,20,3,21,60,20},
					{24,20,20,20,20,32,3,21,61,62},
					{24,20,42,20,20,20,3,16,14,14},
					{24,20,20,20,20,20,56,56,56,56},
					{24,20,20,22,20,20,22,20,39,27},
					{24,20,20,20,20,20,20,20,21,40},
				}
			},
			{
				{
					{44,20,20,44,44,44,20,20,44,44},
					{20,20,20,20,20,20,20,20,20,20},
					{20,63,62,62,62,62,62,64,20,20},
					{62,65,18,14,14,14,15,61,62,62},
					{14,14,17,3,56,3,16,14,14,15},
					{56,56,56,56,20,56,56,56,56,21},
					{27,38,20,20,20,20,20,20,20,21},
					{40,24,20,20,20,20,20,20,20,21},
				}
			},
			{
				{
					{44,44,44,66,18,14,14,14,15,40},
					{20,20,20,67,24,20,20,20,16,15},
					{20,20,20,67,24,20,20,20,20,21},
					{62,62,20,65,24,20,20,20,20,21},
					{18,14,25,14,17,59,20,20,20,21},
					{24,20,20,20,20,3,20,20,20,21},
					{24,20,20,20,20,56,20,20,20,21},
					{37,27,27,27,27,27,38,20,39,30},
				}
			},
			{
				{
					{40,18,14,14,14,31,14,14,15,57},
					{18,17,68,68,68,69,68,68,16,15},
					{24,68,68,68,68,68,68,68,68,21},
					{24,68,68,68,68,68,68,68,68,21},
					{24,68,68,68,68,68,68,68,68,21},
					{24,68,68,68,68,68,68,68,68,21},
					{37,38,68,68,68,68,68,68,39,30},
					{40,37,27,38,20,20,39,27,30,57},
				}
			},
			{
				{
					{18,14,14,14,51,52,14,14,14,15},
					{24,20,20,20,20,20,20,20,20,21},
					{24,20,20,20,20,20,20,20,20,21},
					{24,20,20,20,20,34,20,20,20,21},
					{24,20,20,22,22,22,22,20,20,21},
					{24,20,20,20,20,20,20,20,20,21},
					{24,20,20,20,20,20,20,20,20,21},
					{37,27,27,27,45,46,27,27,27,30},
				}
			},
			{
				{
					{40,40,40,24,20,21,40,40,40,40},
					{40,40,40,24,20,21,40,40,40,40},
					{40,40,40,24,20,21,40,40,40,40},
					{40,40,40,24,20,21,40,40,40,40},
					{40,40,40,24,20,21,40,40,40,40},
					{40,40,40,24,20,21,40,40,40,40},
					{40,40,40,24,20,21,40,40,40,40},
					{40,40,40,24,20,21,40,40,40,40},
				}
			},
			{
				{
					{40,40,18,14,14,14,14,14,14,15},
					{40,18,17,3,56,56,56,3,3,21},
					{40,24,3,56,23,23,23,56,56,21},
					{40,24,3,23,20,23,23,23,23,70},
					{40,24,3,23,23,23,23,23,23,21},
					{40,24,3,59,23,23,23,59,59,21},
					{40,37,38,3,59,59,59,3,3,21},
					{40,40,37,27,27,27,27,27,27,30},
				}
			},
			{
				{
					{24,20,20,20,20,20,20,20,21,40},
					{24,20,20,22,20,20,22,20,16,14},
					{24,20,20,22,20,20,22,20,20,20},
					{20,20,59,20,20,20,20,59,20,20},
					{24,20,56,20,20,20,20,56,20,20},
					{24,59,20,20,20,20,20,20,20,20},
					{24,3,59,59,20,20,59,59,59,20},
					{37,27,27,27,45,46,27,27,27,27},
				}
			},
			{
				{
					{40,24,20,20,20,20,20,20,20,21},
					{14,17,20,23,23,23,20,20,20,16},
					{20,20,20,23,20,23,20,42,20,20},
					{20,20,20,23,23,23,20,20,20,42},
					{20,20,20,20,20,20,20,20,20,20},
					{20,20,20,20,42,20,20,42,20,20},
					{20,20,20,20,20,20,20,20,20,39},
					{27,27,27,27,27,27,27,27,27,30},
				}
			},
			{
				{
					{18,14,14,14,14,14,17,20,16,15},
					{17,20,20,20,20,20,20,20,20,21},
					{20,20,20,42,42,42,42,42,42,21},
					{42,42,42,42,20,20,20,20,20,71},
					{20,20,20,20,20,20,20,20,20,72},
					{20,20,20,20,20,20,20,20,20,21},
					{38,20,20,20,20,20,20,20,20,21},
					{37,27,27,27,28,29,27,27,27,30},
				}
			},
			{
				{
					{18,14,14,17,20,20,16,14,14,15},
					{24,20,20,20,20,20,20,20,20,21},
					{24,20,20,20,20,20,20,59,32,21},
					{73,20,20,39,27,38,20,3,20,35},
					{74,20,20,16,14,17,20,3,20,36},
					{24,20,20,20,20,20,20,56,32,21},
					{24,20,20,20,20,20,20,20,20,21},
					{37,27,27,27,27,27,27,27,27,30},
				}
			},
			{
				{
					{18,14,14,14,51,52,14,14,14,15},
					{24,23,23,23,23,23,23,23,23,21},
					{24,23,23,23,23,23,23,23,23,21},
					{41,23,23,23,23,23,23,23,23,21},
					{43,23,23,23,23,23,23,23,23,21},
					{24,23,23,23,23,23,23,23,23,21},
					{24,23,23,23,23,23,23,23,23,21},
					{37,27,27,27,27,27,27,27,27,30},
				}
			},
			{
				{
					{40,40,40,24,20,21,40,40,40,40},
					{40,40,40,24,20,21,40,40,40,40},
					{40,40,40,24,20,21,40,40,40,40},
					{40,18,14,17,20,16,14,15,40,40},
					{40,24,20,20,20,20,20,21,40,40},
					{40,24,20,20,34,20,20,21,40,40},
					{40,24,20,20,20,20,20,21,40,40},
					{40,37,27,27,27,27,27,30,40,40},
				}
			},
			{
				{
					{57,18,14,14,51,52,14,14,15,40},
					{18,17,75,75,20,20,75,75,16,15},
					{24,75,20,20,20,20,20,20,75,21},
					{24,75,20,22,20,20,22,20,20,71},
					{24,75,20,22,20,20,22,20,20,72},
					{24,75,20,20,20,20,20,20,75,21},
					{37,38,75,75,20,20,75,75,39,30},
					{57,37,27,27,27,27,27,27,30,40},
				}
			},
			{
				{
					{18,14,14,14,14,14,14,14,14,15},
					{24,20,20,20,20,20,20,20,20,21},
					{24,20,20,59,20,20,59,20,20,16},
					{73,20,20,3,20,20,3,20,20,20},
					{74,20,20,56,32,32,56,20,20,20},
					{24,20,20,20,20,20,20,20,20,39},
					{24,20,20,20,20,20,20,20,20,21},
					{37,27,27,38,20,20,39,27,27,30},
				}
			},
			{
				{
					{18,14,14,14,51,52,14,14,14,15},
					{24,3,20,23,23,23,23,20,20,21},
					{17,56,20,23,23,23,23,20,20,21},
					{20,20,20,23,23,23,23,20,20,21},
					{20,20,20,23,23,23,23,20,20,21},
					{38,59,20,22,20,20,22,20,20,21},
					{24,3,20,20,20,20,20,20,20,21},
					{37,27,27,27,27,27,27,27,27,30},
				}
			},
			{
				{
					{18,14,14,14,14,14,15,57,57,57},
					{24,20,20,20,20,20,21,57,57,57},
					{24,20,22,23,22,20,16,14,14,15},
					{24,20,23,20,23,20,20,20,20,71},
					{24,20,23,23,23,20,20,20,20,72},
					{24,20,20,20,20,20,39,27,27,30},
					{24,20,20,20,20,20,21,40,40,40},
					{37,27,27,27,27,27,30,40,40,40},
				}
			},
			{
				{
					{57,18,14,14,14,14,14,14,15,40},
					{18,17,56,56,56,56,56,56,16,15},
					{24,56,20,20,20,20,20,20,56,16},
					{73,20,23,20,20,20,20,20,20,20},
					{74,20,20,20,20,20,20,20,20,20},
					{24,59,20,20,20,20,20,20,59,39},
					{37,38,59,59,59,59,59,59,39,30},
					{40,37,27,27,27,27,27,27,30,57},
				}
			},
			{
				{
					{18,14,14,17,20,20,16,14,14,15},
					{24,23,23,23,23,23,23,23,23,21},
					{17,23,22,22,20,20,22,22,23,21},
					{20,23,22,20,20,20,20,22,23,21},
					{20,23,22,20,20,20,20,22,23,21},
					{38,23,20,76,77,77,78,20,23,21},
					{24,23,23,79,80,81,82,23,23,21},
					{37,27,27,83,84,85,86,27,27,30},
				}
			},
		};

		RoomLinkMap roomLinkMap =
		{
			{0,{-1,1,-1,6}},
			{1,{0,2,-1,7}},
			{2,{1,-1,-1,8}},
			{3,{-1,4,-1,-1}},
			{4,{3,5,-1,10}},
			{5,{4,6,-1,11}},
			{6,{5,7,0,12}},
			{7,{6,8,1,13}},
			{8,{7,-1,2,14}},
			{9,{-1,-1,-1,15}},
			{10,{-1,11,4,17}},
			{11,{10,12,5,18}},
			{12,{11,13,6,19}},
			{13,{12,14,7,20}},
			{14,{13,-1,8,21}},
			{15,{-1,16,9,22}},
			{16,{15,17,-1,-1}},
			{17,{16,18,10,23}},
			{18,{17,19,11,24}},
			{19,{18,20,12,25}},
			{20,{19,21,13,-1}},
			{21,{20,-1,14,-1}},
			{22,{-1,-1,15,-1}},
			{23,{-1,24,17,27}},
			{24,{23,25,18,28}},
			{25,{24,-1,19,-1}},
			{26,{-1,27,-1,-1}},
			{27,{26,28,23,-1}},
			{28,{27,-1,24,-1}},
		};

		// TODO: Load collision data
		// TODO: Load enemies/room objects at some point

		RoomManager::getInstance().createRoom(RoomName::RM_TAIL_CAVE,*ResourceManager::getInstance()[SpriteResource::SPR_DUNGEON_1_TAIL_CAVE],tileIndexArrays, tilemapConfig, roomLinkMap);
	}

	void DataManager::loadRooms() const
	{
		loadTailCave();


		// TODO: Setup initial starting positions somewhere
		// e.g GameManager
		RoomManager::getInstance().useRoom(RoomName::RM_TAIL_CAVE);
		RoomManager::getInstance().setRoomLocation(28);
		//Link::getInstance().setDungeonMarkerLocation(3, 8);
		Controller::getInstance().setController(&Link::getInstance());
		Camera::getInstance().setScrollSpeed(CAMERA_SCROLL_SPEED);


		//Dialogue::getInstance().question("Our colors are  ""never the same! ""If I am red, he ""is blue! If he  ""is red, I am    ""blue! What color""is my cloth?", "Red", "Blue",0);

		//Dialogue::getInstance().message("Level 1--       ""     Tail Cave",0);
	}


};