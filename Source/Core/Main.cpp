#include "Engine.h"
//#include "Rect.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    // Everything starts here
    Zelda::Engine::getInstance().init();

    // Set camera position
    Zelda::Camera::getInstance().setScrollSpeed(Zelda::CAMERA_SCROLL_SPEED);
    Zelda::Camera::getInstance().setPosition(480, 640);
    Zelda::Camera::getInstance().setTileMap(Zelda::RM_TAIL_CAVE);

    //Zelda::Rect<float> s{ 1,2,3,4 };
    
    //auto r = Zelda::rectToSDLRect<float, SDL_FRect>(s);

   /* Zelda::Engine::getInstance().setTestFunction([]() {
        std::cout << "test\n";
    });*/

    Zelda::Engine::getInstance().run();
    Zelda::Engine::getInstance().stop();
    return 0;
}