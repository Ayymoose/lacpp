#include "Engine.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    zelda::engine::Engine::getInstance().init();
    zelda::engine::Engine::getInstance().run();
    return 0;
}