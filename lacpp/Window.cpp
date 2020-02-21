#include <assert.h>
#include "Window.h"
#include "InputControl.h"
#include "Controller.h"


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

       // Load all resources
    ResourceManager resourceManager;
    resourceManager.loadGraphics();

    Camera camera;
    camera.setScrollSpeed(4);
    camera.setPosition(0, 0);
    camera.setCurrentBackground(resourceManager[RSC_BACKGROUND_OVERWORLD_MAIN]);
    Renderer::getInstance().addRenderable(&camera);
   // Controller::getInstance().setController(&camera);

    while (!m_quitApplication)
    {
        if (SDL_PollEvent(&m_eventHandler))
        {
            handleWindowEvents();
            handleInput();
        }
        renderObjects();
    }

}

void Window::handleInput()
{
    Controllable* controller = Controller::getInstance().getController();
    if (controller && (m_eventHandler.type == SDL_KEYDOWN || m_eventHandler.type == SDL_KEYUP))
    {
        controller->control(m_eventHandler);
    }
}

void Window::handleWindowEvents()
{
    switch (m_eventHandler.type)
    {
    case SDL_QUIT:
        m_quitApplication = true;
        break;
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


