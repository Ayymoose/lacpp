#ifndef  BOW_H
#define BOW_H

#include "Weapon.h"
#include <iostream>

class Bow : public Weapon
{
public:
    Bow();
    ~Bow() = default;

    void render(SDL_Renderer* pRenderer) override;
    void useWeapon() override;

private:
    Vec2<float> m_dirVec;
    int m_speed;

};

#endif // ! BOW_H
