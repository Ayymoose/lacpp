#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H

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
    Controllable()
    {
        std::cout << "Controllable constructor called" << std::endl;
        m_keyboardState = nullptr;
    }
protected:
    const uint8_t* m_keyboardState;
};

#endif