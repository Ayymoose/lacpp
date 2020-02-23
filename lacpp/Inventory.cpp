#include "Inventory.h"
#include "Resource.h"
#include "InputControl.h"

Inventory::Inventory()
{
    m_Texture = ResourceManager::getInstance()[RSC_INVENTORY];
    SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_width, &m_height);
}

Inventory::~Inventory()
{

}

void Inventory::control(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case BUTTON_RIGHT:
            break;
        case BUTTON_LEFT: 
            break;
        case BUTTON_DOWN: 
            open();
            break;
        case BUTTON_UP: 
            close();
            break;
        }
        break;
    }
}

void Inventory::render(SDL_Renderer* pRenderer)
{
    SDL_RenderCopy(pRenderer, m_Texture, nullptr, nullptr);
}

void Inventory::open()
{
    m_Texture = ResourceManager::getInstance()[RSC_INVENTORY];
}

void Inventory::close()
{
    m_Texture = nullptr;
}
