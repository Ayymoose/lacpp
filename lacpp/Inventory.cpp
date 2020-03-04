#include "Inventory.h"
#include "Resource.h"
#include "InputControl.h"
#include "Renderer.h"
#include "Depth.h"
#include "Camera.h"

Inventory::Inventory()
{
    m_texture = ResourceManager::getInstance()[RSC_INVENTORY];
    m_selector = ResourceManager::getInstance()[RSC_INVENTORY_SELECTOR];
    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
    m_open = false;
    Renderer::getInstance().addRenderable(this);
    m_depth = INVENTORY_DEPTH;

    // Initial top left position
    m_selector_x = SELECTOR_INITIAL_X;
    m_selector_y = SELECTOR_INITIAL_Y;
    SDL_QueryTexture(m_selector, nullptr, nullptr, &m_selector_width, &m_selector_height);


    m_selector_index = 0;

    // 7 -> 39 x increases of 32
    // 27 -> 50 y increases by 23
    m_singleUpDown = true;
    m_singleLeftRight = true;

    m_flashSelector = false;

    for (int i = 0; i < MAX_WEAPONS; i++)
    {
        m_items[i] = WPN_NONE;
    }
}

void Inventory::control()
{

    m_keyboardState = SDL_GetKeyboardState(nullptr);

   // if (m_keyboardState[BUTTON_SELECT])
    {
        // TODO:
        // m_open = false;
        // Give control back to player?
        // Pressing select opens and close too quickly?
    }

    // How we index the inventory
    // 0 1
    // 2 3
    // 4 5
    // 6 7
    // 8 9

    if (m_keyboardState[BUTTON_RIGHT] && m_singleLeftRight)
    {
        if (m_selector_x == SELECTOR_INITIAL_X + SELECTOR_INCREASE_X)
        {
            m_selector_x = SELECTOR_INITIAL_X;
            // If not the bottom right of the inventory
            if (m_selector_y != SELECTOR_INITIAL_Y + 4*SELECTOR_INCREASE_Y)
            {
                m_selector_y += SELECTOR_INCREASE_Y;
                m_selector_index++;
            }
            else
            {
                m_selector_y = SELECTOR_INITIAL_Y;
                m_selector_index = 0;
            }
        }
        else
        {
            m_selector_x += SELECTOR_INCREASE_X;
            m_selector_index++;
        }
        m_singleLeftRight = false;
    }
    if (m_keyboardState[BUTTON_LEFT] && m_singleLeftRight)
    {
        if (m_selector_x == SELECTOR_INITIAL_X)
        {
            m_selector_x = SELECTOR_INITIAL_X + SELECTOR_INCREASE_X;
            // If not the top left of the inventory
            if (m_selector_y != SELECTOR_INITIAL_Y)
            {
                m_selector_y -= SELECTOR_INCREASE_Y;
                m_selector_index--;
            }
            else
            {
                m_selector_y = SELECTOR_INITIAL_Y + 4 * SELECTOR_INCREASE_Y;
                m_selector_index = MAX_WEAPONS - 1;
            }
        }
        else
        {
            m_selector_x -= SELECTOR_INCREASE_X;
            m_selector_index--;
        }
        m_singleLeftRight = false;
    }
    if (m_keyboardState[BUTTON_UP] && m_singleUpDown)
    {
        if (m_selector_y == SELECTOR_INITIAL_Y)
        {
            if (m_selector_x == SELECTOR_INITIAL_X)
            {
                m_selector_x += SELECTOR_INCREASE_X;
            }
            m_selector_y = SELECTOR_INITIAL_Y + 4 * SELECTOR_INCREASE_Y;
            m_selector_index = MAX_WEAPONS - 1;
        }
        else
        {
            m_selector_index -= 2;
            m_selector_y -= SELECTOR_INCREASE_Y;
        }
        m_singleUpDown = false;

    }
    if (m_keyboardState[BUTTON_DOWN] && m_singleUpDown)
    {
        if (m_selector_y == SELECTOR_INITIAL_Y + 4 * SELECTOR_INCREASE_Y)
        {
            if (m_selector_x == SELECTOR_INITIAL_X + SELECTOR_INCREASE_X)
            {
                m_selector_x -= SELECTOR_INCREASE_X;
            }
            m_selector_index = 0;
            m_selector_y = SELECTOR_INITIAL_Y;
        }
        else
        {
            m_selector_y += SELECTOR_INCREASE_Y;
            // Change by 2 because of the way we index the array (see above)
            m_selector_index += 2;
        }

        m_singleUpDown = false;

    }
    SDL_PumpEvents();

    assert(m_selector_index >= 0 && m_selector_index < MAX_WEAPONS);

    // If any select keys pressed, reset the flashing animation
    if (IS_MOVING(m_keyboardState))
    {
        m_flashSelector = true;
        m_selectorTimer.reset();
    }

    if (IS_MOVING_KEY_RELEASED(m_keyboardState))
    {
        m_singleUpDown = true;
        m_singleLeftRight = true;
    }
}

void Inventory::render(SDL_Renderer* pRenderer)
{
    // if inventory closed
    // render top 16 pixels at bottom of screen
    // else
    // render full screen

    int renderY = 0;

    if (m_open)
    {
        renderY = 0;
    }
    else
    {
        renderY = CAMERA_HEIGHT;
    }

    // Render the inventory background
    SDL_Rect dstRect = { 0, renderY, m_width , m_height };
    SDL_RenderCopyEx(pRenderer, m_texture, nullptr, &dstRect, 0, nullptr,SDL_FLIP_NONE);

    // If the inventory is open

    if (m_open)
    {
        // Render the selector
        // Selector animation
        if (!m_flashSelector && m_selectorTimer.update(INVENTORY_SELECTOR_FPS))
        {
            m_flashSelector = true;
        }
        else
        {
            if (m_selectorTimer.update(INVENTORY_SELECTOR_FPS))
            {
                m_flashSelector = false;
            }
        }

        if (m_flashSelector)
        {
            dstRect = { m_selector_x, m_selector_y, m_selector_width , m_selector_height };
            SDL_RenderCopyEx(pRenderer, m_selector, nullptr, &dstRect, 0, nullptr, SDL_FLIP_NONE);
        }
    }
    
}

void Inventory::open()
{
    m_open = true;
}

void Inventory::close()
{
    m_open = false;
}
