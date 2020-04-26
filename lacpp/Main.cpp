#include "SDL.h"
#include "Window.h"
#include "Resource.h"
#include "MyAssert.h"

int main(int argc, char* argv[])
{
    DASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, SDL_GetError());
    
    // Create main window
    Window mainWindow;
    mainWindow.createWindow(MAIN_WINDOW_TITLE, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

    // Create main renderer on the main Window
    Renderer::getInstance().createRenderer(mainWindow.getWindowHandle());

    // Load all graphics
    ResourceManager::getInstance().loadGraphics();

    mainWindow.beginEventLoop();

    SDL_Quit();
    return 0;
}