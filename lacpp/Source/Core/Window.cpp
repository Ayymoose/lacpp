#include <assert.h>
#include "Window.h"
#include "InputControl.h"
#include "Controller.h"
#include "Keyboard.h"
#include "Inventory.h"
#include <string>
#include "Link.h"
#include "ZD_Assert.h"

Window::~Window()
{
    SDL_DestroyWindow(m_mainWindow);
}

void Window::createWindow(const char* title, const int width, const int height) noexcept
{
    m_mainWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    assert(m_mainWindow != nullptr);
}

SDL_Window* Window::getWindowHandle() const noexcept
{
    return m_mainWindow;
}