#include "RectTests.h"

namespace Testable
{

using namespace Zelda;

void RectTests::runTests()
{
    runTest(this, m_tests);
}

void RectTests::rectTests() noexcept
{
    Rect<int> r1{ 1,2,3,4 };
    Rect<int> r2{ 40,30,20,10 };
    EXPECT(r1 == r2, false);

    Rect<int> r3{ 1,2,3,4 };
    Rect<int> r4{ 1,2,3,4 };
    EXPECT(r3 == r4, true);

}

}
