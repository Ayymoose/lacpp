#include "Keyboard.h"

#include <cassert>
#include <utility>

namespace zelda::engine
{

void Keyboard::eventHandler(SDL_Event event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        updateKeyStates<true, false>(static_cast<Key>(event.key.keysym.scancode));
        break;
    case SDL_KEYUP:
        updateKeyStates<false, true>(static_cast<Key>(event.key.keysym.scancode));
        break;
    default:
        break;
    }
}

template <bool pushed, bool released>
void Keyboard::updateKeyStates(Key key)
{
    const auto idx = std::to_underlying(key);
    assert(idx > 0 && idx < NUM_KEYS);
    auto& state = m_keys[idx];

    if constexpr (pushed)
    {
        state.pushed = true;
        if (!state.record)
        {
            state.pressed = true;
            state.record = true;
        }
    }
    else if constexpr (released)
    {
        state.pushed = false;
        state.released = true;
        // Key must be released before pressed can fire again
        state.record = false;
        state.pressed = false;
    }
}

bool Keyboard::keyPushed(Key key) const
{
    const auto idx = std::to_underlying(key);
    assert(idx > 0 && idx < NUM_KEYS);
    return m_keys[idx].pushed;
}

bool Keyboard::keyPressed(Key key)
{
    const auto idx = std::to_underlying(key);
    assert(idx > 0 && idx < NUM_KEYS);
    auto& state = m_keys[idx];
    if (state.pressed)
    {
        state.pressed = false;
        return true;
    }
    return false;
}

bool Keyboard::keyReleased(Key key)
{
    const auto idx = std::to_underlying(key);
    assert(idx > 0 && idx < NUM_KEYS);
    auto& state = m_keys[idx];
    if (state.released)
    {
        state.released = false;
        return true;
    }
    return false;
}

void Keyboard::clearStates()
{
    m_keys = {};
}

} // namespace zelda::engine
