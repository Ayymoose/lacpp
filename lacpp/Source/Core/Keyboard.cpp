#include "Keyboard.h"
#include <iostream>
#include <assert.h>

using namespace Zelda;

Keyboard::Keyboard()
{
    for (int i = 0; i < SDL_NUM_SCANCODES; i++)
    {
        m_keyStatePushed[i] = false;
        m_keyStateReleased[i] = false;
        m_keyStatePressed[i] = false;
        m_keyStatePressedRecord[i] = false;
    }
}

// Updates the internal key state every frame
void Keyboard::updateKeyStates(int key, bool pushed, bool released) noexcept
{
    assert(key > SDL_SCANCODE_UNKNOWN && key < SDL_NUM_SCANCODES);
    m_keyStatePushed[key] = pushed;
    m_keyStateReleased[key] = released;

    // If a key is pressed (true), record it pressed on this round and return true
    if (pushed && m_keyStatePressedRecord[key] == false)
    {
        m_keyStatePressed[key] = true;
        m_keyStatePressedRecord[key] = true;
    }
    else if (released)
    {
        // Only when released can it be pressed again
        m_keyStatePressedRecord[key] = false;
        m_keyStatePressed[key] = false;
    }
}

bool Keyboard::keyPushed(int key) const noexcept
{
    assert(key > SDL_SCANCODE_UNKNOWN && key < SDL_NUM_SCANCODES);
    return m_keyStatePushed[key];
}

bool Zelda::Keyboard::keyPressed(int key) noexcept
{
    assert(key > SDL_SCANCODE_UNKNOWN && key < SDL_NUM_SCANCODES);
    // Next round, if the key we recorded pressed was still pressed, return false until it is released
    // When it gets released, clear both states 

    // If it's true now, return true then make it false
    if (m_keyStatePressed[key])
    {
        std::cout << key << " was pressed\n";
        m_keyStatePressed[key] = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool Zelda::Keyboard::keyReleased(int key) noexcept
{
    assert(key > SDL_SCANCODE_UNKNOWN && key < SDL_NUM_SCANCODES);
    if (m_keyStateReleased[key])
    {
        std::cout << key << " was released\n";
        m_keyStateReleased[key] = false;
        return true;
    }
    return m_keyStateReleased[key];
}

int Zelda::Keyboard::operator[](int key) noexcept
{
    assert(key > SDL_SCANCODE_UNKNOWN && key < SDL_NUM_SCANCODES);
    return m_keyStatePushed[key];
}