#ifndef RENDERABLE_H
#define RENDERABLE_H
#include <SDL_image.h>


// A Renderable is an object that will be rendered on the screen
// Any screen that implements this class must implement the render() function
// A texture is provided to use for the object


class Renderable
{
public:
    Renderable()
    {
        m_texture = nullptr;
        m_width = 0;
        m_height = 0;
    }
    virtual ~Renderable()
    {

    }

    virtual void render(SDL_Renderer* pRenderer) = 0;

protected:
    SDL_Texture* m_texture;
    int m_width;
    int m_height;
};


#endif // !RENDERABLE_H
