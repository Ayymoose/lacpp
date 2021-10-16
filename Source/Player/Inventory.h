#pragma once

#include "Controllable.h"
#include "Renderable.h"
#include "Vector.h"
#include "Camera.h"

namespace Zelda
{
// Initial selector position and increases
constexpr int SELECTOR_INITIAL_X = 6;
constexpr int SELECTOR_INITIAL_Y = 26;
constexpr int SELECTOR_INCREASE_X = 32;
constexpr int SELECTOR_INCREASE_Y = 23;

// Maximum "storable" items in inventory
constexpr int INVENTORY_MAX_WEAPONS = 10;

// The entire inventory
constexpr int INVENTORY_INTERNAL_X = 0;
constexpr int INVENTORY_INTERNAL_Y = 21;
constexpr int INVENTORY_WIDTH = CAMERA_WIDTH;
constexpr int INVENTORY_HEIGHT = CAMERA_WIDTH - HUD_HEIGHT; // Because of the HUD being at the top of the screen

// Inventory dividers horizontal/vertical
constexpr int INVENTORY_DIVIDER_XH = 0;
constexpr int INVENTORY_DIVIDER_YH = 18;
constexpr int INVENTORY_DIVIDER_XV = 67;
constexpr int INVENTORY_DIVIDER_YV = 24;
constexpr int INVENTORY_DIVIDER_WIDTH_H = 7;
constexpr int INVENTORY_DIVIDER_HEIGHT_H = 3;
constexpr int INVENTORY_DIVIDER_WIDTH_V = 3;
constexpr int INVENTORY_DIVIDER_HEIGHT_V = 7;

// Sprite width/height of the inventory items
constexpr int INVENTORY_SPRITE_WIDTH = 8;
constexpr int INVENTORY_SPRITE_HEIGHT = 16;

// Initial position of the inventory sprite item
constexpr int INVENTORY_POS_X = 8;
constexpr int INVENTORY_POS_Y = 25;

// Spacing between each inventory sprite item on the lhs
constexpr int INVENTORY_X_SPACING = 32;
constexpr int INVENTORY_Y_SPACING = 23;

// RGB components of inventory colour
constexpr int INVENTORY_R = 248;
constexpr int INVENTORY_G = 248;
constexpr int INVENTORY_B = 168;

// Item limits
// TODO: This acually changes throughout the game IIRC
constexpr int BOMBS_MAX = 50;
constexpr int MAGIC_POWDER_MAX = 50;
constexpr int ARROWS_MAX = 30;

// Except for this
constexpr int RUPPEES_MAX = 999;

// The width/height of the weapon level sprite
constexpr int WEAPON_LEVEL_X = 16;
constexpr int WEAPON_LEVEL_Y = 33;
constexpr int WEAPON_LEVEL_SPACING_X = 32;
constexpr int WEAPON_LEVEL_SPACING_Y = 23;
constexpr int WEAPON_LEVEL_WIDTH = 8;
constexpr int WEAPON_LEVEL_HEIGHT = 8;

// Subscreen constants
constexpr int SELECT_SUBSCREEN_WIDTH = 80;
constexpr int SELECT_SUBSCREEN_HEIGHT = 32;

// Hearts per row
constexpr int HEARTS_PER_ROW = 7;
constexpr int HEARTS_PIECE_MAX = 4;

// Maximum photographs we are allowed
constexpr int MAX_PHOTOGRAPHS = 12;

// Animation stuff
constexpr int INSTRUMENTS_FRAME = 12;

// Dungeon map
constexpr int DUNGEON_MAX_BLOCKS_X = 9;
constexpr int DUNGEON_MAX_BLOCKS_Y = 9;

constexpr float INVENTORY_SELECTOR_FPS = (1.0f / 4.0f);
constexpr float INSTRUMENT_FPS = (1.0f / 6.0f);
constexpr float PUSH_SELECTOR_FPS = (1.0f / 2.0f);

// The order of these items matters as we use them to index the sprite src rect from the sprite sheet
enum WeaponItem
{
    WPN_NONE = -1,
    WPN_SWORD = 0,
    WPN_SHIELD,
    WPN_BOW,
    WPN_BOOMERANG,
    WPN_MAGIC_POWDER,
    WPN_BOMBS,
    WPN_POWER_BRACELET,
    // 
    WPN_ROC_FEATHER,
    WPN_HOOKSHOT,
    WPN_OCARINA,
    WPN_PEGASUS_BOOT,
    WPN_SHOVEL,
    WPN_FLAME_ROD,
    WPN_COUNT
};

enum WeaponLevel
{
    WPN_LEVEL_NONE = -1,
    WPN_LEVEL_1 = 1,
    WPN_LEVEL_2,
    WPN_LEVEL_COUNT
};

enum class OcarinaSong
{
    SNG_NONE = -1,
    SNG_MARIN = 1,
    SNG_FROG,
    SNG_FISH,
    SNG_COUNT
};

enum InventorySprites
{
    INVENTORY_DIVIDER_H = WPN_COUNT + 1, // +1 because I removed the power-bracelet 2
    INVENTORY_DIVIDER_V,
    INVENTORY_B_BUTTON,
    INVENTORY_A_BUTTON,
    INVENTORY_SELECTOR_BUTTON_1,
    INVENTORY_SELECTOR_BUTTON_2,
    INVENTORY_RUPPEE,
    INVENTORY_LEVEL,
    INVENTORY_DIGIT_B,
    INVENTORY_DIGIT_W,
    INVENTORY_HEART_WHOLE,
    INVENTORY_INSTRUMENT_BACK_0,
    INVENTORY_INSTRUMENT_BACK_1,
    INVENTORY_INSTRUMENT_BACK_2,
    INVENTORY_INSTRUMENT_BACK_3,
    INVENTORY_INSTRUMENT_BACK_4,
    INVENTORY_INSTRUMENT_BACK_5,
    INVENTORY_INSTRUMENT_BACK_6,
    INVENTORY_INSTRUMENT_BACK_7,
    INVENTORY_INSTRUMENT_0,
    INVENTORY_INSTRUMENT_1,
    INVENTORY_INSTRUMENT_2,
    INVENTORY_INSTRUMENT_3,
    INVENTORY_INSTRUMENT_4,
    INVENTORY_INSTRUMENT_5,
    INVENTORY_INSTRUMENT_6,
    INVENTORY_INSTRUMENT_7,
    INVENTORY_COMPASS,
    INVENTORY_NIGHTMARE_KEY,
    INVENTORY_OWL_BEAK,
    INVENTORY_DUNGEON_MAP,
    INVENTORY_DUNGEON_KEY,
    INVENTORY_FLIPPERS,
    INVENTORY_POTION,
    INVENTORY_SEASHELLS,
    INVENTORY_DOLL,
    INVENTORY_BOW,
    INVENTORY_DOG_FOOD,
    INVENTORY_BANANAS,
    INVENTORY_STICK,
    INVENTORY_HONEYCOMB,
    INVENTORY_PINEAPPLE,
    INVENTORY_HIBISCUS,
    INVENTORY_LETTER,
    INVENTORY_BROOM,
    INVENTORY_HOOK,
    INVENTORY_NECKLACE,
    INVENTORY_MERMAID_SCALE,
    INVENTORY_LENS,
    INVENTORY_TAIL_KEY,
    INVENTORY_SLIME_KEY,
    INVENTORY_ANGLER_KEY,
    INVENTORY_FACE_KEY,
    INVENTORY_BIRD_KEY,
    INVENTORY_RED_ARROW,
    INVENTORY_PUSH_SELECT,
    INVENTORY_SUBSCREEN,
    INVENTORY_TUNIC,
    INVENTORY_HEART_PIECES,
    INVENTORY_PHOTOGRAPHS,
    INVENTORY_SLASH,

    INVENTORY_AREA_EXIT_RIGHT,
    INVENTORY_AREA_EXIT_LEFT,
    INVENTORY_AREA_EXIT_RIGHT_DOWN,
    INVENTORY_AREA_EXIT_LEFT_DOWN,
    INVENTORY_AREA_EXIT_NONE,
    INVENTORY_AREA_EXIT_LEFT_UP_RIGHT,
    INVENTORY_AREA_EXIT_LEFT_DOWN_RIGHT,
    INVENTORY_AREA_UNVISITED,
    INVENTORY_AREA_EXIT_LEFT_RIGHT,
    INVENTORY_AREA_TREASURE,
    INVENTORY_AREA_NIGHTMARE,
    INVENTORY_AREA_EXIT_DOWN,
    INVENTORY_AREA_EXIT_UP,
    INVENTORY_AREA_EXIT_UP_RIGHT,
    INVENTORY_AREA_EXIT_LEFT_UP,
    INVENTORY_AREA_EXIT_ALL,
    INVENTORY_AREA_EXIT_UP_RIGHT_DOWN,
    INVENTORY_AREA_EXIT_UP_LEFT_DOWN,
    INVENTORY_AREA_EMPTY,
    INVENTORY_AREA_EXIT_UP_DOWN,
    INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW,
    INVENTORY_DUNGEON_MAP_CURRENT_LOCATION,

    INVENTORY_ARROW,

    INVENTORY_COUNT
};

enum Instrument
{
    INSTRUMENT_NONE = -1,
    FULL_MOON_CELLO,
    CONCH_HORN,
    SEA_LILY_BELL,
    SURF_HARP,
    WIND_MARIMBA,
    CORAL_TRIANGLE,
    ORGAN_OF_EVENING_CALM,
    THUNDER_DRUM,
    INSTRUMENT_COUNT
};

enum TradeItem
{
    ITEM_NONE = -1,
    ITEM_DOLL,
    ITEM_BOW,
    ITEM_DOG_FOOD,
    ITEM_BANANAS,
    ITEM_STICK,
    ITEM_HONEYCOMB,
    ITEM_PINEAPPLE,
    ITEM_HIBISCUS,
    ITEM_LETTER,
    ITEM_BROOM,
    ITEM_HOOK,
    ITEM_NECKLACE,
    ITEM_MERMAID_SCALE,
    ITEM_LENS,
    ITEM_COUNT
};

enum class Tunic
{
    TUNIC_NONE = -1,
    TUNIC_GREEN,
    TUNIC_RED,
    TUNIC_BLUE,
    TUNIC_COUNT
};

enum HeartPiece
{
    HEART_NONE = -1,
    HEART_ZERO = 0,
    HEART_ONE_QUARTER,
    HEART_HALF,
    HEART_THREE_QUARTER,
    HEART_FULL,
    HEART_COUNT
};

enum Dungeon
{
    DUNGEON_NONE = -1,
    DUNGEON_COLOUR_DUNGEON,
    DUNGEON_TAIL_CAVE,
    DUNGEON_BOTTLE_GROTTO,
    DUNGEON_KEY_CAVERN,
    DUNGEON_ANGLER_TUNNEL,
    DUNGEON_CATFISH_MAW,
    DUNGEON_FACE_SHRINE,
    DUNGEON_EAGLE_TOWER,
    DUNGEON_TURTLE_ROCK,
    DUNGEON_COUNT
};

enum DungeonKey
{
    KEY_NONE = -1,
    KEY_TAIL,
    KEY_SLIME,
    KEY_ANGLER,
    KEY_FACE,
    KEY_BIRD,
    KEY_COUNT
};

enum class DungeonItem
{
    ITEM_KEY,
    ITEM_COMPASS,
    ITEM_MAP,
    ITEM_NIGHTMARE_KEY,
    ITEM_OWL_BEAK
};

enum class DungeonRoomItem
{
    ITEM_NONE = -1,
    ITEM_CHEST_CLOSED,
    ITEM_CHEST_OPEN,
    ITEM_NIGHTMARE_KEY
};


enum InventoryMiscItem
{
    ITEM_RED_POTION,
    ITEM_FLIPPERS
};

struct DungeonMapEntry
{
    uint8_t roomType;
    bool visited;
    DungeonRoomItem roomItem;
};

enum Ruppee
{
    RUPPEE_ONE = 1,
    RUPPEE_FIVE = 5,
    RUPPEE_TEN = 10,
    RUPPEE_TWENTY = 20,
    RUPPEE_FIFTY = 50,
    RUPPEE_HUNDRED = 100,
    RUPPEE_TWO_HUNDRED = 200
};

#define TRADE_ITEM_SPRITE(ITEM) (INVENTORY_DOLL + ITEM)

using InventoryWeapon = std::pair<WeaponItem, WeaponLevel>;

class Inventory : public Renderable, public Controllable
{
public:
    Inventory();
    void control(double ts) noexcept override;
    void render() noexcept override;
    void update() noexcept override;
    void open() noexcept;
    void close() noexcept;

    bool magicPowder() const noexcept;
    bool arrows() const noexcept;
    bool bombs() const noexcept;

    void addItemQuantity(WeaponItem item, int quantity) noexcept;
    void addItem(const InventoryWeapon& inventoryWeapon) noexcept;
    void addItem(DungeonKey dungeonKey) noexcept;
    void addItem(DungeonItem dungeonItem) noexcept;
    void addItem(TradeItem tradeItem) noexcept;
    void addItem(InventoryMiscItem inventoryMiscItem) noexcept;
    void addItem(Instrument instrument) noexcept;
    void addItem(Ruppee ruppees) noexcept;
    void addItem(Tunic tunic) noexcept;
    void addItem(HeartPiece heartPiece) noexcept;
    void addItem(int photograph) noexcept;

    void useItem(DungeonItem dungeonItem) noexcept;
    void useItem(InventoryMiscItem inventoryMiscItem) noexcept;

    void removeItem(const InventoryWeapon& inventoryWeapon) noexcept;
    WeaponLevel itemLevel(WeaponItem item) const noexcept;

    void inDungeon(bool inside) noexcept;

    void useMagicPowder() noexcept;
    void useBowAndArrow() noexcept;
    void useBombs() noexcept;

    bool shieldEquipped() const noexcept;

    InventoryWeapon weaponA() const noexcept;
    InventoryWeapon weaponB() const noexcept;

    // Set position of current location marker for dungeon
    void setDungeonLocationMarker(int x, int y) noexcept;
    void getDungeonMap(Dungeon dungeon, DungeonMapEntry(&dungeonMapEntry)[DUNGEON_MAX_BLOCKS_X][DUNGEON_MAX_BLOCKS_Y]) const noexcept;
    void setDungeonMapEntry(const int x, const int y, const DungeonMapEntry& dungeonMapEntry) noexcept;


    void drawSubscreen() const noexcept;
    void moveSelectorRight() noexcept;
    void moveSelectorUp() noexcept;
    void moveSelectorDown() noexcept;
    void moveSelectorLeft() noexcept;

private:

    void drawDungeonMap(SDL_Renderer* renderer) noexcept;
    void drawSelectStatus(SDL_Renderer* renderer) noexcept;
    void drawMiscItems(SDL_Renderer* renderer) noexcept;
    void drawInventoryItems(SDL_Renderer* renderer) noexcept;
    void drawDungeonItems(SDL_Renderer* renderer) noexcept;
    void drawInstruments(SDL_Renderer* renderer) noexcept;
    void drawHealth(SDL_Renderer* renderer) noexcept;
    void drawInventoryWeapons(SDL_Renderer* renderer) noexcept;
    void drawSelector(SDL_Renderer* renderer) noexcept;
    void drawInventoryDividers(SDL_Renderer* renderer) noexcept;
    void drawHUD(SDL_Renderer* renderer) noexcept;
    

    void drawNumber(SDL_Renderer* renderer, SDL_Texture* srcTexture, bool drawLevel, bool useNormalFont, int trailingDigits, int number, SDL_Rect* dstRect) const noexcept;
    void drawWeaponLevel(SDL_Renderer* renderer, SDL_Texture* srcTexture, WeaponItem weapon, SDL_Rect* dstRect) noexcept;

    SDL_Texture* m_subscreen;   // The select status at the bottom of the screen
    TradeItem m_tradeItem;      // Current trade item


    // TODO: Golden leaves in Kanalet castle
    // TODO: Flashing instrument background
    // TODO: Dungeon map hidden room connections when discovered
    // TODO: Ocarina song selection window
    // TODO: Chest and nightmare locations for each dungeon map
    // TODO: Every other dungeon map layout
    // TODO: Transition the subscreen
    // TODO: Inventory whiteout


    bool m_open;

    // Dungeon related items
    bool m_inDungeon;    // Are we in a dungeon? 

    // The keys used to open dungeon entrances
    DungeonKey m_dungeonEntraceKeys[KEY_COUNT];

    // Dungeon items
    int m_dungeonKeys[DUNGEON_COUNT];  // Number of dungeon keys (small ones)
    bool m_compass[DUNGEON_COUNT];       // Dungeon compass
    bool m_dungeonMap[DUNGEON_COUNT];   // Dungeon map
    bool m_nightmareKey[DUNGEON_COUNT]; // Nightmare boss key
    bool m_owlBeak[DUNGEON_COUNT];      // Owl beak

    // Inventory related variables
    int m_arrows;         // Number of arrows
    int m_bombs;          // Number of bombs
    int m_magicPowder;    // Number of magic powder
    OcarinaSong m_ocarinaSong;    // Ocarina song level
    int m_seashells;      // Number of Seashells
    bool m_flippers;          // Flippers
    bool m_potion;            // Red potion bottle
    Tunic m_tunic;            // Tunic
    int m_heartPieces;    // Heart pieces (0 to 4)
    int m_goldleafs;       // Golden leaves (Shown in Kanalet castle only)
    int m_photographs;

    int m_ruppees;

    // Weapon A and B
    InventoryWeapon m_weaponA;
    InventoryWeapon m_weaponB;

    // Selector position 
    int m_selectorX;
    int m_selectorY;

    // Index into inventory array
    int m_selectorIndex;

    // Timer for flashing the selector
    Timer m_selectorTimer;

    // Weapons
    InventoryWeapon m_weaponItems[INVENTORY_MAX_WEAPONS];
    bool itemExists(const InventoryWeapon& inventoryWeapon) const noexcept;
    bool itemExists(WeaponItem item) const noexcept;
    bool itemExists(DungeonKey dungeonKey) const noexcept;

    // Return the source rect for the given item
    auto inventoryWeaponSpriteSrc(const InventoryWeapon& item) const noexcept;


    // Instruments
    Instrument m_instruments[INSTRUMENT_COUNT];

    Timer m_instrumentTimer;
    Timer m_pushSelectTimer;

    // Key press related stuff
    bool m_flashSelector;
    bool m_flashSelect;
    bool m_selectPressed;

    // Link position in dungeon map as a vector
    Vector<uint8_t> m_dungeonPosition;

    Timer m_dungeonMapPositionTimer;

    // Array of dungeon maps
    /*

    [X][][] Dungeon select

        0 - Colour Dungeon
        1 - Tail Cave
        2 - Bottle Grotto
        3 - Key Cavern
        4 - Anglers Tunnel
        5 - Catfishs Maw
        6 - Face Shrine
        7 - Eagle Tower
        8 - Turtle Rock

    [][X][X] Area state

        0 - Empty (navy square)
        1 - Blank (white inventory coloured block)
        2 - Unvisited navy square
        3 - Treasure chest
        4 - Nightmare location
        5 - Area RIGHT exit only
        6 - Area LEFT exit only
        7 - Area RIGHT and DOWN exit only
        8 - Area LEFT and DOWN exit only
        9 - Area no exit
        10 - Area LEFT UP and RIGHT exit only
        11 - Area LEFT RIGHT DOWN exit only
        12 - Area DOWN exit only
        13 - Area UP exit only
        14 - Area UP and RIGHT exit only
        15 - Area UP and LEFT exit only
        16 - Area all exits
        17 - Area UP RIGHT and DOWN exit only
        18 - Area UP LEFT and DOWN exit only
        19 - Area UP and DOWN exit only
        20 - Area LEFT and RIGHT exit only

        No dungeon map                 -> Empty map
        Dungeon map (no visietd areas) -> Unvisited block on each area
        Visited map                    -> Reveal area block on map

    */


    // Current dungeon we are in
    Dungeon m_dungeon;

    static_assert(DUNGEON_MAX_BLOCKS_X == DUNGEON_MAX_BLOCKS_Y);

    DungeonMapEntry m_dungeonMaps[DUNGEON_COUNT][DUNGEON_MAX_BLOCKS_X][DUNGEON_MAX_BLOCKS_Y] =
    {
        {   // Lvl 0 - Colour dungeon
            { {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE}, {6,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {4,false,DungeonRoomItem::ITEM_NIGHTMARE_KEY},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {3,false,DungeonRoomItem::ITEM_CHEST_CLOSED}, {8,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE},{19,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {19,false,DungeonRoomItem::ITEM_NONE}, {5,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {13,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {14,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {20,false,DungeonRoomItem::ITEM_NONE}, {18,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} }
        },
        {   // Lvl 1 - Tail Cave
            // TODO: Never thought about where the dungeon marker is when Link is in the side-scrolling part of dungeon
            // Maybe it stays at the last point when we are side scrolling
            
            // TODO: Add the treasure remaininng treeassure cheests
            { {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE}, {6,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {19,false,DungeonRoomItem::ITEM_NIGHTMARE_KEY},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_CHEST_CLOSED}, {8,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE},{19,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {19,false,DungeonRoomItem::ITEM_NONE}, {5,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {13,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {14,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {20,false,DungeonRoomItem::ITEM_NONE}, {18,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} }
            // Rooms start at the bottom left of the map here (0,8)
        },
        {   // Lvl 2 - Bottle Grotto
            { {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE}, {6,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {4,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {3,false,DungeonRoomItem::ITEM_NONE}, {8,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE},{19,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {19,false,DungeonRoomItem::ITEM_NONE}, {5,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {13,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {14,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {20,false,DungeonRoomItem::ITEM_NONE}, {18,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} }
        },
        {   // Lvl 3 - Key Cavern
            { {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE}, {6,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {4,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {3,false,DungeonRoomItem::ITEM_NONE}, {8,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE},{19,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {19,false,DungeonRoomItem::ITEM_NONE}, {5,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {13,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {14,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {20,false,DungeonRoomItem::ITEM_NONE}, {18,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} }
        },
        {   // Lvl 4 - Angler Tunnel
            { {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE}, {6,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {4,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {3,false,DungeonRoomItem::ITEM_NONE}, {8,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE},{19,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {19,false,DungeonRoomItem::ITEM_NONE}, {5,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {13,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {14,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {20,false,DungeonRoomItem::ITEM_NONE}, {18,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} }
        },
        {   // Lvl 5 - Catfish Maw
            { {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE}, {6,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {4,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {3,false,DungeonRoomItem::ITEM_NONE}, {8,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE},{19,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {19,false,DungeonRoomItem::ITEM_NONE}, {5,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {13,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {14,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {20,false,DungeonRoomItem::ITEM_NONE}, {18,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} }
        },
        {   // Lvl 6 - Face Shrine
            { {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE}, {6,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {4,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {3,false,DungeonRoomItem::ITEM_NONE}, {8,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE},{19,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {19,false,DungeonRoomItem::ITEM_NONE}, {5,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {13,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {14,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {20,false,DungeonRoomItem::ITEM_NONE}, {18,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} }
        },
        {   // Lvl 7 - Eagle Tower
            { {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE}, {6,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {4,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {3,false,DungeonRoomItem::ITEM_NONE}, {8,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE},{19,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {19,false,DungeonRoomItem::ITEM_NONE}, {5,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {13,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {14,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {20,false,DungeonRoomItem::ITEM_NONE}, {18,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} }
        },
        {   // Lvl 8 - Turtle Rock
            { {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE},  {1,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE}, {6,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {4,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {12,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {3,false,DungeonRoomItem::ITEM_NONE}, {8,false,DungeonRoomItem::ITEM_NONE}, {12,false,DungeonRoomItem::ITEM_NONE},{19,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {19,false,DungeonRoomItem::ITEM_NONE}, {5,false,DungeonRoomItem::ITEM_NONE}, {17,false,DungeonRoomItem::ITEM_NONE}, {10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{10,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {13,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {14,false,DungeonRoomItem::ITEM_NONE}, {11,false,DungeonRoomItem::ITEM_NONE},{15,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} },
            { {0,false,DungeonRoomItem::ITEM_NONE},  {5,false,DungeonRoomItem::ITEM_NONE}, {20,false,DungeonRoomItem::ITEM_NONE}, {18,false,DungeonRoomItem::ITEM_NONE},{0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE}, {0,false,DungeonRoomItem::ITEM_NONE},  {0,false,DungeonRoomItem::ITEM_NONE}, {1,false,DungeonRoomItem::ITEM_NONE} }
        }
    };

    // Inventory sprite positions (source Rect from the sprite sheet)
    SDL_Rect m_inventorySpritesSrc[WPN_COUNT + INVENTORY_COUNT] =
    {
        {10,20,8,16},   // WPN_SWORD
        {0, 20,8,16},   // WPN_SHIELD
        {90,20,8,16},   // WPN_BOW
        {130,20,8,16},  // WPN_BOOMERANG
        {20,20,8,16},   // WPN_MAGIC_POWDER
        {70,20,8,16},   // WPN_BOMBS
        {40,20,8,16},   // WPN_POWER_BRACELET Level 1
        {80,20,8,16},   // WPN_POWER_BRACELET Level 2
        {30,20,8,16},   // WPN_ROC_FEATHER
        {120,20,8,16},  // WPN_HOOKSHOT
        {110,20,8,16},  // WPN_OCARINA
        {50,20,8,16},   // WPN_PEGASUS_BOOT
        {60,20,8,16},   // WPN_SHOVEL
        {100,20,8,16},  // WPN_FLAME_ROD
        {102,126,7,3},  // Inventory divider horizontal
        {110,126,3,7},  // Inventory divider vertical
        {109,116,5,8},  // "B"
        {102,116,5,8},  // "A"
        {72,116,28,14}, // Inventory selector (next to B)
        {72,116,28,14}, // Inventory selector (next to A)
        {116,116,7,7},  // Ruppee icon on HUD
        {0,0,8,8},      // INVENTORY_LEVEL
        {10,10,8,8},    // INVENTORY_DIGIT_B
        {10,0,8,8},     // INVENTORY_DIGIT_W
        {0,38,8,8},     // INVENTORY_HEART_WHOLE
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_0
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_1
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_2
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_3
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_4
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_5
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_6
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_7
        {140,0,16,16},  // INVENTORY_INSTRUMENT_0 
        {140,16,16,16},  // INVENTORY_INSTRUMENT_1
        {140,32,16,16},  // INVENTORY_INSTRUMENT_2
        {140,48,16,16},  // INVENTORY_INSTRUMENT_3
        {140,64,16,16},  // INVENTORY_INSTRUMENT_4
        {140,80,16,16},  // INVENTORY_INSTRUMENT_5
        {140,96,16,16},  // INVENTORY_INSTRUMENT_6
        {140,112,16,16},  // INVENTORY_INSTRUMENT_7
        {120,134,8,16},  // INVENTORY_COMPASS
        {90,134,8,16},  // INVENTORY_NIGHTMARE_KEY
        {130,134,8,16},  // INVENTORY_OWL_BEAK
        {110,134,8,16},  // INVENTORY_DUNGEON_MAP
        {100,134,8,16}, // INVENTORY_DUNGEON_KEY
        {70,134,8,16},  // INVENTORY_FLIPPERS
        {60,134,8,16},  // INVENTORY_POTION
        {80,134,8,16}, // INVENTORY_SEASHELLS
        {0,48,16,16}, // INVENTORY_DOLL
        {18,48,16,16}, // INVENTORY_BOW
        {36,48,16,16}, // INVENTORY_DOG_FOOD
        {54,48,16,16}, // INVENTORY_BANANAS
        {72,48,16,16}, // INVENTORY_STICK
        {90,48,16,16}, // INVENTORY_HONEYCOMB
        {108,48,16,16}, // INVENTORY_PINEAPPLE
        {0,66,16,16}, // INVENTORY_HIBISCUS
        {18,66,16,16}, // INVENTORY_LETTER
        {36,66,16,16}, // INVENTORY_BROOM
        {54,66,16,16}, // INVENTORY_HOOK
        {72,66,16,16}, // INVENTORY_NECKLACE
        {90,66,16,16}, // INVENTORY_MERMAID_SCALE
        {108,66,16,16}, // INVENTORY_LENS

        {0,134,8,16}, // INVENTORY_TAIL_KEY
        {40,134,8,16}, // INVENTORY_SLIME_KEY
        {10,134,8,16}, // INVENTORY_ANGLER_KEY
        {20,134,8,16}, // INVENTORY_FACE_KEY
        {30,134,8,16}, // INVENTORY_BIRD_KEY

        {90,162,8,8}, // INVENTORY_RED_ARROW
        {50,38,58,8}, // INVENTORY_PUSH_SELECT,

        {0,0,SELECT_SUBSCREEN_WIDTH,SELECT_SUBSCREEN_HEIGHT}, // INVENTORY_SUBSCREEN
        {0,100,31,14}, // INVENTORY_TUNIC (Green)
        {0,84,16,14}, // INVENTORY_HEART_PIECES
        {90,84,14,12}, // INVENTORY_PHOTOGRAPHS

        {126,116,8,8}, // INVENTORY_SLASH

        {0,152,8,8}, // INVENTORY_AREA_EXIT_RIGHT
        {10,152,8,8}, // INVENTORY_AREA_EXIT_LEFT
        {20,152,8,8}, // INVENTORY_AREA_EXIT_RIGHT_DOWN
        {30,152,8,8}, // INVENTORY_AREA_EXIT_LEFT_DOWN
        {40,152,8,8}, // INVENTORY_AREA_EXIT_NONE
        {50,152,8,8}, // INVENTORY_AREA_EXIT_LEFT_UP_DOWN
        {60,152,8,8}, // INVENTORY_AREA_EXIT_LEFT_DOWN_RIGHT
        {70,152,8,8}, // INVENTORY_AREA_UNVISITED
        {80,152,8,8}, // INVENTORY_AREA_EXIT_LEFT_RIGHT
        {90,152,8,8}, // INVENTORY_AREA_TREASURE
        {100,152,8,8}, // INVENTORY_AREA_NIGHTMARE
        {0,162,8,8}, // INVENTORY_AREA_EXIT_DOWN
        {10,162,8,8}, // INVENTORY_AREA_EXIT_UP
        {20,162,8,8}, // INVENTORY_AREA_EXIT_UP_RIGHT
        {30,162,8,8}, // INVENTORY_AREA_EXIT_LEFT_UP
        {40,162,8,8}, // INVENTORY_AREA_EXIT_ALL
        {50,162,8,8}, // INVENTORY_AREA_EXIT_UP_RIGHT_DOWN
        {60,162,8,8}, // INVENTORY_AREA_EXIT_UP_LEFT_DOWN
        {70,162,8,8}, // INVENTORY_AREA_EMPTY
        {80,162,8,8 }, // INVENTORY_AREA_EXIT_UP_DOWN
        {130,152,8,8},   // INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW
        {110,152,8,8},  // INVENTORY_DUNGEON_MAP_CURRENT_LOCATION
        { 130,2,8,16 }  // INVENTORY_ARROW


    };

    SDL_Rect m_inventorySpritesDst[sizeof(m_inventorySpritesSrc) / sizeof(m_inventorySpritesSrc[0])] =
    {
        {0,0,0,0},     // WPN_SWORD
        {0,0,0,0},     // WPN_SHIELD
        {0,0,0,0},     // WPN_BOW
        {0,0,0,0},     // WPN_BOOMERANG
        {0,0,0,0},     // WPN_MAGIC_POWDER
        {0,0,0,0},     // WPN_BOMBS
        {0,0,0,0},     // WPN_POWER_BRACELET_1
        {0,0,0,0},     // WPN_POWER_BRACELET_2
        {0,0,0,0},     // WPN_ROC_FEATHER
        {0,0,0,0},     // WPN_HOOKSHOT
        {0,0,0,0},     // WPN_OCARINA
        {0,0,0,0},     // WPN_PEGASUS_BOOT
        {0,0,0,0},     // WPN_SHOVEL
        {0,0,0,0},     // WPN_FLAME_ROD
        {0,0,0,0},
        {0,0,0,0},
        {1,1,5,8},     // "B"
        {41,1,5,8},    // "A"
        {6,1,28,14},   // Inventory selector (next to B)
        {46,1,28,14},  // Inventory selector (next to A)
        {81,1,7,7},    // Ruppee icon on HUD
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {104,0,8,8},     // INVENTORY_HEART_WHOLE
        {120,64,16,16},  // INVENTORY_INSTRUMENT_BACK_0
        {136,80,16,16},  // INVENTORY_INSTRUMENT_BACK_1
        {136,104,16,16}, // INVENTORY_INSTRUMENT_BACK_2
        {120,120,16,16}, // INVENTORY_INSTRUMENT_BACK_3
        {96,120,16,16},  // INVENTORY_INSTRUMENT_BACK_4
        {80,104,16,16},  // INVENTORY_INSTRUMENT_BACK_5
        {80,80,16,16},   // INVENTORY_INSTRUMENT_BACK_6
        {96,64,16,16},   // INVENTORY_INSTRUMENT_BACK_7
        {120,64,16,16},  // INVENTORY_INSTRUMENT_0
        {136,80,16,16},  // INVENTORY_INSTRUMENT_1
        {136,104,16,16}, // INVENTORY_INSTRUMENT_2
        {120,120,16,16}, // INVENTORY_INSTRUMENT_3
        {96,120,16,16},  // INVENTORY_INSTRUMENT_4
        {80,104,16,16},  // INVENTORY_INSTRUMENT_5
        {80,80,16,16},   // INVENTORY_INSTRUMENT_6
        {96,64,16,16},   // INVENTORY_INSTRUMENT_7
        {96,40,8,16},  // INVENTORY_COMPASS
        {128,40,8,16},  // INVENTORY_NIGHTMARE_KEY
        {112,40,8,16},  // INVENTORY_OWL_BEAK
        {80,40,8,16},  // INVENTORY_DUNGEON_MAP
        {144,40,8,16}, // INVENTORY_DUNGEON_KEY
        {80,24,8,16},  // INVENTORY_FLIPPERS
        {96,24,8,16},  // INVENTORY_POTION
        {136,24,8,16}, // INVENTORY_SEASHELLS

        {112,24,16,16}, // INVENTORY_DOLL
        {112,24,16,16}, // INVENTORY_BOW
        {112,24,16,16}, // INVENTORY_DOG_FOOD
        {112,24,16,16}, // INVENTORY_BANANAS
        {112,24,16,16}, // INVENTORY_STICK
        {112,24,16,16}, // INVENTORY_HONEYCOMB
        {112,24,16,16}, // INVENTORY_PINEAPPLE
        {112,24,16,16}, // INVENTORY_HIBISCUS
        {112,24,16,16}, // INVENTORY_LETTER
        {112,24,16,16}, // INVENTORY_BROOM
        {112,24,16,16}, // INVENTORY_HOOK
        {112,24,16,16}, // INVENTORY_NECKLACE
        {112,24,16,16}, // INVENTORY_MERMAID_SCALE
        {112,24,16,16}, // INVENTORY_LENS

        {80,40,8,16}, // INVENTORY_TAIL_KEY
        {144,40,8,16}, // INVENTORY_SLIME_KEY
        {96,40,8,16}, // INVENTORY_ANGLER_KEY
        {112,40,8,16}, // INVENTORY_FACE_KEY
        {128,40,8,16}, // INVENTORY_BIRD_KEY

        {75,136,8,8}, // INVENTORY_RED_ARROW
        {86,136,58,8}, // INVENTORY_PUSH_SELECT,

        {75,104,SELECT_SUBSCREEN_WIDTH,SELECT_SUBSCREEN_HEIGHT}, //INVENTORY_SUBSCREEN
        {1,1,31,14}, // INVENTORY_TUNIC (Green)
        {41,1,16,14}, // INVENTORY_HEART_PIECES
        {9,18,14,12}, // INVENTORY_PHOTOGRAPHS

        {40,24,8,8}, // INVENTORY_SLASH

        {88,56,8,8}, // INVENTORY_AREA_EXIT_RIGHT
        {88,56,8,8}, // INVENTORY_AREA_EXIT_LEFT
        {88,56,8,8}, // INVENTORY_AREA_EXIT_RIGHT_DOWN
        {88,56,8,8}, // INVENTORY_AREA_EXIT_LEFT_DOWN
        {88,56,8,8}, // INVENTORY_AREA_EXIT_NONE
        {88,56,8,8}, // INVENTORY_AREA_EXIT_LEFT_UP_DOWN
        {88,56,8,8}, // INVENTORY_AREA_EXIT_LEFT_DOWN_RIGHT
        {88,56,8,8}, // INVENTORY_AREA_UNVISITED
        {88,56,8,8}, // INVENTORY_AREA_EXIT_LEFT_RIGHT
        {88,56,8,8}, // INVENTORY_AREA_TREASURE
        {88,56,8,8}, // INVENTORY_AREA_NIGHTMARE
        {88,56,8,8}, // INVENTORY_AREA_EXIT_DOWN
        {88,56,8,8}, // INVENTORY_AREA_EXIT_UP
        {88,56,8,8}, // INVENTORY_AREA_EXIT_UP_RIGHT
        {88,56,8,8}, // INVENTORY_AREA_EXIT_LEFT_UP
        {88,56,8,8}, // INVENTORY_AREA_EXIT_ALL
        {88,56,8,8}, // INVENTORY_AREA_EXIT_UP_RIGHT_DOWN
        {88,56,8,8}, // INVENTORY_AREA_EXIT_UP_LEFT_DOWN
        {88,56,8,8}, // INVENTORY_AREA_EMPTY
        {88,56,8,8 }, // INVENTORY_AREA_EXIT_UP_DOWN
        {88,128,8,8},   // INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW
        {0, 0, 8, 8},  // INVENTORY_DUNGEON_MAP_CURRENT_LOCATION
        { 0,0,8,16 }  // INVENTORY_ARROW
    };

};
}