#pragma once

#include "Testable.h"
#include "Vector.h"

#include <map>
#include <string>

namespace Testable
{

class VectorTests : public TestUnit
{
public:
    constexpr VectorTests() = default;

    using VectorTestsMap = const std::map<std::string, void (VectorTests::*)(void)>;
    void runTests() override;

private:
    VectorTestsMap m_tests =
    {
        {"vector tests", &VectorTests::vectorTests}
    };
    void vectorTests() noexcept;
};

};