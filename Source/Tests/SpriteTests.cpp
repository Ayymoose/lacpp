#include "SpriteTests.h"
#include "ResourceManager.h"
#include "Engine.h"
#include "Renderer.h"
#include "Resource.h"

namespace Tests
{
    /*
    using namespace Zelda;

    void SpriteTests::runTests()
    {
        runTest(this, m_tests);
    }

    void SpriteTests::spriteTests() noexcept
    {
        constexpr Colour TRANSPARENCY_COLOUR = make_rgb(255, 0, 128);

        auto colouredSprite = Sprite(Renderer::getInstance().getRenderer(), 32, 32);
    
        // Create sprite test
        auto spriteBall = Sprite(Renderer::getInstance().getRenderer(), Resource::loadSprite(RESOURCE_OBJECT_PATH + "ball.png", TRANSPARENCY_COLOUR));
        auto spriteObstacle = Sprite(Renderer::getInstance().getRenderer(), Resource::loadSprite(RESOURCE_OBJECT_PATH + "obstacle.png", TRANSPARENCY_COLOUR));

        // Copy sprite test
        auto spriteBallCopy = spriteBall;

        // operator= copy test
        auto spriteObstacleCopy = spriteBall;
        spriteObstacleCopy = spriteObstacle;

        // move constructor test
        auto spriteObstacleMoveConstructed(std::move(spriteObstacleCopy));

        // move assign operator test
        auto spriteBallMoveAssigned(spriteBall);
        spriteBallMoveAssigned = std::move(spriteBallCopy);

        // self assignment test
        spriteBall = spriteBall;
        spriteObstacle = spriteObstacle;

        auto spriteFunction = [&spriteBall, 
            &spriteObstacle, 
            &spriteBallCopy,
            &spriteObstacleCopy, 
            &spriteObstacleMoveConstructed,
            &spriteBallMoveAssigned,
            &colouredSprite]()
        {
            Rect srcRect1 = { 0,0,16,16 };
            Rect dstRect1 = { 32,32,16,16 };
            spriteBall.drawSprite(srcRect1, dstRect1);

            Rect dstRect2 = { 64,32,16,16 };
            spriteObstacle.drawSprite(srcRect1, dstRect2);

            Rect dstRect3 = { 32,64,16,16 };
            spriteBallCopy.drawSprite(srcRect1, dstRect3);

            Rect dstRect4 = { 64,64,16,16 };
            spriteObstacleCopy.drawSprite(srcRect1, dstRect4);

            Rect dstRect5 = { 64,96,16,16 };
            spriteObstacleMoveConstructed.drawSprite(srcRect1, dstRect5);

            Rect dstRect6 = { 32, 96, 16, 16 };
            spriteBallMoveAssigned.drawSprite(srcRect1, dstRect6);

            Rect dstRect7 = { 0,0,32,32 };
            colouredSprite.colourSprite(Rect<int>{0, 0, 32, 32}, make_rgb(255, 0, 0));
            colouredSprite.drawSprite(Rect<int>{0, 0, 32, 32}, dstRect7);
        };

        Engine::getInstance().setRenderTestFunction(spriteFunction);

        Engine::getInstance().run();
    }
    */
}
