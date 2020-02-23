#ifndef INVENTORY_H
#define INVENTORY_H

#include "Controllable.h"
#include "Renderable.h"

class Inventory : public Controllable, public Renderable
{
public:
    Inventory();
    ~Inventory();
    void control(const SDL_Event& event);
    void render(SDL_Renderer* pRenderer);
    void open();
    void close();
private:

};



#endif // !INVENTORY_H
