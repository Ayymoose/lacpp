#include "Engine.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    // Everything starts here
    Engine::getInstance().init();
    Engine::getInstance().run();
    Engine::getInstance().stop();
    return 0;
}