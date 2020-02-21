#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "Singleton.h"
#include "Controllable.h"

class Controller : public Singleton<Controller>
{
    friend class Singleton<Controller>;

public:
    void setController(Controllable* controller)
    {
        m_pController = controller;
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
};

#endif // !MAIN_CONTROLLER_H
