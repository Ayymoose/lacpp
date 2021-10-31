#pragma once

#include <map>
#include <iostream>
#include "Debug.h"

namespace Testable
{

class TestUnit
{
public:
    TestUnit() = default;
    virtual ~TestUnit() = default;
    virtual void runTests() = 0;

    template<typename TestType, typename TestList>
    void runTest(TestType* testType, TestList testList)
    {
        for (auto const& [testName, testFunction] : testList)
        {
            DEBUG(Zelda::DBG_TEST, "Running test: " + testName);
            (testType->*testFunction)();
        }
    }
};


#define EXPECT(ACTUAL, EXPECTED) do {if (!compare(ACTUAL,EXPECTED)) { std::cout << "Failed: " << __FILE__ << '(' << __LINE__ << ')' << " Expected " << (EXPECTED) << " but got " << (ACTUAL) << '\n'; }} while (0)

// Provide some type safety
template<typename E1, typename E2>
constexpr inline bool compare(E1 e1, E2 e2) noexcept
{
    return (e1 == e2);
}

};