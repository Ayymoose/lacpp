#include <cassert>

#include "Window.h"

namespace Zelda
{

    Window::~Window()
    {
        SDL_DestroyWindow(m_mainWindow);
    }

    void Window::createWindow(const char* title, const int width, const int height)
    {
        m_mainWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
        assert(m_mainWindow != nullptr);
    }

}