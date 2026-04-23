#define BOOST_TEST_MODULE CoreTests
#include <boost/test/included/unit_test.hpp>

#include "core/Vector.h"
#include "core/Rect.h"
#include "core/FloatingPoint.h"
#include "core/Random.h"
#include "core/Sprite.h"
#include <SDL.h>
#include <sstream>

using namespace zelda::engine;

namespace vector_tests
{
BOOST_AUTO_TEST_SUITE(VectorTests)

// -------------------------
// Addition
// -------------------------
BOOST_AUTO_TEST_CASE(AddInt)
{
    Vector<int> v1(0, 0);
    Vector<int> v2(2, 2);
    v1 += v2;
    BOOST_TEST(v1 == Vector<int>(2, 2));
}

BOOST_AUTO_TEST_CASE(AddFloat)
{
    Vector<float> v1(0.5f, 0.5f);
    Vector<float> v2(2.5f, 2.5f);
    v1 += v2;
    BOOST_TEST(v1 == Vector<float>(3.0f, 3.0f));
}

BOOST_AUTO_TEST_CASE(AddDouble)
{
    Vector<double> v1(0.5, 0.5);
    Vector<double> v2(2.5, 2.5);
    v1 += v2;
    BOOST_TEST(v1 == Vector<double>(3.0, 3.0));
}

BOOST_AUTO_TEST_CASE(AddZeroVector)
{
    Vector<int> v1(5, 10);
    v1 += Vector<int>(0, 0);
    BOOST_TEST(v1 == Vector<int>(5, 10));
}

BOOST_AUTO_TEST_CASE(AddNegative)
{
    Vector<int> v1(5, 10);
    v1 += Vector<int>(-5, -10);
    BOOST_TEST(v1 == Vector<int>(0, 0));
}

// -------------------------
// Subtraction
// -------------------------

BOOST_AUTO_TEST_CASE(SubBinaryOperator)
{
    Vector<int> v1(5, 10);
    Vector<int> v2(2, 3);
    Vector<int> v3 = v1 - v2;
    BOOST_TEST(v3 == Vector<int>(3, 7));
}

BOOST_AUTO_TEST_CASE(SubInt)
{
    Vector<int> v1(0, 0);
    Vector<int> v2(2, 2);
    v1 -= v2;
    BOOST_TEST(v1 == Vector<int>(-2, -2));
}

BOOST_AUTO_TEST_CASE(SubFloat)
{
    Vector<float> v1(0.5f, 0.5f);
    Vector<float> v2(2.5f, 2.5f);
    v1 -= v2;
    BOOST_TEST(v1 == Vector<float>(-2.0f, -2.0f));
}

BOOST_AUTO_TEST_CASE(SubDouble)
{
    Vector<double> v1(0.5, 0.5);
    Vector<double> v2(2.5, 2.5);
    v1 -= v2;
    BOOST_TEST(v1 == Vector<double>(-2.0, -2.0));
}

BOOST_AUTO_TEST_CASE(SubSelf)
{
    Vector<int> v1(5, 10);
    const Vector<int> v2 = v1;
    v1 -= v2;
    BOOST_TEST(v1 == Vector<int>(0, 0));
}

// -------------------------
// Multiplication
// -------------------------
BOOST_AUTO_TEST_CASE(MulInt)
{
    Vector<int> v1(25, 10);
    v1 *= 2;
    BOOST_TEST(v1 == Vector<int>(50, 20));
}

BOOST_AUTO_TEST_CASE(MulFloat)
{
    Vector<float> v1(25.0f, 10.0f);
    v1 *= 2.5f;
    BOOST_TEST(v1 == Vector<float>(62.5f, 25.0f));
}

BOOST_AUTO_TEST_CASE(MulDouble)
{
    Vector<double> v1(25.0, 10.0);
    v1 *= 2.5;
    BOOST_TEST(v1 == Vector<double>(62.5, 25.0));
}

BOOST_AUTO_TEST_CASE(MulByZero)
{
    Vector<int> v1(25, 10);
    v1 *= 0;
    BOOST_TEST(v1 == Vector<int>(0, 0));
}

BOOST_AUTO_TEST_CASE(MulByOne)
{
    Vector<int> v1(25, 10);
    v1 *= 1;
    BOOST_TEST(v1 == Vector<int>(25, 10));
}

// -------------------------
// Division
// -------------------------
BOOST_AUTO_TEST_CASE(DivInt)
{
    Vector<int> v1(100, 50);
    v1 /= 2;
    BOOST_TEST(v1 == Vector<int>(50, 25));
}

BOOST_AUTO_TEST_CASE(DivFloat)
{
    Vector<float> v1(100.0f, 50.0f);
    v1 /= 2.5f;
    BOOST_TEST(v1 == Vector<float>(40.0f, 20.0f));
}

BOOST_AUTO_TEST_CASE(DivDouble)
{
    Vector<double> v1(100.0, 50.0);
    v1 /= 2.5;
    BOOST_TEST(v1 == Vector<double>(40.0, 20.0));
}

BOOST_AUTO_TEST_CASE(DivByOne)
{
    Vector<int> v1(25, 10);
    v1 /= 1;
    BOOST_TEST(v1 == Vector<int>(25, 10));
}

// Note: DivByZero is guarded by assert() in Vector so is not tested here.
// It would terminate the process in Debug builds.

// -------------------------
// Dot Product
// -------------------------
BOOST_AUTO_TEST_CASE(DotInt)
{
    BOOST_TEST(Vector<int>::dot(Vector<int>(1, 2), Vector<int>(3, 4)) == 11);
}

BOOST_AUTO_TEST_CASE(DotFloat)
{
    BOOST_TEST(Vector<float>::dot(Vector<float>(1.0f, 2.0f), Vector<float>(3.0f, 4.0f)) == 11.0f);
}

BOOST_AUTO_TEST_CASE(DotDouble)
{
    BOOST_TEST(Vector<double>::dot(Vector<double>(1.0, 2.0), Vector<double>(3.0, 4.0)) == 11.0);
}

BOOST_AUTO_TEST_CASE(DotPerpendicularVectors)
{
    BOOST_TEST(Vector<int>::dot(Vector<int>(1, 0), Vector<int>(0, 1)) == 0);
}

BOOST_AUTO_TEST_CASE(DotWithZeroVector)
{
    BOOST_TEST(Vector<int>::dot(Vector<int>(5, 10), Vector<int>(0, 0)) == 0);
}

// -------------------------
// Cross Product
// -------------------------
BOOST_AUTO_TEST_CASE(CrossInt)
{
    BOOST_TEST(Vector<int>::cross(Vector<int>(1, 2), Vector<int>(3, 4)) == -2);
}

BOOST_AUTO_TEST_CASE(CrossFloat)
{
    BOOST_TEST(Vector<float>::cross(Vector<float>(1.0f, 2.0f), Vector<float>(3.0f, 4.0f)) == -2.0f);
}

BOOST_AUTO_TEST_CASE(CrossDouble)
{
    BOOST_TEST(Vector<double>::cross(Vector<double>(1.0, 2.0), Vector<double>(3.0, 4.0)) == -2.0);
}

BOOST_AUTO_TEST_CASE(CrossParallelVectors)
{
    BOOST_TEST(Vector<int>::cross(Vector<int>(2, 4), Vector<int>(1, 2)) == 0);
}

BOOST_AUTO_TEST_CASE(CrossAntiCommutativity)
{
    Vector<int> v1(1, 2);
    Vector<int> v2(3, 4);
    BOOST_TEST(Vector<int>::cross(v1, v2) == -Vector<int>::cross(v2, v1));
}

// -------------------------
// Length
// -------------------------
BOOST_AUTO_TEST_CASE(LengthInt)
{
    BOOST_TEST(Vector<int>(3, 4).length() == 5.0);
}

BOOST_AUTO_TEST_CASE(LengthFloat)
{
    Vector<float> v1(3.5f, 4.5f);
    const float expected = std::sqrt(3.5f * 3.5f + 4.5f * 4.5f);
    BOOST_TEST(FloatingPoint<float>::almostEqual(expected, v1.length()));
}

BOOST_AUTO_TEST_CASE(LengthDouble)
{
    Vector<double> v1(3.5, 4.5);
    const double expected = std::sqrt(3.5 * 3.5 + 4.5 * 4.5);
    BOOST_TEST(FloatingPoint<double>::almostEqual(expected, v1.length()));
}

BOOST_AUTO_TEST_CASE(LengthZeroVector)
{
    BOOST_TEST(Vector<int>(0, 0).length() == 0.0);
}

BOOST_AUTO_TEST_CASE(LengthUnitVector)
{
    BOOST_TEST(FloatingPoint<double>::almostEqual(1.0, Vector<double>(1.0, 0.0).length()));
}

// -------------------------
// Negation
// -------------------------
BOOST_AUTO_TEST_CASE(NegateInt)
{
    BOOST_TEST(-Vector<int>(3, 4) == Vector<int>(-3, -4));
}

BOOST_AUTO_TEST_CASE(NegateFloat)
{
    BOOST_TEST(-Vector<float>(3.0f, 4.0f) == Vector<float>(-3.0f, -4.0f));
}

BOOST_AUTO_TEST_CASE(NegateDouble)
{
    BOOST_TEST(-Vector<double>(3.0, 4.0) == Vector<double>(-3.0, -4.0));
}

BOOST_AUTO_TEST_CASE(DoubleNegation)
{
    Vector<int> v1(3, 4);
    BOOST_TEST(-(-v1) == v1);
}

BOOST_AUTO_TEST_CASE(NegateZeroVector)
{
    BOOST_TEST(-Vector<int>(0, 0) == Vector<int>(0, 0));
}

// -------------------------
// Distance
// -------------------------
BOOST_AUTO_TEST_CASE(DistanceInt)
{
    BOOST_TEST(Vector<int>::distanceBetween(Vector<int>(0, 0), Vector<int>(30, 40)) == 50.0);
}

BOOST_AUTO_TEST_CASE(DistanceFloat)
{
    BOOST_TEST(Vector<float>::distanceBetween(Vector<float>(0, 0), Vector<float>(30, 40)) == 50.0f);
}

BOOST_AUTO_TEST_CASE(DistanceDouble)
{
    BOOST_TEST(Vector<double>::distanceBetween(Vector<double>(0, 0), Vector<double>(30, 40)) == 50.0);
}

BOOST_AUTO_TEST_CASE(DistanceSamePoint)
{
    BOOST_TEST(Vector<int>::distanceBetween(Vector<int>(5, 5), Vector<int>(5, 5)) == 0.0);
}

BOOST_AUTO_TEST_CASE(DistanceIsSymmetric)
{
    Vector<double> v1(1.0, 2.0);
    Vector<double> v2(4.0, 6.0);
    BOOST_TEST(Vector<double>::distanceBetween(v1, v2) == Vector<double>::distanceBetween(v2, v1));
}

// -------------------------
// Normalise
// -------------------------
BOOST_AUTO_TEST_CASE(NormalFloat)
{
    BOOST_TEST(Vector<float>(30.0f, 40.0f).normal() == Vector<float>(0.6f, 0.8f));
}

BOOST_AUTO_TEST_CASE(NormalDouble)
{
    BOOST_TEST(Vector<double>(30.0, 40.0).normal() == Vector<double>(0.6, 0.8));
}

BOOST_AUTO_TEST_CASE(NormaliseInPlaceFloat)
{
    Vector<float> v1(30.0f, 40.0f);
    v1.normalise();
    BOOST_TEST(FloatingPoint<float>::almostEqual(0.6f, v1.x));
    BOOST_TEST(FloatingPoint<float>::almostEqual(0.8f, v1.y));
}

BOOST_AUTO_TEST_CASE(NormaliseInPlaceDouble)
{
    Vector<double> v1(30.0, 40.0);
    v1.normalise();
    BOOST_TEST(FloatingPoint<double>::almostEqual(0.6, v1.x));
    BOOST_TEST(FloatingPoint<double>::almostEqual(0.8, v1.y));
}

BOOST_AUTO_TEST_CASE(NormalisedVectorHasLengthOne)
{
    BOOST_TEST(FloatingPoint<double>::almostEqual(1.0, Vector<double>(30.0, 40.0).normal().length()));
}

// -------------------------
// Default constructor
// -------------------------
BOOST_AUTO_TEST_CASE(DefaultConstructorZeroInitialises)
{
    Vector<int> vi;
    BOOST_TEST(vi.x == 0);
    BOOST_TEST(vi.y == 0);

    Vector<float> vf;
    BOOST_TEST(vf.x == 0.0f);
    BOOST_TEST(vf.y == 0.0f);
}

// -------------------------
// Binary operator+ (returns new vector)
// -------------------------
BOOST_AUTO_TEST_CASE(AddBinaryInt)
{
    const Vector<int> v1(3, 4);
    const Vector<int> v2(1, 2);
    BOOST_TEST(v1 + v2 == Vector<int>(4, 6));
}

BOOST_AUTO_TEST_CASE(AddBinaryFloat)
{
    const Vector<float> v1(1.5f, 2.5f);
    const Vector<float> v2(0.5f, 0.5f);
    BOOST_TEST(v1 + v2 == Vector<float>(2.0f, 3.0f));
}

// -------------------------
// Binary operator* (returns new vector)
// -------------------------
BOOST_AUTO_TEST_CASE(MulBinaryInt)
{
    const Vector<int> v(3, 4);
    BOOST_TEST(v * 2 == Vector<int>(6, 8));
}

BOOST_AUTO_TEST_CASE(MulBinaryFloat)
{
    const Vector<float> v(3.0f, 4.0f);
    BOOST_TEST(v * 2.0f == Vector<float>(6.0f, 8.0f));
}

BOOST_AUTO_TEST_CASE(MulBinaryDouble)
{
    const Vector<double> v(3.0, 4.0);
    BOOST_TEST(v * 2.5 == Vector<double>(7.5, 10.0));
}

// -------------------------
// Binary operator/ (returns new vector)
// -------------------------
BOOST_AUTO_TEST_CASE(DivBinaryInt)
{
    const Vector<int> v(100, 50);
    BOOST_TEST(v / 2 == Vector<int>(50, 25));
}

BOOST_AUTO_TEST_CASE(DivBinaryFloat)
{
    const Vector<float> v(100.0f, 50.0f);
    BOOST_TEST(v / 2.0f == Vector<float>(50.0f, 25.0f));
}

BOOST_AUTO_TEST_CASE(DivBinaryDouble)
{
    const Vector<double> v(100.0, 50.0);
    BOOST_TEST(v / 2.5 == Vector<double>(40.0, 20.0));
}

// -------------------------
// operator!=
// -------------------------
BOOST_AUTO_TEST_CASE(NotEqualInt)
{
    BOOST_TEST(Vector<int>(1, 2) != Vector<int>(3, 4));
}

BOOST_AUTO_TEST_CASE(NotEqualFloat)
{
    BOOST_TEST(Vector<float>(1.0f, 2.0f) != Vector<float>(3.0f, 4.0f));
}

BOOST_AUTO_TEST_CASE(NotEqualDiffersOnlyInX)
{
    BOOST_TEST(Vector<int>(99, 2) != Vector<int>(1, 2));
}

BOOST_AUTO_TEST_CASE(NotEqualDiffersOnlyInY)
{
    BOOST_TEST(Vector<int>(1, 99) != Vector<int>(1, 2));
}

// -------------------------
// operator<<
// -------------------------
BOOST_AUTO_TEST_CASE(StreamOutputInt)
{
    std::ostringstream oss;
    oss << Vector<int>(3, 4);
    BOOST_TEST(oss.str() == "(3,4)");
}

BOOST_AUTO_TEST_CASE(StreamOutputFloat)
{
    std::ostringstream oss;
    oss << Vector<float>(1.5f, 2.5f);
    BOOST_TEST(oss.str() == "(1.5,2.5)");
}

BOOST_AUTO_TEST_CASE(StreamOutputZeroVector)
{
    std::ostringstream oss;
    oss << Vector<int>(0, 0);
    BOOST_TEST(oss.str() == "(0,0)");
}

BOOST_AUTO_TEST_SUITE_END()
} // namespace vector_tests

namespace rect_tests
{
BOOST_AUTO_TEST_SUITE(RectTests)

// -------------------------
// Equality
// -------------------------
BOOST_AUTO_TEST_CASE(EqualInt)
{
    BOOST_TEST(Rect<int>(1, 2, 3, 4) == Rect<int>(1, 2, 3, 4));
}

BOOST_AUTO_TEST_CASE(EqualFloat)
{
    BOOST_TEST(Rect<float>(1.0f, 2.0f, 3.0f, 4.0f) == Rect<float>(1.0f, 2.0f, 3.0f, 4.0f));
}

BOOST_AUTO_TEST_CASE(EqualDouble)
{
    BOOST_TEST(Rect<double>(1.0, 2.0, 3.0, 4.0) == Rect<double>(1.0, 2.0, 3.0, 4.0));
}

BOOST_AUTO_TEST_CASE(EqualDefaultConstructed)
{
    BOOST_TEST(Rect<int>() == Rect<int>(0, 0, 0, 0));
}

// -------------------------
// Inequality
// -------------------------
BOOST_AUTO_TEST_CASE(NotEqualInt)
{
    BOOST_TEST(Rect<int>(1, 2, 3, 4) != Rect<int>(40, 30, 20, 10));
}

BOOST_AUTO_TEST_CASE(NotEqualFloat)
{
    BOOST_TEST(Rect<float>(1.0f, 2.0f, 3.0f, 4.0f) != Rect<float>(40.0f, 30.0f, 20.0f, 10.0f));
}

BOOST_AUTO_TEST_CASE(NotEqualDouble)
{
    BOOST_TEST(Rect<double>(1.0, 2.0, 3.0, 4.0) != Rect<double>(40.0, 30.0, 20.0, 10.0));
}

BOOST_AUTO_TEST_CASE(NotEqualDiffersOnlyInX)
{
    BOOST_TEST(Rect<int>(99, 2, 3, 4) != Rect<int>(1, 2, 3, 4));
}

BOOST_AUTO_TEST_CASE(NotEqualDiffersOnlyInY)
{
    BOOST_TEST(Rect<int>(1, 99, 3, 4) != Rect<int>(1, 2, 3, 4));
}

BOOST_AUTO_TEST_CASE(NotEqualDiffersOnlyInW)
{
    BOOST_TEST(Rect<int>(1, 2, 99, 4) != Rect<int>(1, 2, 3, 4));
}

BOOST_AUTO_TEST_CASE(NotEqualDiffersOnlyInH)
{
    BOOST_TEST(Rect<int>(1, 2, 3, 99) != Rect<int>(1, 2, 3, 4));
}

// -------------------------
// rectToSDLRect (integral)
// -------------------------
BOOST_AUTO_TEST_CASE(ToSDLRectInt)
{
    const Rect<int> r(1, 2, 3, 4);
    const SDL_Rect sdl = rectToSDLRect(r);
    BOOST_TEST(sdl.x == 1);
    BOOST_TEST(sdl.y == 2);
    BOOST_TEST(sdl.w == 3);
    BOOST_TEST(sdl.h == 4);
}

BOOST_AUTO_TEST_CASE(ToSDLRectIntZero)
{
    const SDL_Rect sdl = rectToSDLRect(Rect<int>(0, 0, 0, 0));
    BOOST_TEST(sdl.x == 0);
    BOOST_TEST(sdl.y == 0);
    BOOST_TEST(sdl.w == 0);
    BOOST_TEST(sdl.h == 0);
}

// -------------------------
// rectToSDLRect (floating point)
// -------------------------
BOOST_AUTO_TEST_CASE(ToSDLFRectFloat)
{
    const Rect<float> r(1.5f, 2.5f, 3.5f, 4.5f);
    const SDL_FRect sdl = rectToSDLRect(r);
    BOOST_TEST(FloatingPoint<float>::almostEqual(sdl.x, 1.5f));
    BOOST_TEST(FloatingPoint<float>::almostEqual(sdl.y, 2.5f));
    BOOST_TEST(FloatingPoint<float>::almostEqual(sdl.w, 3.5f));
    BOOST_TEST(FloatingPoint<float>::almostEqual(sdl.h, 4.5f));
}

BOOST_AUTO_TEST_CASE(ToSDLFRectDouble)
{
    const Rect<double> r(1.5, 2.5, 3.5, 4.5);
    const SDL_FRect sdl = rectToSDLRect(r);
    BOOST_TEST(FloatingPoint<float>::almostEqual(sdl.x, 1.5f));
    BOOST_TEST(FloatingPoint<float>::almostEqual(sdl.y, 2.5f));
    BOOST_TEST(FloatingPoint<float>::almostEqual(sdl.w, 3.5f));
    BOOST_TEST(FloatingPoint<float>::almostEqual(sdl.h, 4.5f));
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace rect_tests

namespace random_tests
{

BOOST_AUTO_TEST_SUITE(RandomTests)

// -------------------------
// random()
// -------------------------
BOOST_AUTO_TEST_CASE(RandomIntInRange)
{

    const int result = Random::random<int>(1, 10);
    BOOST_TEST(result >= 1);
    BOOST_TEST(result <= 10);
}

BOOST_AUTO_TEST_CASE(RandomIntSingleValue)
{
    // When start == end the only possible result is that value
    BOOST_TEST(Random::random<int>(5, 5) == 5);
}

// -------------------------
// choose()
// -------------------------
BOOST_AUTO_TEST_CASE(ChooseResultIsOneOfTheArguments)
{
    const int result = Random::choose(1, 2, 3);
    BOOST_TEST((result == 1 || result == 2 || result == 3));
}

BOOST_AUTO_TEST_CASE(ChooseFromTwoOptions)
{
    for (int i = 0; i < 100; ++i)
    {
        const int result = Random::choose(0, 1);
        BOOST_TEST((result == 0 || result == 1));
    }
}

BOOST_AUTO_TEST_CASE(ChooseSinglePair)
{
    // With identical values the result must always be that value
    BOOST_TEST(Random::choose(42, 42) == 42);
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace random_tests

namespace sprite_tests
{

// Fixture that creates a hidden window and a renderer that supports render
// targets (required by Sprite's SDL_TEXTUREACCESS_TARGET textures).
// Falls back to software if hardware acceleration is unavailable.
struct SDLFixture
{
    SDL_Window*   window   = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDLFixture()
    {
        BOOST_REQUIRE_MESSAGE(SDL_Init(SDL_INIT_VIDEO) == 0, SDL_GetError());
        window = SDL_CreateWindow("SpriteTest", 0, 0, 160, 144, SDL_WINDOW_HIDDEN);
        BOOST_REQUIRE_MESSAGE(window != nullptr, SDL_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
        if (!renderer)
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE);

        BOOST_REQUIRE_MESSAGE(renderer != nullptr, SDL_GetError());
    }

    ~SDLFixture()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

BOOST_AUTO_TEST_SUITE(SpriteTests)

// -------------------------
// Null renderer
// -------------------------
BOOST_AUTO_TEST_CASE(NullRenderer_WidthIsZero)
{
    const Sprite s(nullptr, 0, 0);
    BOOST_TEST(s.width() == 0);
    BOOST_TEST(s.height() == 0);
    BOOST_TEST(s.data() == nullptr);
}
// -------------------------
// Move semantics (null renderer)
// -------------------------
BOOST_AUTO_TEST_CASE(MoveConstructor_NullSprite_DestinationIsEmpty)
{
    Sprite src(nullptr, 0, 0);
    const Sprite dst(std::move(src));
    BOOST_TEST(dst.data() == nullptr);
    BOOST_TEST(dst.width() == 0);
    BOOST_TEST(dst.height() == 0);
}

BOOST_AUTO_TEST_CASE(MoveConstructor_NullSprite_SourceBecomesEmpty)
{
    Sprite src(nullptr, 0, 0);
    Sprite dst(std::move(src));
    BOOST_TEST(src.data() == nullptr);
    BOOST_TEST(src.renderer() == nullptr);
}

BOOST_AUTO_TEST_CASE(MoveAssignment_NullSprites_ExchangesState)
{
    Sprite a(nullptr, 0, 0);
    Sprite b(nullptr, 0, 0);
    a = std::move(b);
    BOOST_TEST(a.data() == nullptr);
    BOOST_TEST(a.renderer() == nullptr);
}

// -------------------------
// Swap (null renderer)
// -------------------------
BOOST_AUTO_TEST_CASE(Swap_NullSprites_StateUnchanged)
{
    Sprite a(nullptr, 0, 0);
    Sprite b(nullptr, 0, 0);
    swap(a, b);
    BOOST_TEST(a.data() == nullptr);
    BOOST_TEST(b.data() == nullptr);
}
// -------------------------
// Constructor (SDL renderer)
// -------------------------
BOOST_FIXTURE_TEST_CASE(Constructor_StoresWidth, SDLFixture)
{
    const Sprite s(renderer, 32, 16);
    BOOST_TEST(s.width() == 32);
    BOOST_TEST(s.height() == 16);
    BOOST_TEST(s.data() != nullptr);
}

// -------------------------
// Copy constructor (SDL renderer)
// -------------------------
BOOST_FIXTURE_TEST_CASE(CopyConstructor_SameWidth, SDLFixture)
{
    const Sprite src(renderer, 32, 16);
    const Sprite dst(src);
    BOOST_TEST(dst.width() == src.width());
    BOOST_TEST(dst.height() == src.height());
    BOOST_TEST(dst.renderer() == src.renderer());
    BOOST_TEST(dst.data() != src.data());
}
// -------------------------
// Move constructor (SDL renderer)
// -------------------------
BOOST_FIXTURE_TEST_CASE(MoveConstructor_NewSpriteHasTexture, SDLFixture)
{
    Sprite src(renderer, 32, 16);
    const Sprite dst(std::move(src));
    BOOST_TEST(dst.data() != nullptr);
    BOOST_TEST(dst.width() == 32);
    BOOST_TEST(dst.height() == 16);
    BOOST_TEST(src.data() == nullptr);
    BOOST_TEST(src.width() == 0);
    BOOST_TEST(src.height() == 0);
}

// -------------------------
// Assignment operator (SDL renderer)
// -------------------------
BOOST_FIXTURE_TEST_CASE(AssignmentOperator_CopiesDimensions, SDLFixture)
{
    const Sprite src(renderer, 32, 16);
    Sprite dst(renderer, 8, 8);
    dst = src;
    BOOST_TEST(dst.width() == 32);
    BOOST_TEST(dst.height() == 16);
    BOOST_TEST(dst.data() != src.data());
}

// -------------------------
// Move assignment operator (SDL renderer)
// -------------------------
BOOST_FIXTURE_TEST_CASE(MoveAssignment_DestinationAcquiresDimensions, SDLFixture)
{
    Sprite src(renderer, 32, 16);
    Sprite dst(renderer, 8, 8);
    dst = std::move(src);
    BOOST_TEST(dst.width() == 32);
    BOOST_TEST(dst.height() == 16);
    BOOST_TEST(src.data() != dst.data());
    BOOST_TEST(src.width() == 8);
    BOOST_TEST(src.height() == 8);
}

BOOST_FIXTURE_TEST_CASE(MoveAssignment_DestinationAcquiresTexture, SDLFixture)
{
    Sprite src(renderer, 32, 16);
    SDL_Texture* originalTexture = src.data();
    Sprite dst(renderer, 8, 8);
    dst = std::move(src);
    BOOST_TEST(dst.data() == originalTexture);
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace sprite_tests