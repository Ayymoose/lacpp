#pragma once

#include <SDL_image.h>
#include "UpdateTimer.h"
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
    Renderable()
    {
        m_texture = nullptr;
        m_width = 0;
        m_height = 0;
        m_depth = 0;
        m_animationFPS = 0.0;
        m_animateXPos = 0;
        m_animateYPos = 0;
        m_currentFrame = 0;
        m_endFrame = 0;
        m_orientation = 0.0;

        m_animationStart = false;
        m_animationComplete = false;
    }
    virtual ~Renderable() = default;

    // Make it render the default texture if none specified
    virtual void render(SDL_Renderer* pRenderer) noexcept
    {
        ZD_ASSERT(SDL_RenderCopy(pRenderer, m_texture, nullptr, nullptr) == 0, "SDL Error: " << SDL_GetError());
    }

    int depth() const noexcept
    {
        assert(m_depth > 0);
        return m_depth;
    }

    std::string friendlyName() const noexcept
    {
        return m_name;
    }

protected:
    // Default rendering
    SDL_Texture* m_texture;
    int m_width;
    int m_height;


    // Debug name
    std::string m_name;

    // Z-ordering
    int m_depth;

    // Animation
    // TODO: Animating sprites common function

    UpdateTimer m_animationTimer;
    bool m_animationStart;
    bool m_animationComplete;
    float m_animationFPS;
    int m_animateXPos;
    int m_animateYPos;
    int m_currentFrame;
    int m_endFrame;
    float m_orientation;
};