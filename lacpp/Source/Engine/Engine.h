#pragma once

#include "Singleton.h"
#include "Window.h"
#include "Resource.h"

namespace Zelda
{
    class Engine : public Singleton<Engine>
    {
        friend class Singleton<Engine>;
    public:
        void init() noexcept;
        void run() noexcept;
        void stop() const noexcept;
        void pause(bool pause) noexcept;
        bool paused() const noexcept;
    private:
        Engine() : m_enginePaused(false), m_engineRunning(false)
        {

        }
        void processEvents() noexcept;
        void processInput() noexcept;
        void renderObjects() const noexcept;

        void engineTest();

        Window m_mainWindow;
        bool m_enginePaused;
        bool m_engineRunning;
    };
}
