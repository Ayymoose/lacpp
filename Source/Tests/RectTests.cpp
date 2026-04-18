#include "RectTests.h"

namespace Tests
{

    using namespace Zelda;

    void RectTests::rectEqual()
    {
        {
            {
                Rect<int> r1{ 1, 2, 3, 4 };
                Rect<int> r2{ 40, 30, 20, 10 };
                CHECK(!(r1 == r2));
            }
            {
                Rect<float> r1{ 1, 2, 3, 4 };
                Rect<float> r2{ 40, 30, 20, 10 };
                CHECK(!(r1 == r2));
            }
            {
                Rect<double> r1{ 1, 2, 3, 4 };
                Rect<double> r2{ 40, 30, 20, 10 };
                CHECK(!(r1 == r2));
            }
        }
        {
            {
                Rect<int> r1{ 1, 2, 3, 4 };
                Rect<int> r2{ 1, 2, 3, 4 };
                CHECK_EQUAL(r1, r2);
            }
            {
                Rect<float> r1{ 1, 2, 3, 4 };
                Rect<float> r2{ 1, 2, 3, 4 };
                CHECK_EQUAL(r1, r2);
            }
            {
                Rect<double> r1{ 1, 2, 3, 4 };
                Rect<double> r2{ 1, 2, 3, 4 };
                CHECK_EQUAL(r1, r2);
            }
        }
    }
    
}
