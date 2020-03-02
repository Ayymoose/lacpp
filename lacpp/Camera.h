#ifndef CAMERA_H
#define CAMERA_H

#include <SDL_image.h>
#include "Controller.h"
#include "Renderable.h"
#include "Character.h"
#include "UpdateTimer.h"
#include "Singleton.h"

// The "viewing region" dimensions
#define CAMERA_WIDTH 160
#define CAMERA_HEIGHT 128

// Player related definitions
// How much we add to the position vector of the player to scroll
#define PLAYER_SCROLL_SPEED 1

// How much edge pixels to add to the width/height of the character before it triggers a scroll
#define SCROLL_RIGHT_EDGE 10
#define SCROLL_LEFT_EDGE 0
#define SCROLL_UP_EDGE 0
#define SCROLL_DOWN_EDGE 0

class Camera : public Renderable, public Singleton<Camera>, public Controllable
{
    friend class Singleton<Camera>;
public:
    void setPosition(int x, int y);
    void setScrollSpeed(int scrollSpeed);
    void render(SDL_Renderer* pRenderer) override;
    void setCurrentBackground(SDL_Texture* currentBackground);
   

    void control() override;

    // The camera will track a Character
    void track(Character* character);

    int getX() const;
    int getY() const;

private:
    Camera();
    // Called in the render function
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

    UpdateTimer m_timerCameraScroll;
    UpdateTimer m_timerPlayerScroll;

};

#endif
