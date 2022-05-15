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
    bool keyPushed(const int key) const noexcept;

    bool keyPressed(const int key) noexcept;

    bool keyReleased(const int key) noexcept;
    int operator[](const int key) noexcept;
private:
    Keyboard();
    // Updates the internal key state for every key
    void updateKeyStates(const int key, const bool pushed, const bool released) noexcept;

    bool m_keyStatePushed[SDL_NUM_SCANCODES];
    bool m_keyStatePressed[SDL_NUM_SCANCODES];
    bool m_keyStatePressedRecord[SDL_NUM_SCANCODES];
    bool m_keyStateReleased[SDL_NUM_SCANCODES];
};

}