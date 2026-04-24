#pragma once

#include "Singleton.h"
#include "Controllable.h"
#include "Logger.h"
#include <stack>

namespace zelda::engine
{

class Controller : public Singleton<Controller>
{
public:
    Controller()
        : m_controller(nullptr)
    {
        Logger::instance().log<Logger::Mask::INFO>("Controller is no-one");
    }
    void setController(Controllable* controller)
    {
        m_controller = controller;
        if (controller)
        {
            Logger::instance().log<Logger::Mask::INFO>("Controller is now " + m_controller->name());
        }
        else
        {
            Logger::instance().log<Logger::Mask::INFO>("No one has control");
        }

        // Clear stack
        auto emptyStack = std::stack<Controllable*>();
        m_stack.swap(emptyStack);
    }

    void pushController(Controllable* controller)
    {
        // TODO: There must be an existing controller in place
        // assert(m_controller && "No existing controller in place");
        assert(controller);
        Logger::instance().log<Logger::Mask::INFO>("Controller is now " + controller->name());
        m_stack.push(controller);
    }

    void popController()
    {
        assert(!m_stack.empty());
        m_stack.pop();
        if (!m_stack.empty())
        {
            Logger::instance().log<Logger::Mask::INFO>("Controller is now " + m_stack.top()->name());
        }
        else
        {
            Logger::instance().log<Logger::Mask::INFO>("No one has control");
        }
    }

    Controllable* getController() const
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
    Controllable* m_controller;
    std::stack<Controllable*> m_stack;
};

} // namespace zelda::engine