#include "Engine.h"
#include "Keyboard.h"
#include "Link.h"
#include "ZD_Assert.h"
#include "Dialogue.h"
#include "Controllable.h"

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

    // Dialogue::getInstance().message("You got your sword! It has your name on the back! Very nice");
    // Dialogue::getInstance().message("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFABCDEFGHIJKLMNOPXRSTUVWXYZABCDEFABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFABCDEFGHIJKLMNOPXRSTUVWXYZABCDEF");//"You've got a    Guardian Acorn! It will reduce  the damage you  take by half!");
     Dialogue::getInstance().question("Our colors are  ""never the same! ""If I am red, he ""is blue! If he  ""is red, I am    ""blue! What color""is my cloth?", "Red","Blue");
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

void Zelda::Engine::pause(bool pause) noexcept
{
    m_enginePaused = pause;
}

bool Zelda::Engine::paused() const noexcept
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
    Controllable* controller = Controller::getInstance().getController();
    if (controller)
    {
        controller->control();
    }
}

void Zelda::Engine::renderObjects() const noexcept
{
    SDL_Renderer* pRenderer = Renderer::getInstance().getRenderer();

    // Render any objects
    auto renderSet = Renderer::getInstance().getRenderSet();

    for (auto& renderable : renderSet)
    {
        assert(renderable);

        if (!Engine::getInstance().paused())
        {
            // TODO: If engine is paused, all animation/movement must be stopped until resumed
            // Engine is paused when 
            // - Opening the inventory and remains paused until inventory is closed
            // - Opening the file save screen
            // - Dialogue is running
            // - An item that opens the dialogue is obtained
        }

        auto cullable = dynamic_cast<CullableParent*>(renderable);
        if (cullable)
        {
            cullable->cull();
        }
        renderable->render(pRenderer);

       /* auto controllable = dynamic_cast<Controllable*>(renderable);
        if (controllable)
        {
            std::cout << "Controller name for " << renderable->name() << " is " << controllable->name() << '\n';
        }*/
    }

    // Represent to the screen
    SDL_RenderPresent(pRenderer);
}
