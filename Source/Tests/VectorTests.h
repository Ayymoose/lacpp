#pragma once

#include "Testable.h"
#include "Vector.h"

#include <map>
#include <string>

namespace Tests
{

    class VectorTests
    {
    public:
        VectorTests() = default;

        void runTests()
        {
            for (auto const& [testName, testFunction] : m_testMap)
            {
                (this->*testFunction)();
            }
        }
        
    private:

        using TestMap = std::map<std::string, void (VectorTests::*)(void)>;
        TestMap m_testMap =
        {
            {"vector add", &VectorTests::vectorAdd},
            {"vector sub", &VectorTests::vectorSub},
            {"vector mul", &VectorTests::vectorMul},
            {"vector div", &VectorTests::vectorDiv},
            {"vector assign", &VectorTests::vectorAssign},
            {"vector dot", &VectorTests::vectorDot},
            {"vector cross", &VectorTests::vectorCross},
            {"vector length", &VectorTests::vectorLength},
            {"vector negation",&VectorTests::vectorNegation},
            {"vector distance",&VectorTests::vectorDistance},
            {"vector normal",&VectorTests::vectorNormal}
        };

        void vectorAdd();
        void vectorSub();
        void vectorMul();
        void vectorDiv();
        void vectorAssign();
        void vectorDot();
        void vectorCross();
        void vectorLength();
        void vectorNegation();
        void vectorDistance();
        void vectorNormal();

    };

};