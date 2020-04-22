#include "Inventory.h"
#include "Resource.h"
#include "InputControl.h"
#include "Renderer.h"
#include "Depth.h"
#include "Camera.h"
#include "Drawing.h"
#include "Player.h"
#include <assert.h>

Inventory::Inventory()
{
    if (sizeof(m_inventorySpritesSrc) != sizeof(m_inventorySpritesDst))
    {
        //std::cout << sizeof(m_inventorySpritesSrc)/sizeof(SDL_Rect) << std::endl;
        //std::cout << sizeof(m_inventorySpritesDst)/ sizeof(SDL_Rect) << std::endl;
        assert(sizeof(m_inventorySpritesSrc) == sizeof(m_inventorySpritesDst));
    }

    SDL_Rect srcRect;

    // Select sub screen
    m_subscreen = SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, SELECT_SUBSCREEN_WIDTH, SELECT_SUBSCREEN_HEIGHT);
    ColourTexture(Renderer::getInstance().getRenderer(), m_subscreen, nullptr, SDL_RGB(0, 0, 0));
    assert(m_subscreen != nullptr);
    
    // m_texture is the main texture we draw ontoas
    m_texture = SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, INVENTORY_WIDTH, INVENTORY_HEIGHT);
    assert(m_texture != nullptr);

    // Inventory divider
    srcRect = m_inventorySpritesSrc[INVENTORY_DIVIDER_H];
    m_inventoryDividerH = SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, INVENTORY_DIVIDER_WIDTH_H, INVENTORY_DIVIDER_HEIGHT_H);
    assert(m_inventoryDividerH != nullptr);
    CopyToTexture(Renderer::getInstance().getRenderer(), ResourceManager::getInstance()[RSC_INVENTORY], m_inventoryDividerH, &srcRect, nullptr);
    srcRect = m_inventorySpritesSrc[INVENTORY_DIVIDER_V];
    m_inventoryDividerV = SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, INVENTORY_DIVIDER_WIDTH_V, INVENTORY_DIVIDER_HEIGHT_V);
    assert(m_inventoryDividerV != nullptr);
    CopyToTexture(Renderer::getInstance().getRenderer(), ResourceManager::getInstance()[RSC_INVENTORY], m_inventoryDividerV, &srcRect, nullptr);
    //

    assert(SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height) == 0);
    m_open = false;
    m_inDungeon = true;
    Renderer::getInstance().addRenderable(this);
    m_depth = INVENTORY_DEPTH;
    m_tradeItem = ITEM_NONE;
    m_seashells = 0;
    m_flippers = false;
    m_potion = false;
    m_tunic = TUNIC_BLUE;
    m_heartPieces = HEART_HALF;
    m_selectPressed = false;

    // Initial top left position
    m_selector_x = SELECTOR_INITIAL_X;
    m_selector_y = SELECTOR_INITIAL_Y;

    m_arrows = 10;
    m_bombs = 10;
    m_magicPowder = 10;

    m_selector_index = 0;

    // 7 -> 39 x increases of 32
    // 27 -> 50 y increases by 23
    m_singleUpDown = true;
    m_singleLeftRight = true;

    m_flashSelector = false;
    m_flashSelect = false;
    for (int i = 0; i < INVENTORY_MAX_WEAPONS; i++)
    {
        m_items[i] = WPN_NONE;
    }

    for (int i = 0; i < INSTRUMENT_COUNT; i++)
    {
        m_instruments[i] = INSTRUMENT_NONE;
    }

    m_instruments[0] = FULL_MOON_CELLO;
    m_instruments[1] = CONCH_HORN;
    m_instruments[2] = SEA_LILY_BELL;
    m_instruments[3] = SURF_HARP;
    m_instruments[4] = WIND_MARIMBA;
    m_instruments[5] = CORAL_TRIANGLE;
    m_instruments[6] = ORGAN_OF_EVENING_CALM;
    m_instruments[7] = THUNDER_DRUM;

    m_singlePressA = true;
    m_singlePressB = true;
    m_weaponA = WPN_FLAME_ROD;
    m_weaponB = WPN_SWORD;

    m_ocarinaSong = SNG_FISH;

    m_swordLevel = WPN_LEVEL_1;
    m_shieldLevel = WPN_LEVEL_2;
    m_braceletLevel = WPN_LEVEL_1;

    m_items[0] = WPN_SHOVEL;
    m_items[1] = WPN_BOW;
    m_items[2] = WPN_SHIELD;
    m_items[3] = WPN_BOOMERANG;
    m_items[4] = WPN_MAGIC_POWDER;
    m_items[5] = WPN_BOMBS;
    m_items[6] = WPN_POWER_BRACELET_2;
    m_items[7] = WPN_ROC_FEATHER;
    m_items[8] = WPN_HOOKSHOT;
    m_items[9] = WPN_OCARINA;

    m_dungeonKeys = 1;
    m_compass = true;
    m_dungeonMap = true;
    m_nightmareKey = true;
    m_owlBeak = true;
    m_flippers = true;
    m_potion = true;
    m_tradeItem = ITEM_STICK;

    m_goldleaf = 0;

    m_tailKey = true;
    m_slimeKey = true;
    m_anglerKey = true;
    m_faceKey = true;
    m_birdKey = true;

    m_dungeon = DUNGEON_TAIL_CAVE;
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

    if (m_keyboardState[BUTTON_SELECT])
    {
        m_pushSelectTimer.reset();
        m_selectPressed = true;
    }

    if (m_keyboardState[BUTTON_START])
    {
        close();
        Controller::getInstance().popController();
        Player::getInstance().updateState();
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

    if (IS_SELECT_RELEASED(m_keyboardState))
    {
        m_selectPressed = true;
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
    assert(SDL_RenderCopy(pRenderer, m_texture, nullptr, &dstRect) == 0);
    ColourTexture(pRenderer, m_texture, nullptr, SDL_RGB(INVENTORY_R, INVENTORY_G, INVENTORY_B));

    drawTopHUD(pRenderer);

    // If the inventory is open
    if (m_open)
    {
        drawInventoryDividers(pRenderer);
        drawInventoryWeapons(pRenderer);
        drawSelector(pRenderer);
        if (m_inDungeon)
        {
            drawDungeonItems(pRenderer);
        }
        else
        {
            drawInventoryItems(pRenderer);
        }
        drawMiscItems(pRenderer);
        drawSelectStatus(pRenderer);
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

WEAPON Inventory::weaponA() const
{
    return m_weaponA;
}

WEAPON Inventory::weaponB() const
{
    return m_weaponB;
}

bool Inventory::shieldEquipped() const
{
    return (m_weaponA == WPN_SHIELD || m_weaponB == WPN_SHIELD);
}

WEAPON_LEVEL Inventory::shieldLevel() const
{
    return m_shieldLevel;
}

void Inventory::drawDungeonMap(SDL_Renderer* pRenderer)
{
    assert(m_dungeon > DUNGEON_NONE && m_dungeon < DUNGEON_COUNT);

    /*
        0 - Empty (navy square)
        1 - Blank (white inventory coloured block)
        2 - Unvisited navy square
        3 - Treasure chest
        4 - Nightmare location
        5 - INVENTORY_AREA_EXIT_RIGHT
        6 - Area LEFT exit only
        7 - Area RIGHT and DOWN exit only
        8 - Area LEFT and DOWN exit only
        9 - Area no exit
        10 - Area LEFT UP and RIGHT exit only
        11 - Area LEFT RIGHT DOWN exit only
        12 - Area DOWN exit only
        13 - Area UP exit only
        14 - Area UP and RIGHT exit only
        15 - Area UP and LEFT exit only
        16 - Area all exits
        17 - Area UP RIGHT and DOWN exit only
        18 - Area UP LEFT and DOWN exit only
        19 - Area UP and DOWN exit only

    */


    // Draw current location grid arrow
    SDL_Rect srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW];
    SDL_Rect dstRect = m_inventorySpritesDst[INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW];

    switch (m_dungeon)
    {
    case DUNGEON_COLOUR_DUNGEON: break;
    case DUNGEON_TAIL_CAVE: dstRect.x = 112;  break;
    case DUNGEON_BOTTLE_GROTTO: break;
    case DUNGEON_KEY_CAVERN: break;
    case DUNGEON_ANGLER_TUNNEL: break;
    case DUNGEON_CATFISH_MAW: break;
    case DUNGEON_FACE_SHRINE: break;
    case DUNGEON_EAGLE_TOWER: break;
    case DUNGEON_TURTLE_ROCK: break;
    }

    assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);

    // Draw dungeon map level
    dstRect = {72,64,8,8};
    drawNumber(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], true, true, 0, m_dungeon, &dstRect);

    // Draw the dungeon map


    // Tail cave start position
    // Player position in dungeon map
    m_dungeonPosition.x = 3;
    m_dungeonPosition.y = 8;

    // Without a map, all the paths are not drawn
    // Unvisited areas are marked with a grey block
    for (int x = 0; x < DUNGEON_MAX_BLOCK_X; x++)
    {
        for (int y = 0; y < DUNGEON_MAX_BLOCK_Y; y++)
        {
            switch (m_dungeonMaps[m_dungeon][y][x])
            {
            case 0: // INVENTORY_AREA_EMPTY
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EMPTY];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EMPTY];
                break;
            case 1: // Inventory space
                continue;
            case 2: // INVENTORY_AREA_UNVISITED
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_UNVISITED];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_UNVISITED];
                break;
            case 3: // INVENTORY_AREA_TREASURE
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_TREASURE];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_TREASURE];
                break;
            case 4: // INVENTORY_AREA_NIGHTMARE
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_NIGHTMARE];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_NIGHTMARE];
                break;
            case 5: // INVENTORY_AREA_EXIT_RIGHT
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_RIGHT];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_RIGHT];
                break;
            case 6: // INVENTORY_AREA_EXIT_LEFT
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_LEFT];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_LEFT];
                break;
            case 7: // INVENTORY_AREA_EXIT_RIGHT_DOWN
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_RIGHT_DOWN];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_RIGHT_DOWN];
                break;
            case 8: // INVENTORY_AREA_EXIT_LEFT_DOWN
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_LEFT_DOWN];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_LEFT_DOWN];
                break;
            case 9: // INVENTORY_AREA_EXIT_NONE
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_NONE];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_NONE];
                break;
            case 10: // INVENTORY_AREA_EXIT_LEFT_UP_RIGHT
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_LEFT_UP_RIGHT];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_LEFT_UP_RIGHT];
                break;
            case 11: // INVENTORY_AREA_EXIT_LEFT_DOWN_RIGHT
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_LEFT_DOWN_RIGHT];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_LEFT_DOWN_RIGHT];
                break;
            case 12: // INVENTORY_AREA_EXIT_DOWN
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_DOWN];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_DOWN];
                break;
            case 13: // INVENTORY_AREA_EXIT_UP
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_UP];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_UP];
                break;
            case 14: // INVENTORY_AREA_EXIT_UP_RIGHT
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_UP_RIGHT];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_UP_RIGHT];
                break;
            case 15: // INVENTORY_AREA_EXIT_LEFT_UP
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_LEFT_UP];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_LEFT_UP];
                break;
            case 16: // INVENTORY_AREA_EXIT_ALL
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_ALL];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_ALL];
                break;
            case 17: // INVENTORY_AREA_EXIT_UP_RIGHT_DOWN
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_UP_RIGHT_DOWN];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_UP_RIGHT_DOWN];
                break;
            case 18: // INVENTORY_AREA_EXIT_UP_LEFT_DOWN
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_UP_LEFT_DOWN];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_UP_LEFT_DOWN];
                break;
            case 19: // INVENTORY_AREA_EXIT_UP_DOWN
                srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_UP_DOWN];
                dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_UP_DOWN];
                break;
            default:
                assert(false);
            }
            dstRect.x += x * srcRect.w;
            dstRect.y += y * srcRect.w;
            assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);

            // Draw current location flashing
            if (m_dungeonPosition.x == x && m_dungeonPosition.y == y)
            {
                srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_MAP_CURRENT_LOCATION];
                srcRect.x = srcRect.x + ((2 + srcRect.w) * m_dungeonMapPositionTimer.m_counter);
                if (m_dungeonMapPositionTimer.update(INSTRUMENT_FPS))
                {
                    if (m_dungeonMapPositionTimer.m_counter > 1)
                    {
                        m_dungeonMapPositionTimer.m_counter = 0;
                    }
                }
                assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
            }

        }
    }

}

void Inventory::drawSelectStatus(SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect, dstRect;

    if (!m_selectPressed)
    {
        // Draw two red arrows
        srcRect = m_inventorySpritesSrc[INVENTORY_RED_ARROW];
        dstRect = m_inventorySpritesDst[INVENTORY_RED_ARROW];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);

        dstRect.x += 73;
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);

        srcRect = m_inventorySpritesSrc[INVENTORY_PUSH_SELECT];
        dstRect = m_inventorySpritesDst[INVENTORY_PUSH_SELECT];

        if (!m_flashSelect && m_pushSelectTimer.update(PUSH_SELECTOR_FPS))
        {
            m_flashSelect = true;
        }
        else
        {
            if (m_pushSelectTimer.update(PUSH_SELECTOR_FPS))
            {
                m_flashSelect = false;
            }
        }

        // Draw "PUSH SELECT"
        if (m_flashSelect)
        {
            assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
        }
    }
    else
    {
        // TODO: Transition the subscreen
        dstRect = m_inventorySpritesDst[INVENTORY_SUBSCREEN];
        assert(SDL_RenderCopy(pRenderer, m_subscreen, nullptr, &dstRect) == 0);

        assert(SDL_SetRenderTarget(pRenderer, m_subscreen) == 0);


        // Tunic
        srcRect = m_inventorySpritesSrc[INVENTORY_TUNIC];
        switch (m_tunic)
        {
        case TUNIC_GREEN:
            break;
        case TUNIC_BLUE:
            srcRect.x += srcRect.w + 2;
        break;
        case TUNIC_RED:
            srcRect.x = 2 * (srcRect.w + 2);
        break;

        }
        dstRect = m_inventorySpritesDst[INVENTORY_TUNIC];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);

        // Heart pieces
        srcRect = m_inventorySpritesSrc[INVENTORY_HEART_PIECES];
        dstRect = m_inventorySpritesDst[INVENTORY_HEART_PIECES];

        switch (m_heartPieces)
        {
        case HEART_ZERO:
            break;
        case HEART_ONE_QUARTER:
            srcRect.x += srcRect.w + 2;
            break;
        case HEART_HALF:
            srcRect.x += 2 * (srcRect.w + 2);
            break;
        case HEART_THREE_QUARTER:
            srcRect.x += 3 * (srcRect.w + 2);
            break;
        case HEART_FULL:
            // Will this ever be used?
            srcRect.x += 4 * (srcRect.w + 2);
            break;
        }
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);

        // Photographs
        srcRect = m_inventorySpritesSrc[INVENTORY_PHOTOGRAPHS];
        dstRect = m_inventorySpritesDst[INVENTORY_PHOTOGRAPHS];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);

        // Inventory "/"
        srcRect = m_inventorySpritesSrc[INVENTORY_SLASH];
        dstRect = m_inventorySpritesDst[INVENTORY_SLASH];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
        dstRect.x = 64; dstRect.y = 8;
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
        
        // Draw how many heart pieces we have (out of 4)
        dstRect = {56,7,8,8};
        drawNumber(pRenderer, m_subscreen, false, false, 0, m_heartPieces, &dstRect);
        dstRect = { 72,7,8,8 };
        drawNumber(pRenderer, m_subscreen, false, false, 0, HEART_PIECES_MAX, &dstRect);

        // Draw number of photographs
        dstRect = { 24,23,8,8 };
        drawNumber(pRenderer, m_subscreen, false, false, 1, m_photographs, &dstRect);
        dstRect = { 48,23,8,8 };
        drawNumber(pRenderer, m_subscreen, false, false, 1, MAX_PHOTOGRAPHS, &dstRect);

        // Remember! This resets the drawing target to the screen
        assert(SDL_SetRenderTarget(pRenderer, nullptr) == 0);

    }

}

void Inventory::drawMiscItems(SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect, dstRect;

    if (m_flippers)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_FLIPPERS];
        dstRect = m_inventorySpritesDst[INVENTORY_FLIPPERS];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
    }

    if (m_potion)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_POTION];
        dstRect = m_inventorySpritesDst[INVENTORY_POTION];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
    }

    // Draw number of seashells
    srcRect = m_inventorySpritesSrc[INVENTORY_SEASHELLS];
    dstRect = m_inventorySpritesDst[INVENTORY_SEASHELLS];
    assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
    dstRect.w = 8; dstRect.h = 8;
    dstRect.x += dstRect.w; dstRect.y += dstRect.h;
    drawNumber(pRenderer, m_texture, false, true, 1, m_seashells, &dstRect);

    // Draw currently traded item (if any)
    if (m_tradeItem != ITEM_NONE)
    {
        srcRect = m_inventorySpritesSrc[TRADE_ITEM_SPRITE(m_tradeItem)];
        dstRect = m_inventorySpritesDst[TRADE_ITEM_SPRITE(m_tradeItem)];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
    }
}

void Inventory::drawInventoryItems(SDL_Renderer* pRenderer)
{
    // Depending on whether we are in a dungeon or not,
    // draws the inventory items or the dungeon items

    SDL_Rect srcRect, dstRect;

    // Draw any keys we have
    if (m_tailKey)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_TAIL_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_TAIL_KEY];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
    }

    if (m_slimeKey)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_SLIME_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_SLIME_KEY];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
    }

    if (m_anglerKey)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_ANGLER_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_ANGLER_KEY];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
    }
    
    if (m_faceKey)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_FACE_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_FACE_KEY];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
    }

    if (m_birdKey)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_BIRD_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_BIRD_KEY];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
    }

    drawInstruments(pRenderer);
}

void Inventory::drawDungeonItems(SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect, dstRect;

    if (m_compass)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_COMPASS];
        dstRect = m_inventorySpritesDst[INVENTORY_COMPASS];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
    }

    if (m_nightmareKey)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_NIGHTMARE_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_NIGHTMARE_KEY];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
    }

    if (m_owlBeak)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_OWL_BEAK];
        dstRect = m_inventorySpritesDst[INVENTORY_OWL_BEAK];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
    }

    if (m_dungeonMap)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_MAP];
        dstRect = m_inventorySpritesDst[INVENTORY_DUNGEON_MAP];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
    }


    // Draw the dungeon map
    drawDungeonMap(pRenderer);

    // Draw dungeon keys
    srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_KEY];
    dstRect = m_inventorySpritesDst[INVENTORY_DUNGEON_KEY];
    assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
    dstRect.w = 8; dstRect.h = 8;
    dstRect.x += dstRect.w; dstRect.y += dstRect.h;
    drawNumber(pRenderer, m_texture, false, true, 0, m_dungeonKeys, &dstRect);



}

void Inventory::drawInstruments(SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect, dstRect;

    // Instrument positions
    // 1st 120,60
    // 2nd 136,80
    // 3rd 136,104
    // 4th 120,120
    // 5th 96,120
    // 6th 80,104
    // 7th 80,80
    // 8th 96,64

    for (int i = 1; i <= INSTRUMENT_COUNT; i++)
    {
        switch (m_instruments[i - 1])
        {
        case FULL_MOON_CELLO:
        case CONCH_HORN: 
        case SEA_LILY_BELL: 
        case SURF_HARP: 
        case WIND_MARIMBA: 
        case CORAL_TRIANGLE: 
        case ORGAN_OF_EVENING_CALM: 
        case THUNDER_DRUM: 
            srcRect = m_inventorySpritesSrc[INVENTORY_INSTRUMENT_0 + (i-1)];
            dstRect = m_inventorySpritesDst[INVENTORY_INSTRUMENT_0 + (i-1)];
            srcRect.x = srcRect.x + (srcRect.w * m_instrumentTimer.m_counter);
            if (m_instrumentTimer.update(INSTRUMENT_FPS))
            {
                if (m_instrumentTimer.m_counter > INSTRUMENTS_FRAME)
                {
                    m_instrumentTimer.m_counter = 0;
                }
            }
            assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
            break;
        default:
            // If we don't have the instrument yet
            srcRect = m_inventorySpritesSrc[INVENTORY_INSTRUMENT_BACK_0];
            dstRect = m_inventorySpritesDst[INVENTORY_INSTRUMENT_BACK_0 + i - 1];
            assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
            dstRect.x += 8; dstRect.y += 8; dstRect.w = 8; dstRect.h = 8;
            drawNumber(pRenderer, m_texture, false, true, 0, i, &dstRect);
            break;
        }
    }
}

void Inventory::drawHealth(SDL_Renderer* pRenderer)
{
    float currentHealth = Player::getInstance().health();
    float healthMax =  Player::getInstance().maxHealth();

    int wholeHearts = (int)currentHealth;
    float quarterHearts = currentHealth - (int)currentHealth;
    int emptyHearts = (currentHealth - (int)currentHealth > 0 ? healthMax - std::ceil(currentHealth) : healthMax - wholeHearts);

#ifdef TEST
    assert(wholeHearts == 1);
    assert(quarterHearts == 0.75);
    assert(emptyHearts == 1);

    healthMax = 3;
    currentHealth = 0;

    wholeHearts = (int)currentHealth;
    quarterHearts = currentHealth - (int)currentHealth;
    emptyHearts = (currentHealth - (int)currentHealth > 0 ? healthMax - std::ceil(currentHealth) : healthMax - wholeHearts);

    assert(wholeHearts == 0);
    assert(quarterHearts == 0);
    assert(emptyHearts == 3);

    healthMax = 3;
    currentHealth = 3;

    wholeHearts = (int)currentHealth;
    quarterHearts = currentHealth - (int)currentHealth;
    emptyHearts = (currentHealth - (int)currentHealth > 0 ? healthMax - std::ceil(currentHealth) : healthMax - wholeHearts);

    assert(wholeHearts == 3);
    assert(quarterHearts == 0);
    assert(emptyHearts == 0);

    healthMax = 3;
    currentHealth = 0.25;

    wholeHearts = (int)currentHealth;
    quarterHearts = currentHealth - (int)currentHealth;
    emptyHearts = (currentHealth - (int)currentHealth > 0 ? healthMax - std::ceil(currentHealth) : healthMax - wholeHearts);

    assert(wholeHearts == 0);
    assert(quarterHearts == 0.25);
    assert(emptyHearts == 2);
#endif // TEST

    // draw whole hearts
    // draw quarter hear
    /// draw empty hearts

    SDL_Rect srcRect = m_inventorySpritesSrc[INVENTORY_HEART_WHOLE];
    SDL_Rect dstRect = m_inventorySpritesDst[INVENTORY_HEART_WHOLE];
    int drawnHearts = 0;

    // Draw whole hearts
    for (int i = 0; i < wholeHearts; i++)
    {
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
        dstRect.x += srcRect.w;
        drawnHearts++;
        if (drawnHearts == HEARTS_PER_ROW)
        {
            dstRect.y += srcRect.h;
            dstRect.x = m_inventorySpritesDst[INVENTORY_HEART_WHOLE].x;
        }
    }

    // Draw any quarter hearts
    if (quarterHearts == 0.25)
    {
        srcRect.x = (srcRect.w + 2) * 3;
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
        dstRect.x += srcRect.w;
        drawnHearts++;
        if (drawnHearts == HEARTS_PER_ROW)
        {
            dstRect.y += srcRect.h;
            dstRect.x = m_inventorySpritesDst[INVENTORY_HEART_WHOLE].x;
        }
    }
    else if (quarterHearts == 0.5)
    {
        srcRect.x = (srcRect.w + 2) * 2;
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
        dstRect.x += srcRect.w;
        drawnHearts++;
        if (drawnHearts == HEARTS_PER_ROW)
        {
            dstRect.y += srcRect.h;
            dstRect.x = m_inventorySpritesDst[INVENTORY_HEART_WHOLE].x;
        }
    }
    else if (quarterHearts == 0.75)
    {
        srcRect.x = (srcRect.w + 2) * 1;
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
        dstRect.x += srcRect.w;
        drawnHearts++;
        if (drawnHearts == HEARTS_PER_ROW)
        {
            dstRect.y += srcRect.h;
            dstRect.x = m_inventorySpritesDst[INVENTORY_HEART_WHOLE].x;
        }
    }

    // Draw empty hearts
    srcRect.x = (srcRect.w + 2) * 4;
    for (int i = 0; i < emptyHearts; i++)
    {
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
        dstRect.x += srcRect.w;
        drawnHearts++;
        if (drawnHearts == HEARTS_PER_ROW)
        {
            dstRect.y += srcRect.h;
            dstRect.x = m_inventorySpritesDst[INVENTORY_HEART_WHOLE].x;
        }
    }
}

void Inventory::drawInventoryWeapons(SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect, dstRect;

    // Instead of creating an object for each item we have
    // We just render the items we have to a single texture
    // and render that instead

    assert(SDL_SetRenderTarget(pRenderer, m_texture) == 0);

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
            assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
        }
    }

    assert(SDL_SetRenderTarget(pRenderer, nullptr) == 0);

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
    assert(SDL_SetRenderTarget(pRenderer, m_texture) == 0);

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
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
    }
    assert(SDL_SetRenderTarget(pRenderer, nullptr) == 0);

}

void Inventory::drawInventoryDividers(SDL_Renderer* pRenderer)
{
    SDL_Rect dstRect;
    assert(SDL_SetRenderTarget(pRenderer, m_texture) == 0);

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
        assert(SDL_RenderCopy(pRenderer, m_inventoryDividerH, nullptr, &dstRect) == 0);
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
        assert(SDL_RenderCopy(pRenderer, m_inventoryDividerV, nullptr, &dstRect) == 0);
    }
    assert(SDL_SetRenderTarget(pRenderer, nullptr) == 0);
}

void Inventory::drawTopHUD(SDL_Renderer* pRenderer)
{
    assert(SDL_SetRenderTarget(pRenderer, m_texture) == 0);

    SDL_Rect srcRect, dstRect;

    // Copy "B" 
    srcRect = m_inventorySpritesSrc[INVENTORY_B_BUTTON];
    dstRect = m_inventorySpritesDst[INVENTORY_B_BUTTON];
    assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);

    // Copy "A"
    srcRect = m_inventorySpritesSrc[INVENTORY_A_BUTTON];
    dstRect = m_inventorySpritesDst[INVENTORY_A_BUTTON];
    assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);

    // Copy selector
    srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_1];
    dstRect = m_inventorySpritesDst[INVENTORY_SELECTOR_BUTTON_1];
    assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);

    srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_2];
    dstRect = m_inventorySpritesDst[INVENTORY_SELECTOR_BUTTON_2];
    assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);

    // Ruppee icon
    srcRect = m_inventorySpritesSrc[INVENTORY_RUPPEE];
    dstRect = m_inventorySpritesDst[INVENTORY_RUPPEE];
    assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);

    // Draw health
    drawHealth(pRenderer);

    // Draw weapon A
    if (m_weaponA != WPN_NONE)
    {
        // Draw the actual weapon
        srcRect = m_inventorySpritesSrc[m_weaponA];
        dstRect = {48,0, srcRect.w, srcRect.h };
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);

        // Draw the weapon level
        dstRect = { 56,8, 8, 8 };
        drawWeaponLevel(pRenderer, m_texture, m_weaponA, &dstRect);
    }

    // Draw weapon B
    if (m_weaponB != WPN_NONE)
    {
        srcRect = m_inventorySpritesSrc[m_weaponB];
        dstRect = { 8,0, srcRect.w, srcRect.h };
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, &dstRect) == 0);
        dstRect = { 16,8, 8, 8 };
        drawWeaponLevel(pRenderer, m_texture, m_weaponB, &dstRect);
    }

    // Draw current ruppees
    dstRect = { 80,8,8,8 };
    drawNumber(pRenderer, m_texture, false, true, 2, 10, &dstRect);

    assert(SDL_SetRenderTarget(pRenderer, nullptr) == 0);
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

    //TODO: Find out why this fails
    /*assert(*/SDL_SetRenderTarget(pRenderer, srcTexture)/* == 0)*/;

    SDL_Rect srcRect;

    // Draw level
    if (drawLevel)
    {
        // Draw the "L-"
        srcRect = m_inventorySpritesSrc[INVENTORY_LEVEL];
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, dstRect) == 0);

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
        assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, dstRect) == 0);
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
            assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, dstRect) == 0);
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
            assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, dstRect) == 0);
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
            assert(SDL_RenderCopy(pRenderer, ResourceManager::getInstance()[RSC_INVENTORY], &srcRect, dstRect) == 0);
            dstRect->x += srcRect.w;
        }
    }
    assert(SDL_SetRenderTarget(pRenderer, nullptr) == 0);
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
