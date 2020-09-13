#include "Engine.h"
#include "Keyboard.h"
#include "Link.h"
#include "ZD_Assert.h"

void Zelda::Engine::init() noexcept
{
    // Initialise SDL
    ZD_ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL Error: " << SDL_GetError());

    // Create the main window
    m_mainWindow.createWindow(MAIN_WINDOW_TITLE, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

    // Create main hardware renderer
    Renderer::getInstance().createRenderer(m_mainWindow.getWindowHandle());

    // Stretch the textures to the window size
    ZD_ASSERT(SDL_RenderSetScale(Renderer::getInstance().getRenderer(), MAIN_WINDOW_WIDTH / (float)CameraWidth, MAIN_WINDOW_HEIGHT / ((float)CameraHeight + HUDHeight)) == 0, "SDL Error: " << SDL_GetError());

    // Load all resources (sound + graphics)
    ResourceManager::getInstance().loadGraphics();

    // Initialise the keyboard
    Keyboard::getInstance();
    
    // Initialise the camera
    Camera::getInstance().track(&Link::getInstance());
    Camera::getInstance().setScrollSpeed(ScrollSpeed);
    Camera::getInstance().setPosition(480, 640);

    // TODO: Replace
    Camera::getInstance().setCurrentBackground(ResourceManager::getInstance()[Graphic::GFX_DUNGEON_1_TAIL_CAVE]);
}

void Zelda::Engine::run() noexcept
{
    m_engineRunning = true;

    // Main game loop
    while (m_engineRunning)
    {
        // Process window/keyboard events
        processEvents();
        // Process input
        processInput();
        // Render objects
        renderObjects();
    }
 
}

void Zelda::Engine::stop() const noexcept
{
    // Cleanup
    SDL_Quit();
}

void Zelda::Engine::pauseEngine(bool pause) noexcept
{
    m_enginePaused = pause;
}

bool Zelda::Engine::enginePaused() const noexcept
{
    return m_enginePaused;
}

void Zelda::Engine::processEvents() noexcept
{
    SDL_Event eventHandler;
    if (SDL_PollEvent(&eventHandler))
    {
        switch (eventHandler.type)
        {
        case SDL_QUIT:
            m_engineRunning = false;
            break;
        case SDL_KEYDOWN:
            Keyboard::getInstance().updateKeyStates(eventHandler.key.keysym.scancode, true, false);
            // If key was released in the next frame, set it to not released now
            break;
        case SDL_KEYUP:
            Keyboard::getInstance().updateKeyStates(eventHandler.key.keysym.scancode, false, true);
            // Set key released to true on this frame
            break;

        }
    }
}

void Zelda::Engine::processInput() noexcept
{
    // Handles input from the user and designates it to the Controller
    Controllable* pController = Controller::getInstance().getController();
    if (pController)
    {
        pController->control();
    }
}

void Zelda::Engine::renderObjects() const noexcept
{
    // Clear the screen
    SDL_Renderer* pRenderer = Renderer::getInstance().getRenderer();

    ZD_ASSERT(SDL_RenderClear(pRenderer) == 0, "SDL Error: " << SDL_GetError());

    // Draw any objects
    auto renderSet = Renderer::getInstance().getRenderSet();

    for (auto iterator = renderSet.begin(); iterator != renderSet.end(); iterator++)
    {
        auto renderable = *iterator;
        assert(renderable != nullptr);
        if (!Engine::getInstance().enginePaused())
        {
            // TODO: If engine is paused, all animation/movement must be stopped until resumed
            // Engine is paused when 
            // - Opening the inventory and remains paused until inventory is closed
            // - Opening the file save screen
            // - Dialogue is running
        }
        // TODO: Culling
        renderable->render(pRenderer);
    }

    // Represent to the screen
    SDL_RenderPresent(pRenderer);
}
