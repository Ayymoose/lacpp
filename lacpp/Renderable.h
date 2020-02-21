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
        m_Texture = nullptr;
    }
    virtual ~Renderable()
    {
    }

    virtual void render(SDL_Renderer* pRenderer) = 0;

protected:
    SDL_Texture* m_Texture;
};


#endif // !RENDERABLE_H
