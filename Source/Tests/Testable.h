#pragma once

#include <map>
#include <memory>

#include "Debug.h"

namespace Tests
{


    /*template<typename TestObject, typename TestMap>
    class TestUnit
    {
    public:
        constexpr TestUnit() : m_testObject(std::make_unique<TestObject>())
        {
        }
        virtual ~TestUnit() = default;

        void runTests()
        {
            for (auto const& [testName, testFunction] : m_testMap)
            {
                DEBUG(Zelda::DBG_TEST, "Running test: " + testName);
                (m_testObject.get()->*testFunction)();
            }
        }
    private:
        TestMap m_testMap;
        std::unique_ptr<TestObject> m_testObject;
    };*/


    #define CHECK(VALUE) do {if (!VALUE) {std::cout << "Failed: " << __FILE__ << '(' << __LINE__ << ')' << " false" << std::endl;} } while (0);

    #define CHECK_EQUAL(ACTUAL, EXPECTED) do {if (!((ACTUAL) == (EXPECTED))) { std::cout << "Failed: " << __FILE__ << '(' << __LINE__ << ')' << " Expected " << (EXPECTED) << " but got " << (ACTUAL) << '\n'; }} while (0)


};