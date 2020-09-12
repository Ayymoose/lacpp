#include "Keyboard.h"
#include <iostream>
#include <assert.h>

using namespace Zelda;

Keyboard::Keyboard()
{
    for (int i = 0; i < SDL_NUM_SCANCODES; i++)
    {
        m_keyStatePushed[i] = false;
    }
}

// Updates the internal key state every frame
void Keyboard::updateKeyStates(int key, bool pushed) noexcept
{
    assert(key > SDL_SCANCODE_UNKNOWN && key < SDL_NUM_SCANCODES);
    m_keyStatePushed[key] = pushed;
}

bool Keyboard::keyPushed(int key) const noexcept
{
    assert(key > SDL_SCANCODE_UNKNOWN && key < SDL_NUM_SCANCODES);
    if (m_keyStatePushed[key])
    {
        std::cout << key << " was pushed\n";
    }
    return m_keyStatePushed[key];
}

int Zelda::Keyboard::operator[](int key) noexcept
{
    assert(key > SDL_SCANCODE_UNKNOWN && key < SDL_NUM_SCANCODES);
    return m_keyStatePushed[key];
}
