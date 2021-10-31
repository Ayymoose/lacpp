#include "Testable.h"
#include "VectorTests.h"
#include "InventoryTests.h"
#include "DialogueTests.h"
#include "RectTests.h"
#include "Engine.h"
#include <vector>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    // TODO: Tidy this up
    Zelda::Engine::getInstance().init();

    Zelda::Camera::getInstance().setScrollSpeed(Zelda::CAMERA_SCROLL_SPEED);
    Zelda::Camera::getInstance().setPosition(480, 640);
    Zelda::Camera::getInstance().setTileMap(Zelda::RM_TAIL_CAVE);

    std::vector<std::unique_ptr<Testable::TestUnit>> tests;
    
    // Add tests here
    //tests.emplace_back(std::make_unique<Testable::VectorTests>());
    //tests.emplace_back(std::make_unique<Testable::InventoryTests>());
    //tests.emplace_back(std::make_unique<Testable::RectTests>());
    tests.emplace_back(std::make_unique<Testable::DialogueTests>());

    for (auto const& test : tests)
    {
        test->runTests();
    }

    std::cout << "All tests run\n";
    std::cin.get();
    return 0;
}