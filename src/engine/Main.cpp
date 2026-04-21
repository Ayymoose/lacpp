#include "Engine.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    zelda::Engine::getInstance().init();
    zelda::Engine::getInstance().run();
    return 0;
}