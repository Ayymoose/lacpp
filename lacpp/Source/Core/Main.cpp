#include "Engine.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    // Everything starts here
    Zelda::Engine::getInstance().init();
    Zelda::Engine::getInstance().run();
    Zelda::Engine::getInstance().stop();
    return 0;
}