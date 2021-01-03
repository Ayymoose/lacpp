#include "Inventory.h"
#include "Resource.h"
#include "InputControl.h"
#include "Renderer.h"
#include "Depth.h"
#include "Camera.h"
#include "Drawing.h"
#include "Link.h"
#include "ZD_Assert.h"
#include "Keyboard.h"
#include "Engine.h"
#include "Common.h"

using namespace Zelda;

Inventory::Inventory() : 
    Renderable("Inventory", SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, INVENTORY_WIDTH, INVENTORY_HEIGHT), ZD_DEPTH_INVENTORY),
    Controllable(m_name),
    m_subscreen(SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, SELECT_SUBSCREEN_WIDTH, SELECT_SUBSCREEN_HEIGHT)),
    m_tradeItem(ITEM_NONE),
    m_open(false),
    m_inDungeon(true),
    m_tailKey(true),
    m_slimeKey(true),
    m_anglerKey(true),
    m_faceKey(true),
    m_birdKey(true),
    m_arrows(60),
    m_bombs(60),
    m_magicPowder(60),
    m_swordLevel(WeaponLevel::WPN_LEVEL_1),
    m_shieldLevel(WeaponLevel::WPN_LEVEL_2),
    m_braceletLevel(WeaponLevel::WPN_LEVEL_1),
    m_ocarinaSong(OcarinaSong::SNG_FISH),
    m_seashells(0),
    m_flippers(false),
    m_potion(false),
    m_tunic(Tunic::TUNIC_BLUE),
    m_heartPieces(static_cast<int>(HeartPieces::HEART_HALF)),
    m_goldleaf(0),
    m_photographs(0),
    m_weaponA(WEAPON::WPN_BOW),
    m_weaponB(WEAPON::WPN_SWORD),
    m_selectorX(SELECTOR_INITIAL_X),
    m_selectorY(SELECTOR_INITIAL_Y),
    m_selectorIndex(0),
    m_flashSelector(false),
    m_flashSelect(false),
    m_selectPressed(false),
    m_dungeon(Dungeon::DUNGEON_TAIL_CAVE)
{
    static_assert(sizeof(m_inventorySpritesSrc) == sizeof(m_inventorySpritesDst));

    // Select sub screen
    assert(m_subscreen);
    // m_texture is the main texture we draw ontoas
    assert(m_texture);
    colourTexture(Renderer::getInstance().getRenderer(), m_subscreen, nullptr, SDL_RGB(0, 0, 0));

    // 7 -> 39 x increases of 32
    // 27 -> 50 y increases by 23

    for (int i = 0; i < INVENTORY_MAX_WEAPONS; i++)
    {
        m_items[i] = WPN_NONE;
    }

    for (int i = 0; i < static_cast<int>(Instrument::INSTRUMENT_COUNT); i++)
    {
        m_instruments[i] = Instrument::INSTRUMENT_NONE;
    }

    m_instruments[0] = Instrument::FULL_MOON_CELLO;
    m_instruments[1] = Instrument::CONCH_HORN;
    m_instruments[2] = Instrument::SEA_LILY_BELL;
    m_instruments[3] = Instrument::SURF_HARP;
    m_instruments[4] = Instrument::WIND_MARIMBA;
    m_instruments[5] = Instrument::CORAL_TRIANGLE;
    m_instruments[6] = Instrument::ORGAN_OF_EVENING_CALM;
    m_instruments[7] = Instrument::THUNDER_DRUM;

    m_items[0] = WPN_SHOVEL;
    m_items[1] = WPN_HOOKSHOT;
    m_items[2] = WPN_SHIELD;
    m_items[3] = WPN_BOMBS;
    m_items[4] = WPN_MAGIC_POWDER;
    m_items[5] = WPN_POWER_BRACELET_1;
    m_items[6] = WPN_POWER_BRACELET_2;
    m_items[7] = WPN_ROC_FEATHER;
    m_items[8] = WPN_BOOMERANG;
    m_items[9] = WPN_OCARINA;

    for (uint8_t i = 0; i < static_cast<uint8_t>(Dungeon::DUNGEON_COUNT); i++)
    {
        m_dungeonKeys[i] = 1;
        m_compass[i] = true;
        m_dungeonMap[i] = true;
        m_nightmareKey[i] = true;
        m_owlBeak[i] = true;
    }

    Renderer::getInstance().addRenderable(this);
}

void Inventory::control() noexcept
{
    if (Keyboard::getInstance().keyPressed(BUTTON_A))
    {
       std::swap(m_weaponA, m_items[m_selectorIndex]);
    }
    if (Keyboard::getInstance().keyPressed(BUTTON_B))
    {
       std::swap(m_weaponB, m_items[m_selectorIndex]);
    }

    // Show the subscreen only when the select key is pushed
    // TODO: Transition it in
    if (Keyboard::getInstance().keyPushed(BUTTON_SELECT))
    {
        //m_pushSelectTimer.reset();
        m_selectPressed = true;
    }
    else if (Keyboard::getInstance().keyReleased(BUTTON_SELECT))
    {
        m_selectPressed = false;
    }

    if (Keyboard::getInstance().keyPressed(BUTTON_START))
    {
        close();
        Controller::getInstance().popController();
        Link::getInstance().updateState();
        Engine::getInstance().pause(false);
        std::cout << "Inventory closed!\n";
    }



    // How we index the inventory
    // 0 1
    // 2 3
    // 4 5
    // 6 7
    // 8 9

    // If a key is pressed, record it was pressed
    // If it was pressed and hadn't been released yet, 

    // This code controls the selector through arrow keys
    if (Keyboard::getInstance().keyPressed(BUTTON_RIGHT))
    {
        if (m_selectorX == SELECTOR_INITIAL_X + SELECTOR_INCREASE_X)
        {
            m_selectorX = SELECTOR_INITIAL_X;
            // If not the bottom right of the inventory
            if (m_selectorY != SELECTOR_INITIAL_Y + 4*SELECTOR_INCREASE_Y)
            {
                m_selectorY += SELECTOR_INCREASE_Y;
                m_selectorIndex++;
            }
            else
            {
                m_selectorY = SELECTOR_INITIAL_Y;
                m_selectorIndex = 0;
            }
        }
        else
        {
            m_selectorX += SELECTOR_INCREASE_X;
            m_selectorIndex++;
        }
    }
    if (Keyboard::getInstance().keyPressed(BUTTON_LEFT))
    {
        if (m_selectorX == SELECTOR_INITIAL_X)
        {
            m_selectorX = SELECTOR_INITIAL_X + SELECTOR_INCREASE_X;
            // If not the top left of the inventory
            if (m_selectorY != SELECTOR_INITIAL_Y)
            {
                m_selectorY -= SELECTOR_INCREASE_Y;
                m_selectorIndex--;
            }
            else
            {
                m_selectorY = SELECTOR_INITIAL_Y + 4 * SELECTOR_INCREASE_Y;
                m_selectorIndex = INVENTORY_MAX_WEAPONS - 1;
            }
        }
        else
        {
            m_selectorX -= SELECTOR_INCREASE_X;
            m_selectorIndex--;
        }
    }
    if (Keyboard::getInstance().keyPressed(BUTTON_UP))
    {
        if (m_selectorY == SELECTOR_INITIAL_Y)
        {
            if (m_selectorX == SELECTOR_INITIAL_X)
            {
                m_selectorX += SELECTOR_INCREASE_X;
            }
            m_selectorY = SELECTOR_INITIAL_Y + 4 * SELECTOR_INCREASE_Y;
            m_selectorIndex = INVENTORY_MAX_WEAPONS - 1;
        }
        else
        {
            m_selectorIndex -= 2;
            m_selectorY -= SELECTOR_INCREASE_Y;
        }

    }
    if (Keyboard::getInstance().keyPressed(BUTTON_DOWN))
    {
        if (m_selectorY == SELECTOR_INITIAL_Y + 4 * SELECTOR_INCREASE_Y)
        {
            if (m_selectorX == SELECTOR_INITIAL_X + SELECTOR_INCREASE_X)
            {
                m_selectorX -= SELECTOR_INCREASE_X;
            }
            m_selectorIndex = 0;
            m_selectorY = SELECTOR_INITIAL_Y;
        }
        else
        {
            m_selectorY += SELECTOR_INCREASE_Y;
            // Change by 2 because of the way we index the array (see above)
            m_selectorIndex += 2;
        }
    }
    assert(m_selectorIndex < INVENTORY_MAX_WEAPONS);

    // If any select keys pressed, reset the flashing animation
    if (Keyboard::getInstance().keyPushed(BUTTON_RIGHT) ||
        Keyboard::getInstance().keyPushed(BUTTON_LEFT) ||
        Keyboard::getInstance().keyPushed(BUTTON_DOWN) ||
        Keyboard::getInstance().keyPushed(BUTTON_UP))
    {
        m_flashSelector = true;
        m_selectorTimer.reset();
    }

    if (Keyboard::getInstance().keyReleased(BUTTON_SELECT))
    {
        m_selectPressed = true;
    }
}

void Inventory::render(SDL_Renderer* renderer) noexcept
{
    // if inventory closed
    // render top 16 pixels at bottom of screen
    // else
    // render full screen

    int renderY;

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
    SDL_ASSERT(SDL_RenderCopy(renderer, m_texture, nullptr, &dstRect), SDL_ERROR_MESSAGE);
    colourTexture(renderer, m_texture, nullptr, SDL_RGB(INVENTORY_R, INVENTORY_G, INVENTORY_B));

    drawTopHUD(renderer);

    // If the inventory is open
    if (m_open)
    {
        drawInventoryDividers(renderer);
        drawInventoryWeapons(renderer);
        drawSelector(renderer);
        if (m_inDungeon)
        {
            drawDungeonItems(renderer);
        }
        else
        {
            drawInventoryItems(renderer);
        }
        drawMiscItems(renderer);
        drawSelectStatus(renderer);
    }

}

void Inventory::open() noexcept
{
    m_open = true;
}

void Inventory::close() noexcept
{
    m_open = false;
}

bool Inventory::magicPowderAvailabe() const noexcept
{
    return m_magicPowder;
}

bool Inventory::bowAndArrowAvailable() const noexcept
{
    return m_arrows;
}

bool Inventory::bombsAvailable() const noexcept
{
    return m_bombs;
}

void Inventory::useMagicPowder() noexcept
{
    if (m_magicPowder > 0)
    {
        m_magicPowder--;
    }
}

void Inventory::useBowAndArrow() noexcept
{
    if (m_arrows > 0)
    {
        m_arrows--;
    }
}

void Inventory::useBombs() noexcept
{
    if (m_bombs > 0)
    {
        m_bombs--;
    }
}

WEAPON Inventory::weaponA() const noexcept
{
    return m_weaponA;
}

WEAPON Inventory::weaponB() const noexcept
{
    return m_weaponB;
}

void Zelda::Inventory::setDungeonLocationMarker(int x, int y) noexcept
{
    assert(x < DUNGEON_MAX_BLOCKS_X && x >= 0 && y >= 0 && y < DUNGEON_MAX_BLOCKS_Y);
    m_dungeonPosition.x = x;
    m_dungeonPosition.y = y;
}

bool Inventory::shieldEquipped() const noexcept
{
    return (m_weaponA == WPN_SHIELD || m_weaponB == WPN_SHIELD);
}

WeaponLevel Inventory::shieldLevel() const noexcept
{
    return m_shieldLevel;
}

void Inventory::drawDungeonMap(SDL_Renderer* renderer) noexcept
{
    assert(m_dungeon > Dungeon::DUNGEON_NONE && m_dungeon < Dungeon::DUNGEON_COUNT);

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
        20 - Area LEFT and RIGHT exit only
    */


    // Draw current location grid arrow
    SDL_Rect srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW];
    SDL_Rect dstRect = m_inventorySpritesDst[INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW];

    switch (m_dungeon)
    {
    case Dungeon::DUNGEON_COLOUR_DUNGEON: break;
    case Dungeon::DUNGEON_TAIL_CAVE: dstRect.x = 112;  break;
    case Dungeon::DUNGEON_BOTTLE_GROTTO: break;
    case Dungeon::DUNGEON_KEY_CAVERN: break;
    case Dungeon::DUNGEON_ANGLER_TUNNEL: break;
    case Dungeon::DUNGEON_CATFISH_MAW: break;
    case Dungeon::DUNGEON_FACE_SHRINE: break;
    case Dungeon::DUNGEON_EAGLE_TOWER: break;
    case Dungeon::DUNGEON_TURTLE_ROCK: break;
    }

    SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);

    // Draw dungeon map level
    SDL_Rect dstRectMapLevel = {72,64,8,8};
    drawNumber(renderer, m_texture, true, true, 0, static_cast<int>(m_dungeon), &dstRectMapLevel);

    // Draw the dungeon map

    // TODO: Show the nightmare and chest locations if they have the compass
    
    // Without a map, all the paths are not drawn
    // Unvisited areas are marked with a grey block
    for (int x = 0; x < DUNGEON_MAX_BLOCKS_X; x++)
    {
        for (int y = 0; y < DUNGEON_MAX_BLOCKS_Y; y++)
        {
            // Don't display anything if dungeon map not present
            if (m_dungeonMap)
            {
                // TODO: enum these magic values
                switch (m_dungeonMaps[static_cast<int>(m_dungeon)][y][x])
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
                case 20: // INVENTORY_AREA_EXIT_LEFT_RIGHT
                    srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EXIT_LEFT_RIGHT];
                    dstRect = m_inventorySpritesDst[INVENTORY_AREA_EXIT_LEFT_RIGHT];
                    break;
                default:
                    assert(false);
                }
            }
            else
            {
                // Hide map
                if (m_dungeonMaps[static_cast<int>(m_dungeon)][y][x] != 1)
                {
                    srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EMPTY];
                    dstRect = m_inventorySpritesDst[INVENTORY_AREA_EMPTY];
                }
            }
            dstRect.x += x * srcRect.w;
            dstRect.y += y * srcRect.w;
            SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);

            // Draw current location flashing
            if (m_dungeonPosition.x == x && m_dungeonPosition.y == y)
            {
                srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_MAP_CURRENT_LOCATION];
                basicAnimate(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], srcRect, dstRect, 2, 0, 2, INSTRUMENT_FPS, Engine::getInstance().paused());
            }

        }
    }

}

void Inventory::drawSelectStatus(SDL_Renderer* renderer) noexcept
{
    SDL_Rect srcRect, dstRect;

    if (!m_selectPressed)
    {
        // Draw two red arrows
        srcRect = m_inventorySpritesSrc[INVENTORY_RED_ARROW];
        dstRect = m_inventorySpritesDst[INVENTORY_RED_ARROW];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);

        dstRect.x += 73;
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);

        srcRect = m_inventorySpritesSrc[INVENTORY_PUSH_SELECT];
        dstRect = m_inventorySpritesDst[INVENTORY_PUSH_SELECT];

        toggleItem(m_flashSelect, m_pushSelectTimer, PUSH_SELECTOR_FPS);

        // Draw "PUSH SELECT"
        if (m_flashSelect)
        {
            SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
        }
    }
    else
    {
        // TODO: Transition the subscreen
        dstRect = m_inventorySpritesDst[INVENTORY_SUBSCREEN];
        SDL_ASSERT(SDL_RenderCopy(renderer, m_subscreen, nullptr, &dstRect), SDL_ERROR_MESSAGE);

        auto currentRenderingTarget = SDL_GetRenderTarget(renderer);
        SDL_ASSERT(SDL_SetRenderTarget(renderer, m_subscreen), SDL_ERROR_MESSAGE);


        // Tunic
        srcRect = m_inventorySpritesSrc[INVENTORY_TUNIC];
        switch (m_tunic)
        {
        case Tunic::TUNIC_GREEN:
            break;
        case Tunic::TUNIC_BLUE:
            srcRect.x += srcRect.w + 2;
        break;
        case Tunic::TUNIC_RED:
            srcRect.x = 2 * (srcRect.w + 2);
        break;

        }
        dstRect = m_inventorySpritesDst[INVENTORY_TUNIC];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);

        // Heart pieces
        srcRect = m_inventorySpritesSrc[INVENTORY_HEART_PIECES];
        dstRect = m_inventorySpritesDst[INVENTORY_HEART_PIECES];

        switch (static_cast<HeartPieces>(m_heartPieces))
        {
        case HeartPieces::HEART_ZERO:
            break;
        case HeartPieces::HEART_ONE_QUARTER:
            srcRect.x += srcRect.w + 2;
            break;
        case HeartPieces::HEART_HALF:
            srcRect.x += 2 * (srcRect.w + 2);
            break;
        case HeartPieces::HEART_THREE_QUARTER:
            srcRect.x += 3 * (srcRect.w + 2);
            break;
        case HeartPieces::HEART_FULL:
            // Will this ever be used?
            srcRect.x += 4 * (srcRect.w + 2);
            break;
        }
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);

        // Photographs
        srcRect = m_inventorySpritesSrc[INVENTORY_PHOTOGRAPHS];
        dstRect = m_inventorySpritesDst[INVENTORY_PHOTOGRAPHS];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);

        // Inventory "/"
        srcRect = m_inventorySpritesSrc[INVENTORY_SLASH];
        dstRect = m_inventorySpritesDst[INVENTORY_SLASH];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
        dstRect.x = 64; dstRect.y = 8;
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
        
        // Draw how many heart pieces we have (out of 4)
        dstRect = {56,7,8,8};
        drawNumber(renderer, m_subscreen, false, false, 0, m_heartPieces, &dstRect);
        dstRect = { 72,7,8,8 };
        drawNumber(renderer, m_subscreen, false, false, 0, HEARTS_PIECE_MAX, &dstRect);

        // Draw number of photographs
        dstRect = { 24,23,8,8 };
        drawNumber(renderer, m_subscreen, false, false, 1, m_photographs, &dstRect);
        dstRect = { 48,23,8,8 };
        drawNumber(renderer, m_subscreen, false, false, 1, MAX_PHOTOGRAPHS, &dstRect);

        // Remember! This resets the drawing target to the screen
        SDL_ASSERT(SDL_SetRenderTarget(renderer, currentRenderingTarget), SDL_ERROR_MESSAGE);

    }

}

void Inventory::drawMiscItems(SDL_Renderer* renderer) noexcept
{
    SDL_Rect srcRect, dstRect;

    if (m_flippers)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_FLIPPERS];
        dstRect = m_inventorySpritesDst[INVENTORY_FLIPPERS];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }

    if (m_potion)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_POTION];
        dstRect = m_inventorySpritesDst[INVENTORY_POTION];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }

    // Draw number of seashells
    srcRect = m_inventorySpritesSrc[INVENTORY_SEASHELLS];
    dstRect = m_inventorySpritesDst[INVENTORY_SEASHELLS];
    SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    dstRect.w = 8; dstRect.h = 8;
    dstRect.x += dstRect.w; dstRect.y += dstRect.h;
    drawNumber(renderer, m_texture, false, true, 1, m_seashells, &dstRect);

    // Draw currently traded item (if any)
    if (m_tradeItem != ITEM_NONE)
    {
        srcRect = m_inventorySpritesSrc[TRADE_ITEM_SPRITE(m_tradeItem)];
        dstRect = m_inventorySpritesDst[TRADE_ITEM_SPRITE(m_tradeItem)];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }
}

void Inventory::drawInventoryItems(SDL_Renderer* renderer) noexcept
{
    // Depending on whether we are in a dungeon or not,
    // draws the inventory items or the dungeon items

    SDL_Rect srcRect, dstRect;

    // Draw any keys we have
    if (m_tailKey)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_TAIL_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_TAIL_KEY];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }

    if (m_slimeKey)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_SLIME_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_SLIME_KEY];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }

    if (m_anglerKey)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_ANGLER_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_ANGLER_KEY];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }
    
    if (m_faceKey)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_FACE_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_FACE_KEY];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }

    if (m_birdKey)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_BIRD_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_BIRD_KEY];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }

    drawInstruments(renderer);
}

void Inventory::drawDungeonItems(SDL_Renderer* renderer) noexcept
{
    SDL_Rect srcRect, dstRect;

    if (m_compass[static_cast<uint8_t>(m_dungeon)])
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_COMPASS];
        dstRect = m_inventorySpritesDst[INVENTORY_COMPASS];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }

    if (m_nightmareKey[static_cast<uint8_t>(m_dungeon)])
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_NIGHTMARE_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_NIGHTMARE_KEY];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }

    if (m_owlBeak[static_cast<uint8_t>(m_dungeon)])
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_OWL_BEAK];
        dstRect = m_inventorySpritesDst[INVENTORY_OWL_BEAK];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }

    if (m_dungeonMap[static_cast<uint8_t>(m_dungeon)])
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_MAP];
        dstRect = m_inventorySpritesDst[INVENTORY_DUNGEON_MAP];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }


    // Draw the dungeon map
    drawDungeonMap(renderer);

    // Draw dungeon keys
    srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_KEY];
    dstRect = m_inventorySpritesDst[INVENTORY_DUNGEON_KEY];
    SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    dstRect.w = 8; dstRect.h = 8;
    dstRect.x += dstRect.w; dstRect.y += dstRect.h;
    drawNumber(renderer, m_texture, false, true, 0, m_dungeonKeys[static_cast<uint8_t>(m_dungeon)], &dstRect);



}

void Inventory::drawInstruments(SDL_Renderer* renderer) noexcept
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

    for (int i = 1; i <= static_cast<int>(Instrument::INSTRUMENT_COUNT); i++)
    {
        switch (m_instruments[i - 1])
        {
        case Instrument::FULL_MOON_CELLO:
        case Instrument::CONCH_HORN:
        case Instrument::SEA_LILY_BELL:
        case Instrument::SURF_HARP:
        case Instrument::WIND_MARIMBA:
        case Instrument::CORAL_TRIANGLE:
        case Instrument::ORGAN_OF_EVENING_CALM:
        case Instrument::THUNDER_DRUM:
            srcRect = m_inventorySpritesSrc[INVENTORY_INSTRUMENT_0 + (i-1)];
            dstRect = m_inventorySpritesDst[INVENTORY_INSTRUMENT_0 + (i-1)];
            basicAnimate(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], srcRect, dstRect, 0, 0, INSTRUMENTS_FRAME, INSTRUMENT_FPS, Engine::getInstance().paused());
            break;
        default:
            // If we don't have the instrument yet
            srcRect = m_inventorySpritesSrc[INVENTORY_INSTRUMENT_BACK_0];
            dstRect = m_inventorySpritesDst[INVENTORY_INSTRUMENT_BACK_0 + i - 1];
            SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
            dstRect.x += 8; dstRect.y += 8; dstRect.w = 8; dstRect.h = 8;
            drawNumber(renderer, m_texture, false, true, 0, i, &dstRect);
            break;
        }
    }
}

void Inventory::drawHealth(SDL_Renderer* renderer) noexcept
{
    float currentHealth = Link::getInstance().health();
    float healthMax =  Link::getInstance().maxHealth();

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
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
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
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
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
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
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
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
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
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
        dstRect.x += srcRect.w;
        drawnHearts++;
        if (drawnHearts == HEARTS_PER_ROW)
        {
            dstRect.y += srcRect.h;
            dstRect.x = m_inventorySpritesDst[INVENTORY_HEART_WHOLE].x;
        }
    }
}

void Inventory::drawInventoryWeapons(SDL_Renderer* renderer) noexcept
{
    SDL_Rect srcRect, dstRect;

    // Instead of creating an object for each item we have
    // We just render the items we have to a single texture
    // and render that instead
    auto currentRenderingTarget = SDL_GetRenderTarget(renderer);
    SDL_ASSERT(SDL_SetRenderTarget(renderer, m_texture), SDL_ERROR_MESSAGE);

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
            SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
        }
    }

    SDL_ASSERT(SDL_SetRenderTarget(renderer, currentRenderingTarget), SDL_ERROR_MESSAGE);

    for (int i = 0; i < INVENTORY_MAX_WEAPONS; i++)
    {
        if (m_items[i] != WPN_NONE)
        {
            dstRect =
            {
                WEAPON_LEVEL_X + ((((i & 1) == 1) ? 1 : 0) * WEAPON_LEVEL_SPACING_X),
                WEAPON_LEVEL_Y + ((i / 2) * WEAPON_LEVEL_SPACING_Y),
                WEAPON_LEVEL_WIDTH,
                WEAPON_LEVEL_HEIGHT
            };

            drawWeaponLevel(renderer, m_texture, m_items[i], &dstRect);
        }
    }
  

}

void Inventory::drawSelector(SDL_Renderer* renderer) noexcept
{
    auto currentRenderingTarget = SDL_GetRenderTarget(renderer);
    SDL_ASSERT(SDL_SetRenderTarget(renderer, m_texture), SDL_ERROR_MESSAGE);

    SDL_Rect srcRect, dstRect;
    // Render the selector

    // Selector animation
    toggleItem(m_flashSelector, m_selectorTimer, INVENTORY_SELECTOR_FPS);

    if (m_flashSelector)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_1];
        dstRect = { m_selectorX, m_selectorY, srcRect.w , srcRect.h };
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }
    SDL_ASSERT(SDL_SetRenderTarget(renderer, currentRenderingTarget), SDL_ERROR_MESSAGE);

}

void Inventory::drawInventoryDividers(SDL_Renderer* renderer) noexcept
{
    SDL_Rect srcRect, dstRect;
    auto currentRenderingTarget = SDL_GetRenderTarget(renderer);
    SDL_ASSERT(SDL_SetRenderTarget(renderer, m_texture), SDL_ERROR_MESSAGE);

    srcRect = m_inventorySpritesSrc[INVENTORY_DIVIDER_H];
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
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }
    srcRect = m_inventorySpritesSrc[INVENTORY_DIVIDER_V];
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
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
    }
    SDL_ASSERT(SDL_SetRenderTarget(renderer, currentRenderingTarget), SDL_ERROR_MESSAGE);
}

void Inventory::drawTopHUD(SDL_Renderer* renderer) noexcept 
{
    auto currentRenderingTarget = SDL_GetRenderTarget(renderer);
    SDL_ASSERT(SDL_SetRenderTarget(renderer, m_texture), SDL_ERROR_MESSAGE);

    SDL_Rect srcRect, dstRect;

    // Copy "B" 
    srcRect = m_inventorySpritesSrc[INVENTORY_B_BUTTON];
    dstRect = m_inventorySpritesDst[INVENTORY_B_BUTTON];
    SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);

    // Copy "A"
    srcRect = m_inventorySpritesSrc[INVENTORY_A_BUTTON];
    dstRect = m_inventorySpritesDst[INVENTORY_A_BUTTON];
    SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);

    // Copy selector
    srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_1];
    dstRect = m_inventorySpritesDst[INVENTORY_SELECTOR_BUTTON_1];
    SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);

    srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_2];
    dstRect = m_inventorySpritesDst[INVENTORY_SELECTOR_BUTTON_2];
    SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);

    // Ruppee icon
    srcRect = m_inventorySpritesSrc[INVENTORY_RUPPEE];
    dstRect = m_inventorySpritesDst[INVENTORY_RUPPEE];
    SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);

    // Draw health
    drawHealth(renderer);

    // Draw weapon A
    if (m_weaponA != WPN_NONE)
    {
        // Draw the actual weapon
        srcRect = m_inventorySpritesSrc[m_weaponA];
        dstRect = {48,0, srcRect.w, srcRect.h };
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);

        // Draw the weapon level
        dstRect = { 56,8, 8, 8 };
        drawWeaponLevel(renderer, m_texture, m_weaponA, &dstRect);
    }

    // Draw weapon B
    if (m_weaponB != WPN_NONE)
    {
        srcRect = m_inventorySpritesSrc[m_weaponB];
        dstRect = { 8,0, srcRect.w, srcRect.h };
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect), SDL_ERROR_MESSAGE);
        dstRect = { 16,8, 8, 8 };
        drawWeaponLevel(renderer, m_texture, m_weaponB, &dstRect);
    }

    // Draw current ruppees
    dstRect = { 80,8,8,8 };
    drawNumber(renderer, m_texture, false, true, 2, 10, &dstRect);

    // Pop rendering target
    SDL_ASSERT(SDL_SetRenderTarget(renderer, currentRenderingTarget), SDL_ERROR_MESSAGE);
}

// Draw a number or level onto a texture
// examples
// 2
// L-1 L-2
// 09
// 320

void Inventory::drawNumber(SDL_Renderer* renderer, SDL_Texture* srcTexture, bool drawLevel, bool useNormalFont, int trailingDigits, int number, SDL_Rect* dstRect) noexcept
{
    // drawLevel      = Draw the "L-" text next to the number
    // useNormalFont  = Use the normal digit text or text with black background
    // trailingDigits = Number of trailing digits to append to the LHS of the number (e.g 1 01 001)

    // Save the current renderering target
    auto currentRenderingTarget = SDL_GetRenderTarget(renderer);
    SDL_ASSERT(SDL_SetRenderTarget(renderer, srcTexture), SDL_ERROR_MESSAGE);

    SDL_Rect srcRect;

    // Draw level
    if (drawLevel)
    {
        // Draw the "L-"
        srcRect = m_inventorySpritesSrc[INVENTORY_LEVEL];
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, dstRect), SDL_ERROR_MESSAGE);

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
        SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, dstRect), SDL_ERROR_MESSAGE);
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
            SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, dstRect), SDL_ERROR_MESSAGE);
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
            SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, dstRect), SDL_ERROR_MESSAGE);
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
            SDL_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, dstRect), SDL_ERROR_MESSAGE);
            dstRect->x += srcRect.w;
        }
    }
    // Restore "pop" the target backk
    SDL_ASSERT(SDL_SetRenderTarget(renderer, currentRenderingTarget), SDL_ERROR_MESSAGE);
}

void Inventory::drawWeaponLevel(SDL_Renderer* renderer, SDL_Texture* srcTexture, WEAPON weapon, SDL_Rect* dstRect) noexcept
{
    switch (weapon)
    {
    case WPN_SHIELD:
        drawNumber(renderer, srcTexture, true, true, 0, (int)m_shieldLevel, dstRect);
        break;
    case WPN_SWORD:
        drawNumber(renderer, srcTexture, true, true, 0, (int)m_swordLevel, dstRect);
        break;
    case WPN_POWER_BRACELET_1:
    case WPN_POWER_BRACELET_2:
        drawNumber(renderer, srcTexture, true, true, 0, (int)m_braceletLevel, dstRect);
        break;
    case WPN_BOMBS:
        drawNumber(renderer, srcTexture, false, true, 1, m_bombs, dstRect);
        break;
    case WPN_BOW:
        drawNumber(renderer, srcTexture, false, true, 1, m_arrows, dstRect);
        break;
    case WPN_MAGIC_POWDER:
        drawNumber(renderer, srcTexture, false, true, 1, m_magicPowder, dstRect);
        break;
    case WPN_OCARINA:
        drawNumber(renderer, srcTexture, false, true, 0, (int)m_ocarinaSong, dstRect);
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
