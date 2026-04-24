#pragma once

#include <SDL_video.h>

namespace zelda::engine
{

class Window
{
public:
    Window();
    ~Window();

    void create(const char* title, int width, int height);

    auto getHandle() const { return m_mainWindow; }

private:
    SDL_Window* m_mainWindow;
};
} // namespace zelda::engine