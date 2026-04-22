#pragma once

#include "Singleton.h"
#include <SDL_scancode.h>
#include <SDL_events.h>

namespace zelda::engine
{

class Keyboard : public Singleton<Keyboard>
{
public:
    Keyboard();
    void eventHandler(SDL_Event event);

    // Returns true if a key is being pushed (held)
    bool keyPushed(const int key) const;

    bool keyPressed(const int key);

    bool keyReleased(const int key);
    int operator[](const int key);

private:
    // Updates the internal key state for every key
    void updateKeyStates(const int key, const bool pushed, const bool released);

    bool m_keyStatePushed[SDL_NUM_SCANCODES];
    bool m_keyStatePressed[SDL_NUM_SCANCODES];
    bool m_keyStatePressedRecord[SDL_NUM_SCANCODES];
    bool m_keyStateReleased[SDL_NUM_SCANCODES];
};

} // namespace zelda::engine