#include "DialogueTests.h"
#include "Engine.h"
#include "Link.h"

namespace Testable
{

using namespace Zelda;

void DialogueTests::runTests()
{
    runTest(this, m_tests);
}

void DialogueTests::everyCharacterTest() noexcept
{
    Dialogue::getInstance().message("You got your sword! It has your name on the back! Very nice",0);

    Engine::getInstance().run();
}

void DialogueTests::maxCharactersTest() noexcept
{
}

void DialogueTests::questionTest() noexcept
{
}

void DialogueTests::heartTest() noexcept
{
}

void DialogueTests::positionTest() noexcept
{
}

void DialogueTests::colourTest() noexcept
{
}


}