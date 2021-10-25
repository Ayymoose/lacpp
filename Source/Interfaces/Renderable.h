#pragma once

#include <SDL_image.h>
#include "Timer.h"
#include <iostream>
#include <cassert>
#include "ZD_Assert.h"
#include "Vector.h"
#include "Sprite.h"

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
    virtual void update() noexcept = 0;

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
        m_srcRect({ 0,0,0,0 }),
        m_dstRect({ 0,0,0,0 }),
        m_xTransition(0),
        m_yTransition(0),
        m_name(name),
        m_animationStart(false),
        m_animationComplete(false),
        m_animationFPS(0.0f),
        m_animateXPos(0),
        m_animateYPos(0),
        m_currentFrame(0),
        m_endFrame(0),
        m_orientation(0.0f),
        m_flip(SDL_RendererFlip::SDL_FLIP_NONE)
    {
        assert(texture.data());
        m_texture = texture;
        m_depth = depth;
    }

    Renderable() :
        m_texture(nullptr),
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
        m_flip(SDL_RendererFlip::SDL_FLIP_NONE)
    {
    }
private:

    // pause is to have the animation keep running or not when the engine is paused
    // gap is the number of pixels between each sprite in sheet (usually 0 and should be :|)
    void basicAnimateHelper(SDL_Rect& srcRect, int gap, int startFrame, int frameCount, float fps, bool pause) noexcept
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
    Sprite m_texture;

    // Dimensions
    int m_width;
    int m_height;

    // For sprite
    SDL_Rect m_srcRect;
    SDL_FRect m_dstRect;

    int m_xTransition;
    int m_yTransition;

    // Debug name
    std::string m_name;

    // Z-ordering
    int m_depth;

    // Animation

    // Basic horizontal strip animation
    void basicAnimate(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect, int gap, int startFrame, int frameCount, float fps, bool pause)
    {
        basicAnimateHelper(srcRect, gap, startFrame, frameCount, fps, pause);
        SDL_ASSERT(SDL_RenderCopy(renderer, texture, &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }

    // Note: Takes an SDL_FRect for dstRect
    void basicAnimateExF(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect, SDL_FRect dstRect, int gap, int startFrame, int frameCount, float fps, float orientation, bool pause)
    {
        basicAnimateHelper(srcRect, gap, startFrame, frameCount, fps, pause);
        SDL_ASSERT(SDL_RenderCopyExF(renderer, texture, &srcRect, &dstRect, orientation, nullptr, SDL_RendererFlip::SDL_FLIP_NONE), SDL_ERROR_MESSAGE);
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
        SDL_ASSERT(SDL_RenderCopy(renderer, texture, &srcRect, &dstRect), SDL_ERROR_MESSAGE);
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

    // Updateable
    static constexpr double m_dt = 1000.0 / (double)60;
    double m_currentTime = 0;
    double m_accumulator = 0;
    static constexpr double m_maxFrameTime = 60;
    double m_alphaTime = 0;
    Vector<float> m_lerpPrevious;

};

}