#include "Tilemap.h"
#include "Resource.h"
#include <cassert>

Zelda::Tilemap::Tilemap()
{
	m_currentTileMap.tilemap = Graphic::GFX_RESOURCE_NONE;
	m_currentTileMap.roomsAcross = 0;
	m_currentTileMap.roomsDown = 0;

	// Autogenerated using python script
	TilemapInformation ti;
	ti.rooms =
	{
		{
			{
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
			}
		},
		{
			{
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
			}
		},
		{
			{
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
			}
		},
		{
			{
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
			}
		},
		{
			{
				{1,1,2,1,1,1,1,1,1,1},
				{3,4,5,4,4,4,6,7,6,4},
				{3,4,5,4,4,4,7,8,7,4},
				{3,4,5,4,4,4,4,4,4,4},
				{9,9,5,9,9,4,9,9,5,9},
				{10,11,5,4,4,4,4,4,5,3},
				{10,11,5,4,4,4,4,4,5,3},
				{10,10,12,12,12,12,12,12,12,12},
			}
		},
		{
			{
				{1,1,1,1,1,1,1,2,1,1},
				{4,6,7,6,4,4,4,5,4,3},
				{4,7,8,7,4,4,4,5,4,3},
				{4,4,4,4,4,4,9,5,9,9},
				{9,5,4,9,9,4,4,5,13,10},
				{3,5,4,4,4,4,4,5,13,10},
				{3,5,4,4,4,4,4,5,13,10},
				{12,12,12,12,12,12,12,12,10,10},
			}
		},
		{
			{
				{14,15,16,17,15,15,18,19,15,16},
				{20,21,22,23,24,24,23,25,21,22},
				{20,26,22,24,24,24,24,25,26,22},
				{20,26,22,23,24,24,23,25,26,22},
				{20,26,17,15,27,27,15,18,26,22},
				{20,26,26,26,24,24,26,26,26,22},
				{20,21,26,26,24,24,26,26,21,22},
				{28,29,29,30,31,32,30,29,29,33},
			}
		},
		{
			{
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
			}
		},
		{
			{
				{19,15,15,15,15,34,15,15,15,16},
				{25,26,26,35,26,36,35,26,37,22},
				{25,26,35,26,26,26,26,35,26,38},
				{25,26,26,26,26,26,26,26,26,39},
				{25,26,26,26,26,26,26,26,26,22},
				{25,21,26,26,26,26,26,26,21,22},
				{40,41,21,26,26,26,26,21,42,33},
				{43,40,29,29,29,29,29,29,33,43},
			}
		},
		{
			{
				{19,15,15,34,15,15,15,15,15,15},
				{44,21,26,36,26,26,26,26,26,26},
				{45,24,24,24,46,24,46,24,24,24},
				{47,24,46,24,24,46,24,46,24,24},
				{44,26,26,26,26,26,26,26,26,26},
				{25,48,35,35,48,48,48,48,48,48},
				{25,21,26,26,24,24,24,24,24,24},
				{40,29,29,30,49,50,30,29,29,29},
			}
		},
		{
			{
				{15,15,15,15,15,15,15,15,15,16},
				{26,26,26,26,26,26,26,26,21,22},
				{24,24,24,46,24,24,46,24,26,22},
				{24,24,46,24,24,46,24,24,26,22},
				{26,26,26,26,46,26,24,46,26,22},
				{48,48,48,46,26,26,46,24,26,22},
				{24,24,24,24,24,24,24,24,21,22},
				{29,29,29,29,29,29,29,29,29,33},
			}
		},
		{
			{
				{3,4,51,4,4,51,4,4,51,4},
				{3,4,52,4,4,51,4,4,52,4},
				{3,4,53,4,4,52,4,4,53,4},
				{9,9,6,7,6,53,6,7,6,4},
				{3,4,7,8,7,4,7,8,7,4},
				{3,4,4,4,4,4,4,4,4,4},
				{3,54,54,4,54,4,4,4,4,4},
				{9,9,9,9,9,9,9,9,9,9},
			}
		},
		{
			{
				{4,4,4,4,4,9,9,5,9,9},
				{4,4,4,4,4,3,4,5,4,3},
				{4,4,4,4,4,3,4,5,4,3},
				{4,6,7,6,4,9,9,5,9,9},
				{4,7,8,7,4,4,4,5,4,3},
				{4,4,4,4,4,4,4,5,4,3},
				{4,4,4,4,54,4,54,5,54,3},
				{9,9,9,9,9,9,9,9,9,9},
			}
		},
		{
			{
				{14,15,15,55,56,57,55,15,15,16},
				{20,58,59,24,24,24,24,59,58,22},
				{20,58,24,24,24,24,24,24,58,22},
				{20,58,24,24,24,24,24,24,58,22},
				{20,58,24,24,24,24,24,24,58,22},
				{20,58,24,24,24,24,24,24,58,22},
				{20,58,60,24,24,24,24,60,58,22},
				{28,29,29,29,31,32,29,29,29,33},
			}
		},
		{
			{
				{19,15,15,15,15,15,15,15,15,16},
				{25,4,21,24,24,24,21,4,4,22},
				{25,4,26,24,61,24,26,4,4,22},
				{25,4,26,24,24,24,26,4,4,22},
				{25,62,35,35,26,35,35,62,62,22},
				{25,26,26,26,26,26,26,26,26,22},
				{25,21,26,26,26,26,26,26,21,22},
				{40,29,29,41,26,42,29,29,29,33},
			}
		},
		{
			{
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
			}
		},
		{
			{
				{43,43,19,15,63,64,15,16,65,48},
				{43,19,18,26,26,26,66,22,67,26},
				{19,18,35,26,26,26,4,22,67,26},
				{25,26,26,26,26,35,4,22,68,69},
				{25,26,46,26,26,26,4,17,15,15},
				{25,26,26,26,26,26,62,62,62,62},
				{25,21,26,23,26,26,23,26,42,29},
				{25,26,26,26,26,26,26,26,22,43},
			}
		},
		{
			{
				{48,21,21,48,48,48,21,21,48,48},
				{26,26,26,26,61,26,26,26,26,26},
				{26,70,69,69,69,69,69,71,26,26},
				{69,72,19,15,15,15,16,68,69,69},
				{15,15,18,4,62,4,17,15,15,16},
				{62,62,62,62,26,62,62,62,62,22},
				{29,41,26,26,26,26,26,26,26,22},
				{43,25,26,26,26,26,26,26,26,22},
			}
		},
		{
			{
				{48,48,48,73,19,15,15,15,16,43},
				{26,26,26,74,25,26,26,26,17,16},
				{26,26,26,74,25,26,26,26,26,22},
				{69,69,26,72,25,26,26,26,26,22},
				{19,15,27,15,18,66,26,26,26,22},
				{25,26,75,26,26,4,26,26,26,22},
				{25,26,26,26,26,62,26,26,26,22},
				{40,29,29,29,29,29,41,26,42,33},
			}
		},
		{
			{
				{43,19,15,15,15,34,15,15,16,43},
				{19,18,76,76,76,77,76,76,17,16},
				{25,21,76,76,76,76,76,76,61,22},
				{25,76,76,76,76,76,76,76,76,22},
				{25,76,76,76,76,76,76,76,76,22},
				{25,76,76,76,76,76,76,76,76,22},
				{40,41,76,76,76,76,76,76,42,33},
				{43,40,29,41,26,26,42,29,33,43},
			}
		},
		{
			{
				{19,15,15,55,78,79,55,15,15,16},
				{25,26,26,26,26,26,26,26,26,22},
				{25,26,26,26,26,26,26,26,26,22},
				{25,26,26,21,26,37,21,26,26,22},
				{25,26,26,23,23,23,23,26,26,22},
				{25,26,26,26,26,26,26,26,26,22},
				{25,26,26,26,26,26,26,26,26,22},
				{40,29,29,29,49,50,29,29,29,33},
			}
		},
		{
			{
				{43,43,43,25,26,22,43,43,43,43},
				{43,43,43,25,26,22,43,43,43,43},
				{43,43,43,25,26,22,43,43,43,43},
				{43,43,43,25,26,22,43,43,43,43},
				{43,43,43,25,26,22,43,43,43,43},
				{43,43,43,25,26,22,43,43,43,43},
				{43,43,43,25,26,22,43,43,43,43},
				{43,43,43,25,26,22,43,43,43,43},
			}
		},
		{
			{
				{43,43,19,15,15,15,15,15,15,16},
				{43,19,18,4,62,62,62,4,4,22},
				{43,25,4,62,24,24,24,62,62,22},
				{43,25,4,24,61,24,24,24,24,80},
				{43,25,4,24,24,24,24,24,24,22},
				{43,25,4,66,24,24,24,66,66,22},
				{43,40,41,4,66,66,66,4,4,22},
				{43,43,40,29,29,29,29,29,29,33},
			}
		},
		{
			{
				{25,26,26,26,26,26,26,26,22,43},
				{25,26,26,23,26,26,23,26,17,15},
				{25,26,26,23,26,26,23,26,61,26},
				{81,26,66,26,26,26,26,66,26,26},
				{25,26,62,26,26,26,26,62,26,26},
				{25,66,26,26,26,26,26,26,26,26},
				{25,4,66,66,82,82,66,66,66,26},
				{40,29,29,29,49,50,29,29,29,29},
			}
		},
		{
			{
				{43,25,26,26,26,26,26,26,26,22},
				{15,18,26,24,24,24,26,26,26,17},
				{26,26,26,24,61,24,26,46,26,26},
				{26,26,26,24,24,24,26,26,26,46},
				{26,26,26,26,26,26,26,26,26,26},
				{26,26,26,26,46,26,26,46,26,26},
				{26,26,26,26,26,26,26,26,26,42},
				{29,29,29,29,29,29,29,29,29,33},
			}
		},
		{
			{
				{19,15,15,15,15,15,18,26,17,16},
				{18,26,26,26,26,26,26,26,26,22},
				{26,26,26,46,46,46,46,46,46,22},
				{46,46,46,46,26,26,26,26,26,83},
				{26,26,26,26,26,26,26,26,26,84},
				{26,26,26,26,26,26,26,26,26,22},
				{41,26,26,26,26,26,26,26,26,22},
				{40,29,29,29,85,86,29,29,29,33},
			}
		},
		{
			{
				{19,15,15,18,26,26,17,15,15,16},
				{25,26,26,26,26,26,26,26,26,22},
				{25,26,26,26,26,26,26,66,35,87},
				{88,26,26,42,29,41,26,4,26,38},
				{89,26,26,17,15,18,26,4,26,39},
				{25,26,26,26,26,26,26,62,35,87},
				{25,26,26,26,26,26,26,26,26,22},
				{40,29,29,29,29,29,29,29,29,33},
			}
		},
		{
			{
				{19,15,15,55,56,57,55,15,15,16},
				{25,24,24,24,24,24,24,24,24,22},
				{44,24,24,24,24,24,24,24,24,22},
				{45,24,24,24,24,24,24,24,24,22},
				{47,24,24,24,24,24,24,24,24,22},
				{44,24,24,24,24,24,24,24,24,22},
				{25,24,24,24,24,24,24,24,24,22},
				{40,29,29,29,29,29,29,29,29,33},
			}
		},
		{
			{
				{43,43,43,25,26,22,43,43,43,43},
				{43,43,43,25,26,22,43,43,43,43},
				{43,43,43,25,26,22,43,43,43,43},
				{43,19,15,18,26,17,15,16,43,43},
				{43,25,21,26,26,26,21,22,43,43},
				{43,25,26,26,37,26,26,22,43,43},
				{43,25,21,26,26,26,21,22,43,43},
				{43,40,29,29,29,29,29,33,43,43},
			}
		},
		{
			{
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
			}
		},
		{
			{
				{43,19,15,15,56,57,15,15,16,43},
				{19,18,90,90,26,26,90,90,17,16},
				{25,90,26,26,26,26,26,26,90,87},
				{25,90,26,23,26,26,23,26,26,91},
				{25,90,26,23,26,26,23,26,26,92},
				{25,90,26,26,26,26,26,26,90,87},
				{40,41,90,90,26,26,90,90,42,33},
				{43,40,29,29,29,29,29,29,33,43},
			}
		},
		{
			{
				{19,15,15,15,15,15,15,15,15,16},
				{25,26,26,26,26,26,26,26,26,22},
				{25,26,26,66,26,26,66,26,26,17},
				{88,26,26,4,26,93,4,26,26,26},
				{89,26,26,62,35,35,62,26,26,26},
				{25,26,26,26,26,26,26,26,26,42},
				{25,21,26,26,26,26,26,26,21,22},
				{40,29,29,41,26,26,42,29,29,33},
			}
		},
		{
			{
				{19,15,15,15,94,95,15,15,15,16},
				{25,4,26,21,24,24,21,26,26,22},
				{18,62,26,24,24,24,24,26,61,22},
				{26,26,26,24,24,24,24,26,26,22},
				{26,26,26,24,24,24,24,26,26,22},
				{41,66,26,23,26,26,23,26,26,22},
				{25,4,26,26,26,26,26,26,26,22},
				{40,29,29,29,29,29,29,29,29,33},
			}
		},
		{
			{
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
			}
		},
		{
			{
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
			}
		},
		{
			{
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
			}
		},
		{
			{
				{19,15,15,15,15,15,16,43,43,43},
				{25,21,26,26,26,21,22,43,43,43},
				{25,26,23,24,23,26,17,15,15,16},
				{25,26,24,61,24,26,26,26,26,91},
				{25,26,24,24,24,26,26,26,26,92},
				{25,26,26,26,26,26,42,29,29,33},
				{25,21,26,26,26,21,22,43,43,43},
				{40,29,29,29,29,29,33,43,43,43},
			}
		},
		{
			{
				{43,19,15,15,15,15,15,15,16,43},
				{19,18,62,62,62,62,62,62,17,16},
				{44,62,26,26,26,26,26,26,62,17},
				{88,26,24,26,26,26,26,26,26,26},
				{89,26,26,26,26,26,26,26,26,26},
				{44,66,26,26,26,26,26,26,66,42},
				{40,41,66,66,66,66,66,66,42,33},
				{43,40,29,29,29,29,29,29,33,43},
			}
		},
		{
			{
				{19,15,15,18,26,26,17,15,15,16},
				{25,21,24,24,24,24,24,24,21,22},
				{18,24,23,23,26,26,23,23,24,22},
				{26,24,23,26,26,26,26,23,24,22},
				{26,24,23,26,26,26,26,23,24,22},
				{41,24,26,96,97,97,98,26,24,22},
				{25,21,24,99,100,101,102,24,21,22},
				{40,29,29,103,104,105,106,29,29,33},
			}
		},
		{
			{
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
			}
		},
		{
			{
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
			}
		},
		{
			{
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
			}
		}
	};
	ti.roomsAcross = 7;
	ti.roomsDown = 6;
	ti.tilemap = Graphic::GFX_DUNGEON_1_TAIL_CAVE;
	m_tileMaps[TM_TAIL_CAVE] = ti;
}

void Zelda::Tilemap::setTileMap(TilemapArea tilemap) noexcept
{
	assert(tilemap > TM_NONE && tilemap < TM_COUNT);
	m_currentTileMap = m_tileMaps[tilemap];
}

Zelda::Room Zelda::Tilemap::getRoomTiles(int roomIndex) const noexcept
{
	// Check room index is within bounds
	assert(roomIndex >= 0 && roomIndex < (m_currentTileMap.roomsAcross * m_currentTileMap.roomsDown));
	// Check if there is a room
	assert(m_currentTileMap.rooms.size());

    return m_currentTileMap.rooms[roomIndex];
}

uint16_t Zelda::Tilemap::roomWidth() const noexcept
{
	return m_currentTileMap.roomsAcross;
}

SDL_Texture* Zelda::Tilemap::getTilemapTexture() const noexcept
{
	assert(m_currentTileMap.tilemap != Graphic::GFX_RESOURCE_NONE);
	return ResourceManager::getInstance()[m_currentTileMap.tilemap];
}

