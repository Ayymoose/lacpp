#pragma once

#include <SDL_image.h>
#include "Controller.h"
#include "Renderable.h"
#include "Character.h"
#include "Singleton.h"
#include "Timer.h"
#include "Tilemap.h"

namespace Zelda
{
    // The "viewing region" dimensions
    constexpr int CAMERA_WIDTH = 160;
    constexpr int CAMERA_HEIGHT = 128;

    // How much we add to the position vector of the player to scroll
    constexpr int PLAYER_SCROLL_SPEED = 1;

    // How much edge pixels to add to the width/height of the character before it triggers a scroll
    constexpr int SCROLL_RIGHT_EDGE = 10;
    constexpr int SCROLL_LEFT_EDGE = 0;
    constexpr int SCROLL_UP_EDGE = 0;
    constexpr int SCROLL_DOWN_EDGE = 0;

    // HUD Height
    constexpr int HUD_HEIGHT = 16;

    constexpr int CAMERA_SCROLL_SPEED = 4;

    // The game is locked to 60 fps because of VSync
    // So everything runs at 60 fps
    // It seems like using timers for scrolling to lock it 60fps was messing with that
    // It's not choppy anymore

    // #define FPS_60 (1.0 / 60.0) 
    constexpr float FPS_66 = (1.0f / 60.0f);
    constexpr float FPS_33 = (1.0f / 33.0f);    // To be adjusted!

    class Camera : public Renderable, public Singleton<Camera>
    {
        friend class Singleton<Camera>;
    public:
        void setPosition(int x, int y) noexcept;
        void setScrollSpeed(int scrollSpeed) noexcept;
        void render(SDL_Renderer* renderer) noexcept override;

        void setTileMap(TilemapArea tilemap) noexcept;

        // Returns true whether a rect is visible in the camera region
        bool visible(SDL_FRect&& rectangle) const noexcept;

        int getX() const noexcept;
        int getY() const noexcept;

        // Position as a vector
        Vector<float> position() const noexcept;

    private:
        Camera();
        // Called in the render function
        void renderTileMap(SDL_Renderer* renderer, SDL_Rect dstRect, SDL_Texture* srcTexture, uint16_t roomIndex) noexcept;

        // m_scrollX and m_scrollY are manipulated to achieve scrolling
        int m_scrollX;
        int m_scrollY;

        // m_x and m_y is the initial position of the camera in the tilemap
        int m_x;
        int m_y;

        int m_screenX;
        int m_screenY;


        int m_swapX;
        int m_swapY;
        
        // Scrolling speed
        int m_scrollSpeed;

        // Boolean flags to indicate which way the camera is scrolling
        bool m_scrollLeft;
        bool m_scrollRight;
        bool m_scrollDown;
        bool m_scrollUp;

        // How many we scrolled by
        int m_scrolled;

        // World tilemap
        Tilemap m_tilemap;

        // TODO: Fix player movement during scrolling
        Timer m_timerPlayerScroll;

        SDL_Texture* m_swapCanvas;
        int m_nextRoomIndex;
    };
}