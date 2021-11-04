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
    //static Inventory inventory;
    //inventory.open();
    //Dialogue::getInstance().message("You got your sword! It has your name on the back! Very nice",0);
    //Dialogue::getInstance().question("Our colors are  ""never the same! ""If I am red, he ""is blue! If he  ""is red, I am    ""blue! What color""is my cloth?", "Red", "Blue", 0);

    //Engine::getInstance().run();
}

void DialogueTests::maxCharactersTest() noexcept
{
    static Inventory inventory;
    inventory.open();

    Dialogue::getInstance().message("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ", 0);

    Engine::getInstance().run();
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

void DialogueTests::maxCharsButNoContinue() noexcept
{

}


}