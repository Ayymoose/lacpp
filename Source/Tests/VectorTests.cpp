#include "FloatingPoint.h"
#include "VectorTests.h"

namespace Tests
{
    using namespace Zelda;

    void VectorTests::vectorAdd()
    {
        {
            Vector<int> v1(0, 0);
            Vector<int> v2(2, 2);

            v1 += v2;

            Vector<int> v3(2, 2);
            CHECK_EQUAL(v1,v3);
        }
        {
            Vector<float> v1(0.5, 0.5);
            Vector<float> v2(2.5, 2.5);

            v1 += v2;

            Vector<float> v3(3, 3);
            CHECK_EQUAL(v1, v3);
        }
        {
            Vector<double> v1(0.5, 0.5);
            Vector<double> v2(2.5, 2.5);

            v1 += v2;

            Vector<double> v3(3, 3);
            CHECK_EQUAL(v1, v3);
        }
    }

    void VectorTests::vectorSub()
    {
        {
            Vector<int> v1(0, 0);
            Vector<int> v2(2, 2);

            v1 -= v2;

            Vector<int> v3(-2, -2);
            CHECK_EQUAL(v1, v3);
        }
        {
            Vector<float> v1(0.5, 0.5);
            Vector<float> v2(2.5, 2.5);

            v1 -= v2;

            Vector<float> v3(-2, -2);
            CHECK_EQUAL(v1, v3);
        }
        {
            Vector<double> v1(0.5, 0.5);
            Vector<double> v2(2.5, 2.5);

            v1 -= v2;

            Vector<double> v3(-2, -2);
            CHECK_EQUAL(v1, v3);
        }
    }

    void VectorTests::vectorMul()
    {
        {
            Vector<int> v1(25, 10);
            v1 *= 2;
            Vector<int> v2{50, 20};
            CHECK_EQUAL(v1, v2);
        }
        {
            Vector<float> v1(25, 10);
            v1 *= 2.5f;
            Vector<float> v2{62.5, 25};
            CHECK_EQUAL(v1, v2);
        }
        {
            Vector<double> v1(25, 10);
            v1 *= 2.5;
            Vector<double> v2{62.5, 25};
            CHECK_EQUAL(v1, v2);
        }
    }

    void VectorTests::vectorDiv()
    {
        {
            Vector<int> v1(100, 50);
            v1 /= 2;
            Vector<int> v2{50, 25};
            CHECK_EQUAL(v1, v2);
        }
        {
            Vector<float> v1(100, 50);
            v1 /= 2.5f;
            Vector<float> v2{40, 20};
            CHECK_EQUAL(v1, v2);
        }
        {
            Vector<double> v1(100, 50);
            v1 /= 2.5;
            Vector<double> v2(40, 20);
            CHECK_EQUAL(v1, v2);
        }
    }

    void VectorTests::vectorAssign()
    {
        {
            Vector<int> v1(453, 34);
            auto v2 = v1;
            CHECK_EQUAL(v2, v1);
        }
        {
            Vector<float> v1(453, 34);
            auto v2 = v1;
            CHECK_EQUAL(v2, v1);
        }
        {
            Vector<double> v1(453, 34);
            auto v2 = v1;
            CHECK_EQUAL(v2, v1);
        }
    }

    void VectorTests::vectorDot()
    {
        {
            Vector<int> v1(1, 2);
            Vector<int> v2(3, 4);
            CHECK_EQUAL(11, Vector<int>::dot(v1, v2));
        }
        {
            Vector<float> v1(1, 2);
            Vector<float> v2(3, 4);
            CHECK_EQUAL(11, Vector<float>::dot(v1, v2));
        }
        {
            Vector<double> v1(1, 2);
            Vector<double> v2(3, 4);
            CHECK_EQUAL(11, Vector<double>::dot(v1, v2));
        }
    }

    void VectorTests::vectorCross()
    {
        {
            Vector<int> v1(1, 2);
            Vector<int> v2(3, 4);
            CHECK_EQUAL(-2, Vector<int>::cross(v1, v2));
        }
        {
            Vector<float> v1(1, 2);
            Vector<float> v2(3, 4);
            CHECK_EQUAL(-2, Vector<float>::cross(v1, v2));
        }
        {
            Vector<double> v1(1, 2);
            Vector<double> v2(3, 4);
            CHECK_EQUAL(-2, Vector<double>::cross(v1, v2));
        }
    }

    void VectorTests::vectorLength()
    {
        {
            Vector<int> v1(3, 4);
            CHECK_EQUAL(5, v1.length());
        }
        {
            Vector<float> v1(3.5, 4.5);
            CHECK(FloatingPoint<float>::almostEqual(std::sqrt(3.5*3.5 + 4.5*4.5), v1.length()));
        }
        {
            Vector<double> v1(3.5, 4.5);
            CHECK(FloatingPoint<double>::almostEqual(std::sqrt(3.5 * 3.5 + 4.5 * 4.5), v1.length()));
        }
    }

    void VectorTests::vectorNegation()
    {
        {
            Vector<int> v1(3, 4);
            Vector<int> v2(-3, -4);
            CHECK_EQUAL(v2, -v1);
        }
        {
            Vector<float> v1(3, 4);
            Vector<float> v2(-3, -4);
            CHECK_EQUAL(v2, -v1);
        }
        {
            Vector<double> v1(3, 4);
            Vector<double> v2(-3, -4);
            CHECK_EQUAL(v2, -v1);
        }
    }

    void VectorTests::vectorDistance()
    {
        {
            Vector<int> v1(0, 0);
            Vector<int> v2(30, 40);
            CHECK_EQUAL(50, Vector<int>::distanceBetween(v1, v2));
        }
        {
            Vector<float> v1(0, 0);
            Vector<float> v2(30, 40);
            CHECK_EQUAL(50, Vector<float>::distanceBetween(v1, v2));
        }
        {
            Vector<double> v1(0, 0);
            Vector<double> v2(30, 40);
            CHECK_EQUAL(50, Vector<double>::distanceBetween(v1, v2));
        }
    }

    void VectorTests::vectorNormal()
    {
        {
            {
                // If we ever need to compare int to float Vectors then fix this
                /*
                Vector<int> v1(30, 40);
                v1.normal();
                Vector<float> v2(0.5, 0.8);
                CHECK_EQUAL(v2, v1.normal());
                */
            }
            {
                Vector<float> v1(30, 40);
                Vector<float> v2(0.6, 0.8);
                CHECK_EQUAL(v2, v1.normal());
            }
            {
                Vector<double> v1(30, 40);
                Vector<double> v2(0.6, 0.8);
                CHECK_EQUAL(v2, v1.normal());
            }
        }
        {
            Vector<float> v1(30, 40);
            v1.normalise();
            CHECK_EQUAL(0.6f, v1.x);
            CHECK_EQUAL(0.8f, v1.y);
        }
        {
            Vector<double> v1(30, 40);
            v1.normalise();
            CHECK_EQUAL(0.6, v1.x);
            CHECK_EQUAL(0.8, v1.y);
        }
    }

}
