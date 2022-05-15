#pragma once

#include "Updateable.h"
#include "Renderable.h"
#include "Singleton.h"
#include "Vector.h"

namespace Zelda
{
// The "viewing region" dimensions
constexpr int CAMERA_WIDTH = 160;
constexpr int CAMERA_HEIGHT = 128;

// HUD Height
constexpr int HUD_HEIGHT = 16;

// How much edge pixels to add to the width/height of the character before it triggers a scroll
// TODO: Check these again, along with the scrolling, when animation corrected to see if these are correct
constexpr int SCROLL_RIGHT_EDGE = 12;
constexpr int SCROLL_LEFT_EDGE = 4;
constexpr int SCROLL_UP_EDGE = 4;
constexpr int SCROLL_DOWN_EDGE = HUD_HEIGHT - 4;

// How many pixels per frame the camera scrolls
constexpr int CAMERA_SCROLL_SPEED = 4;
 

class Camera : public Renderable, public Singleton<Camera>, public Updateable
{
    friend class Singleton<Camera>;
public:
    void setPosition(const int x, const int y) noexcept;
    void setScrollSpeed(const int scrollSpeed) noexcept;

    void render() noexcept override;
    void update() noexcept override;

    // Returns true whether a rect is visible in the camera region
    template <typename R>
    bool visible(const Rect<R>& rectangle) const noexcept
    {
        if (rectangle.x > (m_scrollX + CAMERA_WIDTH) - rectangle.w)
        {
            return false;
        }
        else if (rectangle.x < m_scrollX)
        {
            return false;
        }
        else if (rectangle.y < m_scrollY)
        {
            return false;
        }
        else if (rectangle.y > (m_scrollY + CAMERA_HEIGHT) - rectangle.h)
        {
            return false;
        }
        return true;
    }

    int getX() const noexcept;
    int getY() const noexcept;

    // Position as a vector
    Vector<float> position() const noexcept;

private:
    Camera();

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

};
}