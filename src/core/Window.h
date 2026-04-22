#pragma once

#include <SDL_video.h>

namespace zelda::engine
{

class Window
{
public:
    Window()
        : m_mainWindow(nullptr) {};
    ~Window();
    void createWindow(const char* title, const int width, const int height);

    auto getWindowHandle() const { return m_mainWindow; }

private:
    SDL_Window* m_mainWindow;
};
} // namespace zelda::engine