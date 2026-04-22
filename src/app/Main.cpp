#include "core/Engine.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    zelda::engine::Engine::instance().init();
    zelda::engine::Engine::instance().run();
    return 0;
}