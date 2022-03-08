#include "SpriteTests.h"
#include "Renderer.h"

namespace Testable
{

using namespace Zelda;

void SpriteTests::runTests()
{
    runTest(this, m_tests);
}

void SpriteTests::spriteTests() noexcept
{
    Sprite s1;
    Sprite s2(s1);

   /* Window w;
    w.createWindow("Sprite test", 640, 480);
    Renderer::getInstance().createRenderer(w);
    Sprite s3(Renderer::getInstance().getRenderer(), 32, 32);
    Sprite::colourSprite(*/

}

}
