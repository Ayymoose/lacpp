#pragma once

#include "Singleton.h"
#include "Keys.h"

#include <SDL_events.h>
#include <array>

namespace zelda::engine
{

class Keyboard : public Singleton<Keyboard>
{
public:
    void eventHandler(SDL_Event event);

    [[nodiscard]] bool keyPushed(Key key) const;
    [[nodiscard]] bool keyPressed(Key key);
    [[nodiscard]] bool keyReleased(Key key);

    void clearStates();

private:
    template <bool Pushed, bool Released>
    void updateKeyStates(Key key);

    struct KeyState
    {
        bool pushed = false;   // held down this frame
        bool pressed = false;  // single-fire: true for one query after first press
        bool record = false;   // latch: prevents pressed re-triggering while held
        bool released = false; // true for one query after key-up
    };

    static constexpr int NUM_KEYS = 512; // SDL_NUM_SCANCODES
    std::array<KeyState, NUM_KEYS> m_keys{};
};

} // namespace zelda::engine
