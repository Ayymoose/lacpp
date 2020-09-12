#pragma once

#include "Singleton.h"
#include <SDL_scancode.h>

namespace Zelda
{

    class Keyboard : public Singleton<Keyboard>
    {
    public:
        Keyboard();
        // Updates the internal key state for every key
        void updateKeyStates(int key, bool pushed) noexcept;
        // Returns true if a key is being pushed (held)
        bool keyPushed(int key) const noexcept;
        int operator[](int key) noexcept;
    private:
        bool m_keyStatePushed[SDL_NUM_SCANCODES];
    };

}