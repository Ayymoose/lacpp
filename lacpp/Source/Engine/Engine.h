#pragma once

#include "Singleton.h"
#include "Window.h"
#include "Resource.h"

namespace Zelda
{
    class Engine : public Singleton<Engine>
    {
    public:
        Engine() : m_enginePaused(false), m_engineRunning(false) {}
        void init() noexcept;
        void run() noexcept;
        void stop() const noexcept;
        void pauseEngine(bool pause) noexcept;
        bool enginePaused() const noexcept;
    private:

        void processEvents() noexcept;
        void processInput() noexcept;
        void renderObjects() const noexcept;

        Window m_mainWindow;
        bool m_enginePaused;
        bool m_engineRunning;
    };
}
