#pragma once

#include "Singleton.h"
#include "Window.h"

namespace zelda::engine
{

class Engine : public Singleton<Engine>
{
public:

    static constexpr int MAIN_WINDOW_WIDTH = 160 * 6;
    static constexpr int MAIN_WINDOW_HEIGHT = 144 * 6;
    static constexpr const char* MAIN_WINDOW_TITLE = "Link's Awakening";

    ~Engine();

    void init();

    void run();
    void stop();
    void pause(bool pause);
    bool paused() const;

private:
    void input();
    void update() const;
    void render() const;

    void initVideo() const;
    void initWindow();
    void initData() const;
    void initAudio() const;
    void initControl() const;
    void initSingleton() const;

    Window m_mainWindow;
    bool m_paused{false};
    bool m_running{false};
    bool m_initialised{false};

};
} // namespace zelda::engine
