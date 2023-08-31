#pragma once

namespace Zelda
{
    class Toggle
    {
    public:
        Toggle(int toggleAfterTicks);

        operator bool();

        void reset();

    private:
        int m_currentTick;
        int m_endTick;
        bool m_toggle;

    };

}