#pragma once

#include "Vector.h"
#include "Enum.h"
#include "Macro.h"

#include <utility>
#include <array>
#include <memory>
#include <algorithm>

namespace Zelda
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
        int lockedDoorKeys{0};   // Number of dungeon keys (small ones)
        int compass{0};          // Dungeon compass
        int dungeonMap{0};       // Dungeon map
        int nightmareKey{0};     // Nightmare boss key
        int owlBeak{0};          // Owl beak
    };

    // Usable inventory items
    enum class UsableItem
    {
        USABLE_ITEM_NONE = -1,
        USABLE_ITEM_SWORD,
        USABLE_ITEM_SHIELD,
        USABLE_ITEM_BOW,
        USABLE_ITEM_BOOMERANG,
        USABLE_ITEM_MAGIC_POWDER,
        USABLE_ITEM_BOMBS,
        USABLE_ITEM_POWER_BRACELET,
        USABLE_ITEM_ROC_FEATHER,
        USABLE_ITEM_HOOKSHOT,
        USABLE_ITEM_OCARINA,
        USABLE_ITEM_PEGASUS_BOOT,
        USABLE_ITEM_SHOVEL,
        USABLE_ITEM_FLAME_ROD,
        USABLE_ITEM_MUSHROOM,
        USABLE_ITEM_COUNT
    };

    enum class ItemAttribute
    {
        ITEM_ATTRIBUTE_NONE,
        ITEM_ATTRIBUTE_QUANTITY,
        ITEM_ATTRIBUTE_LEVEL,
        ITEM_ATTRIBUTE_SONG
    };

    struct InventoryItem
    {

        constexpr InventoryItem() :
            usuableItem(UsableItem::USABLE_ITEM_NONE),
            itemAttribute(ItemAttribute::ITEM_ATTRIBUTE_NONE),
            value(0)
        {
        }

        constexpr InventoryItem(UsableItem usableItem, ItemAttribute itemAttribute, int value) :
            usuableItem(usableItem),
            itemAttribute(itemAttribute),
            value(value)
        {
        }

        UsableItem usuableItem;
        ItemAttribute itemAttribute;
        int value;

        friend std::ostream& operator<<(std::ostream& ostream, const InventoryItem& item)
        {
            ostream << '(' << ENUM_VALUE(item.usuableItem) << ',' << ENUM_VALUE(item.itemAttribute) << ',' << item.value << ')';
            return ostream;
        }

        bool operator==(const InventoryItem& item) const
        {
            return value == item.value && itemAttribute == item.itemAttribute && usuableItem == item.usuableItem;
        }

        bool operator!=(const InventoryItem& item) const
        {
            return !operator==(item);
        }
    };

    // Songs available for Ocarina
    enum class OcarinaSong
    {
        OCARINA_SONG_NONE = -1,
        OCARINA_SONG_MARIN,
        OCARINA_SONG_FROG,
        OCARINA_SONG_FISH,
        OCARINA_SONG_COUNT
    };

    // Instruments
    enum class Instrument
    {
        INSTRUMENT_NONE = -1,
        INSTRUMENT_FULL_MOON_CELLO,
        INSTRUMENT_CONCH_HORN,
        INSTRUMENT_SEA_LILY_BELL,
        INSTRUMENT_SURF_HARP,
        INSTRUMENT_WIND_MARIMBA,
        INSTRUMENT_CORAL_TRIANGLE,
        INSTRUMENT_ORGAN_OF_EVENING_CALM,
        INSTRUMENT_THUNDER_DRUM,
        INSTRUMENT_COUNT
    };

    // Items used in the trade sequence
    enum class TradeItem
    {
        TRADE_ITEM_NONE = -1,
        TRADE_ITEM_YOSHI_DOLL,
        TRADE_ITEM_RIBBON,
        TRADE_ITEM_DOG_FOOD,
        TRADE_ITEM_BANANAS,
        TRADE_ITEM_STICK,
        TRADE_ITEM_HONEYCOMB,
        TRADE_ITEM_PINEAPPLE,
        TRADE_ITEM_HIBISCUS,
        TRADE_ITEM_LETTER,
        TRADE_ITEM_BROOM,
        TRADE_ITEM_FISHING_HOOK,
        TRADE_ITEM_MERMAID_NECKLACE,
        TRADE_ITEM_MERMAID_SCALE,
        TRADE_ITEM_MAGNIFYING_LENS,
        TRADE_ITEM_BOOMERANG, // Doesn't show in inventory
        TRADE_ITEM_COUNT
    };

    // Tunic types
    enum class Tunic
    {
        TUNIC_NONE = -1,
        TUNIC_GREEN,
        TUNIC_RED,
        TUNIC_BLUE,
        TUNIC_COUNT
    };

    // Name of dungeon
    enum class Dungeon
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

    // Entrace key types for each dungeon
    enum class DungeonEntranceKey
    {
        DUNGEON_ENTRACE_KEY_NONE = -1,
        DUNGEON_ENTRACE_KEY_TAIL,
        DUNGEON_ENTRACE_KEY_SLIME,
        DUNGEON_ENTRACE_KEY_ANGLER,
        DUNGEON_ENTRACE_KEY_FACE,
        DUNGEON_ENTRACE_KEY_BIRD,
        DUNGEON_ENTRACE_KEY_COUNT
    };

    // Items available in a dungeon
    enum class DungeonItem
    {
        DUNGEON_ITEM_LOCKED_DOOR_KEY,
        DUNGEON_ITEM_COMPASS,
        DUNGEON_ITEM_MAP,
        DUNGEON_ITEM_NIGHTMARE_KEY,
        DUNGEON_ITEM_OWL_BEAK
    };

    // All types of items shown on the dungeon map
    enum class DungeonMapItem
    {
        DUNGEON_MAP_ITEM_NONE = -1,
        DUNGEON_MAP_ITEM_CHEST_CLOSED,
        DUNGEON_MAP_ITEM_CHEST_OPEN,
        DUNGEON_MAP_ITEM_NIGHTMARE_KEY
    };

    // Misc inventory items
    enum class InventoryMiscItem
    {
        INVENTORY_MISC_ITEM_NONE = -1,
        INVENTORY_MISC_ITEM_RED_POTION,
        INVENTORY_MISC_ITEM_FLIPPERS,
        INVENTORY_MISC_ITEM_COUNT
    };

    // Rupee types available
    enum class Rupee
    {
        RUPEE_ONE = 1,
        RUPEE_FIVE = 5,
        RUPEE_TEN = 10,
        RUPEE_TWENTY = 20,
        RUPEE_FIFTY = 50,
        RUPEE_HUNDRED = 100,
        RUPEE_TWO_HUNDRED = 200
    };

    // All photographs possible
    enum class Photograph
    {
        PHOTOGRAPH_NONE = -1,
        PHOTOGRAPH_HERE_STANDS_A_BRAVE_MAN,
        PHOTOGRAPH_GAME_OVER,
        PHOTOGRAPH_OCEAN_VIEW,
        PHOTOGRAPH_HEADS_UP,
        PHOTOGRAPH_SAY_MUSHROOM,
        PHOTOGRAPH_LINK_DISCOVERS_ULRIRAS_SECRET,
        PHOTOGRAPH_LINK_PLAYS_WITH_BOWOW,
        PHOTOGRAPH_THIEF,
        PHOTOGRAPH_CANT_SWIM,
        PHOTOGRAPH_I_FOUND_ZORA,
        PHOTOGRAPH_A_REGAL_HOME,
        PHOTOGRAPH_I_WAS_VERY_AFRAID,
        PHOTOGRAPH_CLOSE_CALL,
        PHOTOGRAPH_COUNT
    };

    struct DungeonMapEntry
    {
        uint8_t roomType;
        bool visited;
        DungeonMapItem roomItem;
    };

    class InventoryImpl
    {
    public:
        InventoryImpl();

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
        std::array<Instrument, ENUM_VALUE(Instrument::INSTRUMENT_COUNT)> instruments() const;

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
        std::array<OcarinaSong, ENUM_VALUE(OcarinaSong::OCARINA_SONG_COUNT)> ocarinaSongs() const;

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
        std::array<Photograph, ENUM_VALUE(Photograph::PHOTOGRAPH_COUNT)> photographs() const;
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
        void setDungeonMapLocationVisited(const Vector<int>& location);
        bool dungeonMapLocationVisited(const int x, const int y) const;
        int dungeonMapLocationRoomType(const int x, const int y) const;
        DungeonMapItem dungeonMapLocationRoomItem(const int x, const int y) const;


        void setPositionInDungeonMap(const Vector<int>& location);
        Vector<int> dungeonMapPositionLocation() const;
        void movePositionInDungeonMap(Direction direction);


    private:

        // TODO: Dungeon map hidden room connections when discovered
        // TODO: Ocarina song selection window
        // TODO: Chest and nightmare locations for each dungeon map
        // TODO: Every other dungeon map layout

        // Inventory related variables
        int m_arrows;                   // Number of arrows
        int m_maxArrows;
        int m_bombs;                    // Number of bombs
        int m_maxBombs;
        int m_magicPowder;              // Number of magic powder
        int m_maxMagicPowder;

        OcarinaSong m_ocarinaSong;      // Selected ocarina song
        std::array<OcarinaSong, ENUM_VALUE(OcarinaSong::OCARINA_SONG_COUNT)> m_ocarinaSongs;

        int m_secretSeaShells;                // Number of Seashells
        
        std::array<InventoryMiscItem, ENUM_VALUE(InventoryMiscItem::INVENTORY_MISC_ITEM_COUNT)> m_inventoryMiscItems;

        Tunic m_tunic;                  // Tunic type
        int m_heartContainerPieces;     // Heart container pieces
        int m_goldenLeaves;             // Golden leaves (Shown in Kanalet castle only)
        
        std::array<Photograph, ENUM_VALUE(Photograph::PHOTOGRAPH_COUNT)> m_photographs;

        int m_rupees;                   // Number of rupees 0-999
        TradeItem m_tradeItem;          // Current trade item


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
        std::array<Instrument, ENUM_VALUE(Instrument::INSTRUMENT_COUNT)> m_instruments;

        // Dungeon related items
        bool m_inDungeon;   // Are we in a dungeon? 

        // The keys used to open dungeon entrances
        std::array<DungeonEntranceKey, ENUM_VALUE(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_COUNT)> m_dungeonEntraceKeys;

        // Dungeon items
        std::array<DungeonItemStruct, ENUM_VALUE(Dungeon::DUNGEON_COUNT)> m_dungeonItemsStruct;

        // Link position in dungeon map as a vector position
        Vector<int> m_positionInDungeonMap;

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

        DungeonMapEntry m_dungeonMaps[ENUM_VALUE(Dungeon::DUNGEON_COUNT)][DUNGEON_MAX_BLOCKS_X][DUNGEON_MAX_BLOCKS_Y] =
        {
            {   // Lvl 0 - Colour dungeon
                { {1,false, DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false, DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false, DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false, DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false, DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {6,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {4,false,DungeonMapItem::DUNGEON_MAP_ITEM_NIGHTMARE_KEY},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {3,false,DungeonMapItem::DUNGEON_MAP_ITEM_CHEST_CLOSED}, {8,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {13,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {14,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false, DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {20,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {18,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} }
            },
            {   // Lvl 1 - Tail Cave
                { {1,false, DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false, DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false, DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false, DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false, DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {6,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NIGHTMARE_KEY},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_CHEST_CLOSED}, {8,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {13,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {14,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false, DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {20,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {18,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} }
                // Rooms start at the bottom left of the map here (3, 8);
            },
            {   // Lvl 2 - Bottle Grotto
                { {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {6,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {4,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {3,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {8,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {13,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {14,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {20,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {18,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} }
            },
            {   // Lvl 3 - Key Cavern
                { {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {6,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {4,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {3,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {8,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {13,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {14,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {20,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {18,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} }
            },
            {   // Lvl 4 - Angler Tunnel
                { {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {6,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {4,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {3,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {8,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {13,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {14,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {20,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {18,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} }
            },
            {   // Lvl 5 - Catfish Maw
                { {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {6,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {4,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {3,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {8,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {13,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {14,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {20,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {18,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} }
            },
            {   // Lvl 6 - Face Shrine
                { {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {6,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {4,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {3,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {8,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {13,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {14,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {20,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {18,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} }
            },
            {   // Lvl 7 - Eagle Tower
                { {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {6,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {4,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {3,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {8,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {13,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {14,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {20,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {18,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} }
            },
            {   // Lvl 8 - Turtle Rock
                { {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {6,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {4,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {3,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {8,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {12,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {19,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {17,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{10,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {13,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {14,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {11,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{15,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} },
                { {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {5,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {20,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {18,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},{0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE},  {0,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE}, {1,false,DungeonMapItem::DUNGEON_MAP_ITEM_NONE} }
            }
        };

    };

    template <typename Enum, size_t Size>
    bool InventoryImpl::checkItemExists(const std::array<Enum, Size>& array, Enum item)
    {
        return std::any_of(array.cbegin(), array.cend(), [&item](Enum exists)
        {
            return item == exists;
        });
    }
}