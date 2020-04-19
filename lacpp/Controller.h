#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "Singleton.h"
#include "Controllable.h"
#include <stack>

class Controller : public Singleton<Controller>
{
    friend class Singleton<Controller>;

public:
    void setController(Controllable* controller)
    {
        m_pController = controller;
    }

    void pushController(Controllable *parent, Controllable* child)
    {
        m_pController = child;
        m_stack.push(parent);
    }

    void popController()
    {
        m_pController = m_stack.top();
        m_stack.pop();
    }

    Controllable* getController() const
    {
        return m_pController;
    }

private:
    Controller()
    {
        m_pController = nullptr;
    }
    Controllable* m_pController;
    std::stack<Controllable*> m_stack;
};

#endif // !MAIN_CONTROLLER_H
