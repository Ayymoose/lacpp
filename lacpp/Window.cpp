#include <assert.h>
#include "Window.h"
#include "InputControl.h"
#include "Controller.h"
#include "Keyboard.h"
#include "Inventory.h"
#include "Timer.h"
#include <string>
#include "Player.h"
#include "BackgroundObject.h"

Window::Window()
{
    m_mainWindow = nullptr;
    m_quitApplication = false;
}

Window::~Window()
{
    SDL_DestroyWindow(m_mainWindow);
}

void Window::createWindow(const char* title, const int width, const int height)
{
    m_mainWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    assert(m_mainWindow != nullptr);
}

void Window::beginEventLoop()
{
    // Some testing stuff
    Camera::getInstance().track(&Player::getInstance());
    Camera::getInstance().setScrollSpeed(4);
    Camera::getInstance().setPosition(480, 640);
    Camera::getInstance().setCurrentBackground(ResourceManager::getInstance()[RSC_DUNGEON_1_TAIL_CAVE]);

    BackgroundObject candle1(RSC_CANDLE, 16, 16, 0);
    BackgroundObject torch1(RSC_TORCH_1, -160, 32, 270);
    
    //
    // This should be in the initialise code
    Keyboard::getInstance();
    
    // 


    // Stretch the textures to the window
    DASSERT(SDL_RenderSetScale(Renderer::getInstance().getRenderer(),
        MAIN_WINDOW_WIDTH / (float)CAMERA_WIDTH,
        MAIN_WINDOW_HEIGHT / ((float)CAMERA_HEIGHT + 16)) == 0, SDL_GetError());
   
    std::string windowTitle;

    Timer fpsTimer;
    uint64_t framesRendered = 0;

    while (!m_quitApplication)
    {

        handleInput();
        handleEvents();

        auto renderSet = Renderer::getInstance().getRenderSet();

        double fps = framesRendered / (fpsTimer.getTicks() / 1000.0);
        windowTitle = 
            "CX: " + std::to_string(Camera::getInstance().getX()) + " CY: " + std::to_string(Camera::getInstance().getY()) +
            " PX: " + std::to_string(Player::getInstance().position().x) + " PY: " + std::to_string(Player::getInstance().position().y) +
            " FPS: " + std::to_string((int)fps) + 
            " Renderables: " + std::to_string(renderSet.size())
            ;
        renderObjects();
        framesRendered++;

        SDL_SetWindowTitle(m_mainWindow, windowTitle.c_str());

    }

}

void Window::handleInput()
{
    // Handles input from the user and designates it to the Controller
    Controllable* pController = Controller::getInstance().getController();
    if (pController)
    {
        pController->control();
    }

    /*if (Keyboard::getInstance().keyPushed(BUTTON_SELECT))
    {
        std::cout << "BUTTON_DOWN was pushed\n";
    }
    if (Keyboard::getInstance().keyPressed(BUTTON_SELECT))
    {
        std::cout << "BUTTON_DOWN was pressed\n";
    }
    if (Keyboard::getInstance().keyReleased(BUTTON_SELECT))
    {
        std::cout << "BUTTON_DOWN was released\n";
    }*/
}

void Window::handleEvents()
{
    if (SDL_PollEvent(&m_eventHandler))
    {
        switch (m_eventHandler.type)
        {
        case SDL_QUIT:
            m_quitApplication = true;
            break;
        case SDL_KEYDOWN:
            Keyboard::getInstance().updateKeyStates(m_eventHandler.key.keysym.scancode, true,false);
            break;
        case SDL_KEYUP:
            Keyboard::getInstance().updateKeyStates(m_eventHandler.key.keysym.scancode, false,true);
            break;

        }
    }
}

void Window::renderObjects()
{

    // Main rendering loop

    // Clear the screen
    SDL_Renderer* pRenderer = Renderer::getInstance().getRenderer();

    DASSERT(SDL_RenderClear(pRenderer) == 0, SDL_GetError());

    // Draw any objects
    auto renderSet = Renderer::getInstance().getRenderSet();

    for (auto iterator = renderSet.begin(); iterator != renderSet.end(); iterator++)
    {
        auto renderable = *iterator;
        assert(renderable != nullptr);

        // TODO: Culling
        renderable->render(pRenderer);
    }  

    // Represent to the screen
    SDL_RenderPresent(pRenderer);


}


SDL_Window* Window::getWindowHandle() const
{
    return m_mainWindow;
}