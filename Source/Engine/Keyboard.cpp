#include "Keyboard.h"
#include "Debug.h"
#include <iostream>
#include <cassert>

namespace Zelda
{

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

void Keyboard::eventHandler(SDL_Event event) noexcept
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
            Keyboard::getInstance().updateKeyStates(event.key.keysym.scancode, true, false);
            // If key was released in the next frame, set it to not released now
            break;
        case SDL_KEYUP:
            Keyboard::getInstance().updateKeyStates(event.key.keysym.scancode, false, true);
            // Set key released to true on this frame
            break;
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

bool Keyboard::keyPressed(int key) noexcept
{
    assert(key > SDL_SCANCODE_UNKNOWN && key < SDL_NUM_SCANCODES);
    // Next round, if the key we recorded pressed was still pressed, return false until it is released
    // When it gets released, clear both states 

    // If it's true now, return true then make it false
    if (m_keyStatePressed[key])
    {
        DEBUG(DBG_INFO, std::to_string(key) + " was pressed");
        m_keyStatePressed[key] = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool Keyboard::keyReleased(int key) noexcept
{
    assert(key > SDL_SCANCODE_UNKNOWN && key < SDL_NUM_SCANCODES);
    if (m_keyStateReleased[key])
    {
        DEBUG(DBG_INFO, std::to_string(key) + " was released");
        m_keyStateReleased[key] = false;
        return true;
    }
    return m_keyStateReleased[key];
}

int Keyboard::operator[](int key) noexcept
{
    assert(key > SDL_SCANCODE_UNKNOWN && key < SDL_NUM_SCANCODES);
    return m_keyStatePushed[key];
}

}