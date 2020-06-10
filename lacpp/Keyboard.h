#pragma once
#include "Singleton.h"
#include <SDL_scancode.h>

class Keyboard : public Singleton<Keyboard>
{
public:
    Keyboard();
    ~Keyboard() = default;
    void updateKeyStates(int key, bool pushedOrPressed, bool released);

    // Returns true if a key was pressed (single press)
    bool keyPressed(int key);
    // Returns true if a key was released
    bool keyReleased(int key);

    // Returns true if a key is being pushed (held)
    bool keyPushed(int key) const;
private:
    bool m_keyStatePushed[SDL_NUM_SCANCODES];
    bool m_keyStateReleased[SDL_NUM_SCANCODES];
    bool m_keyStatePressed[SDL_NUM_SCANCODES];
};