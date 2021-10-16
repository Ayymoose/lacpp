#include "Engine.h"
#include "Keyboard.h"
#include "Link.h"
#include "ZD_Assert.h"
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
    // Initialise SDL
    SDL_ASSERT(SDL_Init(SDL_INIT_VIDEO), SDL_ERROR_MESSAGE);

    // Create the main window
    m_mainWindow.createWindow(MAIN_WINDOW_TITLE, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

    // Create main hardware renderer
    Renderer::getInstance().createRenderer(m_mainWindow.getWindowHandle());

    // Stretch the textures to the window size
    SDL_ASSERT(SDL_RenderSetScale(Renderer::getInstance().getRenderer(), MAIN_WINDOW_WIDTH / (float)CAMERA_WIDTH, MAIN_WINDOW_HEIGHT / ((float)CAMERA_HEIGHT + HUD_HEIGHT)), SDL_ERROR_MESSAGE);

    // Needs to be separated

    // Load all resources (sound + graphics)
    ResourceManager::getInstance().loadGraphics();

    // Initialise the keyboard
    Keyboard::getInstance();

    // Room manager
    RoomManager::getInstance();

    // Init camera
    Camera::getInstance();

    // TODO: Move this somwhere
    m_initialised = true;

    std::cout << "Engine initialised\n";
}

void Engine::run() noexcept
{
    assert(m_initialised && "Engine is not initialised");

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
    std::cout << "Engine has stopped running\n";
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

void Engine::events() noexcept
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

void Engine::update() const noexcept
{
    // TODO: Create an Updateable interface class and remove update() from Renderable
    auto const renderables = Renderer::getInstance().getRenderSet();
    for (const auto& renderable : renderables)
    {
        assert(renderable);
        renderable->update();
    }
}

void Engine::clearScreen() const noexcept
{
    // Clear black
    auto const renderer = Renderer::getInstance().getRenderer();
    SDL_ASSERT(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0), SDL_ERROR_MESSAGE);
    SDL_ASSERT(SDL_RenderClear(renderer), SDL_ERROR_MESSAGE);
}

void Engine::renderScreen() const noexcept
{
    // Represent to the screen
    auto const renderer = Renderer::getInstance().getRenderer();
    SDL_RenderPresent(renderer);
}

void Engine::render() const noexcept
{
    static auto renderStartTime = SDL_GetTicks();
    static auto renderedFrames = 0;

    clearScreen();

    // Render any objects
    auto const renderables = Renderer::getInstance().getRenderSet();

    for (const auto& renderable : renderables)
    {
        assert(renderable);

        // This shouldn't be here

        //////////////////////////////////////////////////
        // Cull any objects out of view
        auto cullable = dynamic_cast<CullableParent*>(renderable);
        if (cullable)
        {
            cullable->cull();
        }

        // TODO: Should be in a logic function

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

        renderable->render();

    }


    renderTestFunction();

    renderScreen();

    renderedFrames++;

    //auto lx = Link::getInstance().position().x;
    //auto ly = Link::getInstance().position().y;
    //std::string windowTitle = MAIN_WINDOW_TITLE " - LX: " + std::to_string(lx) + " LY: " + std::to_string(ly);
    //SDL_SetWindowTitle(m_mainWindow.getWindowHandle(), windowTitle.c_str());

#if 0

    auto elapsedTicks = SDL_GetTicks() - renderStartTime;
    //std::cout << "elapsed: " << elapsedTicks << "\n";

   if (elapsedTicks >= 1000)
    {
        std::string windowTitle = MAIN_WINDOW_TITLE " - FPS: " + std::to_string((elapsedTicks / 1000.0f) * (double)renderedFrames);
        std::cout << "Rendererd frames in this second: " << renderedFrames << '\n';
        SDL_SetWindowTitle(m_mainWindow.getWindowHandle(), windowTitle.c_str());
        renderStartTime = SDL_GetTicks();
        renderedFrames = 0;
    }
#endif
}

#if 0
void Engine::engineTest()
{
    // Set camera position
    Camera::getInstance().setScrollSpeed(CAMERA_SCROLL_SPEED);
    Camera::getInstance().setPosition(480, 640);
    Camera::getInstance().setTileMap(RM_TAIL_CAVE);


    // Dialogue::getInstance().message("You got your sword! It has your name on the back! Very nice");
    // Dialogue::getInstance().message("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFABCDEFGHIJKLMNOPXRSTUVWXYZABCDEFABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFABCDEFGHIJKLMNOPXRSTUVWXYZABCDEF");//"You've got a    Guardian Acorn! It will reduce  the damage you  take by half!");
    //Dialogue::getInstance().question("Our colors are  ""never the same! ""If I am red, he ""is blue! If he  ""is red, I am    ""blue! What color""is my cloth?", "Red","Blue", Link::getInstance().position().y);

    //std::string test = "test";
   // Dialogue::getInstance().message("Level 1--       ""     Tail Cave", Link::getInstance().position().y);

    // TODO: Make sure local objects when destroyed get removed from renderer
    /*static SeaUrchin su(72,64);
    static Beamos be(72, 80);
    static GopongaFlower goflower(32, 80);
    static Gibdo gibdo(16, 64);
    static LikeLike likelike(32, 64);
    static HardhatBeetle hhb(80, 32);
    static Bubble bubble(32, 16);
    static Star star(64, 32);
    static Vacuum vacuum(96, 0);
    static BladeTrap bladeTrap(64, 64);
    static ArmMimic arm(64, 64);
    static ShyGuy arm(64, 64);
    static WaterTektite waterTektite(64, 64);
    static IronMask ironMask(64, 64);
    static ThreeOfAKind threeOfAKind(64, 64);
    static Spark spark(64, 64);
    static Leever leever(64, 64);
    static SandCrab sandcrab(64, 64);
    static BuzzBlob buzzblod(64, 64);
    static Zombie zombie(64, 64);
    static Peahat peahat(64, 64);*/

    // 18/02/2021 - Update

    /*
    Too many things are broken here and I'm too lazy to work on this anymore

    1) Frame rate will be dependant on the users VSync refresh rate either 60Hz, 75Hz or 120Hz
    2) Not entirely sure how to do the corner cutting and Link collisions
    3) Need to create GUI tool to allow me to place solid tiles and auto-generate collision maps
    4) Software timers are kind of broken
    5) Animation
    6) Keyboard input
    7) Graphics loading

    * /

    /*

        // TODOs

        // 1. Game introduction
        // 2. File select
        // 3. Save file
        // 4. Collisions
        // 5. Enemies
        // 6. Sound
        // 7. Objects
        // 8. Fix timer classes
        // 9. Dialogue outstanding issues
        // 10. Engine pausing


    */
}

#endif

}