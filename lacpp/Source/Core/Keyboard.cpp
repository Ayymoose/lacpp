#include "Keyboard.h"
#include <iostream>
#include <assert.h>

Keyboard::Keyboard()
{
    for (int i = 0; i < SDL_NUM_SCANCODES; i++)
    {
        m_keyStatePushed[i] = false;
        m_keyStateReleased[i] = false;
        m_keyStatePressed[i] = false;
    }
}

void Keyboard::updateKeyStates(int key, bool pushedOrPressed, bool released)
{
    assert(key > SDL_SCANCODE_UNKNOWN && key < SDL_NUM_SCANCODES);

    // When a key is pressed
    // Record which key was pressed and set variable to true so we don't press it again
    // When that key is released then reset that variable


    m_keyStatePushed[key] = pushedOrPressed;
    m_keyStateReleased[key] = released;

}

bool Keyboard::keyPressed(int key)
{
    assert(key > SDL_SCANCODE_UNKNOWN && key < SDL_NUM_SCANCODES);

    bool pressed = false;

    // If the key was pressed and we haven't released it yet
    if (m_keyStatePushed[key] == true)
    {
        // Return true and mark it as not pressed
        if (!m_keyStatePressed[key])
        {
            m_keyStatePressed[key] = true;
            pressed = m_keyStatePressed[key];
        //    std::cout << key << " was pressed\n";
        }
    }
    return pressed;
}

bool Keyboard::keyReleased(int key)
{
    assert(key > SDL_SCANCODE_UNKNOWN && key < SDL_NUM_SCANCODES);
    bool released = false;
    // If the key was released
    if (m_keyStatePushed[key] == false)
    {
        // Return true and mark it as not released
        released = m_keyStateReleased[key];
        m_keyStateReleased[key] = false;
        m_keyStatePressed[key] = false;
       // std::cout << key << " was released\n";
    }
    return released;
}

bool Keyboard::keyPushed(int key) const
{
    assert(key > SDL_SCANCODE_UNKNOWN && key < SDL_NUM_SCANCODES);
    if (m_keyStatePushed[key])
    {
        std::cout << key << " was pushed\n";
    }
    return m_keyStatePushed[key];
}
