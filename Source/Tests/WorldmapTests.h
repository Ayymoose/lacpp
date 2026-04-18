#pragma once

#include "Testable.h"
#include "Worldmap.h"
#include "Controller.h"

#include <map>
#include <string>

namespace Tests
{
    
    class WorldmapTests
    {
    public:
        WorldmapTests() = default;

        void runTests()
        {
            for (auto const& [testName, testFunction] : m_testMap)
            {
                (this->*testFunction)();
            }
        }

    private:

        using TestMap = std::map<std::string, void (WorldmapTests::*)(void)>;
        TestMap m_testMap =
        {
            {"worldmap tests", &WorldmapTests::worldmapTests}
        };

        void worldmapTests();
    };
    
};