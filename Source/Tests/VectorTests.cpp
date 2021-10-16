#include "VectorTests.h"

namespace Testable
{

using namespace Zelda;

void VectorTests::runTests()
{
    runTest(this, m_tests);
}

void VectorTests::vectorTests() noexcept
{
    Vector<int> v1(0, 0);
    Vector<int> v2(2, 2);

    // Addition
    v1 += v2;

    Vector<int> v3(2, 2);
    EXPECT(v1.x, v3.x);
    EXPECT(v1.y, v3.y);

    // Subtraction
    v1 -= v2;
    EXPECT(v1.x, 0);
    EXPECT(v1.y, 0);

    // Negation
    Vector<int> v4(10, 50);
    Vector<int> v5 = -v4;
    EXPECT(v5.x, -10);
    EXPECT(v5.y, -50);

    // Multiplication by scalar
    Vector<int> v6(25, 10);
    v6 *= 2;
    EXPECT(v6.x, 50);
    EXPECT(v6.y, 20);

    // Division by scalar
    Vector<int> v7(100, 50);
    v7 /= 2;
    EXPECT(v7.x, 50);
    EXPECT(v7.y, 25);

    // Assignment
    Vector<int> v8(453, 34);
    auto v9 = v8;
    EXPECT(v9.x, 453);
    EXPECT(v9.y, 34);

    // Comparison
    Vector<int> v10(56, 65);
    auto v11 = v10;
    auto equal = (v10 == v11);
    EXPECT(equal, true);

    Vector<int> v12(56, 65);
    Vector<int> v13(6, 65);
    equal = (v12 == v13);
    EXPECT(equal, false);

    // Distance between two vectors
    Vector<int> v14(0, 0);
    Vector<int> v15(30, 40);
    auto distance = Vector<int>::distanceBetween(v14, v15);
    EXPECT(distance, 50);

    // Cross product
    Vector<int> v16(12, 43);
    Vector<int> v17(30, 40);
    auto cross = Vector<int>::cross(v16, v17);
    EXPECT(cross, -810);

    // Dot product
    auto dot = Vector<int>::dot(v16, v17);
    EXPECT(dot, 2080);

    // Length
    EXPECT(v17.length(), 50);

    // Normalise
    Vector<float> v18(30,40);
    auto v19 = v18;
    v18.normalise();
    constexpr auto epsilon = std::numeric_limits<float>::epsilon();

    EXPECT((v18.x - 0.6 < epsilon), true);
    EXPECT((v18.y - 0.8 < epsilon), true);

    auto normal = v19.normal();
    EXPECT((normal.x - 0.6 < epsilon), true);
    EXPECT((normal.y - 0.8 < epsilon), true);

    // Linear interpolation
    Vector<float> v20(10, 20);
    Vector<float> v21(30, 20);

    auto v22 = Vector<float>::lerp(v20, v21, 0.5);
    EXPECT(v22.x, 20);
    EXPECT(v22.y, 20);

    auto v23 = Vector<float>::lerp(v20, v21, 0.0);
    EXPECT(v23.x, 10);
    EXPECT(v23.y, 20);

    auto v24 = Vector<float>::lerp(v20, v21, 1.0);
    EXPECT(v24.x, 30);
    EXPECT(v24.y, 20);
}

}
