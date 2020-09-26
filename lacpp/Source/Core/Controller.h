#pragma once

#include "Singleton.h"
#include "Controllable.h"
#include <stack>

class Controller : public Singleton<Controller>
{
    friend class Singleton<Controller>;

public:
    void setController(Controllable* controller) noexcept
    {
        m_controller = controller;
        if (controller)
        {
            std::cout << "Controller is now " << m_controller->name() << '\n';
        }
        else
        {
            std::cout << "No one has control\n";
        }
    }

    void pushController(Controllable *parent, Controllable* child) noexcept
    {
        m_controller = child;
        std::cout << "Controller is now " << m_controller->name() << '\n';
        m_stack.push(parent);
    }

    void popController()
    {
        m_controller = m_stack.top();
        std::cout << "Controller is now " << m_controller->name() << '\n';
        m_stack.pop();
    }

    Controllable* getController() const noexcept
    {
        return m_controller;
    }

private:
    Controller() : m_controller(nullptr)
    {

    }
    Controllable* m_controller;
    std::stack<Controllable*> m_stack;
};