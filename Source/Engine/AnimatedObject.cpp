#include "AnimatedObject.h"

namespace Zelda
{

AnimatedObject::AnimatedObject(AnimatedClass animatedClass, int x, int y, int repeatAcross, float orientation) : 
    Renderable("AnimatedObject", ResourceManager::getInstance()[Graphic::GFX_ANIMATED_TILES], ZD_DEPTH_BACKGROUND)
{
    switch (animatedClass)
    {
    case AnimatedClass::AN_TORCH: 
        m_srcRect = { 0,0,16,16 };
        m_currentFrame = 0;
        m_endFrame = 3;
        break;
    case AnimatedClass::AN_CANDLE: 
        m_srcRect = { 80,0,16,16 };
        m_currentFrame = 0;
        m_endFrame = 3;
        break;
    case AnimatedClass::AN_GREEN_GRASS: 
        m_srcRect = { 0,16,16,16 };
        m_currentFrame = 0;
        m_endFrame = 3;
        break;
    case AnimatedClass::AN_BLUE_WATER: 
        m_srcRect = { 64,16,16,16 };
        m_currentFrame = 0;
        m_endFrame = 3;
        break;
    case AnimatedClass::AN_WATER_FALL: 
        m_srcRect = { 128,16,16,16 };
        m_currentFrame = 0;
        m_endFrame = 3;
        break;
    case AnimatedClass::AN_LAVA: 
        m_srcRect = { 0,32,16,16 };
        m_currentFrame = 0;
        m_endFrame = 3;
        break;
    case AnimatedClass::AN_UNDERWORLD_TORCH: 
        m_srcRect = { 64,32,16,16 };
        m_currentFrame = 0;
        m_endFrame = 3;
        break;
    /*case AnimatedClass::AN_ARROW_PLATFORM: 
        m_srcRect = { 128,32,16,16 };
        break;
    case AnimatedClass::AN_SWIVEL_DOOR: 
        m_srcRect = { 0,48,16,16 };
        break;*/
    case AnimatedClass::AN_SHALLOW_WATER_BLUE: 
        m_srcRect = { 144,48,16,16 };
        m_currentFrame = 0;
        m_endFrame = 3;
        break;
    case AnimatedClass::AN_DEEP_WATER_BLUE: 
        m_srcRect = { 0,64,16,16 };
        m_currentFrame = 0;
        m_endFrame = 3;
        break;
        default:
            assert(false);
    }

    m_width = 16;
    m_height = 16;
    m_position.x = x;
    m_position.y = y;

    m_dstRect = {0,0, static_cast<float>(m_width), static_cast<float>(m_height) };
    m_repeatAcross = repeatAcross;
    m_animationFPS = ANIMATED_OBJECT_FPS;
    m_orientation = orientation;
}

void AnimatedObject::render() noexcept
{
    SDL_FRect dstRect = m_dstRect;
    dstRect.x = m_position.x - m_xTransition - Camera::getInstance().getX();
    dstRect.y = m_position.y - m_yTransition - Camera::getInstance().getY();
    for (int i = 0; i <= m_repeatAcross; i++)
    {
        //basicAnimateExF(Renderer::getInstance().getRenderer(), m_texture, m_srcRect, dstRect, 0, m_currentFrame, m_endFrame, m_animationFPS, m_orientation, Engine::getInstance().paused());
        dstRect.x += m_width;
    }
}

}