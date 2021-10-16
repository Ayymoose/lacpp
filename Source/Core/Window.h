#pragma once

#include <assert.h>
#include "Resource.h"
#include "Renderer.h"
#include "Camera.h"
#include "Jenkins.h"

constexpr int MAIN_WINDOW_WIDTH = 160 * 4;
constexpr int MAIN_WINDOW_HEIGHT = 144 * 4;
#define MAIN_WINDOW_TITLE "Link's Awakening - " LACPP_BUILD " " LACPP_BUILD_DATE

namespace Zelda
{
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