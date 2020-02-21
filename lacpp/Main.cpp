#include "SDL.h"
#include "Window.h"
#include "Resource.h"

int main(int argc, char* argv[])
{
    auto SDLSuccess = SDL_Init(SDL_INIT_VIDEO);
    assert(SDLSuccess == 0);

    // Create main window
    Window mainWindow;
    mainWindow.createWindow(MAIN_WINDOW_TITLE, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

    // Create main renderer on the main Window
    Renderer::getInstance().createRenderer(mainWindow.getWindowHandle());

 

    mainWindow.beginEventLoop();

    SDL_Quit();
    return 0;
}