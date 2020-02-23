#ifndef INVENTORY_H
#define INVENTORY_H

#include "Renderable.h"
#include "Controllable.h"

class Inventory : public Controllable, public Renderable
{
public:
    Inventory();
    ~Inventory();

private:

};

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

#endif // !INVENTORY_H
