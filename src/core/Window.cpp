#include <cassert>

#include "Window.h"
#include "core/SDL_Check.h"

namespace zelda::engine
{

Window::Window()
    : m_mainWindow(nullptr)
{}

Window::~Window()
{
    SDL_DestroyWindow(m_mainWindow);
    SDL_CHECK_NO_ERROR();
}

void Window::create(const char* title, int width, int height)
{
    assert(!m_mainWindow);
    m_mainWindow =
        SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    SDL_ASSERT(m_mainWindow);
}

} // namespace zelda::engine