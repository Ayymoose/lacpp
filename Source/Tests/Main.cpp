#include "Testable.h"
#include "VectorTests.h"
#include "InventoryTests.h"
#include "DialogueTests.h"
#include "RectTests.h"
#include "WorldmapTests.h"
#include "SpriteTests.h"

#include "Engine.h"
#include "Debug.h"
#include <vector>

int main(int, char*[])
{
    using namespace Zelda;

    Engine::getInstance().initVideo();
    Engine::getInstance().initWindow();
    Engine::getInstance().initData();
    
    Tests::VectorTests().runTests();
    Tests::RectTests().runTests();
    // Tests::WorldmapTests().runTests();
    Tests::DialogueTests().runTests();

    // Add tests here
    //tests.emplace_back(std::make_unique<Testable::InventoryTests>());
    //tests.emplace_back(std::make_unique<Testable::DialogueTests>());
    //tests.emplace_back(std::make_unique<Testable::WorldmapTests>());
    //tests.emplace_back(std::make_unique<Testable::SpriteTests>());

    /*for (auto const& test : tests)
    {
        test->runTests();
    }*/

    DEBUG(DBG_TEST, "All tests run");
    std::cin.get();
    return 0;
}