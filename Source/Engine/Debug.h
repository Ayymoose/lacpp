#pragma once

#include <iostream>
#include <string>
#include "Singleton.h"

// Debug output for logging

namespace Zelda
{

enum DebugMask
{
    DBG_ERROR = 0x1,
    DBG_INFO = 0x2,
    DBG_TEST = 0x4
    // Add more tests here
};

#define DEBUG(MASK, MESSAGE) do { Zelda::Debug::getInstance().log(MASK, MESSAGE); } while (0);

class Debug : public Singleton<Debug>
{
    friend class Singleton<Debug>;
public:
    void log(DebugMask mask, const std::string& message) const noexcept
    {
        if (!(m_currentMask & mask))
        {
            std::cout << message << std::endl;
        }
    }
    void setDebugMask(uint32_t mask) noexcept
    {
        std::cout << "Setting mask to: " << mask << std::endl;
        m_currentMask = mask;
    }

    uint32_t getDebugMask() const noexcept
    {
        return m_currentMask;
    }

private:
    Debug() : m_currentMask(0)
    {
    }
    uint32_t m_currentMask;
};

}