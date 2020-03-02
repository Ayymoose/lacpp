#include "Inventory.h"
#include "Resource.h"
#include "InputControl.h"

Inventory::Inventory()
{
    m_texture = ResourceManager::getInstance()[RSC_INVENTORY];
    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
}

Inventory::~Inventory()
{

}

void Inventory::control()
{

    m_keyboardState = SDL_GetKeyboardState(nullptr);



}

void Inventory::render(SDL_Renderer* pRenderer)
{
    SDL_RenderCopy(pRenderer, m_texture, nullptr, nullptr);
}

void Inventory::open()
{
    m_texture = ResourceManager::getInstance()[RSC_INVENTORY];
}

void Inventory::close()
{
    m_texture = nullptr;
}
