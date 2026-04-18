#pragma once

#include "Singleton.h"
#include "Window.h"
#include "Resource.h"
#include <functional>

namespace Zelda
{

constexpr int MAIN_WINDOW_WIDTH = 160 * 6;
constexpr int MAIN_WINDOW_HEIGHT = 144 * 6;
constexpr const char* MAIN_WINDOW_TITLE = "Link's Awakening";

class Engine : public Singleton<Engine>
{
    friend class Singleton<Engine>;
public:
    void init();

    void run();
    void stop();
    void pause(bool pause);
    bool paused() const;
    ~Engine();

    void setPreRenderTestFunction(const std::function<void(void)>& function)
    {
        m_preRenderTestFunction = function;
    }

    void setRenderTestFunction(const std::function<void(void)>& function)
    {
        m_renderTestFunction = function;
    }

    void initVideo() const;
    void initWindow();
    void initData() const;

private:
    Engine() : m_enginePaused(false), m_engineRunning(false), m_initialised(false), m_preRenderTestFunction(nullptr)
    {

    }
    void events();
    void update() const;
    void render() const;

    void initAudio() const;
    void initControl() const;
    void initSingleton() const;
    

    void preRenderTestFunction() const
    {
        if (m_preRenderTestFunction && !m_renderTestFunction)
        {
            m_preRenderTestFunction();
        }
    }

    void renderTestFunction() const
    {
        if (m_renderTestFunction && !m_preRenderTestFunction)
        {
            m_renderTestFunction();
        }
    }

    Window m_mainWindow;
    bool m_enginePaused;
    bool m_engineRunning;
    bool m_initialised;

    std::function<void(void)> m_preRenderTestFunction;
    std::function<void(void)> m_renderTestFunction;
};
}
