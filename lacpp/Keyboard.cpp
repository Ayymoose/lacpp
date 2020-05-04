#include "Keyboard.h"
#include <assert.h>

Keyboard::Keyboard()
{
    for (int i = 0; i < SDL_NUM_SCANCODES; i++)
    {
        m_keys[i] = false;
    }
}

bool& Keyboard::operator[](int keycode)
{
    assert(keycode > 0 && keycode < SDL_NUM_SCANCODES);
    return m_keys[keycode];
}

bool Keyboard::operator[](int keycode) const
{
    assert(keycode > 0 && keycode < SDL_NUM_SCANCODES);
    return m_keys[keycode];
}
