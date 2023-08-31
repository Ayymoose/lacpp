#include "Engine.h"
#include "Keyboard.h"
#include "Link.h"
#include "SDL_Assert.h"
#include "Dialogue.h"
#include "Controllable.h"
#include "RoomManager.h"
#include "DataManager.h"
#include "ResourceManager.h"
#include "Controller.h"

namespace Zelda
{
    void Engine::init()
    {
        // Initialise everything
        initVideo();
        initAudio();
        initControl();
        initWindow();
        initData();
        initSingleton();

        //m_initialised = true;

        DEBUG(DBG_INFO, "Engine initialised");
    }

    void Engine::run()
    {
        //assert(m_initialised && "Engine is not initialised");
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

    void Engine::stop()
    {
        // Cleanup
        assert(m_engineRunning && "Engine is not running");
        DEBUG(DBG_INFO, "Engine has stopped running");
        m_engineRunning = false;
        m_preRenderTestFunction = nullptr;
        m_renderTestFunction = nullptr;
    }

    void Engine::pause(bool pause)
    {
        m_enginePaused = pause;
    }

    bool Engine::paused() const
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

    void Engine::initVideo() const
    {
        SDL_ASSERT(SDL_Init(SDL_INIT_VIDEO));
    }

    void Engine::initAudio() const
    {
        SDL_ASSERT(SDL_Init(SDL_INIT_AUDIO));
    }

    void Engine::initControl() const
    {
        SDL_ASSERT(SDL_Init(SDL_INIT_GAMECONTROLLER));
    }

    void Engine::initData() const
    {
        DataManager::getInstance().loadData();
    }

    void Engine::initSingleton() const
    {
        Debug::getInstance();
        Renderer::getInstance();
        ResourceManager::getInstance();
        Controller::getInstance();
        Keyboard::getInstance();
        RoomManager::getInstance();
        Camera::getInstance();
        DataManager::getInstance();
        Link::getInstance();
    }

    void Engine::initWindow()
    {
        // Create the main window
        m_mainWindow.createWindow(MAIN_WINDOW_TITLE, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

        // Create main hardware renderer
        Renderer::getInstance().createRenderer(m_mainWindow);

        // Stretch the textures to the window size
        Renderer::getInstance().setRendererScale(MAIN_WINDOW_WIDTH / (float)CAMERA_WIDTH, MAIN_WINDOW_HEIGHT / ((float)CAMERA_HEIGHT + HUD_HEIGHT));
    }

    void Engine::events()
    {
        SDL_Event eventHandler;
        if (SDL_PollEvent(&eventHandler))
        {
            if (eventHandler.type == SDL_QUIT)
            {
                stop();
            }
            else if (eventHandler.type == SDL_KEYDOWN || eventHandler.type == SDL_KEYUP)
            {
                Keyboard::getInstance().eventHandler(eventHandler);
            }
        }
    }

    void Engine::update() const
    {
        auto const controller = Controller::getInstance().getController();
        if (controller)
        {
            controller->control();
        }
        auto const gameObjects = Renderer::getInstance().getRenderSet();
        for (const auto& gameObject : gameObjects)
        {
            assert(gameObject);
            auto const updateableGameObject = dynamic_cast<IUpdateable*>(gameObject);
            if (updateableGameObject)
            {
                updateableGameObject->update();
            }
        }
    }

    void Engine::render() const
    {
        Renderer::getInstance().clearScreen(COLOUR_BLACK);
        auto const renderables = Renderer::getInstance().getRenderSet();
        for (const auto& renderable : renderables)
        {
            assert(renderable);
            if (renderable->visible())
            {
                renderable->render();
            }
        }
        renderTestFunction();
        Renderer::getInstance().renderScreen();
    }

}