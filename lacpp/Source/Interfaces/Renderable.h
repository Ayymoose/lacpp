#pragma once

#include <SDL_image.h>
#include "Timer.h"
#include <iostream>
#include <assert.h>
#include "ZD_Assert.h"

// A Renderable is an object that will be rendered on the screen
// Any object that implements this class should override the render() function
// A texture is provided to use for the object

// A Renderable can also be animated too

struct Animation
{
    int x;                 // Initial X-position in sprite sheet for this animation
    int y;                 // Initial Y-position in sprite sheet for this animation
    int startFrame;        // Start frame in this animation
    int endFrame;          // End frame number for this animation
    float animationFPS;    // Animation rate in FPS
    float orientation;     // Rotation
    SDL_RendererFlip flip; // Flip sprite (horizontal or vertical)
};

class Renderable
{
public:

    virtual ~Renderable() = default;
    // Can't be const* because the library takes non-const pointer
    virtual void render(SDL_Renderer* renderer) noexcept = 0;

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

    Renderable(const char* name, SDL_Texture* texture, int depth) :
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
        m_texture = texture;
        SDL_ASSERT(SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height), SDL_ERROR_MESSAGE);
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
protected:

    // Default texture to render
    SDL_Texture* m_texture;

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
    void basicAnimate(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& srcRect, SDL_Rect dstRect, int gap, int startFrame, int frameCount, float fps)
    {
        static Timer animationTimer;
        static int frameCounter = 0;
        srcRect.x = srcRect.x + ((srcRect.w + gap) * (startFrame + frameCounter));
        if (animationTimer.elapsed(fps))
        {
            frameCounter = (frameCounter + 1) % frameCount;
        }
        SDL_ASSERT(SDL_RenderCopy(renderer, texture, &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }

    // TODO: When the animation finishes, reverse the animation
    void reverseAnimate(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& srcRect, SDL_Rect dstRect, int gap, int startFrame, int frameCount, float fps)
    {
        static Timer animationTimer;
        static int frameCounter = 0;
        srcRect.x = srcRect.x + ((srcRect.w + gap) * (startFrame + frameCounter));
        if (animationTimer.elapsed(fps))
        {
            frameCounter = (frameCounter + 1) % frameCount;
        }
        SDL_ASSERT(SDL_RenderCopy(renderer, texture, &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }

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
};