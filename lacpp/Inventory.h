#ifndef INVENTORY_H
#define INVENTORY_H

#include "Controllable.h"
#include "Renderable.h"

#define SELECTOR_INITIAL_X 6
#define SELECTOR_INITIAL_Y 26
#define SELECTOR_INCREASE_X 32
#define SELECTOR_INCREASE_Y 23

#define MAX_WEAPONS 10

enum Weapon
{
    WPN_NONE = -1,
    WPN_SWORD_1 = 0,
    WPN_SWORD_2,
    WPN_SHIELD_1,
    WPN_SHIELD_2,
    WPN_BOW,
    WPN_BOOMERANG,
    WPN_MAGIC_POWDER,
    WPN_BOMBS,
    WPN_POWER_BRACELET_1,
    WPN_POWER_BRACELET_2,
    WPN_ROC_FEATHER,
    WPN_HOOKSHOT,
    WPN_OCARINA,
    WPN_PEGASUS_BOOT,
    WPN_COUNT
};

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
    // The flashing selector you see in the inventory
    SDL_Texture* m_selector;
    int m_selector_width;
    int m_selector_height;
    int m_selector_x;
    int m_selector_y;
    int m_selector_index;
    UpdateTimer m_selectorTimer;
    Weapon m_items[MAX_WEAPONS];
    bool m_singleLeftRight;
    bool m_singleUpDown;


    bool m_flashSelector;
};



#endif // !INVENTORY_H
