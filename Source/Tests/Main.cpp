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

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    using namespace Zelda;

    // TODO: Tidy this up
    //Engine::getInstance().init();

    // Camera::getInstance().setScrollSpeed(Zelda::CAMERA_SCROLL_SPEED);
    //Camera::getInstance().setPosition(480, 640);
    //Camera::getInstance().setTileMap(Zelda::RM_TAIL_CAVE);

    std::vector<std::unique_ptr<Testable::TestUnit>> tests;
    
    // Add tests here
    //tests.emplace_back(std::make_unique<Testable::VectorTests>());
    //tests.emplace_back(std::make_unique<Testable::InventoryTests>());
    //tests.emplace_back(std::make_unique<Testable::RectTests>());
    //tests.emplace_back(std::make_unique<Testable::DialogueTests>());
    //tests.emplace_back(std::make_unique<Testable::WorldmapTests>());
    tests.emplace_back(std::make_unique<Testable::SpriteTests>());

    for (auto const& test : tests)
    {
        test->runTests();
    }

    DEBUG(DBG_TEST, "All tests run");
    std::cin.get();
    return 0;
}