#ifndef INVENTORY_H
#define INVENTORY_H

#include "Controllable.h"
#include "Renderable.h"

class Inventory : public Controllable, public Renderable
{
public:
    Inventory();
    ~Inventory() = default;
    void control() override;
    void render(SDL_Renderer* pRenderer) override;
    void open();
    void close();
private:
    bool m_open;
};



#endif // !INVENTORY_H
