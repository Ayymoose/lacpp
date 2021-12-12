#include "Engine.h"
#include "Keyboard.h"
#include "Link.h"
#include "SDL_Assert.h"
#include "Dialogue.h"
#include "Controllable.h"
#include "Enemy.h"
#include "RoomManager.h"
#include "Tilemap.h"
#include <thread>

namespace Zelda
{
void Engine::init() noexcept
{
    // Initialise everything
    initVideo();
    initAudio();
    initControl();
    initWindow();
    initSingleton();

    // TODO: Move this somwhere

    // Load all resources (sound + graphics)
    ResourceManager::getInstance().loadGraphics();

    m_initialised = true;

    DEBUG(DBG_INFO, "Engine initialised");
}

void Engine::run() noexcept
{
    assert(m_initialised && "Engine is not initialised");
    assert(m_engineRunning == false && "Engine already running");

    m_engineRunning = true;

    // Main game loop
    while (m_engineRunning)
    {
        events();
        update();
        preRenderTestFunction();
        render();
    }

}

void Engine::stop() noexcept
{
    // Cleanup
    assert(m_engineRunning && "Engine is not running");
    DEBUG(DBG_INFO, "Engine has stopped running");
    m_engineRunning = false;
    m_preRenderTestFunction = nullptr;
    m_renderTestFunction = nullptr;
}

void Engine::pause(bool pause) noexcept
{
    m_enginePaused = pause;
}

bool Engine::paused() const noexcept
{
    return m_enginePaused;
}

Engine::~Engine()
{
    if (m_initialised)
    {
        SDL_Quit();
    }
}

void Engine::initVideo() const noexcept
{
    SDL_ASSERT(SDL_Init(SDL_INIT_VIDEO));
}

void Engine::initAudio() const noexcept
{
    SDL_ASSERT(SDL_Init(SDL_INIT_AUDIO));
}

void Engine::initControl() const noexcept
{
    SDL_ASSERT(SDL_Init(SDL_INIT_GAMECONTROLLER));
}

void Engine::initSingleton() const noexcept
{
    Debug::getInstance();
    Renderer::getInstance();
    ResourceManager::getInstance();
    Keyboard::getInstance();
    RoomManager::getInstance();
    Camera::getInstance();
}

void Engine::initWindow() noexcept
{
    // Create the main window
    m_mainWindow.createWindow(MAIN_WINDOW_TITLE, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

    // Create main hardware renderer
    Renderer::getInstance().createRenderer(m_mainWindow);

    // Stretch the textures to the window size
    Renderer::getInstance().setRendererScale(MAIN_WINDOW_WIDTH / (float)CAMERA_WIDTH, MAIN_WINDOW_HEIGHT / ((float)CAMERA_HEIGHT + HUD_HEIGHT));
}

void Engine::events() noexcept
{
    // TODO: There should be a Controller Singleton which can be a Keyboard or GameController
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

void Engine::update() const noexcept
{
    auto const gameObjects = Renderer::getInstance().getRenderSet();
    for (const auto& gameObject : gameObjects)
    {
        assert(gameObject);
        auto const updateableGameObject = dynamic_cast<Updateable*>(gameObject);
        if (updateableGameObject)
        {
            updateableGameObject->update();
        }
    }

    // TOOD: Should this go before or after update() ?
    auto const controller = Controller::getInstance().getController();
    if (controller)
    {
        controller->control();
    }

#if 0
    if (!Engine::getInstance().paused())
    {
        // TODO: If engine is paused, all animation/movement must be stopped until resumed
        // Engine is paused when 
        // - Opening the inventory and remains paused until inventory is closed
        // - Opening the file save screen
        // - Dialogue is running
        // - An item that opens the dialogue is obtained

        // Basic enemy function
        auto enemy = dynamic_cast<Enemy*>(renderable);
        if (enemy)
        {
            // Or can/can't attack
            enemy->attack();

            // Or can/can't be killed
            if (enemy->health() <= 0)
            {
                enemy->die();
            }
        }
    }

    //////////////////////////////////////////////////

#endif
}

void Engine::render() const noexcept
{
    Renderer::getInstance().clearScreen(COLOUR_BLACK);
    auto const renderables = Renderer::getInstance().getRenderSet();
    for (const auto& renderable : renderables)
    {
        assert(renderable);
        // Render only visible objects
        if (renderable->visible())
        {
            renderable->render();
        }
    }
    renderTestFunction();
    Renderer::getInstance().renderScreen();
}

}