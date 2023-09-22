#include "InventoryImpl.h"

#include <algorithm>
#include <cassert>

namespace Zelda
{

    InventoryImpl::InventoryImpl() : 
        m_arrows(0),
        m_maxArrows(0),
        m_bombs(0),
        m_maxBombs(0),
        m_magicPowder(0),
        m_maxMagicPowder(0),
        m_ocarinaSong(OcarinaSong::OCARINA_SONG_NONE),
        m_secretSeaShells(0),
        m_tunic(Tunic::TUNIC_GREEN),
        m_heartContainerPieces(0),
        m_goldenLeaves(0),
        m_rupees(0),
        m_tradeItem(TradeItem::TRADE_ITEM_NONE),
        m_heartPieces(0),
        m_maxHeartPieces(0),
        m_itemA(InventoryItem{}),
        m_itemB(InventoryItem{}),
        m_selectorIndex(0),
        m_inDungeon(false),
        m_positionInDungeonMap(0,0),
        m_dungeon(Dungeon::DUNGEON_NONE)
    {
        std::fill(m_ocarinaSongs.begin(), m_ocarinaSongs.end(), OcarinaSong::OCARINA_SONG_NONE);
        std::fill(m_inventoryMiscItems.begin(), m_inventoryMiscItems.end(), InventoryMiscItem::INVENTORY_MISC_ITEM_NONE);
        std::fill(m_photographs.begin(), m_photographs.end(), Photograph::PHOTOGRAPH_NONE);
        std::fill(m_inventoryItems.begin(), m_inventoryItems.end(), InventoryItem{});
        std::fill(m_instruments.begin(), m_instruments.end(), Instrument::INSTRUMENT_NONE);
        std::fill(m_dungeonEntraceKeys.begin(), m_dungeonEntraceKeys.end(), DungeonEntranceKey::DUNGEON_ENTRACE_KEY_NONE);
        std::fill(m_dungeonItemsStruct.begin(), m_dungeonItemsStruct.end(), DungeonItemStruct{});
    }

    void InventoryImpl::addInventoryItem(const InventoryItem& inventoryItem)
    {
        assert(!inventoryItemExists(inventoryItem) && "Trying to add weapon that already exists");
        auto nextFreeSpace = std::find(m_inventoryItems.begin(), m_inventoryItems.end(), InventoryItem{});
        assert(nextFreeSpace != m_inventoryItems.end() && "Trying to add weapon to full inventory");
        *nextFreeSpace = inventoryItem;
    }

    std::array<InventoryItem, MAX_INVENTORY_ITEMS> InventoryImpl::inventoryItems() const
    {
        return m_inventoryItems;
    }

    void InventoryImpl::removeInventoryItem(const InventoryItem& inventoryItem)
    {
        assert(inventoryItemExists(inventoryItem) && "Trying to remove non-existent weapon");
        auto weaponToRemove = std::find(m_inventoryItems.begin(), m_inventoryItems.end(), inventoryItem);
        *weaponToRemove = InventoryItem{};
    }

    bool InventoryImpl::inventoryItemExists(const InventoryItem& inventoryItem) const
    {
        if (m_itemA == inventoryItem || m_itemB == inventoryItem)
        {
            return true;
        }
        return std::any_of(m_inventoryItems.cbegin(), m_inventoryItems.cend(), [&inventoryItem](const InventoryItem& item)
        {
            return item == inventoryItem;
        });
    }

    void InventoryImpl::addDungeonEntranceKey(DungeonEntranceKey dungeonKey)
    {
        assert(!(checkItemExists<DungeonEntranceKey, ENUM_VALUE(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_COUNT)>(m_dungeonEntraceKeys, dungeonKey)) && "Trying to add dungeon entrance key that already exists");
        auto nextFreeSpace = std::find(m_dungeonEntraceKeys.begin(), m_dungeonEntraceKeys.end(), DungeonEntranceKey::DUNGEON_ENTRACE_KEY_NONE);
        *nextFreeSpace = dungeonKey;
    }

    bool InventoryImpl::dungeonEntranceKey(DungeonEntranceKey dungeonKey) const
    {
        return checkItemExists<DungeonEntranceKey, ENUM_VALUE(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_COUNT)>(m_dungeonEntraceKeys, dungeonKey);
    }

    void InventoryImpl::setInDungeon(const bool inDungeon)
    {
        m_inDungeon = inDungeon;
    }

    bool InventoryImpl::getInDungeon() const
    {
        return m_inDungeon;
    }

    void InventoryImpl::addDungeonItem(DungeonItem dungeonItem)
    {
        assert(getInDungeon() && "Trying to add dungeon item when not in dungeon");
        assert(m_dungeon != Dungeon::DUNGEON_NONE);

        auto const currentDungeon = ENUM_VALUE(m_dungeon);

        switch (dungeonItem)
        {
        case DungeonItem::DUNGEON_ITEM_LOCKED_DOOR_KEY:
            ++m_dungeonItemsStruct[currentDungeon].lockedDoorKeys;
            break;
        case DungeonItem::DUNGEON_ITEM_COMPASS:
            m_dungeonItemsStruct[currentDungeon].compass = 1;
            break;
        case DungeonItem::DUNGEON_ITEM_MAP:
            m_dungeonItemsStruct[currentDungeon].dungeonMap = 1;
            break;
        case DungeonItem::DUNGEON_ITEM_NIGHTMARE_KEY:
            m_dungeonItemsStruct[currentDungeon].nightmareKey = 1;
            break;
        case DungeonItem::DUNGEON_ITEM_OWL_BEAK:
            m_dungeonItemsStruct[currentDungeon].owlBeak = 1;
            break;
        default:
            assert(false);
        }

    }

    void InventoryImpl::useDungeonItem(DungeonItem dungeonItem)
    {
        assert(getInDungeon() && "Trying to add dungeon item when not in dungeon");
        assert(m_dungeon != Dungeon::DUNGEON_NONE);

        auto const currentDungeon = ENUM_VALUE(m_dungeon);

        switch (dungeonItem)
        {
        case DungeonItem::DUNGEON_ITEM_LOCKED_DOOR_KEY:
            m_dungeonItemsStruct[currentDungeon].lockedDoorKeys--;
            break;
        default:
            assert(false && "Trying to use non-usable dungeon item");
        }

    }

    int InventoryImpl::dungeonItem(DungeonItem dungeonItem) const
    {
        assert(m_dungeon > Dungeon::DUNGEON_NONE && m_dungeon < Dungeon::DUNGEON_COUNT);
        auto const dungeonItemStruct = m_dungeonItemsStruct[ENUM_VALUE(m_dungeon)];
        switch (dungeonItem)
        {
        case DungeonItem::DUNGEON_ITEM_COMPASS:
            return dungeonItemStruct.compass;
        case DungeonItem::DUNGEON_ITEM_MAP:
            return dungeonItemStruct.dungeonMap;
        case DungeonItem::DUNGEON_ITEM_OWL_BEAK:
            return dungeonItemStruct.owlBeak;
        case DungeonItem::DUNGEON_ITEM_NIGHTMARE_KEY:
            return dungeonItemStruct.nightmareKey;
        case DungeonItem::DUNGEON_ITEM_LOCKED_DOOR_KEY:
            return dungeonItemStruct.lockedDoorKeys;
        default:
            assert(false);
            return 0;
        }
    }

    // Trade item up the chain
    void InventoryImpl::tradeItem(TradeItem tradeItem)
    {
        if (!(m_tradeItem == TradeItem::TRADE_ITEM_NONE && tradeItem == TradeItem::TRADE_ITEM_YOSHI_DOLL
            || (m_tradeItem == TradeItem::TRADE_ITEM_YOSHI_DOLL && tradeItem == TradeItem::TRADE_ITEM_RIBBON)
            || (m_tradeItem == TradeItem::TRADE_ITEM_RIBBON && tradeItem == TradeItem::TRADE_ITEM_DOG_FOOD)
            || (m_tradeItem == TradeItem::TRADE_ITEM_DOG_FOOD && tradeItem == TradeItem::TRADE_ITEM_BANANAS)
            || (m_tradeItem == TradeItem::TRADE_ITEM_BANANAS && tradeItem == TradeItem::TRADE_ITEM_STICK)
            || (m_tradeItem == TradeItem::TRADE_ITEM_STICK && tradeItem == TradeItem::TRADE_ITEM_HONEYCOMB)
            || (m_tradeItem == TradeItem::TRADE_ITEM_HONEYCOMB && tradeItem == TradeItem::TRADE_ITEM_PINEAPPLE)
            || (m_tradeItem == TradeItem::TRADE_ITEM_PINEAPPLE && tradeItem == TradeItem::TRADE_ITEM_HIBISCUS)
            || (m_tradeItem == TradeItem::TRADE_ITEM_HIBISCUS && tradeItem == TradeItem::TRADE_ITEM_LETTER)
            || (m_tradeItem == TradeItem::TRADE_ITEM_LETTER && tradeItem == TradeItem::TRADE_ITEM_BROOM)
            || (m_tradeItem == TradeItem::TRADE_ITEM_BROOM && tradeItem == TradeItem::TRADE_ITEM_FISHING_HOOK)
            || (m_tradeItem == TradeItem::TRADE_ITEM_FISHING_HOOK && tradeItem == TradeItem::TRADE_ITEM_MERMAID_NECKLACE)
            || (m_tradeItem == TradeItem::TRADE_ITEM_MERMAID_NECKLACE && tradeItem == TradeItem::TRADE_ITEM_MERMAID_SCALE)
            || (m_tradeItem == TradeItem::TRADE_ITEM_MERMAID_SCALE && tradeItem == TradeItem::TRADE_ITEM_MAGNIFYING_LENS)
            || (m_tradeItem == TradeItem::TRADE_ITEM_MAGNIFYING_LENS && tradeItem == TradeItem::TRADE_ITEM_BOOMERANG)))
        {
            assert(false && "Bad trade");
        }

        m_tradeItem = tradeItem;
    }

    void InventoryImpl::setTradeItem(TradeItem tradeItem)
    {
        m_tradeItem = tradeItem;
    }

    TradeItem InventoryImpl::tradedItem() const
    {
        return m_tradeItem;
    }

    void InventoryImpl::addInventoryMiscItem(InventoryMiscItem inventoryMiscItem)
    {
        assert(!(checkItemExists<InventoryMiscItem, ENUM_VALUE(InventoryMiscItem::INVENTORY_MISC_ITEM_COUNT)>(m_inventoryMiscItems, inventoryMiscItem)) && "Trying to add item that already exists");
        auto nextFreeSpace = std::find(m_inventoryMiscItems.begin(), m_inventoryMiscItems.end(), InventoryMiscItem::INVENTORY_MISC_ITEM_NONE);
        *nextFreeSpace = inventoryMiscItem;
    }

    void InventoryImpl::useInventoryMiscItem(InventoryMiscItem inventoryMiscItem)
    {
        assert(miscItemExists(inventoryMiscItem) && "Trying to use non-existent misc item");
        auto it = std::find(m_inventoryMiscItems.begin(), m_inventoryMiscItems.end(), inventoryMiscItem);
        
        switch (inventoryMiscItem)
        {
        case InventoryMiscItem::INVENTORY_MISC_ITEM_RED_POTION:
            *it = InventoryMiscItem::INVENTORY_MISC_ITEM_NONE;
            break;
        default:
            assert(false && "Trying to use non-usable inventory misc item");
        }
        
    }

    bool InventoryImpl::miscItemExists(InventoryMiscItem inventoryMiscItem) const
    {
        return checkItemExists(m_inventoryMiscItems, inventoryMiscItem);
    }

    bool InventoryImpl::instrumentExists(Instrument instrument) const
    {
        return checkItemExists<Instrument, ENUM_VALUE(Instrument::INSTRUMENT_COUNT)>(m_instruments, instrument);
    }

    // Add - Obtain after defeating dungeon boss
    void InventoryImpl::addInstrument(Instrument instrument)
    {      
        assert(!instrumentExists(instrument) && "Trying to add item that already exists");
        auto nextFreeSpace = std::find(m_instruments.begin(), m_instruments.end(), Instrument::INSTRUMENT_NONE);
        *nextFreeSpace = instrument;
    }

    std::array<Instrument, ENUM_VALUE(Instrument::INSTRUMENT_COUNT)> InventoryImpl::instruments() const
    {
        return m_instruments;
    }

    void InventoryImpl::addRupee()
    {
        m_rupees = std::min(++m_rupees, MAX_RUPEES);
    }

    void InventoryImpl::useRupee()
    {
        m_rupees = std::max(--m_rupees, 0);
    }

    int InventoryImpl::rupees() const
    {
        return m_rupees;
    }

    void InventoryImpl::setRupees(const int rupees)
    {
        m_rupees = std::min(rupees, MAX_RUPEES);
    }

    void InventoryImpl::setBombLimit(const int limit)
    {
        m_maxBombs = limit;
    }

    void InventoryImpl::setBombs(const int bombs)
    {
        m_bombs = std::min(bombs, m_maxBombs);
    }

    void InventoryImpl::useBomb()
    {
        m_bombs = std::max(--m_bombs, 0);
    }

    int InventoryImpl::bombs() const
    {
        return m_bombs;
    }

    void InventoryImpl::setArrowLimit(const int limit)
    {
        m_maxArrows = limit;
    }

    void InventoryImpl::setArrows(const int arrow)
    {
        m_arrows = std::min(arrow, m_maxArrows);
    }

    void InventoryImpl::useArrow()
    {
        m_arrows = std::max(--m_arrows, 0);
    }

    int InventoryImpl::arrows() const
    {
        return m_arrows;
    }

    void InventoryImpl::setMagicPowderLimit(const int limit)
    {
        m_maxMagicPowder = limit;
    }

    void InventoryImpl::setMagicPowder(const int magicPowder)
    {
        m_magicPowder = std::min(magicPowder, m_maxMagicPowder);
    }

    void InventoryImpl::useMagicPowder()
    {
        m_magicPowder = std::max(--m_magicPowder, 0);
    }

    int InventoryImpl::magicPowder() const
    {
        return m_magicPowder;
    }

    void InventoryImpl::addOcarinaSong(OcarinaSong ocarinaSong)
    {
        assert(!(checkItemExists<OcarinaSong, ENUM_VALUE(OcarinaSong::OCARINA_SONG_COUNT)>(m_ocarinaSongs, ocarinaSong)) && "Trying to add item that already exists");
        auto nextFreeSpace = std::find(m_ocarinaSongs.begin(), m_ocarinaSongs.end(), OcarinaSong::OCARINA_SONG_NONE);
        *nextFreeSpace = ocarinaSong;
    }

    std::array<OcarinaSong, ENUM_VALUE(OcarinaSong::OCARINA_SONG_COUNT)> InventoryImpl::ocarinaSongs() const
    {
        return m_ocarinaSongs;
    }

    void InventoryImpl::setOcarinaSong(OcarinaSong ocarinaSong)
    {
        m_ocarinaSong = ocarinaSong;
    }

    // Get selected song
    OcarinaSong InventoryImpl::ocarinaSong() const
    {
        return m_ocarinaSong;
    }

    // Add - Only set once
    void InventoryImpl::addTunic(Tunic tunic)
    {
        assert(tunic != m_tunic && "Trying to add tunic that already exists");
        m_tunic = tunic;
    }

    // Currently worn tunic
    Tunic InventoryImpl::tunic() const
    {
        return m_tunic;
    }

    void InventoryImpl::setTunic(Tunic tunic)
    {
        m_tunic = tunic;
    }

    void InventoryImpl::addHeartContainerPiece()
    {
        m_heartContainerPieces = std::min(++m_heartContainerPieces, HEARTS_PIECE_MAX);
    }

    void InventoryImpl::setHeartContainerPieces(const int heartContainerPieces)
    {
        m_heartContainerPieces = heartContainerPieces;
    }

    int InventoryImpl::heartContainerPieces() const
    {
        return m_heartContainerPieces;
    }

    // Add heart pieces
    void InventoryImpl::addHeartPiece(const float heartPiece)
    {
        m_heartPieces = std::fmin(m_maxHeartPieces, m_heartPieces + heartPiece);
    }

    // "Use" heart piece when damage incurred
    void InventoryImpl::useHeartPiece(const float heartPiece)
    {
        m_heartPieces = std::fmax(0, m_heartPieces - heartPiece);
    }

    void InventoryImpl::setHeartPieces(const float heartPieces)
    {
        m_heartPieces = heartPieces;
    }

    void InventoryImpl::setMaxHeartPieces(const float maxHeartPieces)
    {
        m_maxHeartPieces = maxHeartPieces;
    }

    float InventoryImpl::heartPieces() const
    {
        return m_heartPieces;
    }

    float InventoryImpl::maxHeartPieces() const
    {
        return m_maxHeartPieces;
    }

    void InventoryImpl::addPhotograph(Photograph photograph)
    {
        assert(!(checkItemExists<Photograph, ENUM_VALUE(Photograph::PHOTOGRAPH_COUNT)>(m_photographs, photograph)) && "Trying to add item that already exists");
        auto nextFreeSpace = std::find(m_photographs.begin(), m_photographs.end(), Photograph::PHOTOGRAPH_NONE);
        *nextFreeSpace = photograph;
    }

    std::array<Photograph, ENUM_VALUE(Photograph::PHOTOGRAPH_COUNT)> InventoryImpl::photographs() const
    {
        return m_photographs;
    }

    int InventoryImpl::photograph() const
    {
        int photographs = 0;
        for (auto const& photograph : m_photographs)
        {
            if (photograph != Photograph::PHOTOGRAPH_NONE)
            {
                ++photographs;
            }
        }
        return photographs;
    }

    void InventoryImpl::addGoldenLeaf()
    {
        m_goldenLeaves = std::min(++m_goldenLeaves, MAX_GOLDEN_LEAVES);
    }

    // Add golden leaves from Kanalet castle
    void InventoryImpl::setGoldenLeaves(const int goldenLeaves)
    {
        m_goldenLeaves = goldenLeaves;
    }

    // Number of golden leaves we have
    int InventoryImpl::goldenLeaves() const
    {
        return m_goldenLeaves;
    }

    void InventoryImpl::addSecretSeaShell()
    {
        m_secretSeaShells = std::min(++m_secretSeaShells, MAX_SECRET_SEASHELLS);
    }

    void InventoryImpl::setSecretSeaShells(const int secretShells)
    {
        m_secretSeaShells = secretShells;
    }

    int InventoryImpl::secretSeaShells()
    {
        return m_secretSeaShells;
    }
    
    InventoryItem InventoryImpl::itemA() const
    {
        return m_itemA;
    }

    InventoryItem InventoryImpl::itemB() const
    {
        return m_itemB;
    }

    void InventoryImpl::swapItemA()
    {
        std::swap(m_itemA, m_inventoryItems[m_selectorIndex]);
    }

    void InventoryImpl::swapItemB()
    {
        std::swap(m_itemB, m_inventoryItems[m_selectorIndex]);
    }

    void InventoryImpl::setItemA(const InventoryItem& itemA)
    {
        m_itemA = itemA;
    }

    void InventoryImpl::setItemB(const InventoryItem& itemB)
    {
        m_itemB = itemB;
    }

    void InventoryImpl::setPositionInDungeonMap(const Vector<int>& location)
    {
        m_positionInDungeonMap = location;
    }

    Vector<int> InventoryImpl::dungeonMapPositionLocation() const
    {
        return m_positionInDungeonMap;
    }

    void InventoryImpl::setDungeon(Dungeon dungeon)
    {
        m_dungeon = dungeon;
    }

    Dungeon InventoryImpl::dungeon() const
    {
        return m_dungeon;
    }

    DungeonMapItem InventoryImpl::dungeonMapLocationRoomItem(const int x, const int y) const
    {
        assert(m_dungeon > Dungeon::DUNGEON_NONE && m_dungeon < Dungeon::DUNGEON_COUNT);
        return m_dungeonMaps[ENUM_VALUE(m_dungeon)][y][x].roomItem;
    }

    int InventoryImpl::dungeonMapLocationRoomType(const int x, const int y) const
    {
        assert(m_dungeon > Dungeon::DUNGEON_NONE && m_dungeon < Dungeon::DUNGEON_COUNT);
        return m_dungeonMaps[ENUM_VALUE(m_dungeon)][y][x].roomType;
    }

    bool InventoryImpl::dungeonMapLocationVisited(const int x, const int y) const
    {
        assert(m_dungeon > Dungeon::DUNGEON_NONE && m_dungeon < Dungeon::DUNGEON_COUNT);
        return m_dungeonMaps[ENUM_VALUE(m_dungeon)][y][x].visited;
    }

    void InventoryImpl::setDungeonMapLocationVisited(const Vector<int>& location)
    {
        assert(m_dungeon > Dungeon::DUNGEON_NONE && m_dungeon < Dungeon::DUNGEON_COUNT);
        m_dungeonMaps[ENUM_VALUE(m_dungeon)][location.y][location.x].visited = true;
    }

    void InventoryImpl::movePositionInDungeonMap(Direction direction)
    {
        switch (direction)
        {
        case Direction::DIRECTION_DOWN:
            ++m_positionInDungeonMap.y;
            break;
        case Direction::DIRECTION_UP:
            --m_positionInDungeonMap.y;
            break;
        case Direction::DIRECTION_RIGHT:
            ++m_positionInDungeonMap.x;
            break;
        case Direction::DIRECTION_LEFT:
            --m_positionInDungeonMap.x;
            break;
        }
    }

    void InventoryImpl::moveInventorySelector(Direction direction)
    {
        switch (direction)
        {
        case Direction::DIRECTION_DOWN:
            if (m_selectorIndex >= MAX_INVENTORY_ITEMS - INVENTORY_COLUMNS)
            {
                m_selectorIndex = 0;
            }
            else
            {
                m_selectorIndex += INVENTORY_COLUMNS;
            }         
            break;
        case Direction::DIRECTION_UP:            
            if (m_selectorIndex < INVENTORY_COLUMNS)
            {
                m_selectorIndex = MAX_INVENTORY_ITEMS-1;
            }
            else
            {
                m_selectorIndex -= INVENTORY_COLUMNS;
            }
            break;
        case Direction::DIRECTION_RIGHT:
            m_selectorIndex = (m_selectorIndex == MAX_INVENTORY_ITEMS - 1 ? 0 : ++m_selectorIndex);
            break;
        case Direction::DIRECTION_LEFT:
            m_selectorIndex = (m_selectorIndex == 0 ? MAX_INVENTORY_ITEMS - 1 : --m_selectorIndex);
            break;
        }

        assert(m_selectorIndex >= 0 && m_selectorIndex < MAX_INVENTORY_ITEMS);
    }
}