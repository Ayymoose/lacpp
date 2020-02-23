#ifndef CAMERA_H
#define CAMERA_H

#include <SDL_image.h>
#include "Controller.h"
#include "Renderable.h"
#include "Character.h"

// The "viewing region" dimensions
#define CAMERA_WIDTH 160
#define CAMERA_HEIGHT 128

class Camera : public Controllable, public Renderable
{
public:
    Camera();
    void setPosition(int x, int y);
    void setScrollSpeed(int scrollSpeed);
    void render(SDL_Renderer* pRenderer);
    void setCurrentBackground(SDL_Texture* currentBackground);
    void control(const SDL_Event& event);
   
    // The camera will track a Character
    void track(Character* character);

    int getX() const
    {
        return m_scrollX;
    }
    int getY() const
    {
        return m_scrollY;
    }
private:
    void trackCharacter();
    // m_scrollX and m_scrollY are manipulated to achieve scrolling
    int m_scrollX;
    int m_scrollY;
    // m_x and m_y is the initial position of the camera on the screen
    int m_x;
    int m_y;
    int m_scrollSpeed;
    Character* m_tracker;

    bool m_scrollLeft;
    bool m_scrollRight;
    bool m_scrollDown;
    bool m_scrollUp;
    int m_scrolled;
    bool m_scrollCamera;
};

/*

 
  Resource StartX StartY

*/

#endif
