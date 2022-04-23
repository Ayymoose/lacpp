#include "Engine.h"
#include "Camera.h"

#include "Window.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    // Everything starts here
    using namespace Zelda;

    Engine::getInstance().init();
    //Debug::getInstance().setDebugMask(DBG_INFO);

    // Set camera position
    Camera::getInstance().setScrollSpeed(Zelda::CAMERA_SCROLL_SPEED);
    //Camera::getInstance().setPosition(480, 640);

    Engine::getInstance().run();

    return 0;
}