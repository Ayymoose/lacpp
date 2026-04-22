#pragma once

#include "Inventory.h"

namespace zelda::core
{
constexpr auto LEVEL_1_SWORD = InventoryItem(UsableItem::SWORD, ItemAttribute::LEVEL, 1);
constexpr auto LEVEL_2_SWORD = InventoryItem(UsableItem::SWORD, ItemAttribute::LEVEL, 2);
constexpr auto LEVEL_1_SHIELD = InventoryItem(UsableItem::SHIELD, ItemAttribute::LEVEL, 1);
constexpr auto LEVEL_2_SHIELD = InventoryItem(UsableItem::SHIELD, ItemAttribute::LEVEL, 2);
constexpr auto LEVEL_1_POWER_BRACELET = InventoryItem(UsableItem::POWER_BRACELET, ItemAttribute::LEVEL, 1);
constexpr auto LEVEL_2_POWER_BRACELET = InventoryItem(UsableItem::POWER_BRACELET, ItemAttribute::LEVEL, 2);
constexpr auto SHOVEL = InventoryItem(UsableItem::SHOVEL, ItemAttribute::NONE, 0);
constexpr auto HOOKSHOT = InventoryItem(UsableItem::HOOKSHOT, ItemAttribute::NONE, 0);
constexpr auto BOW = InventoryItem(UsableItem::BOW, ItemAttribute::QUANTITY, 0);
constexpr auto MAGIC_POWDER = InventoryItem(UsableItem::MAGIC_POWDER, ItemAttribute::QUANTITY, 0);
constexpr auto ROC_FEATHER = InventoryItem(UsableItem::ROC_FEATHER, ItemAttribute::NONE, 0);
constexpr auto BOOMERANG = InventoryItem(UsableItem::BOOMERANG, ItemAttribute::NONE, 0);
constexpr auto OCARINA = InventoryItem(UsableItem::OCARINA, ItemAttribute::SONG, 0);
constexpr auto BOMBS = InventoryItem(UsableItem::BOMBS, ItemAttribute::QUANTITY, 0);
constexpr auto MUSHROOM = InventoryItem(UsableItem::MUSHROOM, ItemAttribute::NONE, 0);
constexpr auto FLAME_ROD = InventoryItem(UsableItem::FLAME_ROD, ItemAttribute::NONE, 0);
constexpr auto PEGASUS_BOOT = InventoryItem(UsableItem::PEGASUS_BOOT, ItemAttribute::NONE, 0);
} // namespace zelda::core