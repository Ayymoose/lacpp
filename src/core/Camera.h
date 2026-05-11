#pragma once

#include "Updateable.h"
#include "Singleton.h"
#include "core/Vector.h"

#include <functional>

namespace zelda::engine
{

template <typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;

template <arithmetic T>
class Camera : public Singleton<Camera<T>>, public Updateable
{
public:
    void setPosition(T x, T y)
    {
        m_x = x;
        m_y = y;
    }

    void setScrollSpeed(T speed) { m_scrollSpeed = speed; }

    void setWidth(T width) { m_width = width; }

    void setHeight(T height) { m_height = height; }

    void setScrollLeftCondition(const std::function<bool()>& condition) { m_scrollLeftCondition = condition; }

    void setScrollRightCondition(const std::function<bool()>& condition) { m_scrollRightCondition = condition; }

    void setScrollUpCondition(const std::function<bool()>& condition) { m_scrollUpCondition = condition; }

    void setScrollDownCondition(const std::function<bool()>& condition) { m_scrollDownCondition = condition; }

    T scrollX() const { return m_scrollX; }

    T scrollY() const { return m_scrollY; }

    T getWidth() const { return m_width; }

    T getHeight() const { return m_height; }

    Vector<T> position() const { return {m_x, m_y}; }

    // Transforms position to camera coordinates
    Vector<T> toCoordinates(Vector<T> position) const { return position - this->position(); }

    void update() override
    {
        assert(m_scrollLeftCondition);
        assert(m_scrollRightCondition);
        assert(m_scrollUpCondition);
        assert(m_scrollDownCondition);

        // x < m_scrollX - SCROLL_LEFT_EDGE
        if (!m_scrollLeft && m_scrollLeftCondition())
        {
            m_scrollLeft = true;
        }
        else if (!m_scrollRight && m_scrollRightCondition())
        {
            // x > m_scrollX + CAMERA_WIDTH - SCROLL_RIGHT_EDGE
            m_scrollRight = true;
        }
        else if (!m_scrollUp && m_scrollUpCondition())
        {
            // y < m_scrollY - SCROLL_UP_EDGE
            m_scrollUp = true;
        }
        else if (!m_scrollDown && m_scrollRightCondition())
        {
            // y > m_scrollY + CAMERA_HEIGHT - SCROLL_DOWN_EDGE
            m_scrollDown = true;
        }

        if (m_scrollLeft)
        {
            if (m_scrolled != m_width)
            {
                m_scrollX -= m_scrollSpeed;
                m_scrolled += m_scrollSpeed;
            }
            else
            {
                // Update current view
                m_x -= m_width;

                m_scrollX = 0;
                m_scrollY = 0;

                m_scrollLeft = false;
                m_scrolled = 0;
            }
        }
        else if (m_scrollRight)
        {
            if (m_scrolled != m_width)
            {
                m_scrollX += m_scrollSpeed;
                m_scrolled += m_scrollSpeed;
            }
            else
            {
                m_x += m_width;

                m_scrollX = 0;
                m_scrollY = 0;

                m_scrollRight = false;
                m_scrolled = 0;
            }
        }
        else if (m_scrollDown)
        {
            if (m_scrolled != m_height)
            {
                m_scrollY += m_scrollSpeed;
                m_scrolled += m_scrollSpeed;
            }
            else
            {
                m_y += m_height;

                m_scrollX = 0;
                m_scrollY = 0;

                m_scrollDown = false;
                m_scrolled = 0;
            }
        }
        else if (m_scrollUp)
        {
            if (m_scrolled != m_height)
            {
                m_scrollY -= m_scrollSpeed;
                m_scrolled += m_scrollSpeed;
            }
            else
            {
                m_y -= m_height;

                m_scrollX = 0;
                m_scrollY = 0;

                m_scrollUp = false;
                m_scrolled = 0;
            }
        }
    }

private:
    // m_scrollX and m_scrollY are manipulated to achieve scrolling
    T m_scrollX{0};
    T m_scrollY{0};

    // m_x and m_y is the initial position of the camera in the map (screen)
    T m_x{0};
    T m_y{0};

    // Camera viewport dimensions
    T m_width{0};
    T m_height{0};

    // Scrolling speed
    T m_scrollSpeed{0};

    // Boolean flags to indicate which way the camera is scrolling
    bool m_scrollLeft{false};
    bool m_scrollRight{false};
    bool m_scrollDown{false};
    bool m_scrollUp{false};

    // How many we scrolled by
    T m_scrolled{0};

    std::function<bool()> m_scrollLeftCondition;
    std::function<bool()> m_scrollRightCondition;
    std::function<bool()> m_scrollUpCondition;
    std::function<bool()> m_scrollDownCondition;
};
} // namespace zelda::engine