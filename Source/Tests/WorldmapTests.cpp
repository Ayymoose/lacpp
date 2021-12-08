#include "WorldmapTests.h"
#include "Engine.h"
#include "Link.h"

namespace Testable
{

using namespace Zelda;

void WorldmapTests::runTests()
{
    runTest(this, m_tests);
}

void WorldmapTests::allTests() noexcept
{

    static Worldmap worldMap;
    Controller::getInstance().pushController(&worldMap);
    worldMap.open();
    
    Engine::getInstance().run();
}

}