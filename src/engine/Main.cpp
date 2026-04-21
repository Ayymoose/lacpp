#include "Engine.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    Zelda::Engine::getInstance().init();
    Zelda::Engine::getInstance().run();
    return 0;
}