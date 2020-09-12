#include <assert.h>
#include "Window.h"
#include "InputControl.h"
#include "Controller.h"
#include "Keyboard.h"
#include "Inventory.h"
#include <string>
#include "Link.h"
#include "BackgroundObject.h"
#include "ZD_Assert.h"

Window::~Window()
{
    SDL_DestroyWindow(m_mainWindow);
}

void Window::createWindow(const char* title, const int width, const int height) noexcept
{
    m_mainWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    assert(m_mainWindow != nullptr);
}

/*void Window::beginEventLoop()
{
    // Some testing stuff
    Camera::getInstance().track(&Link::getInstance());
    Camera::getInstance().setScrollSpeed(4);
    Camera::getInstance().setPosition(480, 640);
    Camera::getInstance().setCurrentBackground(ResourceManager::getInstance()[GFX_DUNGEON_1_TAIL_CAVE]);

    BackgroundObject candle1(GFX_CANDLE, 16, 16, 0);
    BackgroundObject torch1(GFX_TORCH_1, -160, 32, 270);
    
    //
    // This should be in the initialise code
    Keyboard::getInstance();
    
    // 



   
    std::string windowTitle;

    //Timer fpsTimer;
    uint64_t framesRendered = 0;

    while (!m_quitApplication)
    {

        handleInput();
        handleEvents();

        auto renderSet = Renderer::getInstance().getRenderSet();

        double fps = 0;// framesRendered / (fpsTimer.getTicks() / 1000.0);
        windowTitle = 
            "CX: " + std::to_string(Camera::getInstance().getX()) + " CY: " + std::to_string(Camera::getInstance().getY()) +
            " PX: " + std::to_string(Link::getInstance().position().x) + " PY: " + std::to_string(Link::getInstance().position().y) +
            " FPS: " + std::to_string((int)fps) + 
            " Renderables: " + std::to_string(renderSet.size())
            ;
        renderObjects();
        framesRendered++;

        SDL_SetWindowTitle(m_mainWindow, windowTitle.c_str());

    }

}*/

SDL_Window* Window::getWindowHandle() const noexcept
{
    return m_mainWindow;
}