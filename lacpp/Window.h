#include <assert.h>
#include "Resource.h"
#include "Renderer.h"
#include "Camera.h"

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#define MAIN_WINDOW_WIDTH 160*4
#define MAIN_WINDOW_HEIGHT 144*4

#define MAIN_WINDOW_TITLE "Link's Awakening"

class Window
{
public:
    Window();
    ~Window();
    void createWindow(const char* title, const int width, const int height);
    SDL_Window* getWindowHandle();
    void beginEventLoop();

private:
    SDL_Window* m_mainWindow;
    bool m_quitApplication;
    SDL_Event m_eventHandler;

    void handleWindowEvents();
    void handleInput();
    void renderObjects();

};

#endif