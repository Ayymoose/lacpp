#include "WorldmapTests.h"
#include "Engine.h"
#include "Link.h"

namespace Tests
{
    using namespace Zelda;

    void WorldmapTests::worldmapTests()
    {

        Controller::getInstance().pushController(&Worldmap::getInstance());

        for (int x = 2; x < 8; ++x)
        {
            for (int y = 10; y < 13; ++y)
            {
                Worldmap::getInstance().setLocation(x, y);
            }
        }

        Worldmap::getInstance().open();
    
        Engine::getInstance().run();
    }
}