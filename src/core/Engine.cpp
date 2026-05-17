#include "Engine.h"
#include "Keyboard.h"
#include "zelda_core/Link.h"
#include "SDL_Check.h"
#include "zelda_gui/Dialogue.h"
#include "Controllable.h"
#include "zelda_core/RoomManager.h"
#include "DataManager.h"
#include "ResourceManager.h"
#include "Controller.h"
#include "Renderer.h"
#include "core/Camera.h"

#include <SDL.h>

namespace zelda::engine
{
void Engine::init()
{
    initVideo();
    initAudio();
    initControl();
    initWindow();
    initData();
    initSingleton();
    m_initialised = true;
}

void Engine::run()
{
    assert(!m_running);
    m_running = true;
    while (m_running)
    {
        input();
        update();
        render();
    }
}

void Engine::stop()
{
    assert(m_running);
    m_running = false;
}

void Engine::pause(bool pause)
{
    m_paused = pause;
}

bool Engine::paused() const
{
    return m_paused;
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
    SDL_CHECK(SDL_Init(SDL_INIT_VIDEO));
}

void Engine::initAudio() const
{
    SDL_CHECK(SDL_Init(SDL_INIT_AUDIO));
}

void Engine::initControl() const
{
    SDL_CHECK(SDL_Init(SDL_INIT_GAMECONTROLLER));
}

void Engine::initData() const
{
    DataManager::instance().loadData();
}

void Engine::initSingleton() const
{
    Logger::instance();
    Renderer::instance();
    ResourceManager::instance();
    Controller::instance();
    Keyboard::instance();
    core::RoomManager::instance();
    Camera<float>::instance();
    DataManager::instance();
    core::Link::instance();
}

void Engine::initWindow()
{
    // Create the main window
    m_mainWindow.create(MAIN_WINDOW_TITLE, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

    // Create main hardware renderer
    Renderer::instance().create(m_mainWindow);

    // Stretch the textures to the window size
    Renderer::instance().setRendererScale(MAIN_WINDOW_WIDTH / static_cast<float>(160 /*CAMERA_WIDTH*/),
                                          MAIN_WINDOW_HEIGHT
                                              / (static_cast<float>(128 /*CAMERA_HEIGHT*/) + 16 /*HUD_HEIGHT*/));
}

void Engine::input()
{
    SDL_Event eventHandler;
    if (SDL_PollEvent(&eventHandler))
    {
        if (eventHandler.type == SDL_QUIT)
        {
            stop();
        }
        else
        {
            Keyboard::instance().eventHandler(eventHandler);
        }
    }
}

void Engine::update() const
{
    if (const auto controller = Controller::instance().getController(); controller)
    {
        controller->control();
    }
    for (const auto& object : Renderer::instance().getRenderSet())
    {
        assert(object);
        if (const auto updateable = dynamic_cast<Updateable*>(object); updateable)
        {
            updateable->update();
        }
    }
}

void Engine::render() const
{
    Renderer::instance().clearScreen(Colour::BLACK);
    for (const auto& renderable : Renderer::instance().getRenderSet())
    {
        assert(renderable);
        renderable->render();
    }
    Renderer::instance().renderScreen();
}

} // namespace zelda::engine