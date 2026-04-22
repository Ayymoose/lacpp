#include "Inventory.h"

#include <algorithm>
#include <cassert>

namespace zelda::core
{

Inventory::Inventory()
    : m_arrows(0)
    , m_maxArrows(0)
    , m_bombs(0)
    , m_maxBombs(0)
    , m_magicPowder(0)
    , m_maxMagicPowder(0)
    , m_ocarinaSong(OcarinaSong::OCARINA_SONG_NONE)
    , m_secretSeaShells(0)
    , m_tunic(Tunic::TUNIC_GREEN)
    , m_heartContainerPieces(0)
    , m_goldenLeaves(0)
    , m_rupees(0)
    , m_tradeItem(TradeItem::TRADE_ITEM_NONE)
    , m_heartPieces(0)
    , m_maxHeartPieces(0)
    , m_itemA(InventoryItem{})
    , m_itemB(InventoryItem{})
    , m_selectorIndex(0)
    , m_inDungeon(false)
    , m_positionInDungeonMap(0, 0)
    , m_dungeon(Dungeon::DUNGEON_NONE)
{
    std::fill(m_ocarinaSongs.begin(), m_ocarinaSongs.end(), OcarinaSong::OCARINA_SONG_NONE);
    std::fill(m_inventoryMiscItems.begin(), m_inventoryMiscItems.end(), InventoryMiscItem::INVENTORY_MISC_ITEM_NONE);
    std::fill(m_photographs.begin(), m_photographs.end(), Photograph::PHOTOGRAPH_NONE);
    std::fill(m_inventoryItems.begin(), m_inventoryItems.end(), InventoryItem{});
    std::fill(m_instruments.begin(), m_instruments.end(), Instrument::INSTRUMENT_NONE);
    std::fill(m_dungeonEntraceKeys.begin(), m_dungeonEntraceKeys.end(), DungeonEntranceKey::DUNGEON_ENTRACE_KEY_NONE);
    std::fill(m_dungeonItemsStruct.begin(), m_dungeonItemsStruct.end(), DungeonItemStruct{});
}

void Inventory::addInventoryItem(const InventoryItem& inventoryItem)
{
    assert(!inventoryItemExists(inventoryItem) && "Trying to add weapon that already exists");
    auto nextFreeSpace = std::find(m_inventoryItems.begin(), m_inventoryItems.end(), InventoryItem{});
    assert(nextFreeSpace != m_inventoryItems.end() && "Trying to add weapon to full inventory");
    *nextFreeSpace = inventoryItem;
}

std::array<InventoryItem, MAX_INVENTORY_ITEMS> Inventory::inventoryItems() const
{
    return m_inventoryItems;
}

void Inventory::removeInventoryItem(const InventoryItem& inventoryItem)
{
    assert(inventoryItemExists(inventoryItem) && "Trying to remove non-existent weapon");
    auto weaponToRemove = std::find(m_inventoryItems.begin(), m_inventoryItems.end(), inventoryItem);
    *weaponToRemove = InventoryItem{};
}

bool Inventory::inventoryItemExists(const InventoryItem& inventoryItem) const
{
    if (m_itemA == inventoryItem || m_itemB == inventoryItem)
    {
        return true;
    }
    return std::any_of(m_inventoryItems.cbegin(),
                       m_inventoryItems.cend(),
                       [&inventoryItem](const InventoryItem& item) { return item == inventoryItem; });
}

void Inventory::addDungeonEntranceKey(DungeonEntranceKey dungeonKey)
{
    assert(!(checkItemExists<DungeonEntranceKey,
                             std::to_underlying(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_COUNT)>(m_dungeonEntraceKeys,
                                                                                                dungeonKey))
           && "Trying to add dungeon entrance key that already exists");
    auto nextFreeSpace = std::find(m_dungeonEntraceKeys.begin(),
                                   m_dungeonEntraceKeys.end(),
                                   DungeonEntranceKey::DUNGEON_ENTRACE_KEY_NONE);
    *nextFreeSpace = dungeonKey;
}

bool Inventory::dungeonEntranceKey(DungeonEntranceKey dungeonKey) const
{
    return checkItemExists<DungeonEntranceKey,
                           std::to_underlying(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_COUNT)>(m_dungeonEntraceKeys,
                                                                                              dungeonKey);
}

void Inventory::setInDungeon(const bool inDungeon)
{
    m_inDungeon = inDungeon;
}

bool Inventory::getInDungeon() const
{
    return m_inDungeon;
}

void Inventory::addDungeonItem(DungeonItem dungeonItem)
{
    assert(getInDungeon() && "Trying to add dungeon item when not in dungeon");
    assert(m_dungeon != Dungeon::DUNGEON_NONE);

    auto const currentDungeon = std::to_underlying(m_dungeon);

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

void Inventory::useDungeonItem(DungeonItem dungeonItem)
{
    assert(getInDungeon() && "Trying to add dungeon item when not in dungeon");
    assert(m_dungeon != Dungeon::DUNGEON_NONE);

    auto const currentDungeon = std::to_underlying(m_dungeon);

    switch (dungeonItem)
    {
    case DungeonItem::DUNGEON_ITEM_LOCKED_DOOR_KEY:
        m_dungeonItemsStruct[currentDungeon].lockedDoorKeys--;
        break;
    default:
        assert(false && "Trying to use non-usable dungeon item");
    }
}

int Inventory::dungeonItem(DungeonItem dungeonItem) const
{
    assert(m_dungeon > Dungeon::DUNGEON_NONE && m_dungeon < Dungeon::DUNGEON_COUNT);
    auto const dungeonItemStruct = m_dungeonItemsStruct[std::to_underlying(m_dungeon)];
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
void Inventory::tradeItem(TradeItem tradeItem)
{
    // TODO: Check bad trade
    m_tradeItem = tradeItem;
}

void Inventory::setTradeItem(TradeItem tradeItem)
{
    m_tradeItem = tradeItem;
}

TradeItem Inventory::tradedItem() const
{
    return m_tradeItem;
}

void Inventory::addInventoryMiscItem(InventoryMiscItem inventoryMiscItem)
{
    assert(!(checkItemExists<InventoryMiscItem,
                             std::to_underlying(InventoryMiscItem::INVENTORY_MISC_ITEM_COUNT)>(m_inventoryMiscItems,
                                                                                               inventoryMiscItem))
           && "Trying to add item that already exists");
    auto nextFreeSpace = std::find(m_inventoryMiscItems.begin(),
                                   m_inventoryMiscItems.end(),
                                   InventoryMiscItem::INVENTORY_MISC_ITEM_NONE);
    *nextFreeSpace = inventoryMiscItem;
}

void Inventory::useInventoryMiscItem(InventoryMiscItem inventoryMiscItem)
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

bool Inventory::miscItemExists(InventoryMiscItem inventoryMiscItem) const
{
    return checkItemExists(m_inventoryMiscItems, inventoryMiscItem);
}

bool Inventory::instrumentExists(Instrument instrument) const
{
    return checkItemExists<Instrument, std::to_underlying(Instrument::INSTRUMENT_COUNT)>(m_instruments, instrument);
}

// Add - Obtain after defeating dungeon boss
void Inventory::addInstrument(Instrument instrument)
{
    assert(!instrumentExists(instrument) && "Trying to add item that already exists");
    auto nextFreeSpace = std::find(m_instruments.begin(), m_instruments.end(), Instrument::INSTRUMENT_NONE);
    *nextFreeSpace = instrument;
}

std::array<Instrument, std::to_underlying(Instrument::INSTRUMENT_COUNT)> Inventory::instruments() const
{
    return m_instruments;
}

void Inventory::addRupee()
{
    m_rupees = std::min(m_rupees + 1, MAX_RUPEES);
}

void Inventory::useRupee()
{
    m_rupees = std::max(m_rupees - 1, 0);
}

int Inventory::rupees() const
{
    return m_rupees;
}

void Inventory::setRupees(const int rupees)
{
    m_rupees = std::min(rupees, MAX_RUPEES);
}

void Inventory::setBombLimit(const int limit)
{
    m_maxBombs = limit;
}

void Inventory::setBombs(const int bombs)
{
    m_bombs = std::min(bombs, m_maxBombs);
}

void Inventory::useBomb()
{
    m_bombs = std::max(m_bombs - 1, 0);
}

int Inventory::bombs() const
{
    return m_bombs;
}

void Inventory::setArrowLimit(const int limit)
{
    m_maxArrows = limit;
}

void Inventory::setArrows(const int arrow)
{
    m_arrows = std::min(arrow, m_maxArrows);
}

void Inventory::useArrow()
{
    m_arrows = std::max(m_arrows - 1, 0);
}

int Inventory::arrows() const
{
    return m_arrows;
}

void Inventory::setMagicPowderLimit(const int limit)
{
    m_maxMagicPowder = limit;
}

void Inventory::setMagicPowder(const int magicPowder)
{
    m_magicPowder = std::min(magicPowder, m_maxMagicPowder);
}

void Inventory::useMagicPowder()
{
    m_magicPowder = std::max(m_magicPowder - 1, 0);
}

int Inventory::magicPowder() const
{
    return m_magicPowder;
}

void Inventory::addOcarinaSong(OcarinaSong ocarinaSong)
{
    assert(!(checkItemExists<OcarinaSong, std::to_underlying(OcarinaSong::OCARINA_SONG_COUNT)>(m_ocarinaSongs,
                                                                                               ocarinaSong))
           && "Trying to add item that already exists");
    auto nextFreeSpace = std::find(m_ocarinaSongs.begin(), m_ocarinaSongs.end(), OcarinaSong::OCARINA_SONG_NONE);
    *nextFreeSpace = ocarinaSong;
}

std::array<OcarinaSong, std::to_underlying(OcarinaSong::OCARINA_SONG_COUNT)> Inventory::ocarinaSongs() const
{
    return m_ocarinaSongs;
}

void Inventory::setOcarinaSong(OcarinaSong ocarinaSong)
{
    m_ocarinaSong = ocarinaSong;
}

// Get selected song
OcarinaSong Inventory::ocarinaSong() const
{
    return m_ocarinaSong;
}

// Add - Only set once
void Inventory::addTunic(Tunic tunic)
{
    assert(tunic != m_tunic && "Trying to add tunic that already exists");
    m_tunic = tunic;
}

// Currently worn tunic
Tunic Inventory::tunic() const
{
    return m_tunic;
}

void Inventory::setTunic(Tunic tunic)
{
    m_tunic = tunic;
}

void Inventory::addHeartContainerPiece()
{
    m_heartContainerPieces = std::min(m_heartContainerPieces + 1, HEARTS_PIECE_MAX);
}

void Inventory::setHeartContainerPieces(const int heartContainerPieces)
{
    m_heartContainerPieces = heartContainerPieces;
}

int Inventory::heartContainerPieces() const
{
    return m_heartContainerPieces;
}

// Add heart pieces
void Inventory::addHeartPiece(const float heartPiece)
{
    m_heartPieces = std::fmin(m_maxHeartPieces, m_heartPieces + heartPiece);
}

// "Use" heart piece when damage incurred
void Inventory::useHeartPiece(const float heartPiece)
{
    m_heartPieces = std::fmax(0, m_heartPieces - heartPiece);
}

void Inventory::setHeartPieces(const float heartPieces)
{
    m_heartPieces = heartPieces;
}

void Inventory::setMaxHeartPieces(const float maxHeartPieces)
{
    m_maxHeartPieces = maxHeartPieces;
}

float Inventory::heartPieces() const
{
    return m_heartPieces;
}

float Inventory::maxHeartPieces() const
{
    return m_maxHeartPieces;
}

void Inventory::addPhotograph(Photograph photograph)
{
    assert(!(checkItemExists<Photograph, std::to_underlying(Photograph::PHOTOGRAPH_COUNT)>(m_photographs, photograph))
           && "Trying to add item that already exists");
    auto nextFreeSpace = std::find(m_photographs.begin(), m_photographs.end(), Photograph::PHOTOGRAPH_NONE);
    *nextFreeSpace = photograph;
}

std::array<Photograph, std::to_underlying(Photograph::PHOTOGRAPH_COUNT)> Inventory::photographs() const
{
    return m_photographs;
}

int Inventory::photograph() const
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

void Inventory::addGoldenLeaf()
{
    m_goldenLeaves = std::min(m_goldenLeaves + 1, MAX_GOLDEN_LEAVES);
}

// Add golden leaves from Kanalet castle
void Inventory::setGoldenLeaves(const int goldenLeaves)
{
    m_goldenLeaves = goldenLeaves;
}

// Number of golden leaves we have
int Inventory::goldenLeaves() const
{
    return m_goldenLeaves;
}

void Inventory::addSecretSeaShell()
{
    m_secretSeaShells = std::min(m_secretSeaShells + 1, MAX_SECRET_SEASHELLS);
}

void Inventory::setSecretSeaShells(const int secretShells)
{
    m_secretSeaShells = secretShells;
}

int Inventory::secretSeaShells()
{
    return m_secretSeaShells;
}

InventoryItem Inventory::itemA() const
{
    return m_itemA;
}

InventoryItem Inventory::itemB() const
{
    return m_itemB;
}

void Inventory::swapItemA()
{
    std::swap(m_itemA, m_inventoryItems[m_selectorIndex]);
}

void Inventory::swapItemB()
{
    std::swap(m_itemB, m_inventoryItems[m_selectorIndex]);
}

void Inventory::setItemA(const InventoryItem& itemA)
{
    m_itemA = itemA;
}

void Inventory::setItemB(const InventoryItem& itemB)
{
    m_itemB = itemB;
}

void Inventory::setPositionInDungeonMap(const engine::Vector<int>& location)
{
    m_positionInDungeonMap = location;
}

engine::Vector<int> Inventory::dungeonMapPositionLocation() const
{
    return m_positionInDungeonMap;
}

void Inventory::setDungeon(Dungeon dungeon)
{
    m_dungeon = dungeon;
}

Dungeon Inventory::dungeon() const
{
    return m_dungeon;
}

DungeonMapItem Inventory::dungeonMapLocationRoomItem(const int x, const int y) const
{
    assert(m_dungeon > Dungeon::DUNGEON_NONE && m_dungeon < Dungeon::DUNGEON_COUNT);
    return m_dungeonMaps[std::to_underlying(m_dungeon)][y][x].roomItem;
}

int Inventory::dungeonMapLocationRoomType(const int x, const int y) const
{
    assert(m_dungeon > Dungeon::DUNGEON_NONE && m_dungeon < Dungeon::DUNGEON_COUNT);
    return m_dungeonMaps[std::to_underlying(m_dungeon)][y][x].roomType;
}

bool Inventory::dungeonMapLocationVisited(const int x, const int y) const
{
    assert(m_dungeon > Dungeon::DUNGEON_NONE && m_dungeon < Dungeon::DUNGEON_COUNT);
    return m_dungeonMaps[std::to_underlying(m_dungeon)][y][x].visited;
}

void Inventory::setDungeonMapLocationVisited(const engine::Vector<int>& location)
{
    assert(m_dungeon > Dungeon::DUNGEON_NONE && m_dungeon < Dungeon::DUNGEON_COUNT);
    m_dungeonMaps[std::to_underlying(m_dungeon)][location.y][location.x].visited = true;
}

void Inventory::movePositionInDungeonMap(Direction direction)
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
    default:
        break;
    }
}

void Inventory::moveInventorySelector(Direction direction)
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
            m_selectorIndex = MAX_INVENTORY_ITEMS - 1;
        }
        else
        {
            m_selectorIndex -= INVENTORY_COLUMNS;
        }
        break;
    case Direction::DIRECTION_RIGHT:
        m_selectorIndex = (m_selectorIndex == MAX_INVENTORY_ITEMS - 1 ? 0 : m_selectorIndex + 1);
        break;
    case Direction::DIRECTION_LEFT:
        m_selectorIndex = (m_selectorIndex == 0 ? MAX_INVENTORY_ITEMS - 1 : m_selectorIndex - 1);
        break;
    default:
        break;
    }

    assert(m_selectorIndex >= 0 && m_selectorIndex < MAX_INVENTORY_ITEMS);
}
} // namespace zelda::core