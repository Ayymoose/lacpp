#pragma once

#include "Singleton.h"
#include <SDL_scancode.h>

namespace Zelda
{

    class Keyboard : public Singleton<Keyboard>
    {
        friend class Singleton<Keyboard>;
    public:
        // Updates the internal key state for every key
        void updateKeyStates(int key, bool pushed, bool released) noexcept;
        // Returns true if a key is being pushed (held)
        bool keyPushed(int key) const noexcept;

        bool keyPressed(int key) noexcept;

        bool keyReleased(int key) noexcept;
        int operator[](int key) noexcept;
    private:
        Keyboard();

        bool m_keyStatePushed[SDL_NUM_SCANCODES];
        bool m_keyStatePressed[SDL_NUM_SCANCODES];
        bool m_keyStatePressedRecord[SDL_NUM_SCANCODES];
        bool m_keyStateReleased[SDL_NUM_SCANCODES];
    };

}