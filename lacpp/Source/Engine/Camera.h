#pragma once

#include <SDL_image.h>
#include "Controller.h"
#include "Renderable.h"
#include "Character.h"
#include "UpdateTimer.h"
#include "Singleton.h"
#include "Clock.h"
#include "Tilemap.h"

namespace Zelda
{
    // The "viewing region" dimensions
    constexpr int CAMERA_WIDTH = 160;
    constexpr int CAMERA_HEIGHT = 128;

    // How much we add to the position vector of the player to scroll
    constexpr int PlayerScrollSpeed = 1;

    // How much edge pixels to add to the width/height of the character before it triggers a scroll
    constexpr int ScrollRightEdge = 10;
    constexpr int ScrollLeftEdge = 0;
    constexpr int ScrollUpEdge = 0;
    constexpr int ScrollDownEdge = 0;

    // HUD Height
    constexpr int HUD_HEIGHT = 16;

    constexpr int CAMERA_SCROLL_SPEED = 4;


    class Camera : public Renderable, public Singleton<Camera>
    {
        friend class Singleton<Camera>;
    public:
        void setPosition(int x, int y) noexcept;
        void setScrollSpeed(int scrollSpeed) noexcept;
        void render(SDL_Renderer* renderer) noexcept override;

        void setTileMap(TilemapArea tilemap);

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

        // Are we scrolling
        bool m_scrollCamera;

        // How many we scrolled by
        int m_scrolled;

        // World tilemap
        Tilemap m_tilemap;

        // TODO: Fix player movement during scrolling
        UpdateTimer m_timerPlayerScroll;

        SDL_Texture* m_swapCanvas;
        uint16_t m_nextRoomIndex;
    };
}