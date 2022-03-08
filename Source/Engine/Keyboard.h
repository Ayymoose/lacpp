#pragma once

#include "Singleton.h"
#include <SDL_scancode.h>
#include <SDL_events.h>

namespace Zelda
{

class Keyboard : public Singleton<Keyboard>
{
    friend class Singleton<Keyboard>;
public:

    void eventHandler(SDL_Event event) noexcept;

    // Returns true if a key is being pushed (held)
    bool keyPushed(int key) const noexcept;

    bool keyPressed(int key) noexcept;

    bool keyReleased(int key) noexcept;
    int operator[](int key) noexcept;
private:
    Keyboard();
    // Updates the internal key state for every key
    void updateKeyStates(int key, bool pushed, bool released) noexcept;

    bool m_keyStatePushed[SDL_NUM_SCANCODES];
    bool m_keyStatePressed[SDL_NUM_SCANCODES];
    bool m_keyStatePressedRecord[SDL_NUM_SCANCODES];
    bool m_keyStateReleased[SDL_NUM_SCANCODES];
};

}