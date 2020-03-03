#include "Inventory.h"
#include "Resource.h"
#include "InputControl.h"
#include "Renderer.h"
#include "Depth.h"

Inventory::Inventory()
{
    m_texture = ResourceManager::getInstance()[RSC_INVENTORY];
    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
    m_open = false;
    Renderer::getInstance().addRenderable(this);
    m_depth = INVENTORY_DEPTH;
}

void Inventory::control()
{

    m_keyboardState = SDL_GetKeyboardState(nullptr);

    if (m_keyboardState[BUTTON_SELECT])
    {
        m_open = false;
    }

}

void Inventory::render(SDL_Renderer* pRenderer)
{
    // if inventory closed
    // render top 16 pixels at bottom of screen
    // else
    // render full screen

    int renderX = 0;
    int renderY = 0;

    if (m_open)
    {
        renderY = 0;
    }
    else
    {
        renderY = 128;
    }

    SDL_Rect srcRect = { 0, 0, m_width , m_height };
    SDL_Rect dstRect = { renderX, renderY, m_width , m_height };

    SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, 0, nullptr,SDL_FLIP_NONE);
}

void Inventory::open()
{
    m_open = true;
}

void Inventory::close()
{
    m_open = false;
}
