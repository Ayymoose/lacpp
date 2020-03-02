#ifndef INVENTORY_H
#define INVENTORY_H

#include "Controllable.h"
#include "Renderable.h"

class Inventory : public Controllable, public Renderable
{
public:
    Inventory();
    ~Inventory();
    void control() override;
    void render(SDL_Renderer* pRenderer) override;
    void open();
    void close();
private:

};



#endif // !INVENTORY_H
