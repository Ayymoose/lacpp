#include "SDL.h"
#include "Window.h"
#include "Resource.h"
#include "ZD_Assert.h"


class A
{
public:
    A() noexcept { std::cout << "A constructor" << std::endl; }
    ~A() noexcept { std::cout << "A deconstructor" << std::endl; }
    A(const A&) noexcept { std::cout << "A copy constructor" << std::endl; }
    A& operator=(const A&) noexcept { std::cout << "A assignment constructor" << std::endl; return *this;  }
    A& operator=(A&&) noexcept { std::cout << "A move assignment" << std::endl; return *this;}
    A(A&&) noexcept { std::cout << "A move constructor" << std::endl; }
};

int main(int argc, char* argv[])
{
   /* {
        A a;
        std::cout << "--------\n";
        A aa(std::move(a));
        std::cout << "--------\n";
        std::cout << "--------\n";
    }*/
    ZD_ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL Error: " << SDL_GetError());
    
    // Create main window
    Window mainWindow;
    mainWindow.createWindow(MAIN_WINDOW_TITLE, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

    // Create main renderer on the main Window
    Renderer::getInstance().createRenderer(mainWindow.getWindowHandle());

    // Load all graphics
    ResourceManager::getInstance().loadGraphics();

    mainWindow.beginEventLoop();
    
    SDL_Quit();

    //std::cin.get();
    return 0;
}