#pragma once

#include "Inventory.h"

namespace zelda::core
{
constexpr auto LEVEL_1_SWORD = Inventory::InventoryItem(Inventory::UsableItem::SWORD, Inventory::ItemAttribute::LEVEL, 1);
constexpr auto LEVEL_2_SWORD = Inventory::InventoryItem(Inventory::UsableItem::SWORD, Inventory::ItemAttribute::LEVEL, 2);
constexpr auto LEVEL_1_SHIELD = Inventory::InventoryItem(Inventory::UsableItem::SHIELD, Inventory::ItemAttribute::LEVEL, 1);
constexpr auto LEVEL_2_SHIELD = Inventory::InventoryItem(Inventory::UsableItem::SHIELD, Inventory::ItemAttribute::LEVEL, 2);
constexpr auto LEVEL_1_POWER_BRACELET = Inventory::InventoryItem(Inventory::UsableItem::POWER_BRACELET, Inventory::ItemAttribute::LEVEL, 1);
constexpr auto LEVEL_2_POWER_BRACELET = Inventory::InventoryItem(Inventory::UsableItem::POWER_BRACELET, Inventory::ItemAttribute::LEVEL, 2);
constexpr auto SHOVEL = Inventory::InventoryItem(Inventory::UsableItem::SHOVEL, Inventory::ItemAttribute::NONE, 0);
constexpr auto HOOKSHOT = Inventory::InventoryItem(Inventory::UsableItem::HOOKSHOT, Inventory::ItemAttribute::NONE, 0);
constexpr auto BOW = Inventory::InventoryItem(Inventory::UsableItem::BOW, Inventory::ItemAttribute::QUANTITY, 0);
constexpr auto MAGIC_POWDER = Inventory::InventoryItem(Inventory::UsableItem::MAGIC_POWDER, Inventory::ItemAttribute::QUANTITY, 0);
constexpr auto ROC_FEATHER = Inventory::InventoryItem(Inventory::UsableItem::ROC_FEATHER, Inventory::ItemAttribute::NONE, 0);
constexpr auto BOOMERANG = Inventory::InventoryItem(Inventory::UsableItem::BOOMERANG, Inventory::ItemAttribute::NONE, 0);
constexpr auto OCARINA = Inventory::InventoryItem(Inventory::UsableItem::OCARINA, Inventory::ItemAttribute::SONG, 0);
constexpr auto BOMBS = Inventory::InventoryItem(Inventory::UsableItem::BOMBS, Inventory::ItemAttribute::QUANTITY, 0);
constexpr auto MUSHROOM = Inventory::InventoryItem(Inventory::UsableItem::MUSHROOM, Inventory::ItemAttribute::NONE, 0);
constexpr auto FLAME_ROD = Inventory::InventoryItem(Inventory::UsableItem::FLAME_ROD, Inventory::ItemAttribute::NONE, 0);
constexpr auto PEGASUS_BOOT = Inventory::InventoryItem(Inventory::UsableItem::PEGASUS_BOOT, Inventory::ItemAttribute::NONE, 0);
} // namespace zelda::core