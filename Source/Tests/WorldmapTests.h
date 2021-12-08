#pragma once

#include "Testable.h"
#include "Worldmap.h"

#include <map>
#include <string>

namespace Testable
{

class WorldmapTests : public TestUnit
{
public:
    WorldmapTests() = default;

    using WorldmapTestsMap = const std::map<std::string, void (WorldmapTests::*)(void)>;
    void runTests() override;

private:

    WorldmapTestsMap m_tests =
    {
        {"worldmap all tests", &WorldmapTests::allTests}
    };

    void allTests() noexcept;
};

};