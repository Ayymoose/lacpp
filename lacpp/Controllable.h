#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H

#include <SDL_image.h>
#include <iostream>

// Allows an object to receive control depending on whether it is the controller or not

class Controllable
{
public:
    virtual ~Controllable()
    {
        std::cout << "Controllable deconstructor called" << std::endl;
    }
    virtual void control(const SDL_Event& event)
    {
        std::cout << "Controllable control() called" << std::endl;
    }
    Controllable()
    {
        std::cout << "Controllable constructor called" << std::endl;
    }
};

#endif