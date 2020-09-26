#pragma once

#include <SDL_image.h>
#include "Controller.h"
#include "Renderable.h"
#include "Character.h"
#include "UpdateTimer.h"
#include "Singleton.h"
#include "Clock.h"

namespace Zelda
{
    // The "viewing region" dimensions
    constexpr int CameraWidth = 160;
    constexpr int CameraHeight = 128;

    // How much we add to the position vector of the player to scroll
    constexpr int PlayerScrollSpeed = 1;

    // How much edge pixels to add to the width/height of the character before it triggers a scroll
    constexpr int ScrollRightEdge = 10;
    constexpr int ScrollLeftEdge = 0;
    constexpr int ScrollUpEdge = 0;
    constexpr int ScrollDownEdge = 0;

    // HUD Height
    constexpr int HUDHeight = 16;

    constexpr int ScrollSpeed = 4;


    class Camera : public Renderable, public Singleton<Camera>
    {
        friend class Singleton<Camera>;
    public:
        void setPosition(int x, int y) noexcept;
        void setScrollSpeed(int scrollSpeed) noexcept;
        void render(SDL_Renderer* pRenderer) noexcept override;
        void setCurrentBackground(SDL_Texture* currentBackground) noexcept;

        // Returns true whether a point is visible in the camera region
        bool visible(Vector<float> point) const noexcept;

        // The camera will track a Character
        void track(Character* character) noexcept;

        int getX() const noexcept;
        int getY() const noexcept;

    private:
        Camera();
        // Called in the render function
        void trackCharacter() noexcept;

        // m_scrollX and m_scrollY are manipulated to achieve scrolling
        int m_scrollX;
        int m_scrollY;

        // m_x and m_y is the initial position of the camera on the screen
        int m_x;
        int m_y;
        
        // Scrolling speed
        int m_scrollSpeed;
        Character* m_tracker;

        // Boolean flags to indicate which way the camera is scrolling
        bool m_scrollLeft;
        bool m_scrollRight;
        bool m_scrollDown;
        bool m_scrollUp;

        // Are we scrolling
        bool m_scrollCamera;

        // How many we scrolled by
        int m_scrolled;

        // TODO: Fix player movement during scrolling
        UpdateTimer m_timerPlayerScroll;

    };
}