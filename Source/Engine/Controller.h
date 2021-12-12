#pragma once

#include "Singleton.h"
#include "Controllable.h"
#include "Debug.h"
#include <stack>

namespace Zelda
{

class Controller : public Singleton<Controller>
{
    friend class Singleton<Controller>;

public:
    void setController(Controllable* controller) noexcept
    {
        m_controller = controller;
        if (controller)
        {
            DEBUG(DBG_INFO, "Controller is now " + m_controller->name());
        }
        else
        {
            DEBUG(DBG_INFO, "No one has control");
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
        DEBUG(DBG_INFO, "Controller is now " + controller->name());
        m_stack.push(controller);
    }

    void popController()
    {
        assert(!m_stack.empty());
        m_stack.pop();
        if (!m_stack.empty())
        {
            DEBUG(DBG_INFO, "Controller is now " + m_stack.top()->name());
        }
        else
        {
            DEBUG(DBG_INFO, "No one has control");
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
        DEBUG(DBG_INFO, "Controller is no-one");
    }
    Controllable* m_controller;
    std::stack<Controllable*> m_stack;
};

}