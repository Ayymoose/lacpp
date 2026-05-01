#include "Inventory.h"

#include <algorithm>
#include <cassert>

namespace zelda::core
{

Inventory::Inventory()
{
    std::ranges::fill(m_ocarinaSongs, OcarinaSong::NONE);
    std::ranges::fill(m_miscItems, MiscItem::NONE);
    std::ranges::fill(m_photographs, Photograph::NONE);
    std::ranges::fill(m_inventoryItems, Item{});
    std::ranges::fill(m_instruments, Instrument::NONE);
    std::ranges::fill(m_dungeonEntranceKeys, Dungeon::EntranceKey::NONE);
    std::ranges::fill(m_dungeonItems, Dungeon::Items{});
}

void Inventory::addInventoryItem(const Item& item)
{
    assert(!inventoryItemExists(item) && "Trying to add weapon that already exists");
    auto nextFreeSpace = std::ranges::find(m_inventoryItems, Item{});
    assert(nextFreeSpace != m_inventoryItems.end() && "Trying to add weapon to full inventory");
    *nextFreeSpace = item;
}

std::array<Inventory::Item, Inventory::MAX_ITEMS> Inventory::inventoryItems() const
{
    return m_inventoryItems;
}

void Inventory::removeInventoryItem(const Item& item)
{
    assert(inventoryItemExists(item) && "Trying to remove non-existent weapon");
    auto itemToRemove = std::ranges::find(m_inventoryItems, item);
    *itemToRemove = Item{};
}

bool Inventory::inventoryItemExists(const Item& item) const
{
    if (m_itemA == item || m_itemB == item)
    {
        return true;
    }
    return std::ranges::any_of(m_inventoryItems, [&item](const Item& i) { return item == i; });
}

void Inventory::addDungeonEntranceKey(Dungeon::EntranceKey key)
{
    assert(
        !(checkItemExists<Dungeon::EntranceKey, std::to_underlying(Dungeon::EntranceKey::COUNT)>(m_dungeonEntranceKeys,
                                                                                                 key))
        && "Trying to add dungeon entrance key that already exists");
    auto nextFreeSpace = std::ranges::find(m_dungeonEntranceKeys, Dungeon::EntranceKey::NONE);
    *nextFreeSpace = key;
}

bool Inventory::dungeonEntranceKey(Dungeon::EntranceKey key) const
{
    return checkItemExists<Dungeon::EntranceKey, std::to_underlying(Dungeon::EntranceKey::COUNT)>(m_dungeonEntranceKeys,
                                                                                                  key);
}

void Inventory::setInDungeon(bool inDungeon)
{
    m_inDungeon = inDungeon;
}

bool Inventory::inDungeon() const
{
    return m_inDungeon;
}

void Inventory::addDungeonItem(Dungeon::Item item)
{
    assert(inDungeon() && "Trying to add dungeon item when not in dungeon");
    assert(m_dungeon != Dungeon::Name::NONE);

    const auto currentDungeon = std::to_underlying(m_dungeon);

    switch (item)
    {
    case Dungeon::Item::LOCKED_DOOR_KEY:
        ++m_dungeonItems[currentDungeon].lockedDoorKeys;
        break;
    case Dungeon::Item::COMPASS:
        m_dungeonItems[currentDungeon].compass = true;
        break;
    case Dungeon::Item::MAP:
        m_dungeonItems[currentDungeon].dungeonMap = true;
        break;
    case Dungeon::Item::NIGHTMARE_KEY:
        m_dungeonItems[currentDungeon].nightmareKey = true;
        break;
    case Dungeon::Item::OWL_BEAK:
        m_dungeonItems[currentDungeon].owlBeak = true;
        break;
    default:
        std::unreachable();
    }
}

void Inventory::useDungeonItem(Dungeon::Item item)
{
    assert(inDungeon() && "Trying to use dungeon item when not in dungeon");
    assert(m_dungeon != Dungeon::Name::NONE);

    const auto currentDungeon = std::to_underlying(m_dungeon);

    switch (item)
    {
    case Dungeon::Item::LOCKED_DOOR_KEY:
        m_dungeonItems[currentDungeon].lockedDoorKeys--;
        break;
    default:
        std::unreachable();
    }
}

int Inventory::dungeonItem(Dungeon::Item item) const
{
    assert(m_dungeon > Dungeon::Name::NONE && m_dungeon < Dungeon::Name::COUNT);
    const auto dungeonItems = m_dungeonItems[std::to_underlying(m_dungeon)];
    switch (item)
    {
    case Dungeon::Item::COMPASS:
        return dungeonItems.compass;
    case Dungeon::Item::MAP:
        return dungeonItems.dungeonMap;
    case Dungeon::Item::OWL_BEAK:
        return dungeonItems.owlBeak;
    case Dungeon::Item::NIGHTMARE_KEY:
        return dungeonItems.nightmareKey;
    case Dungeon::Item::LOCKED_DOOR_KEY:
        return dungeonItems.lockedDoorKeys;
    default:
        std::unreachable();
    }
}

void Inventory::tradeItem(TradeItem item)
{
    m_tradeItem = item;
}

void Inventory::setTradeItem(TradeItem item)
{
    m_tradeItem = item;
}

Inventory::TradeItem Inventory::tradedItem() const
{
    return m_tradeItem;
}

void Inventory::addMiscItem(MiscItem item)
{
    assert(!(checkItemExists<MiscItem, std::to_underlying(MiscItem::COUNT)>(m_miscItems, item))
           && "Trying to add item that already exists");
    auto nextFreeSpace = std::ranges::find(m_miscItems, MiscItem::NONE);
    *nextFreeSpace = item;
}

void Inventory::useMiscItem(MiscItem item)
{
    assert(miscItemExists(item) && "Trying to use non-existent misc item");
    auto it = std::ranges::find(m_miscItems, item);

    switch (item)
    {
    case MiscItem::RED_POTION:
        *it = MiscItem::NONE;
        break;
    default:
        std::unreachable();
    }
}

bool Inventory::miscItemExists(MiscItem item) const
{
    return checkItemExists(m_miscItems, item);
}

bool Inventory::instrumentExists(Instrument instrument) const
{
    return checkItemExists<Instrument, std::to_underlying(Instrument::COUNT)>(m_instruments, instrument);
}

void Inventory::addInstrument(Instrument instrument)
{
    assert(!instrumentExists(instrument) && "Trying to add item that already exists");
    auto nextFreeSpace = std::ranges::find(m_instruments, Instrument::NONE);
    *nextFreeSpace = instrument;
}

std::array<Inventory::Instrument, std::to_underlying(Inventory::Instrument::COUNT)> Inventory::instruments() const
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

void Inventory::setRupees(int rupees)
{
    m_rupees = std::min(rupees, MAX_RUPEES);
}

void Inventory::setMaxBombs(int maxBombs)
{
    m_maxBombs = maxBombs;
}

void Inventory::setBombs(int bombs)
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

void Inventory::setMaxArrows(int maxArrows)
{
    m_maxArrows = maxArrows;
}

void Inventory::setArrows(int arrows)
{
    m_arrows = std::min(arrows, m_maxArrows);
}

void Inventory::useArrow()
{
    m_arrows = std::max(m_arrows - 1, 0);
}

int Inventory::arrows() const
{
    return m_arrows;
}

void Inventory::setMaxMagicPowder(int maxMagicPowder)
{
    m_maxMagicPowder = maxMagicPowder;
}

void Inventory::setMagicPowder(int magicPowder)
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
    assert(!(checkItemExists<OcarinaSong, std::to_underlying(OcarinaSong::COUNT)>(m_ocarinaSongs, ocarinaSong))
           && "Trying to add item that already exists");
    auto nextFreeSpace = std::ranges::find(m_ocarinaSongs, OcarinaSong::NONE);
    *nextFreeSpace = ocarinaSong;
}

std::array<Inventory::OcarinaSong, std::to_underlying(Inventory::OcarinaSong::COUNT)> Inventory::ocarinaSongs() const
{
    return m_ocarinaSongs;
}

void Inventory::setOcarinaSong(OcarinaSong ocarinaSong)
{
    m_ocarinaSong = ocarinaSong;
}

Inventory::OcarinaSong Inventory::ocarinaSong() const
{
    return m_ocarinaSong;
}

void Inventory::addTunic(Tunic tunic)
{
    assert(tunic != m_tunic && "Trying to add tunic that already exists");
    m_tunic = tunic;
}

Inventory::Tunic Inventory::tunic() const
{
    return m_tunic;
}

void Inventory::setTunic(Tunic tunic)
{
    m_tunic = tunic;
}

void Inventory::addHeartContainerPiece()
{
    m_heartContainerPieces = std::min(m_heartContainerPieces + 1, MAX_HEART_PIECES);
}

void Inventory::setHeartContainerPieces(int heartContainerPieces)
{
    m_heartContainerPieces = heartContainerPieces;
}

int Inventory::heartContainerPieces() const
{
    return m_heartContainerPieces;
}

void Inventory::addHeartPiece(float heartPiece)
{
    m_heartPieces = std::min(m_maxHeartPieces, m_heartPieces + heartPiece);
}

void Inventory::useHeartPiece(float heartPiece)
{
    m_heartPieces = std::max(0.0f, m_heartPieces - heartPiece);
}

void Inventory::setHeartPieces(float heartPieces)
{
    m_heartPieces = heartPieces;
}

void Inventory::setMaxHeartPieces(float maxHeartPieces)
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
    assert(!(checkItemExists<Photograph, std::to_underlying(Photograph::COUNT)>(m_photographs, photograph))
           && "Trying to add item that already exists");
    auto nextFreeSpace = std::ranges::find(m_photographs, Photograph::NONE);
    *nextFreeSpace = photograph;
}

std::array<Inventory::Photograph, std::to_underlying(Inventory::Photograph::COUNT)> Inventory::photographs() const
{
    return m_photographs;
}

int Inventory::numberOfPhotographs() const
{
    return static_cast<int>(std::ranges::count_if(m_photographs,
        [](Photograph p) { return p != Photograph::NONE; }));
}

void Inventory::addGoldenLeaf()
{
    m_goldenLeaves = std::min(m_goldenLeaves + 1, MAX_GOLDEN_LEAVES);
}

void Inventory::setGoldenLeaves(int goldenLeaves)
{
    m_goldenLeaves = goldenLeaves;
}

int Inventory::goldenLeaves() const
{
    return m_goldenLeaves;
}

void Inventory::addSecretSeaShell()
{
    m_secretSeaShells = std::min(m_secretSeaShells + 1, MAX_SECRET_SEASHELLS);
}

void Inventory::setSecretSeaShells(int secretShells)
{
    m_secretSeaShells = secretShells;
}

int Inventory::secretSeaShells() const
{
    return m_secretSeaShells;
}

Inventory::Item Inventory::itemA() const
{
    return m_itemA;
}

Inventory::Item Inventory::itemB() const
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

void Inventory::setItemA(const Item& itemA)
{
    m_itemA = itemA;
}

void Inventory::setItemB(const Item& itemB)
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

void Inventory::setDungeon(Dungeon::Name dungeon)
{
    m_dungeon = dungeon;
}

Inventory::Dungeon::Name Inventory::dungeon() const
{
    return m_dungeon;
}

Inventory::Dungeon::MapItem Inventory::dungeonMapLocationRoomItem(int x, int y) const
{
    assert(m_dungeon > Dungeon::Name::NONE && m_dungeon < Dungeon::Name::COUNT);
    return m_dungeonMaps[std::to_underlying(m_dungeon)][y][x].roomItem;
}

int Inventory::dungeonMapLocationRoomType(int x, int y) const
{
    assert(m_dungeon > Dungeon::Name::NONE && m_dungeon < Dungeon::Name::COUNT);
    return m_dungeonMaps[std::to_underlying(m_dungeon)][y][x].roomType;
}

bool Inventory::dungeonMapLocationVisited(int x, int y) const
{
    assert(m_dungeon > Dungeon::Name::NONE && m_dungeon < Dungeon::Name::COUNT);
    return m_dungeonMaps[std::to_underlying(m_dungeon)][y][x].visited;
}

void Inventory::setDungeonMapLocationVisited(const engine::Vector<int>& location)
{
    assert(m_dungeon > Dungeon::Name::NONE && m_dungeon < Dungeon::Name::COUNT);
    m_dungeonMaps[std::to_underlying(m_dungeon)][location.y][location.x].visited = true;
}


} // namespace zelda::core