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
        assert(!checkInventoryItemExists(inventoryItem) && "Trying to add weapon that already exists");
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
        assert(checkInventoryItemExists(inventoryItem) && "Trying to remove non-existent weapon");
        auto weaponToRemove = std::find(m_inventoryItems.begin(), m_inventoryItems.end(), inventoryItem);
        *weaponToRemove = InventoryItem{};
    }

    bool InventoryImpl::checkInventoryItemExists(const InventoryItem& inventoryItem) const
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
        assert(!(checkItemExists<DungeonEntranceKey, static_cast<int>(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_COUNT)>(m_dungeonEntraceKeys, dungeonKey)) && "Trying to add dungeon entrance key that already exists");
        auto nextFreeSpace = std::find(m_dungeonEntraceKeys.begin(), m_dungeonEntraceKeys.end(), DungeonEntranceKey::DUNGEON_ENTRACE_KEY_NONE);
        *nextFreeSpace = dungeonKey;
    }

    bool InventoryImpl::dungeonEntranceKey(DungeonEntranceKey dungeonKey) const
    {
        return checkItemExists<DungeonEntranceKey, static_cast<int>(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_COUNT)>(m_dungeonEntraceKeys, dungeonKey);
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

        auto const currentDungeon = static_cast<int>(m_dungeon);

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

        auto const currentDungeon = static_cast<int>(m_dungeon);

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
        auto const dungeonItemStruct = m_dungeonItemsStruct[static_cast<int>(m_dungeon)];
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
        switch (tradeItem)
        {
            case TradeItem::TRADE_ITEM_NONE:
                m_tradeItem = TradeItem::TRADE_ITEM_YOSHI_DOLL;
                break;
            case TradeItem::TRADE_ITEM_YOSHI_DOLL:
                m_tradeItem = TradeItem::TRADE_ITEM_RIBBON;
                break;
            case TradeItem::TRADE_ITEM_RIBBON:
                m_tradeItem = TradeItem::TRADE_ITEM_DOG_FOOD;
                break;
            case TradeItem::TRADE_ITEM_DOG_FOOD:
                m_tradeItem = TradeItem::TRADE_ITEM_BANANAS;
                break;
            case TradeItem::TRADE_ITEM_BANANAS:
                m_tradeItem = TradeItem::TRADE_ITEM_STICK;
                break;
            case TradeItem::TRADE_ITEM_STICK:
                m_tradeItem = TradeItem::TRADE_ITEM_HONEYCOMB;
                break;
            case TradeItem::TRADE_ITEM_HONEYCOMB:
                m_tradeItem = TradeItem::TRADE_ITEM_PINEAPPLE;
                break;
            case TradeItem::TRADE_ITEM_PINEAPPLE:
                m_tradeItem = TradeItem::TRADE_ITEM_HIBISCUS;
                break;
            case TradeItem::TRADE_ITEM_HIBISCUS:
                m_tradeItem = TradeItem::TRADE_ITEM_LETTER;
                break;
            case TradeItem::TRADE_ITEM_LETTER:
                m_tradeItem = TradeItem::TRADE_ITEM_BROOM;
                break;
            case TradeItem::TRADE_ITEM_BROOM:
                m_tradeItem = TradeItem::TRADE_ITEM_FISHING_HOOK;
                break;
            case TradeItem::TRADE_ITEM_FISHING_HOOK:
                m_tradeItem = TradeItem::TRADE_ITEM_MERMAID_NECKLACE;
                break;
            case TradeItem::TRADE_ITEM_MERMAID_NECKLACE:
                m_tradeItem = TradeItem::TRADE_ITEM_MERMAID_SCALE;
                break;
            case TradeItem::TRADE_ITEM_MERMAID_SCALE:
                m_tradeItem = TradeItem::TRADE_ITEM_MAGNIFYING_LENS;
                break;
            case TradeItem::TRADE_ITEM_MAGNIFYING_LENS:
                m_tradeItem = TradeItem::TRADE_ITEM_BOOMERANG;
                break;
            case TradeItem::TRADE_ITEM_BOOMERANG:
                assert(false && "No more items left to trade");
                break;
        }
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
        assert(!(checkItemExists<InventoryMiscItem, static_cast<int>(InventoryMiscItem::INVENTORY_MISC_ITEM_COUNT)>(m_inventoryMiscItems, inventoryMiscItem)) && "Trying to add inventory misc item that already exists");
        auto nextFreeSpace = std::find(m_inventoryMiscItems.begin(), m_inventoryMiscItems.end(), InventoryMiscItem::INVENTORY_MISC_ITEM_NONE);
        *nextFreeSpace = inventoryMiscItem;
    }

    void InventoryImpl::useInventoryMiscItem(InventoryMiscItem inventoryMiscItem)
    {
        assert((checkItemExists<InventoryMiscItem, static_cast<int>(InventoryMiscItem::INVENTORY_MISC_ITEM_COUNT)>(m_inventoryMiscItems, inventoryMiscItem)) && "Trying to use non-existent inventory misc item");

        switch (inventoryMiscItem)
        {
        case InventoryMiscItem::INVENTORY_MISC_ITEM_RED_POTION:
            {
                auto inventoryMiscItemToUse = std::find(m_inventoryMiscItems.begin(), m_inventoryMiscItems.end(), inventoryMiscItem);
                *inventoryMiscItemToUse = InventoryMiscItem::INVENTORY_MISC_ITEM_NONE;
            }
            break;
        default:
            assert(false && "Trying to use non-usable inventory misc item");
        }
        
    }

    bool InventoryImpl::miscItemExists(InventoryMiscItem inventoryMiscItem) const
    {
        return checkItemExists<InventoryMiscItem, static_cast<int>(InventoryMiscItem::INVENTORY_MISC_ITEM_COUNT)>(m_inventoryMiscItems, inventoryMiscItem);
    }

    // Add - Obtain after defeating dungeon boss
    void InventoryImpl::addInstrument(Instrument instrument)
    {        
        assert(!(checkItemExists<Instrument, static_cast<int>(Instrument::INSTRUMENT_COUNT)>(m_instruments, instrument)) && "Trying to add instrument that already exists");
        auto nextFreeSpace = std::find(m_instruments.begin(), m_instruments.end(), Instrument::INSTRUMENT_NONE);
        *nextFreeSpace = instrument;
    }

    std::array<Instrument, static_cast<int>(Instrument::INSTRUMENT_COUNT)> InventoryImpl::instruments() const
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
        m_rupees = rupees;
    }

    void InventoryImpl::setBombLimit(const int limit)
    {
        m_maxBombs = limit;
    }

    void InventoryImpl::setBombs(const int bombs)
    {
        m_bombs = bombs;
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
        m_arrows = arrow;
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
        m_magicPowder = magicPowder;
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
        assert(!(checkItemExists<OcarinaSong, static_cast<int>(OcarinaSong::OCARINA_SONG_COUNT)>(m_ocarinaSongs, ocarinaSong)) && "Trying to add ocarina song that already exists");
        auto nextFreeSpace = std::find(m_ocarinaSongs.begin(), m_ocarinaSongs.end(), OcarinaSong::OCARINA_SONG_NONE);
        *nextFreeSpace = ocarinaSong;
    }

    std::array<OcarinaSong, static_cast<int>(OcarinaSong::OCARINA_SONG_COUNT)> InventoryImpl::ocarinaSongs() const
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
        ++m_heartContainerPieces;
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
        m_heartPieces += heartPiece;
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
        assert(!(checkItemExists<Photograph, static_cast<int>(Photograph::PHOTOGRAPH_COUNT)>(m_photographs, photograph)) && "Trying to add photograph that already exists");
        auto nextFreeSpace = std::find(m_photographs.begin(), m_photographs.end(), Photograph::PHOTOGRAPH_NONE);
        *nextFreeSpace = photograph;
    }

    std::array<Photograph, static_cast<int>(Photograph::PHOTOGRAPH_COUNT)> InventoryImpl::photographs() const
    {
        return m_photographs;
    }

    int InventoryImpl::photograph() const
    {
        int photographs = 0;
        for (auto const& photograph : m_photographs)
        {
            if (photograph == Photograph::PHOTOGRAPH_NONE)
            {
                break;
            }
            ++photographs;
        }
        return photographs;
    }

    void InventoryImpl::addGoldenLeaf()
    {
        ++m_goldenLeaves;
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
        ++m_secretSeaShells;
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
        return m_dungeonMaps[static_cast<int>(m_dungeon)][y][x].roomItem;
    }

    int InventoryImpl::dungeonMapLocationRoomType(const int x, const int y) const
    {
        assert(m_dungeon > Dungeon::DUNGEON_NONE && m_dungeon < Dungeon::DUNGEON_COUNT);
        return m_dungeonMaps[static_cast<int>(m_dungeon)][y][x].roomType;
    }

    bool InventoryImpl::dungeonMapLocationVisited(const int x, const int y) const
    {
        assert(m_dungeon > Dungeon::DUNGEON_NONE && m_dungeon < Dungeon::DUNGEON_COUNT);
        return m_dungeonMaps[static_cast<int>(m_dungeon)][y][x].visited;
    }

    void InventoryImpl::setDungeonMapLocationVisited(const Vector<int>& location)
    {
        assert(m_dungeon > Dungeon::DUNGEON_NONE && m_dungeon < Dungeon::DUNGEON_COUNT);
        m_dungeonMaps[static_cast<int>(m_dungeon)][location.y][location.x].visited = true;
    }

    void InventoryImpl::movePositionInDungeonMap(Direction direction)
    {
        switch (direction)
        {
        case Direction::DIRECTION_DOWN:
            m_positionInDungeonMap.y++;
            break;
        case Direction::DIRECTION_UP:
            m_positionInDungeonMap.y--;
            break;
        case Direction::DIRECTION_RIGHT:
            m_positionInDungeonMap.x++;
            break;
        case Direction::DIRECTION_LEFT:
            m_positionInDungeonMap.x--;
            break;
        }
    }

    void InventoryImpl::moveSelector(Direction direction)
    {
        switch (direction)
        {
        case Direction::DIRECTION_DOWN:
            if (m_selectorIndex == MAX_INVENTORY_ITEMS-1)
            {
                m_selectorIndex = INVENTORY_COLUMNS - 1;
            }
            else if (m_selectorIndex <= MAX_INVENTORY_ITEMS - INVENTORY_COLUMNS)
            {
                m_selectorIndex += INVENTORY_COLUMNS;
            }
            else
            {
                m_selectorIndex = MAX_INVENTORY_ITEMS - m_selectorIndex;
            }            
            break;
        case Direction::DIRECTION_UP:            
            if (m_selectorIndex == 0)
            {
                m_selectorIndex = MAX_INVENTORY_ITEMS - INVENTORY_COLUMNS;
            }
            else if (m_selectorIndex >= INVENTORY_COLUMNS)
            {
                m_selectorIndex -= INVENTORY_COLUMNS;
            }
            else
            {
                m_selectorIndex = MAX_INVENTORY_ITEMS - m_selectorIndex;
            }
            break;
        case Direction::DIRECTION_RIGHT:
            m_selectorIndex = (m_selectorIndex == MAX_INVENTORY_ITEMS - 1 ? 0 : ++m_selectorIndex);
            break;
        case Direction::DIRECTION_LEFT:
            m_selectorIndex = (m_selectorIndex == 0 ? MAX_INVENTORY_ITEMS - 1 : --m_selectorIndex);
            break;
        }
    }
}