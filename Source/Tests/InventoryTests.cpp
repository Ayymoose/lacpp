#include "InventoryTests.h"
#include "Engine.h"
#include "Link.h"

#include "InventoryImpl.h"
#include "InventoryItem.h"

namespace Tests
{

    using namespace Zelda;

    void InventoryTests::heartImplTest()
    {
        InventoryImpl inventoryImpl;

        // Test limits are not breached
        {
            inventoryImpl.setHeartPieces(0);
            inventoryImpl.setMaxHeartPieces(3);

            for (int i = 0; i < 7; i++)
            {
                inventoryImpl.addHeartPiece(0.5);
            }

            CHECK_EQUAL(inventoryImpl.heartPieces(), 3);

            for (int i = 0; i < 7; i++)
            {
                inventoryImpl.useHeartPiece(0.5);
            }

            CHECK_EQUAL(inventoryImpl.heartPieces(), 0);
        }

        {
            inventoryImpl.setHeartContainerPieces(0);
            CHECK_EQUAL(inventoryImpl.heartContainerPieces(), 0);
            for (int i = 0; i < 5; i++)
            {
                inventoryImpl.addHeartContainerPiece();
            }
            CHECK_EQUAL(inventoryImpl.heartContainerPieces(), HEARTS_PIECE_MAX);
        }
    }

    void InventoryTests::tunicImplTest()
    {
        InventoryImpl inventoryImpl;
        inventoryImpl.setTunic(Tunic::TUNIC_GREEN);
        CHECK_EQUAL(ENUM_VALUE(inventoryImpl.tunic()), ENUM_VALUE(Tunic::TUNIC_GREEN));
        inventoryImpl.addTunic(Tunic::TUNIC_RED);
        CHECK_EQUAL(ENUM_VALUE(inventoryImpl.tunic()), ENUM_VALUE(Tunic::TUNIC_RED));
    }

    void InventoryTests::ocarinaImplTest()
    {
        InventoryImpl inventoryImpl;
        inventoryImpl.addOcarinaSong(OcarinaSong::OCARINA_SONG_MARIN);
        inventoryImpl.addOcarinaSong(OcarinaSong::OCARINA_SONG_FISH);
        inventoryImpl.addOcarinaSong(OcarinaSong::OCARINA_SONG_FROG);
        CHECK_EQUAL(inventoryImpl.ocarinaSongs().size(), 3);

        inventoryImpl.setOcarinaSong(OcarinaSong::OCARINA_SONG_FROG);
        CHECK_EQUAL(ENUM_VALUE(inventoryImpl.ocarinaSong()), ENUM_VALUE(OcarinaSong::OCARINA_SONG_FROG));
    }

    void InventoryTests::photographImplTest()
    {
        InventoryImpl inventoryImpl;
        inventoryImpl.addPhotograph(Photograph::PHOTOGRAPH_HEADS_UP);
        inventoryImpl.addPhotograph(Photograph::PHOTOGRAPH_HERE_STANDS_A_BRAVE_MAN);
        CHECK_EQUAL(inventoryImpl.photograph(), 2);
    }

    void InventoryTests::goldenLeafImplTest()
    {
        InventoryImpl inventoryImpl;
        inventoryImpl.setGoldenLeaves(0);
        CHECK_EQUAL(inventoryImpl.goldenLeaves(), 0);

        for (int i = 0; i < 6; i++)
        {
            inventoryImpl.addGoldenLeaf();
        }

        CHECK_EQUAL(inventoryImpl.goldenLeaves(), MAX_GOLDEN_LEAVES);
    }

    void InventoryTests::secretSeaShellImplTest()
    {
        InventoryImpl inventoryImpl;
        inventoryImpl.setSecretSeaShells(0);
        CHECK_EQUAL(inventoryImpl.secretSeaShells(), 0);

        for (int i = 0; i < 51; i++)
        {
            inventoryImpl.addSecretSeaShell();
        }

        CHECK_EQUAL(inventoryImpl.secretSeaShells(), MAX_SECRET_SEASHELLS);
    }

    void InventoryTests::magicPowderImplTest()
    {
        InventoryImpl inventoryImpl;
        inventoryImpl.setMagicPowderLimit(30);
        inventoryImpl.setMagicPowder(10);
        CHECK_EQUAL(inventoryImpl.magicPowder(), 10);


        for (int i = 15; i < 35; i++)
        {
            inventoryImpl.setMagicPowder(i);
        }

        CHECK_EQUAL(inventoryImpl.magicPowder(), 30);

        for (int i = 0; i < 31; i++)
        {
            inventoryImpl.useMagicPowder();
        }

        CHECK_EQUAL(inventoryImpl.magicPowder(), 0);

    }

    void InventoryTests::rupeeImplTest()
    {
        InventoryImpl inventoryImpl;
        inventoryImpl.setRupees(900);
        CHECK_EQUAL(inventoryImpl.rupees(), 900);


        for (int i = 0; i < 10; i++)
        {
            inventoryImpl.addRupee();
        }

        CHECK_EQUAL(inventoryImpl.rupees(), 910);

        for (int i = 0; i < 101; i++)
        {
            inventoryImpl.addRupee();
        }

        CHECK_EQUAL(inventoryImpl.rupees(), MAX_RUPEES);

        for (int i = 0; i < MAX_RUPEES +1; i++)
        {
            inventoryImpl.useRupee();
        }
        CHECK_EQUAL(inventoryImpl.rupees(), 0);
    }

    void InventoryTests::instrumentImplTest()
    {
        InventoryImpl inventoryImpl;
        inventoryImpl.addInstrument(Instrument::INSTRUMENT_CONCH_HORN);
        inventoryImpl.addInstrument(Instrument::INSTRUMENT_CORAL_TRIANGLE);
        inventoryImpl.addInstrument(Instrument::INSTRUMENT_FULL_MOON_CELLO);

        CHECK(inventoryImpl.instrumentExists(Instrument::INSTRUMENT_CONCH_HORN));
        CHECK(inventoryImpl.instrumentExists(Instrument::INSTRUMENT_CORAL_TRIANGLE));
        CHECK(inventoryImpl.instrumentExists(Instrument::INSTRUMENT_FULL_MOON_CELLO));
    }

    void InventoryTests::inventoryMiscItemImplTest()
    {
        InventoryImpl inventoryImpl;
        inventoryImpl.addInventoryMiscItem(InventoryMiscItem::INVENTORY_MISC_ITEM_FLIPPERS);
        inventoryImpl.addInventoryMiscItem(InventoryMiscItem::INVENTORY_MISC_ITEM_RED_POTION);


        if (inventoryImpl.miscItemExists(InventoryMiscItem::INVENTORY_MISC_ITEM_RED_POTION))
        {
            inventoryImpl.useInventoryMiscItem(InventoryMiscItem::INVENTORY_MISC_ITEM_RED_POTION);
        }

        CHECK_EQUAL(inventoryImpl.miscItemExists(InventoryMiscItem::INVENTORY_MISC_ITEM_FLIPPERS), true);
        CHECK_EQUAL(inventoryImpl.miscItemExists(InventoryMiscItem::INVENTORY_MISC_ITEM_RED_POTION), false);
    }

    void InventoryTests::tradeItemImplTest()
    {
        InventoryImpl inventoryImpl;
        inventoryImpl.setTradeItem(TradeItem::TRADE_ITEM_NONE);
        CHECK_EQUAL(ENUM_VALUE(inventoryImpl.tradedItem()), ENUM_VALUE(TradeItem::TRADE_ITEM_NONE));

        inventoryImpl.tradeItem(TradeItem::TRADE_ITEM_YOSHI_DOLL);
        inventoryImpl.tradeItem(TradeItem::TRADE_ITEM_RIBBON);
        inventoryImpl.tradeItem(TradeItem::TRADE_ITEM_DOG_FOOD);
        inventoryImpl.tradeItem(TradeItem::TRADE_ITEM_BANANAS);
        inventoryImpl.tradeItem(TradeItem::TRADE_ITEM_STICK);
        inventoryImpl.tradeItem(TradeItem::TRADE_ITEM_HONEYCOMB);
        inventoryImpl.tradeItem(TradeItem::TRADE_ITEM_PINEAPPLE);
        inventoryImpl.tradeItem(TradeItem::TRADE_ITEM_HIBISCUS);
        inventoryImpl.tradeItem(TradeItem::TRADE_ITEM_LETTER);
        inventoryImpl.tradeItem(TradeItem::TRADE_ITEM_BROOM);
        inventoryImpl.tradeItem(TradeItem::TRADE_ITEM_FISHING_HOOK);
        inventoryImpl.tradeItem(TradeItem::TRADE_ITEM_MERMAID_NECKLACE);
        inventoryImpl.tradeItem(TradeItem::TRADE_ITEM_MERMAID_SCALE);
        inventoryImpl.tradeItem(TradeItem::TRADE_ITEM_MAGNIFYING_LENS);
        inventoryImpl.tradeItem(TradeItem::TRADE_ITEM_BOOMERANG);

        CHECK_EQUAL(ENUM_VALUE(inventoryImpl.tradedItem()), ENUM_VALUE(TradeItem::TRADE_ITEM_BOOMERANG));
    }

    void InventoryTests::dungeonItemImplTest()
    {
        InventoryImpl inventoryImpl;
        inventoryImpl.setDungeon(Dungeon::DUNGEON_ANGLER_TUNNEL);
        inventoryImpl.setInDungeon(true);
        CHECK_EQUAL(ENUM_VALUE(inventoryImpl.getInDungeon()), true);

        inventoryImpl.addDungeonItem(DungeonItem::DUNGEON_ITEM_COMPASS);
        inventoryImpl.addDungeonItem(DungeonItem::DUNGEON_ITEM_LOCKED_DOOR_KEY);
        inventoryImpl.addDungeonItem(DungeonItem::DUNGEON_ITEM_LOCKED_DOOR_KEY);
        inventoryImpl.addDungeonItem(DungeonItem::DUNGEON_ITEM_LOCKED_DOOR_KEY);
        inventoryImpl.addDungeonItem(DungeonItem::DUNGEON_ITEM_MAP);
        inventoryImpl.addDungeonItem(DungeonItem::DUNGEON_ITEM_NIGHTMARE_KEY);
        inventoryImpl.addDungeonItem(DungeonItem::DUNGEON_ITEM_OWL_BEAK);

        inventoryImpl.useDungeonItem(DungeonItem::DUNGEON_ITEM_LOCKED_DOOR_KEY);

        CHECK_EQUAL(inventoryImpl.dungeonItem(DungeonItem::DUNGEON_ITEM_COMPASS), 1);
        CHECK_EQUAL(inventoryImpl.dungeonItem(DungeonItem::DUNGEON_ITEM_LOCKED_DOOR_KEY), 2);
        CHECK_EQUAL(inventoryImpl.dungeonItem(DungeonItem::DUNGEON_ITEM_MAP), 1);
        CHECK_EQUAL(inventoryImpl.dungeonItem(DungeonItem::DUNGEON_ITEM_NIGHTMARE_KEY), 1);
        CHECK_EQUAL(inventoryImpl.dungeonItem(DungeonItem::DUNGEON_ITEM_OWL_BEAK), 1);
    }

    void InventoryTests::dungeonEntraceKeyImplTest()
    {
        InventoryImpl inventoryImpl;
        inventoryImpl.setDungeon(Dungeon::DUNGEON_ANGLER_TUNNEL);
        inventoryImpl.setInDungeon(true);
        CHECK_EQUAL(ENUM_VALUE(inventoryImpl.getInDungeon()), true);

        inventoryImpl.addDungeonEntranceKey(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_ANGLER);
        inventoryImpl.addDungeonEntranceKey(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_BIRD);
        inventoryImpl.addDungeonEntranceKey(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_SLIME);
        inventoryImpl.addDungeonEntranceKey(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_TAIL);

        CHECK_EQUAL(inventoryImpl.dungeonEntranceKey(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_ANGLER), true);
        CHECK_EQUAL(inventoryImpl.dungeonEntranceKey(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_BIRD), true);
        CHECK_EQUAL(inventoryImpl.dungeonEntranceKey(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_SLIME), true);
        CHECK_EQUAL(inventoryImpl.dungeonEntranceKey(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_TAIL), true);
        CHECK_EQUAL(inventoryImpl.dungeonEntranceKey(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_FACE), false);
    }

    void InventoryTests::inventoryItemImplTest()
    {
        InventoryImpl inventoryImpl;

        inventoryImpl.addInventoryItem(LEVEL_1_SWORD);
        CHECK(inventoryImpl.inventoryItemExists(LEVEL_1_SWORD));
        inventoryImpl.removeInventoryItem(LEVEL_1_SWORD);
        CHECK(!inventoryImpl.inventoryItemExists(LEVEL_1_SWORD));

        inventoryImpl.addInventoryItem(LEVEL_2_SWORD);
        inventoryImpl.addInventoryItem(LEVEL_2_SHIELD);
        inventoryImpl.addInventoryItem(LEVEL_2_POWER_BRACELET);
        inventoryImpl.addInventoryItem(SHOVEL);
        inventoryImpl.addInventoryItem(HOOKSHOT);
        inventoryImpl.addInventoryItem(BOW);
        inventoryImpl.addInventoryItem(MAGIC_POWDER);
        inventoryImpl.addInventoryItem(ROC_FEATHER);
        inventoryImpl.addInventoryItem(BOOMERANG);
        inventoryImpl.addInventoryItem(OCARINA);

        inventoryImpl.setItemA(BOMBS);
        inventoryImpl.swapItemA();
        CHECK_EQUAL(inventoryImpl.itemA(), LEVEL_2_SWORD);

        inventoryImpl.setItemB(MUSHROOM);
        inventoryImpl.moveInventorySelector(Direction::DIRECTION_RIGHT);
        inventoryImpl.swapItemB();
        CHECK_EQUAL(inventoryImpl.itemB(), LEVEL_2_SHIELD);
        inventoryImpl.moveInventorySelector(Direction::DIRECTION_LEFT);

        /*
        Initially starts here

        |[0],1|
        | 2 ,3|
        | 4 ,5|
        | 6 ,7|
        | 8 ,9|
        */

        for (int i = 0; i < MAX_INVENTORY_ITEMS; ++i)
        {
            inventoryImpl.moveInventorySelector(Direction::DIRECTION_RIGHT);
        }
        for (int i = 0; i < MAX_INVENTORY_ITEMS; ++i)
        {
            inventoryImpl.moveInventorySelector(Direction::DIRECTION_LEFT);
        }

        inventoryImpl.moveInventorySelector(Direction::DIRECTION_RIGHT);

        for (int i = 0; i < 14; ++i)
        {
            inventoryImpl.moveInventorySelector(Direction::DIRECTION_DOWN);
        }

        for (int i = 0; i < 10; ++i)
        {
            inventoryImpl.moveInventorySelector(Direction::DIRECTION_UP);
        }

        inventoryImpl.swapItemB();
        CHECK_EQUAL(inventoryImpl.itemB(), OCARINA);
    }

    void InventoryTests::arrowImplTest()
    {
        InventoryImpl inventoryImpl;

        inventoryImpl.setArrowLimit(30);
        inventoryImpl.setArrows(10);
        CHECK_EQUAL(inventoryImpl.arrows(), 10);

        for (int i = 15; i < 35; i++)
        {
            inventoryImpl.setArrows(i);
        }

        CHECK_EQUAL(inventoryImpl.arrows(), 30);

        for (int i = 0; i < 31; i++)
        {
            inventoryImpl.useArrow();
        }

        CHECK_EQUAL(inventoryImpl.arrows(), 0);
    }

    void InventoryTests::bombImplTest()
    {
        InventoryImpl inventoryImpl;

        inventoryImpl.setBombLimit(30);
        inventoryImpl.setBombs(10);
        CHECK_EQUAL(inventoryImpl.bombs(), 10);

        for (int i = 15; i < 35; i++)
        {
            inventoryImpl.setBombs(i);
        }

        CHECK_EQUAL(inventoryImpl.bombs(), 30);

        for (int i = 0; i < 31; i++)
        {
            inventoryImpl.useBomb();
        }

        CHECK_EQUAL(inventoryImpl.bombs(), 0);
    }

    void InventoryTests::dungeonMapImplTest()
    {
        InventoryImpl inventoryImpl;
        inventoryImpl.setDungeon(Dungeon::DUNGEON_TAIL_CAVE);
        CHECK_EQUAL(ENUM_VALUE(inventoryImpl.dungeon()), ENUM_VALUE(Dungeon::DUNGEON_TAIL_CAVE));
        
        inventoryImpl.setPositionInDungeonMap({3,8});
        inventoryImpl.movePositionInDungeonMap(Direction::DIRECTION_RIGHT);
        inventoryImpl.setDungeonMapLocationVisited(inventoryImpl.dungeonMapPositionLocation());
        inventoryImpl.movePositionInDungeonMap(Direction::DIRECTION_DOWN);
        inventoryImpl.setDungeonMapLocationVisited(inventoryImpl.dungeonMapPositionLocation());
        inventoryImpl.movePositionInDungeonMap(Direction::DIRECTION_LEFT);
        inventoryImpl.setDungeonMapLocationVisited(inventoryImpl.dungeonMapPositionLocation());
        inventoryImpl.movePositionInDungeonMap(Direction::DIRECTION_UP);
        inventoryImpl.setDungeonMapLocationVisited(inventoryImpl.dungeonMapPositionLocation());

        // TODO: Fix macro expand issue with braces
        const auto position = Vector<int>{ 3,8 };
        CHECK_EQUAL(inventoryImpl.dungeonMapPositionLocation(), position);

        CHECK(inventoryImpl.dungeonMapLocationVisited(3, 8));
        CHECK(inventoryImpl.dungeonMapLocationVisited(3, 9)); // Right
        CHECK(inventoryImpl.dungeonMapLocationVisited(4, 9)); // Down
        CHECK(inventoryImpl.dungeonMapLocationVisited(4, 8)); // Left
        
        CHECK_EQUAL(ENUM_VALUE(inventoryImpl.dungeonMapLocationRoomItem(3, 8)), ENUM_VALUE(DungeonMapItem::DUNGEON_MAP_ITEM_NONE));
        CHECK_EQUAL(inventoryImpl.dungeonMapLocationRoomType(3, 8), 18);
    }

    void InventoryTests::heartTest()
    {

        Link::getInstance().setMaxHealth(16);
        Link::getInstance().setCurrentHealth(0);

        // Setup inventory
        static Inventory inventory;
        inventory.open();

        static auto test = 0;
        static float heartValue = 0.5f;

        static auto heartTest1 = []()
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
                    heartValue += 0.5f;
                }
            }
        };

        Engine::getInstance().setPreRenderTestFunction(heartTest1);

        Engine::getInstance().run();
    }

    void InventoryTests::weaponItemTest()
    {

        /*static InventoryWeapon weaponItems[] =
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
        Engine::getInstance().run();*/
    }

    void InventoryTests::dungeonKeyTest()
    {
        /*static DungeonKey keys[] =
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
            if (item < KEY_COUNT)
            {
                inventory.addItem(keys[item++]);
            }
            else
            {
                Engine::getInstance().stop();
            }
        };

        Engine::getInstance().setPreRenderTestFunction(dungeonItemTest);
        Engine::getInstance().run();*/
    }

    void InventoryTests::miscItemsTest()
    {
        /*// Flippers, Red potion

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
        Engine::getInstance().run();*/
    }

    void InventoryTests::instrumentsTest()
    {

        /*static Instrument instruments[] =
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
        Engine::getInstance().run();*/
    }

    void InventoryTests::rupeesTest()
    {
/*
        static Inventory inventory;
        static auto instrument = 0;
        static auto ruppees = 0;
        inventory.open();

        // Test dungeon items
        static auto ruppeeTest = []()
        {
            if (ruppees < MAX_RUPEES)
            {
                inventory.addItem(RUPPEE_ONE);
                ruppees++;
            }
            else
            {
                Engine::getInstance().stop();
            }
        };

        Engine::getInstance().setPreRenderTestFunction(ruppeeTest);
        Engine::getInstance().run();*/
    }

    void InventoryTests::subscreenTest()
    {
        /*
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
        };

        Engine::getInstance().setRenderTestFunction(subscreenTests);
        Engine::getInstance().run();

        */

    }

    void InventoryTests::selectorTest()
    {
        /*
        static Inventory inventory;
        inventory.open();
        static auto movedRight = 0;
        static auto movedLeft = 0;
        static auto movedUp = 0;
        static auto movedDown = 0;
        // Test dungeon items
        static auto selectorTests = []()
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
        };

        Engine::getInstance().setPreRenderTestFunction(selectorTests);
        Engine::getInstance().run();*/
    }

    void InventoryTests::dungeonItemsTest()
    {
        /*
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
        };

        Engine::getInstance().setPreRenderTestFunction(dungeonItemTest);
        Engine::getInstance().run();*/
    }

    void InventoryTests::tradeItemTest()
    {
        /*
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
            if (item < ITEM_COUNT)
            {
                inventory.addItem(items[item++]);
            }
            else
            {
                Engine::getInstance().stop();
            }
        };

        Engine::getInstance().setPreRenderTestFunction(tradeItemsTest);
        Engine::getInstance().run();

        */
    }
    
}