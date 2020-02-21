#ifndef CAMERA_H
#define CAMERA_H

#include <SDL_image.h>
#include "Controller.h"
#include "Renderable.h"

enum SCROLL_DIRECTION
{
    SCROLL_UP = 0,
    SCROLL_RIGHT,
    SCROLL_LEFT,
    SCROLL_DOWN
};

class Camera : public Controllable, public Renderable
{
public:
    Camera();
    void setPosition(int x, int y);
    void scroll(SCROLL_DIRECTION scrollDirection);
    void setScrollSpeed(int scrollSpeed);
    void render(SDL_Renderer* pRenderer);
    void setCurrentBackground(SDL_Texture* currentBackground);
    void control(const SDL_Event& event);
private:
    int m_x;
    int m_y;
    int m_cameraWidth;
    int m_cameraHeight;
    int m_scrollSpeed;
};


#endif
