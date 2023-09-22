#pragma once

#include "InventoryImpl.h"

namespace Zelda
{
    constexpr InventoryItem LEVEL_1_SWORD = InventoryItem(UsableItem::USABLE_ITEM_SWORD, ItemAttribute::ITEM_ATTRIBUTE_LEVEL, 1);
    constexpr InventoryItem LEVEL_2_SWORD = InventoryItem(UsableItem::USABLE_ITEM_SWORD, ItemAttribute::ITEM_ATTRIBUTE_LEVEL, 2);
    constexpr InventoryItem LEVEL_1_SHIELD = InventoryItem(UsableItem::USABLE_ITEM_SHIELD, ItemAttribute::ITEM_ATTRIBUTE_LEVEL, 1);
    constexpr InventoryItem LEVEL_2_SHIELD = InventoryItem(UsableItem::USABLE_ITEM_SHIELD, ItemAttribute::ITEM_ATTRIBUTE_LEVEL, 2);
    constexpr InventoryItem LEVEL_1_POWER_BRACELET = InventoryItem(UsableItem::USABLE_ITEM_POWER_BRACELET, ItemAttribute::ITEM_ATTRIBUTE_LEVEL, 1);
    constexpr InventoryItem LEVEL_2_POWER_BRACELET = InventoryItem(UsableItem::USABLE_ITEM_POWER_BRACELET, ItemAttribute::ITEM_ATTRIBUTE_LEVEL, 2);
    constexpr InventoryItem SHOVEL = InventoryItem(UsableItem::USABLE_ITEM_SHOVEL, ItemAttribute::ITEM_ATTRIBUTE_NONE, 0);
    constexpr InventoryItem HOOKSHOT = InventoryItem(UsableItem::USABLE_ITEM_HOOKSHOT, ItemAttribute::ITEM_ATTRIBUTE_NONE, 0);
    constexpr InventoryItem BOW = InventoryItem(UsableItem::USABLE_ITEM_BOW, ItemAttribute::ITEM_ATTRIBUTE_QUANTITY, 0);
    constexpr InventoryItem MAGIC_POWDER = InventoryItem(UsableItem::USABLE_ITEM_MAGIC_POWDER, ItemAttribute::ITEM_ATTRIBUTE_QUANTITY, 0);
    constexpr InventoryItem ROC_FEATHER = InventoryItem(UsableItem::USABLE_ITEM_ROC_FEATHER, ItemAttribute::ITEM_ATTRIBUTE_NONE, 0);
    constexpr InventoryItem BOOMERANG = InventoryItem(UsableItem::USABLE_ITEM_BOOMERANG, ItemAttribute::ITEM_ATTRIBUTE_NONE, 0);
    constexpr InventoryItem OCARINA = InventoryItem(UsableItem::USABLE_ITEM_OCARINA, ItemAttribute::ITEM_ATTRIBUTE_SONG, 0);
    constexpr InventoryItem BOMBS = InventoryItem(UsableItem::USABLE_ITEM_BOMBS, ItemAttribute::ITEM_ATTRIBUTE_QUANTITY, 0);
    constexpr InventoryItem MUSHROOM = InventoryItem(UsableItem::USABLE_ITEM_MUSHROOM, ItemAttribute::ITEM_ATTRIBUTE_NONE, 0);
    constexpr InventoryItem FLAME_ROD = InventoryItem(UsableItem::USABLE_ITEM_FLAME_ROD, ItemAttribute::ITEM_ATTRIBUTE_NONE, 0);
    constexpr InventoryItem PEGASUS_BOOT = InventoryItem(UsableItem::USABLE_ITEM_PEGASUS_BOOT, ItemAttribute::ITEM_ATTRIBUTE_NONE, 0);
}