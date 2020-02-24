#include <assert.h>
#include "Window.h"
#include "InputControl.h"
#include "Controller.h"

#include "Inventory.h"
#include "Timer.h"
#include <string>
#include "HUD.h"
#include "Player.h"

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
  
   // Handle window events
   // Handle input events
   // Handle game logic


    Camera camera;
    HUD hud;
    Player player;
    Inventory inventory;

    inventory.close();

    camera.track(&player);
    player.trackedBy(&camera);
    camera.setScrollSpeed(4);
    camera.setPosition(480, 640);
    camera.setCurrentBackground(ResourceManager::getInstance()[RSC_DUNGEON_1_TAIL_CAVE]);

    Renderer::getInstance().addRenderable(&camera);
    Renderer::getInstance().addRenderable(&player);
    Renderer::getInstance().addRenderable(&hud);
    Renderer::getInstance().addRenderable(&inventory);


    Controller::getInstance().setController(&player);
    SDL_RenderSetScale(Renderer::getInstance().getRenderer(), MAIN_WINDOW_WIDTH / (float)CAMERA_WIDTH, MAIN_WINDOW_HEIGHT / ((float)CAMERA_HEIGHT + hud.height()));
   
    std::string windowTitle;

    Timer fpsTimer;
    int framesRendered = 0;

    while (!m_quitApplication)
    {

        handleWindowEvents();
        handleInput();

        std::vector<Renderable*> renderList = Renderer::getInstance().renderableObjects();

        float fps = framesRendered / (fpsTimer.getTicks() / 1000.f);
        windowTitle = 
            "CX: " + std::to_string(camera.getX()) + " CY: " + std::to_string(camera.getY()) +
            " PX: " + std::to_string(player.position().x()) + " PY: " + std::to_string(player.position().y()) +
            " FPS: " + std::to_string((int)fps) + 
            " Renderables: " + std::to_string(renderList.size())
            ;
        renderObjects();
        framesRendered++;

        SDL_SetWindowTitle(m_mainWindow, windowTitle.c_str());

    }

}

void Window::handleInput()
{
    Controllable* pController = Controller::getInstance().getController();
    const uint8_t* pKeyboardState = SDL_GetKeyboardState(nullptr);

    if (pController && IS_GAMEPAD_PRESSED(pKeyboardState))
    {
        pController->control();
    }
}

void Window::handleWindowEvents()
{
    if (SDL_PollEvent(&m_eventHandler))
    {
        switch (m_eventHandler.type)
        {
        case SDL_QUIT:
            m_quitApplication = true;
            break;
        }
    }
}

void Window::renderObjects()
{
    // Clear the screen
    SDL_Renderer* mainRenderer = Renderer::getInstance().getRenderer();
    SDL_RenderClear(mainRenderer);

    // Draw any objects
    std::vector<Renderable*> renderables = Renderer::getInstance().renderableObjects();
    if (renderables.size() > 0)
    {
        for (auto iterator = renderables.begin(); iterator != renderables.end(); iterator++)
        {
            (*iterator)->render(mainRenderer);
        }
    }   

    // Represent to the screen
    SDL_RenderPresent(mainRenderer);
}


