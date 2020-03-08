#include "Inventory.h"
#include "Resource.h"
#include "InputControl.h"
#include "Renderer.h"
#include "Depth.h"
#include "Camera.h"
#include "Drawing.h"

Inventory::Inventory()
{
    // m_texture is the main texture we draw ontoas
    m_texture = SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, INVENTORY_WIDTH, INVENTORY_HEIGHT);

    // Inventory divider
    SDL_Rect srcRect = m_inventorySpritesSrc[INVENTORY_DIVIDER_H];
    m_inventoryDividerH = SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, INVENTORY_DIVIDER_WIDTH_H, INVENTORY_DIVIDER_HEIGHT_H);
    CopyToTexture(Renderer::getInstance().getRenderer(), ResourceManager::getInstance()[RSC_INVENTORY], m_inventoryDividerH, &srcRect, nullptr);
    srcRect = m_inventorySpritesSrc[INVENTORY_DIVIDER_V];
    m_inventoryDividerV = SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, INVENTORY_DIVIDER_WIDTH_V, INVENTORY_DIVIDER_HEIGHT_V);
    CopyToTexture(Renderer::getInstance().getRenderer(), ResourceManager::getInstance()[RSC_INVENTORY], m_inventoryDividerV, &srcRect, nullptr);
    //

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
    m_open = false;
    Renderer::getInstance().addRenderable(this);
    m_depth = INVENTORY_DEPTH;

    // Initial top left position
    m_selector_x = SELECTOR_INITIAL_X;
    m_selector_y = SELECTOR_INITIAL_Y;

    m_arrows = 0;
    m_bombs = 0;
    m_magicPowder = 0;

    m_selector_index = 0;

    // 7 -> 39 x increases of 32
    // 27 -> 50 y increases by 23
    m_singleUpDown = true;
    m_singleLeftRight = true;

    m_flashSelector = false;

    for (int i = 0; i < INVENTORY_MAX_WEAPONS; i++)
    {
        m_items[i] = WPN_NONE;
    }

    m_singlePressA = true;
    m_singlePressB = true;
    m_weaponA = WPN_FLAME_ROD;
    m_weaponB = WPN_SWORD;

    m_ocarinaSong = SNG_FISH;

    m_swordLevel = WPN_LEVEL_1;
    m_shieldLevel = WPN_LEVEL_2;
    m_braceletLevel = WPN_LEVEL_1;

    m_items[0] = WPN_NONE;
    m_items[1] = WPN_BOW;
    m_items[2] = WPN_SHIELD;
    m_items[3] = WPN_BOOMERANG;
    m_items[4] = WPN_MAGIC_POWDER;
    m_items[5] = WPN_NONE;
    m_items[6] = WPN_POWER_BRACELET_2;
    m_items[7] = WPN_ROC_FEATHER;
    m_items[8] = WPN_HOOKSHOT;
    m_items[9] = WPN_OCARINA;
}

void Inventory::control()
{

    m_keyboardState = SDL_GetKeyboardState(nullptr);

    if (m_keyboardState[BUTTON_A] && m_singlePressA)
    {
        std::swap(m_weaponA, m_items[m_selector_index]);
        m_singlePressA = false;
    }
    if (m_keyboardState[BUTTON_B] && m_singlePressB)
    {
        std::swap(m_weaponB, m_items[m_selector_index]);
        m_singlePressB = false;
    }

    // How we index the inventory
    // 0 1
    // 2 3
    // 4 5
    // 6 7
    // 8 9

    // This code controls the selector through arrow keys
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
                m_selector_index = INVENTORY_MAX_WEAPONS - 1;
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
            m_selector_index = INVENTORY_MAX_WEAPONS - 1;
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

    assert(m_selector_index < INVENTORY_MAX_WEAPONS);

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

    if (IS_BUTTON_A_RELEASED(m_keyboardState))
    {
        m_singlePressA = true;
    }
    if (IS_BUTTON_B_RELEASED(m_keyboardState))
    {
        m_singlePressB = true;
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
    SDL_RenderCopy(pRenderer, m_texture, nullptr, &dstRect);

    // If the inventory is open

    if (m_open)
    {
        ColourTexture(Renderer::getInstance().getRenderer(), m_texture, nullptr, SDL_RGB(INVENTORY_R, INVENTORY_G, INVENTORY_B));
        drawInventoryDividers(pRenderer);
        drawTopHUD(pRenderer);
        drawInventoryItems(pRenderer);
        drawSelector(pRenderer);

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

void Inventory::drawInventoryItems(SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect, dstRect;

    // Instead of creating an object for each item we have
    // We just render the items we have to a single texture
    // and render that instead

    SDL_SetRenderTarget(pRenderer, m_texture);

    for (int i = 0; i < INVENTORY_MAX_WEAPONS; i++)
    {
        if (m_items[i] != WPN_NONE)
        {
            // Any item we have, add it to the texture at the right position
            // srcRect is the position on the spritesheet of the item
            srcRect = m_inventorySpritesSrc[m_items[i]];

            // dstRect is the position on the internal inventory lhs
            // This correctly positions the item
            dstRect =
            {
                INVENTORY_POS_X + ((((i & 1) == 1) ? 1 : 0) * INVENTORY_X_SPACING),
                INVENTORY_POS_Y + ((i / 2) * INVENTORY_Y_SPACING),
                INVENTORY_SPRITE_WIDTH,
                INVENTORY_SPRITE_HEIGHT
            };
            // Draw the inventory items onto the internal inventory
            SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect);
        }
    }

    SDL_SetRenderTarget(pRenderer, nullptr);

    for (int i = 0; i < INVENTORY_MAX_WEAPONS; i++)
    {
        if (m_items[i] != WPN_NONE)
        {
            dstRect =
            {
                WPN_LEVEL_X + ((((i & 1) == 1) ? 1 : 0) * WPN_LEVEL_SPACING_X),
                WPN_LEVEL_Y + ((i / 2) * WPN_LEVEL_SPACING_Y),
                WPN_LEVEL_WIDTH,
                WPN_LEVEL_HEIGHT
            };

            drawWeaponLevel(pRenderer, m_texture, m_items[i], &dstRect);
        }
    }
  

}

void Inventory::drawSelector(SDL_Renderer* pRenderer)
{
    SDL_SetRenderTarget(pRenderer, m_texture);

    SDL_Rect srcRect, dstRect;
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
        srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_1];
        dstRect = { m_selector_x, m_selector_y, srcRect.w , srcRect.h };
        SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect);
    }

    SDL_SetRenderTarget(pRenderer, nullptr);

}

void Inventory::drawInventoryDividers(SDL_Renderer* pRenderer)
{
    SDL_Rect dstRect;
    SDL_SetRenderTarget(pRenderer, m_texture);

    // Draw horizontal divider
    for (int i = 0; i < (INVENTORY_WIDTH / INVENTORY_DIVIDER_WIDTH_H)-2; i++)
    {
        dstRect = 
        {
            INVENTORY_DIVIDER_XH + i + INVENTORY_DIVIDER_WIDTH_H * i,
            INVENTORY_DIVIDER_YH,
            INVENTORY_DIVIDER_WIDTH_H,
            INVENTORY_DIVIDER_HEIGHT_H
        };
        SDL_RenderCopy(pRenderer, m_inventoryDividerH, nullptr, &dstRect);
    }

    // Draw vertical divider
    for (int i = 0; i < ((INVENTORY_HEIGHT - INVENTORY_DIVIDER_YV) / INVENTORY_DIVIDER_WIDTH_V); i++)
    {
        dstRect =
        {
            INVENTORY_DIVIDER_XV ,
            INVENTORY_DIVIDER_YV + i + INVENTORY_DIVIDER_HEIGHT_V * i,
            INVENTORY_DIVIDER_WIDTH_V,
            INVENTORY_DIVIDER_HEIGHT_V
        };
        SDL_RenderCopy(pRenderer, m_inventoryDividerV, nullptr, &dstRect);
    }
    SDL_SetRenderTarget(pRenderer, nullptr);
}

void Inventory::drawTopHUD(SDL_Renderer* pRenderer)
{
    SDL_SetRenderTarget(pRenderer, m_texture);

    SDL_Rect srcRect, dstRect;

    // Copy "B" 
    srcRect = m_inventorySpritesSrc[INVENTORY_B_BUTTON];
    dstRect = m_inventorySpritesDst[INVENTORY_B_BUTTON];
    SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect);

    // Copy "A"
    srcRect = m_inventorySpritesSrc[INVENTORY_A_BUTTON];
    dstRect = m_inventorySpritesDst[INVENTORY_A_BUTTON];
    SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect);

    // Copy selector
    srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_1];
    dstRect = m_inventorySpritesDst[INVENTORY_SELECTOR_BUTTON_1];
    SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect);

    srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_2];
    dstRect = m_inventorySpritesDst[INVENTORY_SELECTOR_BUTTON_2];
    SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect);

    // Ruppee icon
    srcRect = m_inventorySpritesSrc[INVENTORY_RUPPEE];
    dstRect = m_inventorySpritesDst[INVENTORY_RUPPEE];
    SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect);

    // Draw current ruppees
    dstRect = {80,9,8,8};
    drawNumber(pRenderer, m_texture, false, true, 2, 10, &dstRect);

    // Draw health

    // Draw weapon A
    if (m_weaponA != WPN_NONE)
    {
        srcRect = m_inventorySpritesSrc[m_weaponA];
        dstRect = {48,0, srcRect.w, srcRect.h };
        SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect);
        dstRect = { 56,8, 8, 8 };
        drawWeaponLevel(pRenderer, m_texture, m_weaponA, &dstRect);

    }

    // Draw weapon B
    if (m_weaponB != WPN_NONE)
    {
        srcRect = m_inventorySpritesSrc[m_weaponB];
        dstRect = { 8,0, srcRect.w, srcRect.h };
        SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect);
        dstRect = { 16,8, 8, 8 };
        drawWeaponLevel(pRenderer, m_texture, m_weaponB, &dstRect);
    }

    SDL_SetRenderTarget(pRenderer, nullptr);
}

// Draw a number or level onto a texture
// examples
// 2
// L-1 L-2
// 09
// 320

void Inventory::drawNumber(SDL_Renderer* pRenderer, SDL_Texture* srcTexture, bool drawLevel, bool useNormalFont, uint8_t trailingDigits, uint16_t number, SDL_Rect* dstRect)
{
    // drawLevel      = Draw the "L-" text next to the number
    // useNormalFont  = Use the normal digit text or text with black background
    // trailingDigits = Number of trailing digits to append to the LHS of the number (e.g 1 01 001)

    SDL_SetRenderTarget(pRenderer, srcTexture);

    SDL_Rect srcRect;

    // Draw level
    if (drawLevel)
    {
        // Draw the "L-"
        srcRect = m_inventorySpritesSrc[INVENTORY_LEVEL];
        SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, dstRect);

        if (useNormalFont)
        {
            srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_W];
        }
        else
        {
            srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_B];
        }

        srcRect.x += 2 * number + srcRect.w * number;
        dstRect->x += srcRect.w;
        SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, dstRect);
    }
    else
    {
        // Reverse the number otherwise it will come out backwards
        int reversedNumber = 0;
        int remainder = 0;
        int trailingZeros = 0;
        int trailNumber = number;

        // Count the number of trailing zeros
        // If we reverse 100, we'll get 1 not 001
        while (trailNumber != 0)
        {
            if (trailNumber % 10 == 0)
            {
                trailingZeros++;
                trailNumber /= 10;
            }
            else
            {
                break;
            }
        }
       
        // Get the number length while calculating the reverse
        int numberLength = 0;
        while (number != 0)
        {
            remainder = number % 10;
            reversedNumber = reversedNumber * 10 + remainder;
            number /= 10;
            numberLength++;
        } 
        number = reversedNumber;

        if (useNormalFont)
        {
            srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_W];
        }
        else
        {
            srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_B];
        }

        // Add any trailing digits if needed in front of the number
        for (int i = 0; i < (number == 0 ? trailingDigits : trailingDigits+1 - numberLength); i++)
        {
            SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, dstRect);
            dstRect->x += srcRect.w;
        }

        // Just draw a standard number with or without trailing digits
        do
        {

            if (useNormalFont)
            {
                srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_W];
            }
            else
            {
                srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_B];
            }

            srcRect.x += 2 * (number % 10) + srcRect.w * (number % 10);
            SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, dstRect);
            dstRect->x += srcRect.w;
            number /= 10;
        } while (number != 0);

        if (useNormalFont)
        {
            srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_W];
        }
        else
        {
            srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_B];
        }

        // Draw any reversed number whose 0 was lost
        for (int i = 0; i < trailingZeros; i++)
        {
            SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, dstRect);
            dstRect->x += srcRect.w;
        }
    }
    SDL_SetRenderTarget(pRenderer, nullptr);
}

void Inventory::drawWeaponLevel(SDL_Renderer* pRenderer, SDL_Texture* srcTexture, WEAPON weapon, SDL_Rect* dstRect)
{
    switch (weapon)
    {
    case WPN_SHIELD:
        drawNumber(pRenderer, srcTexture, true, true, 0, m_shieldLevel, dstRect);
        break;
    case WPN_SWORD:
        drawNumber(pRenderer, srcTexture, true, true, 0, m_swordLevel, dstRect);
        break;
    case WPN_POWER_BRACELET_1:
    case WPN_POWER_BRACELET_2:
        drawNumber(pRenderer, srcTexture, true, true, 0, m_braceletLevel, dstRect);
        break;
    case WPN_BOMBS:
        drawNumber(pRenderer, srcTexture, false, true, 1, m_bombs, dstRect);
        break;
    case WPN_BOW:
        drawNumber(pRenderer, srcTexture, false, true, 1, m_arrows, dstRect);
        break;
    case WPN_MAGIC_POWDER:
        drawNumber(pRenderer, srcTexture, false, true, 1, m_magicPowder, dstRect);
        break;
    case WPN_OCARINA:
        drawNumber(pRenderer, srcTexture, false, true, 0, m_ocarinaSong, dstRect);
        break;
    case WPN_BOOMERANG:
    case WPN_ROC_FEATHER:
    case WPN_HOOKSHOT:
    case WPN_PEGASUS_BOOT:
    case WPN_SHOVEL:
    case WPN_FLAME_ROD:
        break;
    }
}
