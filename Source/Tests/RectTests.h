#pragma once

#include "Testable.h"
#include "Rect.h"

#include <map>
#include <string>

namespace Tests
{

    class RectTests
    {
    public:
        RectTests() = default;

        void runTests()
        {
            for (auto const& [testName, testFunction] : m_testMap)
            {
                (this->*testFunction)();
            }
        }

    private:

        using TestMap = std::map<std::string, void (RectTests::*)(void)>;
        TestMap m_testMap =
        {
            {"rect equal", &RectTests::rectEqual}
        };

        void rectEqual();

    };

};