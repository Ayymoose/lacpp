#pragma once

#include "Debug.h"

#include <string>
#include <iostream>
#include <cassert>

// Allows an object to receive control depending on whether it is the controller or not
namespace Zelda
{

    class Controllable
    {
    public:
        Controllable(const std::string& name) : m_controllableName(name)
        {
        }
        Controllable() = default;
        virtual ~Controllable() = default;

        virtual void control() = 0;
    
    
        std::string name() const
        {
            assert(!m_controllableName.empty());
            return m_controllableName;
        }
    protected:
        std::string m_controllableName;
    };

}