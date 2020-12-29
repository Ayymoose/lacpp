#pragma once

#include "Renderable.h"
#include "Controllable.h"
#include "Resource.h"
#include "Depth.h"
#include "Renderer.h"
#include "Keyboard.h"
#include "InputControl.h"
#include "Controller.h"
#include "Engine.h"
#include "Clock.h"

namespace Zelda
{

    enum LocationName
    {
        LN_TAIL_CAVE,
        LN_BOTTLE_GROTTO,
        LN_KEY_CAVERN,
        LN_ANGLER_TUNNEL,
        LN_CATFISH_MAW,
        LN_FACE_SHRINE,
        LN_EAGLE_TOWER,
        LN_TURTLE_ROCK,
        LN_WINDFISH_EGG,
        LN_SALE_HOUSE_BANANA,
        LN_POTHOLE_FIELD,
        LN_HOUSE_BY_THE_BAY,
        LN_TRENDY_GAME,
        LN_TOWN_TOOL_SHOP,
        LN_MARIN_AND_TARIN_HOUSE,
        LN_WITCH_HUT,
        LN_YARNA_DESERT,
        LN_UKUKU_PRAIRIE,
        LN_MYSTERIOUS_WOODS,
        LN_MT_TAMARANCH,
        LN_TAL_TAL_MOUNTAIN_RANGE,
        LN_SIGNPOST_MAZE,
        LN_MABE_VILLAGE,
        LN_ANIMAL_VILLAGE,
        LN_CEMETERY,
        LN_RAPIDS_RIDE,
        LN_KOHOLINT_PRAIRIE,
        LN_TORONBO_SHORES,
        LN_MARTHA_BAY,
        LN_EAST_OF_THE_BAY,
        LN_GOPONGA_SWAMP,
        LN_SHRINE,
        LN_KANALET_CASTLE,
        LN_TAL_TAL_HEIGHTS,
        LN_TABAHL_WASTELANDS,
        LN_SOUTH_OF_THE_VILLAGE,
        LN_FISHING_POND,
        LN_MADAM_MEOWMEOW_HOUSE,
        LN_OLD_MAN_ULRIRA_HOUSE,
        LN_WEIRD_MR_WRITE,
        LN_CRAZY_TRACY_HOUSE,
        LN_QUADRUPULETS_HOUSE,
        LN_DREAM_SHRINE,
        LN_TELEPHONE_BOOTH,
        LN_SEASHELL_MANSION,
        LN_RICHARD_VILLA,
        LN_HEN_HOUSE,
        LN_VILLAGE_LIBRARY,
        LN_RAFT_SHOP,
        LN_PHOTO_SHOP
    };

    // One of 4 location types
    enum LocationType
    {
        LT_NONE,
        LT_SHOP,
        LT_OWL,
        LT_DUNGEON,
        LT_UNKNOWN
    };

    typedef struct
    {
        bool visited;                   // Did we visit this location
        LocationType locationType;      // Type of the location (see above)
        LocationName locationName;      // The name of the location
    } WorldmapLocation;

    enum WorldmapSprites
    {
        WORLDMAP_AREA_UNVISITED = 0,
        WORLDMAP_AREA_ARROW,
        WORLDMAP_AREA_SCOPE,
        WORLDMAP_AREA_SHOP,
        WORLDMAP_AREA_UNKNOWN,
        WORLDMAP_AREA_DUNGEON,
        WORLDMAP_AREA_OWL,
        WORLDMAP_AREA_LOCATION
    };

    // Worldmap dimensions
    constexpr int WORLDMAP_MAX_X = 16;
    constexpr int WORLDMAP_MAX_Y = 16;

    // Starting point of (0,0) on top left of map
    constexpr int WORLDMAP_START_X = 17;
    constexpr int WORLDMAP_START_Y = 9;

    // Initial starting position of scope (Marin and Tarin house)
    constexpr uint8_t WORLDMAP_INITIAL_POS_X = 2;
    constexpr uint8_t WORLDMAP_INITIAL_POS_Y = 8;

    #define WORLDMAP_SELECTOR_FPS (1.0f / 4.0f)

    class Worldmap : public Controllable, public Renderable
    {
    public:
        Worldmap();
        void control() noexcept override;
        void render(SDL_Renderer* renderer) noexcept override;
        void open() noexcept;
        void close() noexcept;
    private:
        // 16x16 world map
        // TODO: Update with correct place  names and locations
        WorldmapLocation m_worldmapLocation[WORLDMAP_MAX_X][WORLDMAP_MAX_Y] =
        {
            {{true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE}, {true, LT_DUNGEON, LN_TURTLE_ROCK},        {true, LT_NONE, LN_GOPONGA_SWAMP},   {true, LT_UNKNOWN, LN_WEIRD_MR_WRITE}, {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_NONE, LN_MYSTERIOUS_WOODS},       {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_NONE, LN_MABE_VILLAGE},               {true, LT_UNKNOWN, LN_VILLAGE_LIBRARY},     {true, LT_NONE, LN_SOUTH_OF_THE_VILLAGE}, {true, LT_NONE, LN_SOUTH_OF_THE_VILLAGE},{true, LT_NONE, LN_TORONBO_SHORES},     {true, LT_NONE, LN_TORONBO_SHORES}},
            {{true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE}, {true, LT_UNKNOWN, LN_TELEPHONE_BOOTH},    {true, LT_NONE, LN_GOPONGA_SWAMP},   {true, LT_UNKNOWN, LN_TELEPHONE_BOOTH},{true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_SHOP, LN_FISHING_POND},           {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_UNKNOWN, LN_MADAM_MEOWMEOW_HOUSE},    {true, LT_UNKNOWN, LN_OLD_MAN_ULRIRA_HOUSE},{true, LT_NONE, LN_SOUTH_OF_THE_VILLAGE}, {true, LT_NONE, LN_SOUTH_OF_THE_VILLAGE},{true, LT_NONE, LN_TORONBO_SHORES},     {true, LT_NONE, LN_TORONBO_SHORES}},
            {{true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE}, {true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE},{true, LT_NONE, LN_GOPONGA_SWAMP},   {true, LT_NONE, LN_GOPONGA_SWAMP},     {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_UNKNOWN, LN_QUADRUPULETS_HOUSE},  {true, LT_NONE, LN_MABE_VILLAGE},       {true, LT_UNKNOWN, LN_MARIN_AND_TARIN_HOUSE},   {true, LT_UNKNOWN, LN_TELEPHONE_BOOTH},     {true, LT_NONE, LN_SOUTH_OF_THE_VILLAGE}, {true, LT_NONE, LN_SOUTH_OF_THE_VILLAGE},{true, LT_NONE, LN_TORONBO_SHORES},     {true, LT_NONE, LN_TORONBO_SHORES}},
            {{true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE}, {true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE},{true, LT_NONE, LN_GOPONGA_SWAMP},   {true, LT_NONE, LN_GOPONGA_SWAMP},     {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_NONE, LN_MYSTERIOUS_WOODS},   {true, LT_UNKNOWN, LN_DREAM_SHRINE},        {true, LT_SHOP, LN_TOWN_TOOL_SHOP},     {true, LT_NONE, LN_MABE_VILLAGE},               {true, LT_SHOP, LN_TRENDY_GAME},            {true, LT_NONE, LN_SOUTH_OF_THE_VILLAGE}, {true, LT_DUNGEON, LN_TAIL_CAVE},        {true, LT_SHOP, LN_SALE_HOUSE_BANANA},  {true, LT_NONE, LN_TORONBO_SHORES}},
            {{true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE}, {true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE},{true, LT_DUNGEON, LN_BOTTLE_GROTTO},{true, LT_NONE, LN_GOPONGA_SWAMP},     {true, LT_NONE, LN_KOHOLINT_PRAIRIE},   {true, LT_NONE, LN_KOHOLINT_PRAIRIE},   {true, LT_NONE, LN_KOHOLINT_PRAIRIE},   {true, LT_NONE, LN_KOHOLINT_PRAIRIE},   {true, LT_NONE, LN_UKUKU_PRAIRIE},          {true, LT_NONE, LN_UKUKU_PRAIRIE},      {true, LT_UNKNOWN, LN_TELEPHONE_BOOTH},         {true, LT_NONE, LN_UKUKU_PRAIRIE},          {true, LT_NONE, LN_SIGNPOST_MAZE},        {true, LT_NONE, LN_SIGNPOST_MAZE},       {true, LT_NONE, LN_TORONBO_SHORES},     {true, LT_NONE, LN_TORONBO_SHORES}},
            {{true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE}, {true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE},{true, LT_NONE, LN_TAL_TAL_HEIGHTS}, {true, LT_NONE, LN_TAL_TAL_HEIGHTS},   {true, LT_SHOP, LN_CRAZY_TRACY_HOUSE},  {true, LT_NONE, LN_KOHOLINT_PRAIRIE},   {true, LT_SHOP, LN_WITCH_HUT},          {true, LT_NONE, LN_KOHOLINT_PRAIRIE},   {true, LT_NONE, LN_UKUKU_PRAIRIE},          {true, LT_NONE, LN_UKUKU_PRAIRIE},      {true, LT_NONE, LN_UKUKU_PRAIRIE},              {true, LT_DUNGEON, LN_KEY_CAVERN},          {true, LT_NONE, LN_SIGNPOST_MAZE},        {true, LT_NONE, LN_SIGNPOST_MAZE},       {true, LT_NONE, LN_TORONBO_SHORES},     {true, LT_NONE, LN_TORONBO_SHORES}},
            {{true, LT_UNKNOWN, LN_WINDFISH_EGG},        {true, LT_NONE, LN_MT_TAMARANCH},          {true, LT_NONE, LN_TAL_TAL_HEIGHTS}, {true, LT_NONE, LN_TAL_TAL_HEIGHTS},   {true, LT_NONE, LN_TABAHL_WASTELANDS},  {true, LT_NONE, LN_TABAHL_WASTELANDS},  {true, LT_NONE, LN_CEMETERY},           {true, LT_NONE, LN_CEMETERY},           {true, LT_NONE, LN_UKUKU_PRAIRIE},          {true, LT_NONE, LN_UKUKU_PRAIRIE},      {true, LT_NONE, LN_UKUKU_PRAIRIE},              {true, LT_NONE, LN_UKUKU_PRAIRIE},          {true, LT_NONE, LN_POTHOLE_FIELD},        {true, LT_UNKNOWN, LN_RICHARD_VILLA},    {true, LT_NONE, LN_MARTHA_BAY},         {true, LT_UNKNOWN, LN_HOUSE_BY_THE_BAY}},
            {{true, LT_NONE, LN_MT_TAMARANCH},           {true, LT_NONE, LN_MT_TAMARANCH},          {true, LT_NONE, LN_TAL_TAL_HEIGHTS}, {true, LT_SHOP, LN_PHOTO_SHOP},        {true, LT_NONE, LN_TABAHL_WASTELANDS},  {true, LT_NONE, LN_TABAHL_WASTELANDS},  {true, LT_NONE, LN_CEMETERY},           {true, LT_NONE, LN_CEMETERY},           {true, LT_NONE, LN_UKUKU_PRAIRIE},          {true, LT_NONE, LN_UKUKU_PRAIRIE},      {true, LT_NONE, LN_UKUKU_PRAIRIE},              {true, LT_NONE, LN_UKUKU_PRAIRIE},          {true, LT_NONE, LN_POTHOLE_FIELD},        {true, LT_NONE, LN_POTHOLE_FIELD},       {true, LT_NONE, LN_MARTHA_BAY},         {true, LT_NONE, LN_MARTHA_BAY}},
            {{true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE}, {true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE},{true, LT_NONE, LN_TAL_TAL_HEIGHTS}, {true, LT_NONE, LN_TAL_TAL_HEIGHTS},   {true, LT_NONE, LN_KANALET_CASTLE},     {true, LT_NONE, LN_KANALET_CASTLE},     {true, LT_NONE, LN_KANALET_CASTLE},     {true, LT_NONE, LN_KANALET_CASTLE},     {true, LT_UNKNOWN, LN_TELEPHONE_BOOTH},     {true, LT_NONE, LN_UKUKU_PRAIRIE},      {true, LT_NONE, LN_UKUKU_PRAIRIE},              {true, LT_NONE, LN_UKUKU_PRAIRIE},          {true, LT_NONE, LN_MARTHA_BAY},           {true, LT_NONE, LN_MARTHA_BAY},          {true, LT_UNKNOWN, LN_TELEPHONE_BOOTH}, {true, LT_NONE, LN_MARTHA_BAY}},
            {{true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE}, {true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE},{true, LT_NONE, LN_TAL_TAL_HEIGHTS}, {true, LT_NONE, LN_TAL_TAL_HEIGHTS},   {true, LT_NONE, LN_KANALET_CASTLE},     {true, LT_NONE, LN_KANALET_CASTLE},     {true, LT_NONE, LN_KANALET_CASTLE},     {true, LT_NONE, LN_KANALET_CASTLE},     {true, LT_NONE, LN_UKUKU_PRAIRIE},          {true, LT_NONE, LN_UKUKU_PRAIRIE},      {true, LT_NONE, LN_UKUKU_PRAIRIE},              {true, LT_NONE, LN_UKUKU_PRAIRIE},          {true, LT_NONE, LN_MARTHA_BAY},           {true, LT_DUNGEON, LN_CATFISH_MAW},      {true, LT_NONE, LN_MARTHA_BAY},         {true, LT_NONE, LN_MARTHA_BAY}},
            {{true, LT_SHOP, LN_HEN_HOUSE},              {true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE},{true, LT_NONE, LN_TAL_TAL_HEIGHTS}, {true, LT_NONE, LN_TAL_TAL_HEIGHTS},   {true, LT_NONE, LN_KANALET_CASTLE},     {true, LT_NONE, LN_KANALET_CASTLE},     {true, LT_NONE, LN_KANALET_CASTLE},     {true, LT_NONE, LN_KANALET_CASTLE},     {true, LT_UNKNOWN, LN_SEASHELL_MANSION},    {true, LT_NONE, LN_UKUKU_PRAIRIE},      {true, LT_NONE, LN_UKUKU_PRAIRIE},              {true, LT_NONE, LN_UKUKU_PRAIRIE},          {true, LT_NONE, LN_MARTHA_BAY},           {true, LT_NONE, LN_MARTHA_BAY},          {true, LT_NONE, LN_MARTHA_BAY},         {true, LT_NONE, LN_MARTHA_BAY}},
            {{true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE}, {true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE},{true, LT_DUNGEON, LN_ANGLER_TUNNEL},{true, LT_NONE, LN_TAL_TAL_HEIGHTS},   {true, LT_UNKNOWN, LN_TELEPHONE_BOOTH}, {true, LT_NONE, LN_KANALET_CASTLE},     {true, LT_NONE, LN_KANALET_CASTLE},     {true, LT_NONE, LN_KANALET_CASTLE},     {true, LT_NONE, LN_UKUKU_PRAIRIE},          {true, LT_NONE, LN_UKUKU_PRAIRIE},      {true, LT_NONE, LN_UKUKU_PRAIRIE},              {true, LT_NONE, LN_UKUKU_PRAIRIE},          {true, LT_NONE, LN_MARTHA_BAY},           {true, LT_UNKNOWN, LN_TELEPHONE_BOOTH},  {true, LT_NONE, LN_MARTHA_BAY},         {true, LT_NONE, LN_MARTHA_BAY}},
            {{true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE}, {true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE},{true, LT_NONE, LN_TAL_TAL_HEIGHTS}, {true, LT_NONE, LN_TAL_TAL_HEIGHTS},   {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_DUNGEON, LN_FACE_SHRINE},         {true, LT_NONE, LN_SHRINE},             {true, LT_NONE, LN_SHRINE},                     {true, LT_NONE, LN_SHRINE},                 {true, LT_NONE, LN_ANIMAL_VILLAGE},       {true, LT_NONE, LN_ANIMAL_VILLAGE},      {true, LT_NONE, LN_EAST_OF_THE_BAY},    {true, LT_NONE, LN_EAST_OF_THE_BAY}},
            {{true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE}, {true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE},{true, LT_NONE, LN_TAL_TAL_HEIGHTS}, {true, LT_NONE, LN_TAL_TAL_HEIGHTS},   {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_SHRINE},                 {true, LT_NONE, LN_SHRINE},             {true, LT_NONE, LN_SHRINE},                     {true, LT_NONE, LN_SHRINE},                 {true, LT_NONE, LN_ANIMAL_VILLAGE},       {true, LT_NONE, LN_ANIMAL_VILLAGE},      {true, LT_NONE, LN_EAST_OF_THE_BAY},    {true, LT_NONE, LN_EAST_OF_THE_BAY}},
            {{true, LT_DUNGEON, LN_EAGLE_TOWER},         {true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE},{true, LT_NONE, LN_TAL_TAL_HEIGHTS}, {true, LT_NONE, LN_TAL_TAL_HEIGHTS},   {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_RAPIDS_RIDE},            {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_SHRINE},                     {true, LT_NONE, LN_SHRINE},                 {true, LT_NONE, LN_YARNA_DESERT},         {true, LT_NONE, LN_YARNA_DESERT},        {true, LT_NONE, LN_YARNA_DESERT},       {true, LT_NONE, LN_YARNA_DESERT}},
            {{true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE}, {true, LT_NONE, LN_TAL_TAL_MOUNTAIN_RANGE},{true, LT_NONE, LN_TAL_TAL_HEIGHTS}, {true, LT_SHOP, LN_RAFT_SHOP},         {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_RAPIDS_RIDE},            {true, LT_NONE, LN_RAPIDS_RIDE},        {true, LT_NONE, LN_SHRINE},                     {true, LT_NONE, LN_SHRINE},                 {true, LT_NONE, LN_YARNA_DESERT},         {true, LT_NONE, LN_YARNA_DESERT},        {true, LT_NONE, LN_YARNA_DESERT},       {true, LT_NONE, LN_YARNA_DESERT}}
        };
        uint8_t m_scopeX;
        uint8_t m_scopeY;
        bool m_show;

        Clock m_scopeSelectTimer;
        bool m_scopeSelect;

        // Position of Link in the worldmap
        uint8_t m_worldX;
        uint8_t m_worldY;

        SDL_Rect m_worldmapSrcSprites[8] =
        {
            {110,162,7,7},   // WORLDMAP_AREA_UNVISITED
            {100,162,9,8},   // WORLDMAP_AREA_ARROW
            {108,84,16,16},   // WORLDMAP_AREA_SCOPE
            {140,130,30,30},   // WORLDMAP_AREA_SHOP
            {170,130,30,30},   // WORLDMAP_AREA_UNKNOWN
            {200,130,30,30},   // WORLDMAP_AREA_DUNGEON
            {230,130,30,30},   // WORLDMAP_AREA_OWL
            {110,152,8,8} // WORLDMAP_AREA_LOCATION
        };
    };

}