#pragma once
#include "Singleton.h"
#include <SDL_scancode.h>

class Keyboard : public Singleton<Keyboard>
{
public:
    Keyboard();
    ~Keyboard() = default;
    bool& operator[](int keycode);
    bool operator[](int keycode) const;
private:
    bool m_keys[SDL_NUM_SCANCODES];
};