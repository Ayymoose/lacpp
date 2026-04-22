#pragma once

#include "core/Vector.h"
#include "Enum.h"

#include <utility>
#include <array>
#include <memory>
#include <algorithm>

namespace zelda::core
{
// Maximum "storable" items in inventory
constexpr int INVENTORY_COLUMNS = 2;
constexpr int INVENTORY_ROWS = 5;
constexpr int MAX_INVENTORY_ITEMS = INVENTORY_COLUMNS * INVENTORY_ROWS;

// Item limits
constexpr int MAX_BOMBS_1 = 20;
constexpr int MAX_BOMBS_2 = 60;
constexpr int MAX_MAGIC_POWDER_1 = 20;
constexpr int MAX_MAGIC_POWDER_2 = 40;
constexpr int MAX_ARROWS_1 = 30;
constexpr int MAX_ARROWS_2 = 60;

// Except for this
constexpr int MAX_RUPEES = 999;

constexpr int HEARTS_PIECE_MAX = 4;

// Maximum photographs we are allowed
constexpr int MAX_PHOTOGRAPHS = 12;
constexpr int MAX_SECRET_SEASHELLS = 50;
constexpr int MAX_GOLDEN_LEAVES = 5;

// Dungeon map
constexpr int DUNGEON_MAX_BLOCKS_X = 9;
constexpr int DUNGEON_MAX_BLOCKS_Y = 9;

struct DungeonItemStruct
{
    int lockedDoorKeys{0}; // Number of dungeon keys (small ones)
    int compass{0};        // Dungeon compass
    int dungeonMap{0};     // Dungeon map
    int nightmareKey{0};   // Nightmare boss key
    int owlBeak{0};        // Owl beak
};

// Usable inventory items
enum class UsableItem
{
    NONE = -1,
    SWORD,
    SHIELD,
    BOW,
    BOOMERANG,
    MAGIC_POWDER,
    BOMBS,
    POWER_BRACELET,
    ROC_FEATHER,
    HOOKSHOT,
    OCARINA,
    PEGASUS_BOOT,
    SHOVEL,
    FLAME_ROD,
    MUSHROOM,
    COUNT
};

enum class ItemAttribute
{
    NONE,
    QUANTITY,
    LEVEL,
    SONG
};

struct InventoryItem
{
    constexpr InventoryItem()
        : usuableItem(UsableItem::NONE)
        , itemAttribute(ItemAttribute::NONE)
        , value(0)
    {}

    constexpr InventoryItem(UsableItem usableItem, ItemAttribute attribute, int itemValue)
        : usuableItem(usableItem)
        , itemAttribute(attribute)
        , value(itemValue)
    {}

    UsableItem usuableItem;
    ItemAttribute itemAttribute;
    int value;

    friend std::ostream& operator<<(std::ostream& ostream, const InventoryItem& item)
    {
        ostream << '(' << std::to_underlying(item.usuableItem) << ',' << std::to_underlying(item.itemAttribute) << ','
                << item.value << ')';
        return ostream;
    }

    bool operator==(const InventoryItem& item) const
    {
        return value == item.value && itemAttribute == item.itemAttribute && usuableItem == item.usuableItem;
    }

    bool operator!=(const InventoryItem& item) const { return !operator==(item); }
};

// Songs available for Ocarina
enum class OcarinaSong
{
    NONE = -1,
    MARIN,
    FROG,
    FISH,
    COUNT
};

// Instruments
enum class Instrument
{
    NONE = -1,
    FULL_MOON_CELLO,
    CONCH_HORN,
    SEA_LILY_BELL,
    SURF_HARP,
    WIND_MARIMBA,
    CORAL_TRIANGLE,
    ORGAN_OF_EVENING_CALM,
    THUNDER_DRUM,
    COUNT
};

// Items used in the trade sequence
enum class TradeItem
{
    NONE = -1,
    YOSHI_DOLL,
    RIBBON,
    DOG_FOOD,
    BANANAS,
    STICK,
    HONEYCOMB,
    PINEAPPLE,
    HIBISCUS,
    LETTER,
    BROOM,
    FISHING_HOOK,
    MERMAID_NECKLACE,
    MERMAID_SCALE,
    MAGNIFYING_LENS,
    BOOMERANG, // Doesn't show in inventory
    COUNT
};

// Tunic types
enum class Tunic
{
    NONE = -1,
    GREEN,
    RED,
    BLUE,
    COUNT
};

// Name of dungeon
enum class Dungeon
{
    NONE = -1,
    COLOUR_DUNGEON,
    TAIL_CAVE,
    BOTTLE_GROTTO,
    KEY_CAVERN,
    ANGLER_TUNNEL,
    CATFISH_MAW,
    FACE_SHRINE,
    EAGLE_TOWER,
    TURTLE_ROCK,
    COUNT
};

// Entrace key types for each dungeon
enum class DungeonEntranceKey
{
    NONE = -1,
    TAIL,
    SLIME,
    ANGLER,
    FACE,
    BIRD,
    COUNT
};

// Items available in a dungeon
enum class DungeonItem
{
    LOCKED_DOOR_KEY,
    COMPASS,
    MAP,
    NIGHTMARE_KEY,
    OWL_BEAK
};

// All types of items shown on the dungeon map
enum class DungeonMapItem
{
    NONE = -1,
    CHEST_CLOSED,
    CHEST_OPEN,
    NIGHTMARE_KEY
};

// Misc inventory items
enum class InventoryMiscItem
{
    NONE = -1,
    RED_POTION,
    FLIPPERS,
    COUNT
};

// Rupee types available
enum class Rupee
{
    ONE = 1,
    FIVE = 5,
    TEN = 10,
    TWENTY = 20,
    FIFTY = 50,
    ONE_HUNDRED = 100,
    TWO_HUNDRED = 200
};

// All photographs possible
enum class Photograph
{
    NONE = -1,
    HERE_STANDS_A_BRAVE_MAN,
    GAME_OVER,
    OCEAN_VIEW,
    HEADS_UP,
    SAY_MUSHROOM,
    LINK_DISCOVERS_ULRIRAS_SECRET,
    LINK_PLAYS_WITH_BOWOW,
    THIEF,
    CANT_SWIM,
    I_FOUND_ZORA,
    A_REGAL_HOME,
    I_WAS_VERY_AFRAID,
    CLOSE_CALL,
    COUNT
};

struct DungeonMapEntry
{
    uint8_t roomType;
    bool visited;
    DungeonMapItem roomItem;
};

class Inventory
{
public:
    Inventory();

    // Add an inventory weapon
    void addInventoryItem(const InventoryItem& inventoryItem);
    std::array<InventoryItem, MAX_INVENTORY_ITEMS> inventoryItems() const;
    void removeInventoryItem(const InventoryItem& inventoryItem);
    bool inventoryItemExists(const InventoryItem& inventoryItem) const;

    // Add - When finding the keys
    void addDungeonEntranceKey(DungeonEntranceKey dungeonKey);
    bool dungeonEntranceKey(DungeonEntranceKey dungeonKey) const;

    // Add - When finding items in the dungeon
    // Use - Only dungeon key can be +/-
    void addDungeonItem(DungeonItem dungeonItem);
    void useDungeonItem(DungeonItem dungeonItem);
    int dungeonItem(DungeonItem dungeonItem) const;

    // Trade item up the chain
    void tradeItem(TradeItem tradeItem);
    TradeItem tradedItem() const;
    void setTradeItem(TradeItem tradeItem);

    // Add - Red potion only stores once, Flippers can only be set once
    // Use - Red potion usable, Flippers NOT usuable
    void addInventoryMiscItem(InventoryMiscItem inventoryMiscItem);
    void useInventoryMiscItem(InventoryMiscItem inventoryMiscItem);
    bool miscItemExists(InventoryMiscItem inventoryMiscItem) const;

    // Add - Obtain after defeating dungeon boss
    bool instrumentExists(Instrument instrument) const;
    void addInstrument(Instrument instrument);
    std::array<Instrument, std::to_underlying(Instrument::COUNT)> instruments() const;

    // Add - When finding ruppees
    // Use - When purchasing items (return true if can use rupees amount)
    void addRupee();
    void useRupee();
    int rupees() const;
    void setRupees(const int rupees);

    // Add bombs
    // Use bombs (return true if can use bomb)
    void setBombLimit(const int limit);
    void setBombs(const int bombs);
    void useBomb();
    int bombs() const;

    // Add arrows
    // Use arrows (return true if can use arrow)
    void setArrowLimit(const int limit);
    void setArrows(const int arrows);
    void useArrow();
    int arrows() const;

    // Add magic powder
    // Use magic power (return true if can use magic powder)
    void setMagicPowderLimit(const int limit);
    void setMagicPowder(const int magicPowder);
    void useMagicPowder();
    int magicPowder() const;

    // Add only
    void setOcarinaSong(OcarinaSong ocarinaSong);
    void addOcarinaSong(OcarinaSong ocarinaSong);
    std::array<OcarinaSong, std::to_underlying(OcarinaSong::COUNT)> ocarinaSongs() const;

    // Get selected song
    OcarinaSong ocarinaSong() const;

    // Add - Only set once
    void addTunic(Tunic tunic);
    // Currently worn tunic
    Tunic tunic() const;
    void setTunic(Tunic tunic);

    void addHeartContainerPiece();
    void setHeartContainerPieces(const int heartContainerPieces);
    int heartContainerPieces() const;

    // Add heart pieces
    void addHeartPiece(const float heartPiece);
    // "Use" heart piece when damage incurred
    void useHeartPiece(const float heartPiece);

    void setHeartPieces(const float heartPieces);
    void setMaxHeartPieces(const float maxHeartPieces);

    float heartPieces() const;
    float maxHeartPieces() const;

    // Add only
    void addPhotograph(Photograph photograph);
    std::array<Photograph, std::to_underlying(Photograph::COUNT)> photographs() const;
    int photograph() const;

    void addGoldenLeaf();
    // Add golden leaves from Kanalet castle
    void setGoldenLeaves(const int goldenLeaves);
    // Number of golden leaves we have
    int goldenLeaves() const;

    void addSecretSeaShell();
    void setSecretSeaShells(const int secretShells);
    int secretSeaShells();

    // Set/get whether we are in a dungeon or not
    void setInDungeon(const bool inDungeon);
    bool getInDungeon() const;

    // Get the currently set inventory weapons
    InventoryItem itemA() const;
    InventoryItem itemB() const;

    void swapItemA();
    void swapItemB();

    void setItemA(const InventoryItem& itemA);
    void setItemB(const InventoryItem& itemB);

    void moveInventorySelector(Direction direction);


    Dungeon dungeon() const;
    void setDungeon(Dungeon dungeon);
    void setDungeonMapLocationVisited(const engine::Vector<int>& location);
    bool dungeonMapLocationVisited(const int x, const int y) const;
    int dungeonMapLocationRoomType(const int x, const int y) const;
    DungeonMapItem dungeonMapLocationRoomItem(const int x, const int y) const;


    void setPositionInDungeonMap(const engine::Vector<int>& location);
    engine::Vector<int> dungeonMapPositionLocation() const;
    void movePositionInDungeonMap(Direction direction);


private:
    // TODO: Dungeon map hidden room connections when discovered
    // TODO: Ocarina song selection window
    // TODO: Chest and nightmare locations for each dungeon map
    // TODO: Every other dungeon map layout

    // Inventory related variables
    int m_arrows; // Number of arrows
    int m_maxArrows;
    int m_bombs; // Number of bombs
    int m_maxBombs;
    int m_magicPowder; // Number of magic powder
    int m_maxMagicPowder;

    OcarinaSong m_ocarinaSong; // Selected ocarina song
    std::array<OcarinaSong, std::to_underlying(OcarinaSong::COUNT)> m_ocarinaSongs;

    int m_secretSeaShells; // Number of Seashells

    std::array<InventoryMiscItem, std::to_underlying(InventoryMiscItem::COUNT)> m_inventoryMiscItems;

    Tunic m_tunic;              // Tunic type
    int m_heartContainerPieces; // Heart container pieces
    int m_goldenLeaves;         // Golden leaves (Shown in Kanalet castle only)

    std::array<Photograph, std::to_underlying(Photograph::COUNT)> m_photographs;

    int m_rupees;          // Number of rupees 0-999
    TradeItem m_tradeItem; // Current trade item


    float m_heartPieces;
    float m_maxHeartPieces;

    // Item A and B
    InventoryItem m_itemA;
    InventoryItem m_itemB;

    // Index into inventory array
    int m_selectorIndex;

    std::array<InventoryItem, MAX_INVENTORY_ITEMS> m_inventoryItems;

    template <typename Enum, size_t Size>
    static bool checkItemExists(const std::array<Enum, Size>& array, Enum item);

    // Instruments
    std::array<Instrument, std::to_underlying(Instrument::COUNT)> m_instruments;

    // Dungeon related items
    bool m_inDungeon; // Are we in a dungeon?

    // The keys used to open dungeon entrances
    std::array<DungeonEntranceKey, std::to_underlying(DungeonEntranceKey::COUNT)>
        m_dungeonEntraceKeys;

    // Dungeon items
    std::array<DungeonItemStruct, std::to_underlying(Dungeon::COUNT)> m_dungeonItemsStruct;

    // Link position in dungeon map as a vector position
    engine::Vector<int> m_positionInDungeonMap;

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

    // TODO: Never thought about where the dungeon marker is when Link is in the side-scrolling part of dungeon
    // Maybe it stays at the last point when we are side scrolling? Verify
    // TODO: Add the treasure remaininng treeassure cheests

    DungeonMapEntry m_dungeonMaps[std::to_underlying(Dungeon::COUNT)][DUNGEON_MAX_BLOCKS_X]
                                 [DUNGEON_MAX_BLOCKS_Y] =
                                     {{// Lvl 0 - Colour dungeon
                                       {{1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {6, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {4, false, DungeonMapItem::NIGHTMARE_KEY},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {3, false, DungeonMapItem::CHEST_CLOSED},
                                        {8, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {19, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{19, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{13, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {14, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {20, false, DungeonMapItem::NONE},
                                        {18, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}}},
                                      {
                                          // Lvl 1 - Tail Cave
                                          {{1, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE}},
                                          {{0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE}},
                                          {{0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE}},
                                          {{0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {12, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE}},
                                          {{0, false, DungeonMapItem::NONE},
                                           {5, false, DungeonMapItem::NONE},
                                           {11, false, DungeonMapItem::NONE},
                                           {6, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {19, false, DungeonMapItem::NIGHTMARE_KEY},
                                           {0, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE}},
                                          {{12, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {17, false, DungeonMapItem::NONE},
                                           {11, false, DungeonMapItem::CHEST_CLOSED},
                                           {8, false, DungeonMapItem::NONE},
                                           {12, false, DungeonMapItem::NONE},
                                           {19, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE}},
                                          {{19, false, DungeonMapItem::NONE},
                                           {5, false, DungeonMapItem::NONE},
                                           {17, false, DungeonMapItem::NONE},
                                           {10, false, DungeonMapItem::NONE},
                                           {10, false, DungeonMapItem::NONE},
                                           {10, false, DungeonMapItem::NONE},
                                           {15, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE}},
                                          {{13, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {14, false, DungeonMapItem::NONE},
                                           {11, false, DungeonMapItem::NONE},
                                           {15, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE}},
                                          {{0, false, DungeonMapItem::NONE},
                                           {5, false, DungeonMapItem::NONE},
                                           {20, false, DungeonMapItem::NONE},
                                           {18, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {0, false, DungeonMapItem::NONE},
                                           {1, false, DungeonMapItem::NONE}}
                                          // Rooms start at the bottom left of the map here (3, 8);
                                      },
                                      {// Lvl 2 - Bottle Grotto
                                       {{1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {6, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {4, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {3, false, DungeonMapItem::NONE},
                                        {8, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {19, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{19, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{13, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {14, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {20, false, DungeonMapItem::NONE},
                                        {18, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}}},
                                      {// Lvl 3 - Key Cavern
                                       {{1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {6, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {4, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {3, false, DungeonMapItem::NONE},
                                        {8, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {19, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{19, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{13, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {14, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {20, false, DungeonMapItem::NONE},
                                        {18, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}}},
                                      {// Lvl 4 - Angler Tunnel
                                       {{1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {6, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {4, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {3, false, DungeonMapItem::NONE},
                                        {8, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {19, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{19, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{13, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {14, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {20, false, DungeonMapItem::NONE},
                                        {18, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}}},
                                      {// Lvl 5 - Catfish Maw
                                       {{1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {6, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {4, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {3, false, DungeonMapItem::NONE},
                                        {8, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {19, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{19, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{13, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {14, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {20, false, DungeonMapItem::NONE},
                                        {18, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}}},
                                      {// Lvl 6 - Face Shrine
                                       {{1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {6, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {4, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {3, false, DungeonMapItem::NONE},
                                        {8, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {19, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{19, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{13, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {14, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {20, false, DungeonMapItem::NONE},
                                        {18, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}}},
                                      {// Lvl 7 - Eagle Tower
                                       {{1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {6, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {4, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {3, false, DungeonMapItem::NONE},
                                        {8, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {19, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{19, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{13, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {14, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {20, false, DungeonMapItem::NONE},
                                        {18, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}}},
                                      {// Lvl 8 - Turtle Rock
                                       {{1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {6, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {4, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{12, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {3, false, DungeonMapItem::NONE},
                                        {8, false, DungeonMapItem::NONE},
                                        {12, false, DungeonMapItem::NONE},
                                        {19, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{19, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {17, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {10, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{13, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {14, false, DungeonMapItem::NONE},
                                        {11, false, DungeonMapItem::NONE},
                                        {15, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}},
                                       {{0, false, DungeonMapItem::NONE},
                                        {5, false, DungeonMapItem::NONE},
                                        {20, false, DungeonMapItem::NONE},
                                        {18, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {0, false, DungeonMapItem::NONE},
                                        {1, false, DungeonMapItem::NONE}}}};
};

template <typename Enum, size_t Size>
bool Inventory::checkItemExists(const std::array<Enum, Size>& array, Enum item)
{
    return std::any_of(array.cbegin(), array.cend(), [&item](Enum exists) { return item == exists; });
}
} // namespace zelda::core