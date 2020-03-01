#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <SDL_image.h>
#include "UpdateTimer.h"

// A Renderable is an object that will be rendered on the screen
// Any object that implements this class should override the render() function
// A texture is provided to use for the object

// A Renderable can also be animated too

struct Animation
{
    int x;                // Initial X-position in sprite sheet for this animation
    int y;                // Initial Y-position in sprite sheet for this animation
    int currentFrame;     // Initial frame in this animation
    int maxFrame;         // Maximum frame number for this animation
    double animationFPS;  // Animation rate in FPS
    double orientation;   // Rotation
    int m_spacing;        // Spacing between each frame
};

class Renderable
{
public:
    Renderable()
    {
        m_texture = nullptr;
        m_width = 0;
        m_height = 0;

        m_animationFPS = 0.0;
        m_animateXPos = 0;
        m_animateYPos = 0;
        m_currentFrame = 0;
        m_maxFrame = 0;
        m_spacing = 0;
        m_orientation = 0.0;
    }
    virtual ~Renderable()
    {
        SDL_DestroyTexture(m_texture);
    }

    // Make it render the default texture if none specified
    virtual void render(SDL_Renderer* pRenderer)
    {
        SDL_RenderCopy(pRenderer, m_texture, nullptr, nullptr);
    }

protected:
    // Default rendering
    SDL_Texture* m_texture;
    int m_width;
    int m_height;

    // Animation
    UpdateTimer m_animationTimer;
    double m_animationFPS;
    int m_animateXPos;
    int m_animateYPos;
    int m_currentFrame;
    int m_maxFrame;
    int m_spacing;
    double m_orientation;
};


#endif // !RENDERABLE_H
