#include "Toggle.h"

#include <iostream>

namespace Zelda
{
    Toggle::Toggle(int toggleAfterTicks) : m_currentTick(0), m_endTick(toggleAfterTicks), m_toggle(false)
    {

    }

    void Toggle::reset()
    {
        m_currentTick = 0;
        m_toggle = false;
    }

    Toggle::operator bool()
    {
        if (m_currentTick % m_endTick == m_endTick - 1)
        {
            m_toggle = !m_toggle;
            m_currentTick = 0;
        }
        else
        {
            ++m_currentTick;
        }

        return m_toggle;
    }
}

