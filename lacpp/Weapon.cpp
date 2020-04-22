#include "Weapon.h"

Weapon::Weapon(WEAPON weapon)
{
    m_weapon = weapon;
}

void Weapon::render(SDL_Renderer* pRenderer)
{
    SDL_RenderCopy(pRenderer, m_texture, nullptr, nullptr);
}
