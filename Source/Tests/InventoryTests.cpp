#include "InventoryTests.h"
#include "Engine.h"
#include "Link.h"

namespace Tests
{
    /*
    using namespace Zelda;

    void InventoryTests::runTests()
    {
        runTest(this, m_tests);
    }

    void InventoryTests::heartTest() noexcept
    {

        Link::getInstance().setMaxHealth(16);
        Link::getInstance().setCurrentHealth(0);

        // Setup inventory
        static Inventory inventory;
        inventory.open();

        static auto test = 0;
        static float heartValue = 0.25f;

        static auto heartTest1 = []()
        {
            static Timer t;
            if (t.elapsed(1 / 30.0f))
            {
                Link::getInstance().replenish(heartValue);
                if (Link::getInstance().health() == 16)
                {
                    if (test == 3)
                    {
                        Engine::getInstance().stop();
                        inventory.close();
                    }
                    else
                    {
                        Link::getInstance().setCurrentHealth(0);
                        test++;
                        heartValue += 0.25f;
                    }
                }
            }
        };

        Engine::getInstance().setPreRenderTestFunction(heartTest1);

        Engine::getInstance().run();
    }

    void InventoryTests::weaponItemTest() noexcept
    {

        static InventoryWeapon weaponItems[] =
        {
            InventoryWeapon(WPN_SWORD, WPN_LEVEL_1),
            InventoryWeapon(WPN_SHIELD, WPN_LEVEL_1),
            InventoryWeapon(WPN_OCARINA, WPN_LEVEL_NONE),
            InventoryWeapon(WPN_BOW, WPN_LEVEL_NONE),
            InventoryWeapon(WPN_BOOMERANG, WPN_LEVEL_NONE),
            InventoryWeapon(WPN_MAGIC_POWDER, WPN_LEVEL_NONE),
            InventoryWeapon(WPN_BOMBS, WPN_LEVEL_NONE),
            InventoryWeapon(WPN_POWER_BRACELET, WPN_LEVEL_1),
            InventoryWeapon(WPN_ROC_FEATHER, WPN_LEVEL_NONE),
            InventoryWeapon(WPN_HOOKSHOT, WPN_LEVEL_NONE),
            InventoryWeapon(WPN_PEGASUS_BOOT, WPN_LEVEL_NONE),
            InventoryWeapon(WPN_SHOVEL, WPN_LEVEL_NONE),
            InventoryWeapon(WPN_FLAME_ROD, WPN_LEVEL_NONE),
            InventoryWeapon(WPN_POWER_BRACELET, WPN_LEVEL_2),
        };

        // Setup inventory
        static Inventory inventory;
        static auto item = 0;
        static auto removeItem = 0;
        static constexpr auto totalWeapons = sizeof(weaponItems) / sizeof(weaponItems[0]);
        inventory.open();

        // Add all items to the weapon inventory
        static auto itemTest1 = []()
        {
            static Timer t;
            if (t.elapsed(1 / 5.0f))
            {
                if (item < INVENTORY_MAX_WEAPONS+2) // +2 for weapon A and B
                {
                    inventory.addItem(weaponItems[item++]);
                }
                else
                {
                    // Remove two items
                    if (removeItem < 2)
                    {
                        inventory.removeItem(weaponItems[removeItem++]);
                    }
                    else
                    {
                        // Add the rest
                        if (item < totalWeapons)
                        {
                            inventory.addItem(weaponItems[item++]);
                            inventory.addItemQuantity(WPN_BOMBS, 30);
                            inventory.addItemQuantity(WPN_BOMBS, 30);
                        }
                        else
                        {
                            Engine::getInstance().stop();
                        }
                    }
                }
            }
        };

        Engine::getInstance().setPreRenderTestFunction(itemTest1);
        Engine::getInstance().run();
    }

    void InventoryTests::dungeonKeyTest() noexcept
    {
        static DungeonKey keys[] =
        {
            KEY_TAIL,
            KEY_SLIME,
            KEY_ANGLER,
            KEY_FACE,
            KEY_BIRD
        };

        // Setup inventory
        static Inventory inventory;
        static auto item = 0;
        inventory.open();
        inventory.inDungeon(false);

        // Test dungeon items
        static auto dungeonItemTest = []()
        {
            static Timer t;
            if (t.elapsed(1 / 2.0f))
            {
                if (item < KEY_COUNT)
                {
                    inventory.addItem(keys[item++]);
                }
                else
                {
                    Engine::getInstance().stop();
                }
            }
        };

        Engine::getInstance().setPreRenderTestFunction(dungeonItemTest);
        Engine::getInstance().run();
    }

    void InventoryTests::miscItemsTest() noexcept
    {
        // Flippers, Red potion

        static InventoryMiscItem items[] =
        {
            ITEM_RED_POTION,
            ITEM_FLIPPERS
        };

        static Inventory inventory;
        static auto item = 0;
        inventory.open();

        // Test dungeon items
        static auto miscItemsTest = []()
        {
            static Timer t;
            if (t.elapsed(1 / 2.0f))
            {
                if (item < (sizeof(items) / sizeof(items[0])))
                {
                    inventory.addItem(items[item++]);
                }
                else
                {
                    inventory.useItem(ITEM_RED_POTION);
                    Engine::getInstance().stop();
                }
            }
        };

        Engine::getInstance().setPreRenderTestFunction(miscItemsTest);
        Engine::getInstance().run();
    }

    void InventoryTests::instrumentsTest() noexcept
    {

        static Instrument instruments[] =
        {
            FULL_MOON_CELLO,
            CONCH_HORN,
            SEA_LILY_BELL,
            SURF_HARP,
            WIND_MARIMBA,
            CORAL_TRIANGLE,
            ORGAN_OF_EVENING_CALM,
            THUNDER_DRUM
        };

        static Inventory inventory;
        static auto instrument = 0;
        inventory.open();

        // Test dungeon items
        static auto instrumentTest = []()
        {
            static Timer t;
            if (t.elapsed(1 / 2.0f))
            {
                if (instrument < INSTRUMENT_COUNT)
                {
                    inventory.addItem(instruments[instrument++]);
                }
                else
                {
                    Engine::getInstance().stop();
                }
            }
        };

        Engine::getInstance().setPreRenderTestFunction(instrumentTest);
        Engine::getInstance().run();
    }

    void InventoryTests::ruppeesTest() noexcept
    {

        static Inventory inventory;
        static auto instrument = 0;
        static auto ruppees = 0;
        inventory.open();

        // Test dungeon items
        static auto ruppeeTest = []()
        {
            static Timer t;
            if (t.elapsed(1 / 60.0f))
            {
                if (ruppees < RUPPEES_MAX)
                {
                    inventory.addItem(RUPPEE_ONE);
                    ruppees++;
                }
                else
                {
                    Engine::getInstance().stop();
                }
            }
        };

        Engine::getInstance().setPreRenderTestFunction(ruppeeTest);
        Engine::getInstance().run();
    }

    void InventoryTests::subscreenTest() noexcept
    {
        static Inventory inventory;
        inventory.open();

        static int hearts = HEART_ZERO;
        static auto tunic = 0;
        static auto photographs = 0;
        static Tunic tunics[] =
        {
            Tunic::TUNIC_RED,
            Tunic::TUNIC_BLUE
        };

        // Test dungeon items
        static auto subscreenTests = []()
        {
            inventory.drawSubscreen();

            static Timer t;
            if (t.elapsed(1 / 2.0f))
            {
                if (tunic < sizeof(tunics)/sizeof(tunics[0]))
                {
                    inventory.addItem(tunics[tunic++]);
                }
                else
                {
                    if (hearts < HEART_FULL)
                    {
                        inventory.addItem(HEART_ONE_QUARTER);
                        hearts += HEART_ONE_QUARTER;
                    }
                    else
                    {
                        if (photographs < MAX_PHOTOGRAPHS)
                        {
                            inventory.addItem(1);
                            photographs++;
                        }
                        else
                        {
                            Engine::getInstance().stop();
                        }
                    }
                }
            }
        };

        Engine::getInstance().setRenderTestFunction(subscreenTests);
        Engine::getInstance().run();
    }

    void InventoryTests::selectorTest() noexcept
    {

        static Inventory inventory;
        inventory.open();
        static auto movedRight = 0;
        static auto movedLeft = 0;
        static auto movedUp = 0;
        static auto movedDown = 0;
        // Test dungeon items
        static auto selectorTests = []()
        {
            static Timer t;
            if (t.elapsed(1 / 5.0f))
            {
                if (movedRight < INVENTORY_MAX_WEAPONS)
                {
                    inventory.moveSelectorRight();
                    movedRight++;
                }
                else
                {
                    if (movedLeft < INVENTORY_MAX_WEAPONS)
                    {
                        inventory.moveSelectorLeft();
                        movedLeft++;
                    }
                    else
                    {
                        if (movedUp < 1)
                        {
                            inventory.moveSelectorUp();
                            movedUp++;
                        }
                        else
                        {
                            if (movedDown < 1)
                            {
                                inventory.moveSelectorDown();
                                movedDown++;
                            }
                            else
                            {
                                Engine::getInstance().stop();
                            }
                        }
                    }
                }
            }
        };

        Engine::getInstance().setPreRenderTestFunction(selectorTests);
        Engine::getInstance().run();
    }

    void InventoryTests::dungeonItemsTest() noexcept
    {

        static DungeonItem items[] =
        {
            DungeonItem::ITEM_KEY,
            DungeonItem::ITEM_COMPASS,
            DungeonItem::ITEM_NIGHTMARE_KEY,
            DungeonItem::ITEM_OWL_BEAK
        };

        // Setup inventory
        static Inventory inventory;
        static auto item = 0;
        static auto addedSingleItem = false;

        static auto iterateMap = false;
        static auto x = 0, y = 0;
        static float timerSpeed = 1 / 5.0f;

        static DungeonMapEntry thisDungeon[DUNGEON_MAX_BLOCKS_X][DUNGEON_MAX_BLOCKS_Y];
        inventory.getDungeonMap(DUNGEON_TAIL_CAVE, thisDungeon);

        inventory.open();
        inventory.inDungeon(true);

    

        // Test dungeon items
        static auto dungeonItemTest = []()
        {
            static Timer t;
            if (t.elapsed(timerSpeed))
            {
                if (item < (sizeof(items) / sizeof(items[0])))
                {
                    inventory.addItem(items[item++]);
                }
                else if (!addedSingleItem)
                {
                    inventory.addItem(DungeonItem::ITEM_MAP);
                    addedSingleItem = true;
                }
                else
                {
                    timerSpeed = 1 / 10.0f;

                    if (thisDungeon[y][x].roomType > 1)
                    {
                        inventory.setDungeonLocationMarker(x, y);
                    }

                    if (x < DUNGEON_MAX_BLOCKS_X-1)
                    {
                        x++;
                    }
                    else
                    {
                        x = 0;
                        if (y < DUNGEON_MAX_BLOCKS_Y-1)
                        {
                            y++;
                        }
                        else
                        {
                            inventory.setDungeonMapEntry(3, 5, { 11,true,DungeonMapItem::ITEM_CHEST_OPEN });
                            Engine::getInstance().stop();
                        }
                    }

                }
            }



        };

        Engine::getInstance().setPreRenderTestFunction(dungeonItemTest);
        Engine::getInstance().run();
    }

    void InventoryTests::tradeItemTest() noexcept
    {

        static TradeItem items[] =
        {
            ITEM_DOLL,
            ITEM_BOW,
            ITEM_DOG_FOOD,
            ITEM_BANANAS,
            ITEM_STICK,
            ITEM_HONEYCOMB,
            ITEM_PINEAPPLE,
            ITEM_HIBISCUS,
            ITEM_LETTER,
            ITEM_BROOM,
            ITEM_HOOK,
            ITEM_NECKLACE,
            ITEM_MERMAID_SCALE,
            ITEM_LENS
        };

        static Inventory inventory;
        static auto item = 0;
        inventory.open();
        inventory.inDungeon(true);

        static auto tradeItemsTest = []()
        {
            static Timer t;
            if (t.elapsed(1 / 2.0f))
            {
                if (item < ITEM_COUNT)
                {
                    inventory.addItem(items[item++]);
                }
                else
                {
                    Engine::getInstance().stop();
                }
            }
        };

        Engine::getInstance().setPreRenderTestFunction(tradeItemsTest);
        Engine::getInstance().run();
    }
    */
}