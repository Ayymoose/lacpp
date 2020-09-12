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
    virtual void control()
    {
        assert(false && "Controllable control() called");
    }
};