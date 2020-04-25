#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <SDL_image.h>
#include "UpdateTimer.h"
#include <iostream>

// A Renderable is an object that will be rendered on the screen
// Any object that implements this class should override the render() function
// A texture is provided to use for the object

// A Renderable can also be animated too

struct Animation
{
    int x;                 // Initial X-position in sprite sheet for this animation
    int y;                 // Initial Y-position in sprite sheet for this animation
    int currentFrame;      // Initial frame in this animation
    int maxFrame;          // Maximum frame number for this animation
    double animationFPS;   // Animation rate in FPS
    double orientation;    // Rotation
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
        m_maxFrame = 0;
        m_orientation = 0.0;
    }
    virtual ~Renderable() = default;

    // Make it render the default texture if none specified
    virtual void render(SDL_Renderer* pRenderer)
    {
        SDL_RenderCopy(pRenderer, m_texture, nullptr, nullptr);
    }

    int getDepth() const
    {
        return m_depth;
    }

    std::string friendlyName() const
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
    UpdateTimer m_animationTimer;
    double m_animationFPS;
    int m_animateXPos;
    int m_animateYPos;
    int m_currentFrame;
    int m_maxFrame;
    double m_orientation;
};

#endif // !RENDERABLE_H
