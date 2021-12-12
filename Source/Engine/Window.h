#pragma once

#include "Jenkins.h"
#include <SDL_video.h>

namespace Zelda
{

constexpr int MAIN_WINDOW_WIDTH = 160 * 4;
constexpr int MAIN_WINDOW_HEIGHT = 144 * 4;
constexpr const char* MAIN_WINDOW_TITLE = "Link's Awakening - " LACPP_BUILD " ";// LACPP_BUILD_DATE

class Window
{
public:
    Window() : m_mainWindow(nullptr) {};
    ~Window();
    void createWindow(const char* title, const int width, const int height) noexcept;
    SDL_Window* getWindowHandle() const noexcept;
private:
    SDL_Window* m_mainWindow;
};
}