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

        // Clear stack
        auto emptyStack = std::stack<Controllable*>();
        m_stack.swap(emptyStack);
    }

    void pushController(Controllable* controller) noexcept
    {
        // TODO: There must be an existing controller in place
        //assert(m_controller && "No existing controller in place");
        assert(controller);
        std::cout << "Controller is now " << controller->name() << '\n';
        m_stack.push(controller);
    }

    void popController()
    {
        assert(!m_stack.empty());
        m_stack.pop();
        if (!m_stack.empty())
        {
            std::cout << "Controller is now " << m_stack.top()->name() << '\n';
        }
        else
        {
            std::cout << "No one has control\n";
        }
    }

    Controllable* getController() const noexcept
    {
        if (m_stack.empty())
        {
            return m_controller;
        }
        else
        {
            return m_stack.top();
        }
    }

private:
    Controller() : m_controller(nullptr)
    {

    }
    Controllable* m_controller;
    std::stack<Controllable*> m_stack;
};