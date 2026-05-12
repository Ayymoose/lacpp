#pragma once

namespace zelda::core
{

enum class RoomName
{
    NONE = -1,
    TAIL_CAVE,          // Dungeon 1  – MAP_TAIL_CAVE       $00
    BOTTLE_GROTTO,      // Dungeon 2  – MAP_BOTTLE_GROTTO   $01
    KEY_CAVERN,         // Dungeon 3  – MAP_KEY_CAVERN      $02
    ANGLER_TUNNEL,      // Dungeon 4  – MAP_ANGLERS_TUNNEL  $03
    CATFISH_MAW,        // Dungeon 5  – MAP_CATFISHS_MAW    $04
    FACE_SHRINE,        // Dungeon 6  – MAP_FACE_SHRINE     $05
    EAGLE_TOWER,        // Dungeon 7  – MAP_EAGLES_TOWER    $06
    TURTLE_ROCK,        // Dungeon 8  – MAP_TURTLE_ROCK     $07
    WIND_FISH_EGG,      // Final area – MAP_WINDFISHS_EGG   $08
    COLOUR_DUNGEON,     // DX extra   – MAP_COLOR_DUNGEON   $FF
    KANALET_CASTLE,         // MAP_KANALET           $14
    SOUTHERN_FACE_SHRINE,   // MAP_S_FACE_SHRINE     $16 / ROOM_OW_SOUTHERN_FACE_SHRINE_ENTRANCE
    SEASHELL_MANSION,       // ROOM_INDOOR_B_SEASHELL_MANSION $E9
    DREAM_SHRINE,           // MAP_DREAM_SHRINE      $13 (Mabe Village)
    WATER_FLOODED_GROTTO,   // MAP_CAVE_WATER        $1F / ROOM_INDOOR_A_WATER_FLOODED_GROTTO $F2
    QUICKSAND_CAVE,         // ROOM_INDOOR_A_QUICKSAND_CAVE   $F8 (Yarna Desert)
    GORIYA_CAVE,            // ROOM_INDOOR_A_GORIYA           $F5
    MOUNTAIN_CAVE,          // ROOM_INDOOR_B_MOUNTAIN_CAVE_ROOM_1..4 ($7A-$7D, Tal Tal Heights)
    MERMAID_CAVE,           // ROOM_INDOOR_B_UNDER_MERMAID_STATUE $97
    BOWWOW_HIDEOUT,         // MAP_BOWWOW_HIDEOUT    $15 (MeowMeow's yard, Mabe Village)
    GHOST_HOUSE,            // MAP_GHOST_HOUSE       $1E (Animal Village ghost's former home)
    TOOL_SHOP,              // MAP_SHOP              $0E (Mabe Village)
    TRENDY_GAME,            // MAP_MINIGAME          $0F / ROOM_INDOOR_B_TRENDY_MINIGAME $A0
    CAMERA_SHOP,            // ROOM_INDOOR_B_CAMERA_SHOP     $B5 / ROOM_OW_CAMERA_SHOP $37
    FISHING_POND,           // ROOM_INDOOR_B_FISHING_MINIGAME $B1
    MANBOS_POND,            // ROOM_INDOOR_B_MANBO           $FD (cave where Manbo teaches warp song)
    VILLAGE_LIBRARY,        // MAP_LIBRARY           $1D
    MARIN_HOUSE,            // ROOM_INDOOR_B_MARIN_HOUSE     $A3 (Mabe Village)
    MRS_MEOW_MEOW_HOUSE,    // ROOM_INDOOR_B_MRS_MEOW_MEOW   $A7 (Mabe Village)
    MR_WRITE_HOUSE,         // ROOM_INDOOR_B_SCHULE_HOUSE    $DD (Ukuku Prairie)
    CHRISTINES_HOUSE,       // ROOM_INDOOR_B_CHRISTINE_HOUSE $D9 (Animal Village)
    ULRIRA_HOUSE,           // ROOM_OW_ULRIRA_HOUSE          $B1 (Mabe Village)
    FISHERMAN_UNDER_BRIDGE, // ROOM_INDOOR_B_FISHERMAN_UNDER_BRIDGE $F5
    DOG_HOUSE,              // MAP_DOGHOUSE          $12
    RICHARDS_VILLA,         // UNKNOWN_ROOM_C7 (Pothole Field / south of Ukuku Prairie)
    OVERWORLD,
    COUNT
    // TODO: Fill this enum with all locations
};

} // namespace zelda::core
