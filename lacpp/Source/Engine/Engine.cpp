#include "Engine.h"
#include "Keyboard.h"
#include "Link.h"
#include "ZD_Assert.h"
#include "Dialogue.h"
#include "Controllable.h"
#include "Enemy.h"

#include "ArmMimic.h"
#include "SeaUrchin.h"
#include "Beamos.h"
#include "GopongaFlower.h"
#include "Gibdo.h"
#include "LikeLike.h"
#include "HardhatBeetle.h"
#include "Bubble.h"
#include "Star.h"
#include "Vacuum.h"
#include "BladeTrap.h"
#include "ShyGuy.h"
#include "WaterTektite.h"
#include "IronMask.h"
#include "ThreeOfAKind.h"
#include "Spark.h"
#include "Leever.h"
#include "SandCrab.h"
#include "BuzzBlob.h"
#include "Zombie.h"
#include "Peahat.h"


#include "Tilemap.h"

void Zelda::Engine::init() noexcept
{
    // Initialise SDL
    SDL_ASSERT(SDL_Init(SDL_INIT_VIDEO), SDL_ERROR_MESSAGE);

    // Create the main window
    m_mainWindow.createWindow(MAIN_WINDOW_TITLE, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

    // Create main hardware renderer
    Renderer::getInstance().createRenderer(m_mainWindow.getWindowHandle());

    // Stretch the textures to the window size
    SDL_ASSERT(SDL_RenderSetScale(Renderer::getInstance().getRenderer(), MAIN_WINDOW_WIDTH / (float)CAMERA_WIDTH, MAIN_WINDOW_HEIGHT / ((float)CAMERA_HEIGHT + HUD_HEIGHT)), SDL_ERROR_MESSAGE);

    // Load all resources (sound + graphics)
    ResourceManager::getInstance().loadGraphics();
    ResourceManager::getInstance().loadSounds();

    // Initialise the keyboard
    Keyboard::getInstance();
    
    // Initialise the camera
    Camera::getInstance().setScrollSpeed(CAMERA_SCROLL_SPEED);

    // Testing goes in here
    engineTest();
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
    SDL_Renderer* renderer = Renderer::getInstance().getRenderer();

    // Clear black
    SDL_ASSERT(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0), SDL_ERROR_MESSAGE);
    SDL_ASSERT(SDL_RenderClear(renderer), SDL_ERROR_MESSAGE);

    // Render any objects
    auto renderSet = Renderer::getInstance().getRenderSet();

    for (const auto& renderable : renderSet)
    {
        assert(renderable);


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

        renderable->render(renderer);

    }

    // Represent to the screen
    SDL_RenderPresent(renderer);
}

void Engine::engineTest()
{
    // Set camera position
    Camera::getInstance().setPosition(480, 640);
    Camera::getInstance().setTileMap(TM_TAIL_CAVE);


    // Dialogue::getInstance().message("You got your sword! It has your name on the back! Very nice");
    // Dialogue::getInstance().message("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFABCDEFGHIJKLMNOPXRSTUVWXYZABCDEFABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFABCDEFGHIJKLMNOPXRSTUVWXYZABCDEF");//"You've got a    Guardian Acorn! It will reduce  the damage you  take by half!");
    //Dialogue::getInstance().question("Our colors are  ""never the same! ""If I am red, he ""is blue! If he  ""is red, I am    ""blue! What color""is my cloth?", "Red","Blue", Link::getInstance().position().y);

    //std::string test = "test";
    Dialogue::getInstance().message("Level 1--       ""     Tail Cave", Link::getInstance().position().y);

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
    static Zombie zombie(64, 64);*/
    static Peahat peahat(64, 64);



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