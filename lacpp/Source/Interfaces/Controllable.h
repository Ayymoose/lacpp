#pragma once

#include <iostream>
#include <cassert>

// Allows an object to receive control depending on whether it is the controller or not

class Controllable
{
public:
    virtual ~Controllable()
    {
        std::cout << "Controllable deconstructor called" << std::endl;
    }
    virtual void control() noexcept = 0;
    std::string name() const noexcept
    {
        assert(!m_controllableName.empty());
        return m_controllableName;
    }
protected:
    std::string m_controllableName;
};