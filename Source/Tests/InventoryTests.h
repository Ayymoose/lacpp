#pragma once

#include "Testable.h"
#include "Inventory.h"

#include <map>
#include <string>

namespace Tests
{
    class InventoryTests
    {
    public:
        InventoryTests() = default;

        void runTests()
        {
            for (auto const& [testName, testFunction] : m_testMap)
            {
                (this->*testFunction)();
            }
        }

    private:

        using TestMap = std::map<std::string, void (InventoryTests::*)(void)>;
        TestMap m_testMap =
        {
            {"impl heart test", &InventoryTests::heartImplTest},
            {"impl hearts test", &InventoryTests::heartTest},
            {"impl tunic test", &InventoryTests::tunicImplTest},
            {"impl ocarina test", &InventoryTests::ocarinaImplTest},
            {"impl photograph test", &InventoryTests::photographImplTest},
            {"impl golden leaf test", &InventoryTests::goldenLeafImplTest},
            {"impl secret sea shell test", &InventoryTests::secretSeaShellImplTest},
            {"impl magic powder test", &InventoryTests::magicPowderImplTest},
            {"impl arrow test", &InventoryTests::arrowImplTest},
            {"impl bomb test", &InventoryTests::bombImplTest},
            {"impl rupee test", &InventoryTests::rupeeImplTest},
            {"impl instrument test", &InventoryTests::instrumentImplTest},
            {"impl inventory misc item test", &InventoryTests::inventoryMiscItemImplTest},
            {"impl trade item test", &InventoryTests::tradeItemImplTest},
            {"impl dungeon item test", &InventoryTests::dungeonItemImplTest},
            {"impl dungeon map test", &InventoryTests::dungeonMapImplTest},
            {"impl dungeon entrance key test", &InventoryTests::dungeonEntraceKeyImplTest},
            {"impl iventory item test", &InventoryTests::inventoryItemImplTest},

            {"ui weapons item test", &InventoryTests::weaponItemTest},
            {"ui dungeons item test", &InventoryTests::dungeonItemsTest},
            {"ui trade item test", &InventoryTests::tradeItemTest},
            {"ui dungeon key test", &InventoryTests::dungeonKeyTest},
            {"ui misc item test", &InventoryTests::miscItemsTest},
            {"ui instruments test", &InventoryTests::instrumentsTest},
            {"ui rupees test", &InventoryTests::rupeesTest},
            {"ui subscreen test", &InventoryTests::subscreenTest},
            {"ui selector test", &InventoryTests::selectorTest}
        };

        void heartImplTest();
        void heartTest(); 
        void tunicImplTest();
        void ocarinaImplTest();
        void photographImplTest();
        void goldenLeafImplTest();
        void secretSeaShellImplTest();
        void magicPowderImplTest();
        void arrowImplTest();
        void bombImplTest();
        void rupeeImplTest();
        void instrumentImplTest();
        void inventoryMiscItemImplTest();
        void tradeItemImplTest();
        void dungeonItemImplTest();
        void dungeonEntraceKeyImplTest();
        void inventoryItemImplTest();
        void dungeonMapImplTest();

        void weaponItemTest();
        void dungeonItemsTest();
        void tradeItemTest();
        void dungeonKeyTest();
        void miscItemsTest();
        void instrumentsTest();
        void rupeesTest();
        void subscreenTest();
        void selectorTest();
    };
    
};