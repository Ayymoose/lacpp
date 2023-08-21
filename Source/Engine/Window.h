#pragma once

#include <SDL_video.h>

namespace Zelda
{

    class Window
    {
    public:
        Window() : m_mainWindow(nullptr) {};
        ~Window();
        void createWindow(const char* title, const int width, const int height);

        auto getWindowHandle() const
        {
            return m_mainWindow;
        }

    private:
        SDL_Window* m_mainWindow;
    };
}