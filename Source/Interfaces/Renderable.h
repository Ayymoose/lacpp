#pragma once

#include <SDL_image.h>
#include "Timer.h"
#include <iostream>
#include <cassert>
#include "SDL_Assert.h"
#include "Vector.h"
#include "Sprite.h"
#include <memory>

// A Renderable is an object that will be rendered on the screen
// Any object that implements this class should override the render() function
// A texture is provided to use for the object

// A Renderable can also be animated too

namespace Zelda
{

struct Animation
{
    int x;                 // Initial X-position in sprite sheet for this animation
    int y;                 // Initial Y-position in sprite sheet for this animation
    int startFrame;        // Start frame in this animation
    int endFrame;          // End frame number for this animation
    float animationFPS;    // Animation rate in FPS
};

class Renderable
{
public:

    virtual ~Renderable() = default;
    virtual void render() noexcept = 0;

    bool visible() const noexcept
    {
        return m_visible;
    }

    int depth() const noexcept
    {
        assert(m_depth > 0);
        return m_depth;
    }

    std::string name() const noexcept
    {
        assert(!m_name.empty());
        return m_name;
    }

    void transition(int xTransition, int yTransition) noexcept
    {
        m_xTransition = xTransition;
        m_yTransition = yTransition;
    }

    Renderable(const char* name, const Sprite& texture, int depth) :
        m_sprite(std::make_unique<Sprite>(texture)),
        //m_sprite(std::make_unique<Sprite>(texture.renderer(), texture.surface())),
        m_width(0),
        m_height(0),
        m_srcRect({ 0,0,0,0 }),
        m_dstRect({ 0,0,0,0 }),
        m_xTransition(0),
        m_yTransition(0),
        m_name(name),
        m_depth(depth),
        m_animationStart(false),
        m_animationComplete(false),
        m_animationFPS(0.0f),
        m_animateXPos(0),
        m_animateYPos(0),
        m_currentFrame(0),
        m_endFrame(0),
        m_orientation(0.0f),
        m_flip(SDL_RendererFlip::SDL_FLIP_NONE),
        m_visible(true)
    {
        assert(depth > 0);
        // TODO: Fix error when this is uncommented
        //Renderer::getInstance().addRenderable(this);
    }

    Renderable() :
        //m_sprite(nullptr),
        m_width(0),
        m_height(0),
        m_srcRect({ 0,0,0,0 }),
        m_dstRect({ 0,0,0,0 }),
        m_xTransition(0),
        m_yTransition(0),
        m_depth(0),
        m_animationStart(false),
        m_animationComplete(false),
        m_animationFPS(0.0f),
        m_animateXPos(0),
        m_animateYPos(0),
        m_currentFrame(0),
        m_endFrame(0),
        m_orientation(0.0f),
        m_flip(SDL_RendererFlip::SDL_FLIP_NONE),
        m_visible(true)
    {
        assert(false && "Method not allowed");
        //Renderer::getInstance().addRenderable(this);
    }
private:

    // pause is to have the animation keep running or not when the engine is paused
    // gap is the number of pixels between each sprite in sheet (usually 0 and should be :|)
    template<typename R>
    void basicAnimateHelper(Rect<R>& srcRect, int gap, int startFrame, int frameCount, float fps, bool pause) noexcept
    {
        static Timer animationTimer;
        static int frameCounter = 0;
        srcRect.x = srcRect.x + ((srcRect.w + gap) * (startFrame + frameCounter));
        if (animationTimer.elapsed(fps) && !pause)
        {
            frameCounter = (frameCounter + 1) % frameCount;
        }
    }

protected:

    // Default texture to render
    std::unique_ptr<Sprite> m_sprite;

    // Dimensions
    int m_width;
    int m_height;

    // For sprite
    Rect<int> m_srcRect;
    Rect<float> m_dstRect;

    int m_xTransition;
    int m_yTransition;

    // Debug name
    std::string m_name;

    // Z-ordering
    int m_depth;

    // Animation

    // Basic horizontal strip animation
    template<typename R1, typename R2>
    void basicAnimate(SDL_Renderer* renderer, const Sprite& texture, Rect<R1> srcRect, Rect<R2> dstRect, int gap, int startFrame, int frameCount, float fps, bool pause)
    {
        basicAnimateHelper(srcRect, gap, startFrame, frameCount, fps, pause);
        texture.drawSprite(renderer, srcRect, dstRect);
    }

    // Extended animation
    template<typename R1, typename R2>
    void basicAnimateEx(SDL_Renderer* renderer, const Sprite& texture, const Rect<R1>& srcRect, const Rect<R2>& dstRect, int gap, int startFrame, int frameCount, float fps, float angle, bool pause)
    {
        basicAnimateHelper(srcRect, gap, startFrame, frameCount, fps, pause);
        texture.drawSpriteEx(renderer, srcRect, dstRect, angle, SpriteFlip::FLIP_NONE);
    }

    // TODO: When the animation finishes, reverse the animation
    /*void reverseAnimate(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& srcRect, SDL_Rect dstRect, int gap, int startFrame, int frameCount, float fps)
    {
        static Timer animationTimer;
        static int frameCounter = 0;
        srcRect.x = srcRect.x + ((srcRect.w + gap) * (startFrame + frameCounter));
        if (animationTimer.elapsed(fps))
        {
            frameCounter = (frameCounter + 1) % frameCount;
        }
        SDL_ASSERT(SDL_RenderCopy(renderer, texture, &srcRect, &dstRect));
    }*/

    Timer m_animationTimer;
    bool m_animationStart;
    bool m_animationComplete;
    float m_animationFPS;
    int m_animateXPos;
    int m_animateYPos;
    int m_currentFrame;
    int m_endFrame;
    float m_orientation;
    SDL_RendererFlip m_flip;
    bool m_visible;

    // Updateable
    /*static constexpr double m_dt = 1000.0 / (double)60;
    double m_currentTime = 0;
    double m_accumulator = 0;
    static constexpr double m_maxFrameTime = 60;
    double m_alphaTime = 0;
    Vector<float> m_lerpPrevious;*/

};

}