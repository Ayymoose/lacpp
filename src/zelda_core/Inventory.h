#pragma once

#include "core/Vector.h"
#include "core/Direction.h"

#include <algorithm>
#include <array>
#include <ostream>
#include <ranges>
#include <utility>

namespace zelda::core
{

class Inventory
{
public:
    // Maximum "storable" items in inventory
    static constexpr int MAX_COLUMNS = 2;
    static constexpr int MAX_ROWS = 5;
    static constexpr int MAX_ITEMS = MAX_COLUMNS * MAX_ROWS;

    // Item limits
    static constexpr int MAX_BOMBS_1 = 20;
    static constexpr int MAX_BOMBS_2 = 60;
    static constexpr int MAX_MAGIC_POWDER_1 = 20;
    static constexpr int MAX_MAGIC_POWDER_2 = 40;
    static constexpr int MAX_ARROWS_1 = 30;
    static constexpr int MAX_ARROWS_2 = 60;

    static constexpr int MAX_RUPEES = 999;

    static constexpr int MAX_HEART_PIECES = 4;

    static constexpr int MAX_PHOTOGRAPHS = 12;
    static constexpr int MAX_SECRET_SEASHELLS = 50;
    static constexpr int MAX_GOLDEN_LEAVES = 5;

    // Dungeon map area limits
    static constexpr int MAX_DUNGEON_BLOCKS_X = 9;
    static constexpr int MAX_DUNGEON_BLOCKS_Y = 9;


    struct Item
    {
        enum class Attribute
        {
            NONE,
            QUANTITY,
            LEVEL,
            SONG
        };

        // Usable inventory items
        enum class Type
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

        Item() = default;

        constexpr Item(Type usableItem, Attribute attribute, int itemValue)
            : usableItem(usableItem)
            , itemAttribute(attribute)
            , value(itemValue)
        {}

        Type usableItem = Type::NONE;
        Attribute itemAttribute = Attribute::NONE;
        int value = 0;

        friend std::ostream& operator<<(std::ostream& ostream, const Item& item)
        {
            ostream << '(' << std::to_underlying(item.usableItem) << ',' << std::to_underlying(item.itemAttribute)
                    << ',' << item.value << ')';
            return ostream;
        }

        [[nodiscard]] bool operator==(const Item& item) const
        {
            return value == item.value && itemAttribute == item.itemAttribute && usableItem == item.usableItem;
        }
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

    struct Dungeon
    {
        // Name of dungeon
        enum class Name
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

        // Entrance key types for each dungeon
        enum class EntranceKey
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
        enum class Item
        {
            LOCKED_DOOR_KEY,
            COMPASS,
            MAP,
            NIGHTMARE_KEY,
            OWL_BEAK
        };

        // All types of items shown on the dungeon map
        enum class MapItem
        {
            NONE = -1,
            CHEST_CLOSED,
            CHEST_OPEN,
            NIGHTMARE_KEY
        };

        struct MapEntry
        {
            uint8_t roomType;
            bool visited;
            MapItem roomItem;
        };

        struct Items
        {
            int lockedDoorKeys{0};    // Number of dungeon keys (small ones)
            bool compass{false};      // Dungeon compass
            bool dungeonMap{false};   // Dungeon map
            bool nightmareKey{false}; // Nightmare boss key
            bool owlBeak{false};      // Owl beak
        };
    };

    // Misc inventory items
    enum class MiscItem
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


    Inventory();

    // Add an inventory weapon
    void addInventoryItem(const Item& item);
    [[nodiscard]] std::array<Item, MAX_ITEMS> inventoryItems() const;
    void removeInventoryItem(const Item& item);
    [[nodiscard]] bool inventoryItemExists(const Item& item) const;

    void addDungeonEntranceKey(Dungeon::EntranceKey key);
    [[nodiscard]] bool dungeonEntranceKey(Dungeon::EntranceKey key) const;

    void addDungeonItem(Dungeon::Item item);
    void useDungeonItem(Dungeon::Item item);
    [[nodiscard]] int dungeonItem(Dungeon::Item item) const;

    void tradeItem(TradeItem item);
    [[nodiscard]] TradeItem tradedItem() const;
    void setTradeItem(TradeItem item);

    void addMiscItem(MiscItem item);
    void useMiscItem(MiscItem item);
    [[nodiscard]] bool miscItemExists(MiscItem item) const;

    [[nodiscard]] bool instrumentExists(Instrument instrument) const;
    void addInstrument(Instrument instrument);
    [[nodiscard]] std::array<Instrument, std::to_underlying(Instrument::COUNT)> instruments() const;

    void addRupee();
    void useRupee();
    [[nodiscard]] int rupees() const;
    void setRupees(int rupees);

    void setMaxBombs(int maxBombs);
    void setBombs(int bombs);
    void useBomb();
    [[nodiscard]] int bombs() const;

    void setMaxArrows(int maxArrows);
    void setArrows(int arrows);
    void useArrow();
    [[nodiscard]] int arrows() const;

    void setMaxMagicPowder(int maxMagicPowder);
    void setMagicPowder(int magicPowder);
    void useMagicPowder();
    [[nodiscard]] int magicPowder() const;

    void setOcarinaSong(OcarinaSong ocarinaSong);
    void addOcarinaSong(OcarinaSong ocarinaSong);
    [[nodiscard]] std::array<OcarinaSong, std::to_underlying(OcarinaSong::COUNT)> ocarinaSongs() const;

    [[nodiscard]] OcarinaSong ocarinaSong() const;

    void addTunic(Tunic tunic);
    [[nodiscard]] Tunic tunic() const;
    void setTunic(Tunic tunic);

    void addHeartContainerPiece();
    void setHeartContainerPieces(int heartContainerPieces);
    [[nodiscard]] int heartContainerPieces() const;

    void addHeartPiece(float heartPiece);
    void useHeartPiece(float heartPiece);

    void setHeartPieces(float heartPieces);
    void setMaxHeartPieces(float maxHeartPieces);

    [[nodiscard]] float heartPieces() const;
    [[nodiscard]] float maxHeartPieces() const;

    void addPhotograph(Photograph photograph);
    [[nodiscard]] std::array<Photograph, std::to_underlying(Photograph::COUNT)> photographs() const;
    [[nodiscard]] int numberOfPhotographs() const;

    void addGoldenLeaf();
    void setGoldenLeaves(int goldenLeaves);
    [[nodiscard]] int goldenLeaves() const;

    void addSecretSeaShell();
    void setSecretSeaShells(int secretShells);
    [[nodiscard]] int secretSeaShells() const;

    void setInDungeon(bool inDungeon);
    [[nodiscard]] bool inDungeon() const;

    [[nodiscard]] Item itemA() const;
    [[nodiscard]] Item itemB() const;

    void swapItemA();
    void swapItemB();

    void setItemA(const Item& itemA);
    void setItemB(const Item& itemB);

    template <engine::Direction D>
    void moveInventorySelector()
    {
        if constexpr (D == engine::Direction::DOWN)
        {
            m_selectorIndex = (m_selectorIndex >= MAX_ITEMS - MAX_COLUMNS) ? 0 : m_selectorIndex + MAX_COLUMNS;
        }
        else if constexpr (D == engine::Direction::UP)
        {
            m_selectorIndex = (m_selectorIndex < MAX_COLUMNS) ? MAX_ITEMS - 1 : m_selectorIndex - MAX_COLUMNS;
        }
        else if constexpr (D == engine::Direction::RIGHT)
        {
            m_selectorIndex = (m_selectorIndex == MAX_ITEMS - 1) ? 0 : m_selectorIndex + 1;
        }
        else if constexpr (D == engine::Direction::LEFT)
        {
            m_selectorIndex = (m_selectorIndex == 0) ? MAX_ITEMS - 1 : m_selectorIndex - 1;
        }
        assert(m_selectorIndex >= 0 && m_selectorIndex < MAX_ITEMS);
    }


    [[nodiscard]] Dungeon::Name dungeon() const;
    void setDungeon(Dungeon::Name dungeon);

    void setDungeonMapLocationVisited(const engine::Vector<int>& location);
    [[nodiscard]] bool dungeonMapLocationVisited(int x, int y) const;

    // TODO: Enum this type
    [[nodiscard]] int dungeonMapLocationRoomType(int x, int y) const;

    [[nodiscard]] Dungeon::MapItem dungeonMapLocationRoomItem(int x, int y) const;

    void setPositionInDungeonMap(const engine::Vector<int>& location);
    [[nodiscard]] engine::Vector<int> dungeonMapPositionLocation() const;

    template <engine::Direction D>
    void movePositionInDungeonMap()
    {
        if constexpr (D == engine::Direction::DOWN)
            ++m_positionInDungeonMap.y;
        else if constexpr (D == engine::Direction::UP)
            --m_positionInDungeonMap.y;
        else if constexpr (D == engine::Direction::RIGHT)
            ++m_positionInDungeonMap.x;
        else if constexpr (D == engine::Direction::LEFT)
            --m_positionInDungeonMap.x;
    }


private:
    // TODO: Dungeon map hidden room connections when discovered
    // TODO: Ocarina song selection window
    // TODO: Chest and nightmare locations for each dungeon map
    // TODO: Every other dungeon map layout

    // Inventory related variables
    int m_arrows = 0; // Number of arrows
    int m_maxArrows = 0;
    int m_bombs = 0; // Number of bombs
    int m_maxBombs = 0;
    int m_magicPowder = 0; // Number of magic powder
    int m_maxMagicPowder = 0;

    OcarinaSong m_ocarinaSong = OcarinaSong::NONE; // Selected ocarina song
    std::array<OcarinaSong, std::to_underlying(OcarinaSong::COUNT)> m_ocarinaSongs{};

    int m_secretSeaShells = 0; // Number of Seashells

    std::array<MiscItem, std::to_underlying(MiscItem::COUNT)> m_miscItems{};

    Tunic m_tunic = Tunic::GREEN;   // Tunic type
    int m_heartContainerPieces = 0; // Heart container pieces
    int m_goldenLeaves = 0;         // Golden leaves (Shown in Kanalet castle only)

    std::array<Photograph, std::to_underlying(Photograph::COUNT)> m_photographs{};

    int m_rupees = 0;                        // Number of rupees 0-999
    TradeItem m_tradeItem = TradeItem::NONE; // Current trade item


    float m_heartPieces = 0.0f;
    float m_maxHeartPieces = 0.0f;

    // Item A and B
    Item m_itemA;
    Item m_itemB;

    // Index into inventory array
    int m_selectorIndex = 0;

    std::array<Item, MAX_ITEMS> m_inventoryItems;

    template <typename Enum, size_t Size>
    [[nodiscard]] static bool checkItemExists(const std::array<Enum, Size>& arr, Enum item);

    // Instruments
    std::array<Instrument, std::to_underlying(Instrument::COUNT)> m_instruments{};

    // Dungeon related items
    bool m_inDungeon = false; // Are we in a dungeon?

    // The keys used to open dungeon entrances
    std::array<Dungeon::EntranceKey, std::to_underlying(Dungeon::EntranceKey::COUNT)> m_dungeonEntranceKeys{};

    // Dungeon items
    std::array<Dungeon::Items, std::to_underlying(Dungeon::Name::COUNT)> m_dungeonItems;

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
    Dungeon::Name m_dungeon = Dungeon::Name::NONE;

    // TODO: Never thought about where the dungeon marker is when Link is in the side-scrolling part of dungeon
    // Maybe it stays at the last point when we are side scrolling? Verify
    // TODO: Add the treasure remaininng treeassure cheests

    Dungeon::MapEntry m_dungeonMaps[std::to_underlying(Dungeon::Name::COUNT)][MAX_DUNGEON_BLOCKS_X]
                                   [MAX_DUNGEON_BLOCKS_Y] =
                                       {{// Lvl 0 - Colour dungeon
                                         {{1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {6, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {4, false, Dungeon::MapItem::NIGHTMARE_KEY},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {3, false, Dungeon::MapItem::CHEST_CLOSED},
                                          {8, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {19, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{19, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{13, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {14, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {20, false, Dungeon::MapItem::NONE},
                                          {18, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}}},
                                        {
                                            // Lvl 1 - Tail Cave
                                            {{1, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE}},
                                            {{0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE}},
                                            {{0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE}},
                                            {{0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {12, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE}},
                                            {{0, false, Dungeon::MapItem::NONE},
                                             {5, false, Dungeon::MapItem::NONE},
                                             {11, false, Dungeon::MapItem::NONE},
                                             {6, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {19, false, Dungeon::MapItem::NIGHTMARE_KEY},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE}},
                                            {{12, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {17, false, Dungeon::MapItem::NONE},
                                             {11, false, Dungeon::MapItem::CHEST_CLOSED},
                                             {8, false, Dungeon::MapItem::NONE},
                                             {12, false, Dungeon::MapItem::NONE},
                                             {19, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE}},
                                            {{19, false, Dungeon::MapItem::NONE},
                                             {5, false, Dungeon::MapItem::NONE},
                                             {17, false, Dungeon::MapItem::NONE},
                                             {10, false, Dungeon::MapItem::NONE},
                                             {10, false, Dungeon::MapItem::NONE},
                                             {10, false, Dungeon::MapItem::NONE},
                                             {15, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE}},
                                            {{13, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {14, false, Dungeon::MapItem::NONE},
                                             {11, false, Dungeon::MapItem::NONE},
                                             {15, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE}},
                                            {{0, false, Dungeon::MapItem::NONE},
                                             {5, false, Dungeon::MapItem::NONE},
                                             {20, false, Dungeon::MapItem::NONE},
                                             {18, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {0, false, Dungeon::MapItem::NONE},
                                             {1, false, Dungeon::MapItem::NONE}}
                                            // Rooms start at the bottom left of the map here (3, 8);
                                        },
                                        {// Lvl 2 - Bottle Grotto
                                         {{1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {6, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {4, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {3, false, Dungeon::MapItem::NONE},
                                          {8, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {19, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{19, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{13, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {14, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {20, false, Dungeon::MapItem::NONE},
                                          {18, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}}},
                                        {// Lvl 3 - Key Cavern
                                         {{1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {6, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {4, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {3, false, Dungeon::MapItem::NONE},
                                          {8, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {19, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{19, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{13, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {14, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {20, false, Dungeon::MapItem::NONE},
                                          {18, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}}},
                                        {// Lvl 4 - Angler Tunnel
                                         {{1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {6, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {4, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {3, false, Dungeon::MapItem::NONE},
                                          {8, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {19, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{19, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{13, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {14, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {20, false, Dungeon::MapItem::NONE},
                                          {18, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}}},
                                        {// Lvl 5 - Catfish Maw
                                         {{1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {6, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {4, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {3, false, Dungeon::MapItem::NONE},
                                          {8, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {19, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{19, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{13, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {14, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {20, false, Dungeon::MapItem::NONE},
                                          {18, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}}},
                                        {// Lvl 6 - Face Shrine
                                         {{1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {6, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {4, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {3, false, Dungeon::MapItem::NONE},
                                          {8, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {19, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{19, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{13, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {14, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {20, false, Dungeon::MapItem::NONE},
                                          {18, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}}},
                                        {// Lvl 7 - Eagle Tower
                                         {{1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {6, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {4, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {3, false, Dungeon::MapItem::NONE},
                                          {8, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {19, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{19, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{13, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {14, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {20, false, Dungeon::MapItem::NONE},
                                          {18, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}}},
                                        {// Lvl 8 - Turtle Rock
                                         {{1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {6, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {4, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{12, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {3, false, Dungeon::MapItem::NONE},
                                          {8, false, Dungeon::MapItem::NONE},
                                          {12, false, Dungeon::MapItem::NONE},
                                          {19, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{19, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {17, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {10, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{13, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {14, false, Dungeon::MapItem::NONE},
                                          {11, false, Dungeon::MapItem::NONE},
                                          {15, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}},
                                         {{0, false, Dungeon::MapItem::NONE},
                                          {5, false, Dungeon::MapItem::NONE},
                                          {20, false, Dungeon::MapItem::NONE},
                                          {18, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {0, false, Dungeon::MapItem::NONE},
                                          {1, false, Dungeon::MapItem::NONE}}}};
};

template <typename Enum, size_t Size>
[[nodiscard]] bool Inventory::checkItemExists(const std::array<Enum, Size>& arr, Enum item)
{
    return std::ranges::any_of(arr, [item](Enum e) { return e == item; });
}
} // namespace zelda::core