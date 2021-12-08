#include "Inventory.h"
#include "Resource.h"
#include "InputControl.h"
#include "Renderer.h"
#include "Depth.h"
#include "Camera.h"
#include "Link.h"
#include "ZD_Assert.h"
#include "Keyboard.h"
#include "Engine.h"
#include "Common.h"

namespace Zelda
{

Inventory::Inventory() : 
    Renderable("Inventory", Sprite(Renderer::getInstance().getRenderer(), INVENTORY_WIDTH, INVENTORY_HEIGHT), ZD_DEPTH_INVENTORY),
    Controllable(m_name),
    m_subscreen(Sprite(Renderer::getInstance().getRenderer(), SELECT_SUBSCREEN_WIDTH, SELECT_SUBSCREEN_HEIGHT)),
    m_tradeItem(ITEM_NONE),
    m_open(false),
    m_inDungeon(false),
    m_arrows(0),
    m_bombs(0),
    m_magicPowder(0),
    m_ocarinaSong(OcarinaSong::SNG_FISH),
    m_seashells(0),
    m_flippers(false),
    m_potion(false),
    m_tunic(Tunic::TUNIC_GREEN),
    m_heartPieces(HEART_ZERO),
    m_goldleafs(0),
    m_photographs(0),
    m_ruppees(0),
    m_weaponA(InventoryWeapon(WeaponItem::WPN_NONE, WeaponLevel::WPN_LEVEL_NONE)),
    m_weaponB(InventoryWeapon(WeaponItem::WPN_NONE, WeaponLevel::WPN_LEVEL_NONE)),
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
    assert(m_subscreen.data());
    // m_texture is the main texture we draw ontoas
    assert(m_texture.data());
    Rect<int> srcRect = { 0,0, m_subscreen.width(), m_subscreen.height() };    
    Sprite::colourSprite(Renderer::getInstance().getRenderer(), m_subscreen, srcRect, SDL_RGB(0, 0, 0));

    // 7 -> 39 x increases of 32
    // 27 -> 50 y increases by 23

    // Initialise inventory
    for (int i = 0; i < INVENTORY_MAX_WEAPONS; i++)
    {
        m_weaponItems[i] = InventoryWeapon(WeaponItem::WPN_NONE, WeaponLevel::WPN_LEVEL_NONE);
    }

    for (int i = 0; i < INSTRUMENT_COUNT; i++)
    {
        m_instruments[i] = INSTRUMENT_NONE;
    }

    for (int i = 0; i < KEY_COUNT; i++)
    {
        m_dungeonEntraceKeys[i] = KEY_NONE;
    }

    for (uint8_t i = 0; i < DUNGEON_COUNT; i++)
    {
        m_dungeonKeys[i] = 0;
        m_compass[i] = false;
        m_dungeonMap[i] = false;
        m_nightmareKey[i] = false;
        m_owlBeak[i] = false;
    }

    Renderer::getInstance().addRenderable(this);
}

void Inventory::control() noexcept
{
    if (Keyboard::getInstance().keyPressed(BUTTON_A))
    {
       std::swap(m_weaponA, m_weaponItems[m_selectorIndex]);
    }
    if (Keyboard::getInstance().keyPressed(BUTTON_B))
    {
       std::swap(m_weaponB, m_weaponItems[m_selectorIndex]);
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
        DEBUG(DBG_INFO, "Inventory closed!");
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
        moveSelectorRight();
    }
    if (Keyboard::getInstance().keyPressed(BUTTON_LEFT))
    {
        moveSelectorLeft();
    }
    if (Keyboard::getInstance().keyPressed(BUTTON_UP))
    {
        moveSelectorUp();
    }
    if (Keyboard::getInstance().keyPressed(BUTTON_DOWN))
    {
        moveSelectorDown();
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

void Inventory::render() noexcept
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
    Rect<int> dstRect = { 0, renderY, m_texture.width() , m_texture.height() };
    Rect<int> srcRect = { 0, 0,  m_texture.width() , m_texture.height() };
    m_texture.drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    Sprite::colourSprite(Renderer::getInstance().getRenderer(), m_texture, srcRect, SDL_RGB(INVENTORY_R, INVENTORY_G, INVENTORY_B));

    drawHUD();

    // If the inventory is open
    if (m_open)
    {
        drawInventoryDividers();
        drawInventoryWeapons();
        drawSelector();
        if (m_inDungeon)
        {
            drawDungeonItems();
        }
        else
        {
            drawInventoryItems();
        }
        drawMiscItems();

        if (!m_selectPressed)
        {
            drawSelectStatus();
        }
        else
        {
            drawSubscreen();
        }
    }

}

void Inventory::getDungeonMap(Dungeon dungeon, DungeonMapEntry (&dungeonMapEntry)[DUNGEON_MAX_BLOCKS_X][DUNGEON_MAX_BLOCKS_Y]) const noexcept
{
    assert(dungeon > DUNGEON_NONE && dungeon < DUNGEON_COUNT);
    std::memcpy(&dungeonMapEntry, m_dungeonMaps[dungeon], sizeof(m_dungeonMaps[dungeon]));
}

void Inventory::setDungeonMapEntry(const int x, const int y, const DungeonMapEntry& dungeonMapEntry) noexcept
{
    assert(x >= 0 && x < DUNGEON_MAX_BLOCKS_X && y >= 0 && y < DUNGEON_MAX_BLOCKS_Y);
    m_dungeonMaps[m_dungeon][y][x] = dungeonMapEntry;
}

void Inventory::update() noexcept
{
}

void Inventory::open() noexcept
{
    m_open = true;
}

void Inventory::close() noexcept
{
    m_open = false;
}

bool Inventory::magicPowder() const noexcept
{
    return m_magicPowder;
}

bool Inventory::arrows() const noexcept
{
    return m_arrows;
}

bool Inventory::bombs() const noexcept
{
    return m_bombs;
}

void Inventory::addItemQuantity(WeaponItem item, int quantity) noexcept
{
    switch (item)
    {
    case WPN_BOMBS:
        m_bombs = std::min(m_bombs + quantity, BOMBS_MAX);
        break;
    case WPN_BOW:
        m_arrows = std::min(m_arrows + quantity, ARROWS_MAX);
        break;
    case WPN_MAGIC_POWDER:
        m_magicPowder = std::min(m_magicPowder + quantity, MAGIC_POWDER_MAX);
        break;
    default:
        assert(false);
    }
}

void Inventory::addItem(const InventoryWeapon& inventoryWeapon) noexcept
{
    assert(itemExists(inventoryWeapon) == false);

    // Find an empty space in the inventory
    for (int i = 0; i < INVENTORY_MAX_WEAPONS; i++)
    {
        if (m_weaponItems[i] == InventoryWeapon(WeaponItem::WPN_NONE, WeaponLevel::WPN_LEVEL_NONE))
        {
            m_weaponItems[i] = inventoryWeapon;
            return;
        }
    }

    // Otherwise weapon A or B
    if (m_weaponA == InventoryWeapon(WeaponItem::WPN_NONE, WeaponLevel::WPN_LEVEL_NONE))
    {
        m_weaponA = inventoryWeapon;
    }
    else if (m_weaponB == InventoryWeapon(WeaponItem::WPN_NONE, WeaponLevel::WPN_LEVEL_NONE))
    {
        m_weaponB = inventoryWeapon;
    }
    else
    {
        assert(false && "Can't add item to full inventory");
    }
}

void Inventory::addItem(DungeonKey dungeonKey) noexcept
{
    assert(itemExists(dungeonKey) == false);
    for (int i = 0; i < KEY_COUNT; i++)
    {
        if (m_dungeonEntraceKeys[i] == KEY_NONE)
        {
            m_dungeonEntraceKeys[i] = dungeonKey;
            break;
        }
    }
}

void Inventory::addItem(DungeonItem dungeonItem) noexcept
{
    switch (dungeonItem)
    {
    case DungeonItem::ITEM_KEY: 
        // Add a small key
        m_dungeonKeys[m_dungeon]++;
        break;
    // These can only be added once 
    case DungeonItem::ITEM_COMPASS:
        assert(m_compass[m_dungeon] == false);
        m_compass[m_dungeon] = true;
        break;
    case DungeonItem::ITEM_MAP:
        assert(m_dungeonMap[m_dungeon] == false);
        m_dungeonMap[m_dungeon] = true;
        break;
    case DungeonItem::ITEM_NIGHTMARE_KEY:
        assert(m_nightmareKey[m_dungeon] == false);
        m_nightmareKey[m_dungeon] = true;
        break;
    case DungeonItem::ITEM_OWL_BEAK:
        assert(m_owlBeak[m_dungeon] == false);
        m_owlBeak[m_dungeon] = true;
        break;
    default:
        assert(false);
    }
}

void Inventory::addItem(TradeItem tradeItem) noexcept
{
    // We can only trade upwards
    assert(tradeItem > m_tradeItem);
    assert(tradeItem > ITEM_NONE && tradeItem < ITEM_COUNT);
    m_tradeItem = tradeItem;
}

void Inventory::addItem(InventoryMiscItem inventoryMiscItem) noexcept
{
    switch (inventoryMiscItem)
    {
    case ITEM_RED_POTION:
        assert(m_potion == false);
        m_potion = true;
    break;
    case ITEM_FLIPPERS:
        assert(m_flippers == false);
        m_flippers = true;
    break;
    default:
        assert(false);

    }
}

void Inventory::addItem(Instrument instrument) noexcept
{
    assert(instrument > INSTRUMENT_NONE && instrument < INSTRUMENT_COUNT);
    for (int i = 0; i < INSTRUMENT_COUNT; i++)
    {
        if (m_instruments[i] == INSTRUMENT_NONE)
        {
            m_instruments[i] = instrument;
            break;
        }
    }
}

void Inventory::addItem(Ruppee ruppees) noexcept
{
    // I think 200 is the maximum single ruppee amount you can get
    assert(ruppees == RUPPEE_ONE || ruppees == RUPPEE_FIVE || ruppees == RUPPEE_TEN ||
        ruppees == RUPPEE_TWENTY || ruppees == RUPPEE_FIFTY || ruppees == RUPPEE_HUNDRED ||
        ruppees == RUPPEE_TWO_HUNDRED);

    m_ruppees = std::min(m_ruppees + ruppees, RUPPEES_MAX);

    // The ruppees are added 1 by 1 on a timer
}

void Inventory::addItem(Tunic tunic) noexcept
{
    assert(tunic > Tunic::TUNIC_NONE && tunic < Tunic::TUNIC_COUNT);
    m_tunic = tunic;
}

void Inventory::addItem(HeartPiece heartPiece) noexcept
{
    // A Piece of Heart is 1/4 so we can only add this
    assert(heartPiece == HEART_ONE_QUARTER);
    m_heartPieces += heartPiece;
}

void Inventory::addItem(int photograph) noexcept
{
    m_photographs = std::min(m_photographs + photograph, MAX_PHOTOGRAPHS);
}

void Inventory::useItem(DungeonItem dungeonItem) noexcept
{
    switch (dungeonItem)
    {
    case DungeonItem::ITEM_KEY:
        assert(m_dungeonKeys[m_dungeon] > 0);
        assert(m_dungeon > DUNGEON_NONE && m_dungeon < DUNGEON_COUNT);
        m_dungeonKeys[m_dungeon]--;
    break;
    default:
        assert(false);
    }
}

void Inventory::useItem(InventoryMiscItem inventoryMiscItem) noexcept
{
    switch (inventoryMiscItem)
    {
    case ITEM_RED_POTION:
        assert(m_potion == true);
        m_potion = false;
        break;
    default:
        assert(false && "Only red potion is usable");

    }
}

void Inventory::removeItem(const InventoryWeapon& inventoryWeapon) noexcept
{
    assert(itemExists(inventoryWeapon) == true);

    // Remove weapon
    for (int i = 0; i < INVENTORY_MAX_WEAPONS; i++)
    {
        if (m_weaponItems[i] == inventoryWeapon)
        {
            m_weaponItems[i] = InventoryWeapon(WeaponItem::WPN_NONE, WeaponLevel::WPN_LEVEL_NONE);
            return;
        }
    }

    // Otherwise weapon A or B
    if (m_weaponA == inventoryWeapon)
    {
        m_weaponA = InventoryWeapon(WeaponItem::WPN_NONE, WeaponLevel::WPN_LEVEL_NONE);
    }
    else if (m_weaponB == inventoryWeapon)
    {
        m_weaponB = InventoryWeapon(WeaponItem::WPN_NONE, WeaponLevel::WPN_LEVEL_NONE);
    }
    else
    {
        assert(false && "Removing an item failed");
    }
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

InventoryWeapon Inventory::weaponA() const noexcept
{
    return m_weaponA;
}

InventoryWeapon Inventory::weaponB() const noexcept
{
    return m_weaponB;
}

void Inventory::setDungeonLocationMarker(int x, int y) noexcept
{
    assert(x < DUNGEON_MAX_BLOCKS_X && x >= 0 && y >= 0 && y < DUNGEON_MAX_BLOCKS_Y);

    // Must be a place we can actually access
    assert(m_dungeonMaps[m_dungeon][y][x].roomType > 1  && "Index shouldn't be accessible in dungeon map");

    m_dungeonPosition.x = x;
    m_dungeonPosition.y = y;

    // Mark as visited
    m_dungeonMaps[m_dungeon][y][x].visited = true;
}

auto Inventory::inventoryWeaponSpriteSrc(const InventoryWeapon& item) const noexcept
{
    // Any item we have, add it to the texture at the right position
    // srcRect is the position on the spritesheet of the item

    // The power-bracelet has a different sprite for Level-2 for some reason!
    Rect<int> srcRect;

    if (item.first == WeaponItem::WPN_POWER_BRACELET)
    {
        if (item.second == WeaponLevel::WPN_LEVEL_1)
        {
            srcRect = m_inventorySpritesSrc[item.first];
        }
        else
        {
            srcRect = m_inventorySpritesSrc[item.first + 1];
        }
    }
    else if (item.first < WeaponItem::WPN_POWER_BRACELET)
    {
        srcRect = m_inventorySpritesSrc[item.first];
    }
    else if (item.first > WeaponItem::WPN_POWER_BRACELET)
    {
        srcRect = m_inventorySpritesSrc[item.first + 1];
    }
    else
    {
        assert(false);
        return Rect<int>();
    }
    return srcRect;
}

bool Inventory::shieldEquipped() const noexcept
{
    return (m_weaponA.first == WPN_SHIELD || m_weaponB.first == WPN_SHIELD);
}

void Inventory::drawDungeonMap() noexcept
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
    auto srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW];
    auto dstRect = m_inventorySpritesDst[INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW];

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

    ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

    // Draw dungeon map level
    Rect<int> dstRectMapLevel = {72,64,8,8};
    drawNumber(m_texture, true, true, 0, m_dungeon, dstRectMapLevel);

    // Draw the dungeon map
    
    // Without a map, all the paths are not drawn
    // Unvisited areas are marked with a grey block
    for (int x = 0; x < DUNGEON_MAX_BLOCKS_X; x++)
    {
        for (int y = 0; y < DUNGEON_MAX_BLOCKS_Y; y++)
        {
            // Don't display anything if dungeon map not present
            if (m_dungeonMap[m_dungeon])
            {
                // Show the room in the map if we visited it already
                if (m_dungeonMaps[m_dungeon][y][x].visited)
                {

                    // TODO: Hidden rooms are not connected on the map until they are explored
                    // This will probably be the most tricky one to implement

                    // TODO: enum these magic values
                    switch (m_dungeonMaps[m_dungeon][y][x].roomType)
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
                        // Shown when we have the compass
                        assert(false && "Treasure chest can't exist in map array");
                        break;
                    case 4: // INVENTORY_AREA_NIGHTMARE
                        // Shown when we have the compass
                        assert(false && "Nightmare key can't exist in map array");
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
                        assert(false && "Unknown map entry");
                    }
                }
                else
                {
                    if (m_dungeonMaps[m_dungeon][y][x].roomType > 1)
                    {
                        // Display a "unvisited" square
                        srcRect = m_inventorySpritesSrc[INVENTORY_AREA_UNVISITED];
                        dstRect = m_inventorySpritesDst[INVENTORY_AREA_UNVISITED];
                    }
                    else if (m_dungeonMaps[m_dungeon][y][x].roomType == 1)
                    {
                        continue;
                    }
                    else
                    {
                        srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EMPTY];
                        dstRect = m_inventorySpritesDst[INVENTORY_AREA_EMPTY];
                    }

                }
            }
            else
            {
                // Add empty square
                if (m_dungeonMaps[m_dungeon][y][x].roomType != 1)
                {
                    srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EMPTY];
                    dstRect = m_inventorySpritesDst[INVENTORY_AREA_EMPTY];
                }
            }

            // If we have the compass, show the nightmare and treasure chests
            if (m_compass[m_dungeon])
            {
                if (m_dungeonMaps[m_dungeon][y][x].roomItem == DungeonRoomItem::ITEM_NIGHTMARE_KEY)
                {
                    srcRect = m_inventorySpritesSrc[INVENTORY_AREA_NIGHTMARE];
                    dstRect = m_inventorySpritesDst[INVENTORY_AREA_NIGHTMARE];
                }
                else
                {
                    if (m_dungeonMaps[m_dungeon][y][x].roomItem == DungeonRoomItem::ITEM_CHEST_CLOSED)
                    {
                        srcRect = m_inventorySpritesSrc[INVENTORY_AREA_TREASURE];
                        dstRect = m_inventorySpritesDst[INVENTORY_AREA_TREASURE];
                    }
                }
            }

            dstRect.x += x * srcRect.w;
            dstRect.y += y * srcRect.w;

            ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

            // Draw current location flashing
            if (m_dungeonPosition.x == x && m_dungeonPosition.y == y)
            {
                srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_MAP_CURRENT_LOCATION];
                basicAnimate(Renderer::getInstance().getRenderer(), ResourceManager::getInstance()[Graphic::GFX_INVENTORY], srcRect, dstRect, 2, 0, 2, INSTRUMENT_FPS, Engine::getInstance().paused());
            }

        }
    }

}

void Inventory::drawSelectStatus() noexcept
{
    Rect<int> srcRect, dstRect;

    // Draw two red arrows
    srcRect = m_inventorySpritesSrc[INVENTORY_RED_ARROW];
    dstRect = m_inventorySpritesDst[INVENTORY_RED_ARROW];

    ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

    dstRect.x += 73;
    ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

    srcRect = m_inventorySpritesSrc[INVENTORY_PUSH_SELECT];
    dstRect = m_inventorySpritesDst[INVENTORY_PUSH_SELECT];

    toggleItem(m_flashSelect, m_pushSelectTimer, PUSH_SELECTOR_FPS);

    // Draw "PUSH SELECT"
    if (m_flashSelect)
    {
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    }
}

void Inventory::drawMiscItems() noexcept
{
    Rect<int> srcRect, dstRect;

    if (m_flippers)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_FLIPPERS];
        dstRect = m_inventorySpritesDst[INVENTORY_FLIPPERS];
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    }

    if (m_potion)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_POTION];
        dstRect = m_inventorySpritesDst[INVENTORY_POTION];
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    }

    // Draw number of seashells
    srcRect = m_inventorySpritesSrc[INVENTORY_SEASHELLS];
    dstRect = m_inventorySpritesDst[INVENTORY_SEASHELLS];
    ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

    dstRect.w = 8; dstRect.h = 8;
    dstRect.x += dstRect.w; dstRect.y += dstRect.h;
    drawNumber(m_texture, false, true, 1, m_seashells, dstRect);

    // Draw currently traded item (if any)
    if (m_tradeItem != ITEM_NONE)
    {
        srcRect = m_inventorySpritesSrc[TRADE_ITEM_SPRITE(m_tradeItem)];
        dstRect = m_inventorySpritesDst[TRADE_ITEM_SPRITE(m_tradeItem)];
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    }
}

void Inventory::drawInventoryItems() noexcept
{
    // Depending on whether we are in a dungeon or not,
    // draws the inventory items or the dungeon items

    Rect<int> srcRect, dstRect;

    // Draw any keys we have
    if (itemExists(KEY_TAIL))
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_TAIL_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_TAIL_KEY];
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    }

    if (itemExists(KEY_SLIME))
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_SLIME_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_SLIME_KEY];
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    }

    if (itemExists(KEY_ANGLER))
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_ANGLER_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_ANGLER_KEY];
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    }
    
    if (itemExists(KEY_FACE))
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_FACE_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_FACE_KEY];
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    }

    if (itemExists(KEY_FACE))
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_BIRD_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_BIRD_KEY];
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    }

    drawInstruments();
}

void Inventory::drawDungeonItems() noexcept
{
    Rect<int> srcRect, dstRect;

    if (m_compass[m_dungeon])
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_COMPASS];
        dstRect = m_inventorySpritesDst[INVENTORY_COMPASS];
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    }

    if (m_nightmareKey[m_dungeon])
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_NIGHTMARE_KEY];
        dstRect = m_inventorySpritesDst[INVENTORY_NIGHTMARE_KEY];
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    }

    if (m_owlBeak[m_dungeon])
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_OWL_BEAK];
        dstRect = m_inventorySpritesDst[INVENTORY_OWL_BEAK];
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    }

    if (m_dungeonMap[m_dungeon])
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_MAP];
        dstRect = m_inventorySpritesDst[INVENTORY_DUNGEON_MAP];
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    }

    // Draw the dungeon map
    drawDungeonMap();

    // Draw dungeon keys
    srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_KEY];
    dstRect = m_inventorySpritesDst[INVENTORY_DUNGEON_KEY];
    ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    
    dstRect.w = 8; dstRect.h = 8;
    dstRect.x += dstRect.w; dstRect.y += dstRect.h;
    drawNumber(m_texture, false, true, 0, m_dungeonKeys[m_dungeon], dstRect);
}

void Inventory::drawInstruments() noexcept
{
    Rect<int> srcRect, dstRect;

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
            basicAnimate(Renderer::getInstance().getRenderer(), ResourceManager::getInstance()[Graphic::GFX_INVENTORY], srcRect, dstRect, 0, 0, INSTRUMENTS_FRAME, INSTRUMENT_FPS, Engine::getInstance().paused());
            break;
        default:
            // If we don't have the instrument yet
            srcRect = m_inventorySpritesSrc[INVENTORY_INSTRUMENT_BACK_0];
            dstRect = m_inventorySpritesDst[INVENTORY_INSTRUMENT_BACK_0 + i - 1];
            ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
        
            dstRect.x += 8; dstRect.y += 8; dstRect.w = 8; dstRect.h = 8;
            drawNumber(m_texture, false, true, 0, i, dstRect);
            break;
        }
    }
}

void Inventory::drawHealth() noexcept
{
    float currentHealth = Link::getInstance().health();
    float healthMax =  Link::getInstance().maxHealth();

    const int wholeHearts = (int)currentHealth;
    const float quarterHearts = currentHealth - (int)currentHealth;
    const int emptyHearts = (currentHealth - (int)currentHealth > 0 ? healthMax - std::ceil(currentHealth) : healthMax - wholeHearts);

    auto srcRect = m_inventorySpritesSrc[INVENTORY_HEART_WHOLE];
    auto dstRect = m_inventorySpritesDst[INVENTORY_HEART_WHOLE];
    int drawnHearts = 0;

    auto drawHeart = [&]() noexcept
    {
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
        dstRect.x += srcRect.w;

        // Append to new row of hearts
        drawnHearts++;
        if (drawnHearts == HEARTS_PER_ROW)
        {
            dstRect.y += srcRect.h;
            dstRect.x = m_inventorySpritesDst[INVENTORY_HEART_WHOLE].x;
        }
    };

    // Draw whole hearts
    for (int i = 0; i < wholeHearts; i++)
    {
        drawHeart();
    }

    assert(quarterHearts == 0.0 || quarterHearts == 0.25 || quarterHearts == 0.5 || quarterHearts == 0.75);
    // Draw any quarter hearts
    if (quarterHearts > 0)
    {
        if (quarterHearts == 0.25)
        {
            srcRect.x = (srcRect.w + 2) * 3;
        }
        else if (quarterHearts == 0.5)
        {
            srcRect.x = (srcRect.w + 2) * 2;
        }
        else if (quarterHearts == 0.75)
        {
            srcRect.x = (srcRect.w + 2) * 1;
        }
        drawHeart();
    }
    
    // Draw empty hearts
    srcRect.x = (srcRect.w + 2) * 4;
    for (int i = 0; i < emptyHearts; i++)
    {
        drawHeart();
    }
}

void Inventory::drawInventoryWeapons() noexcept
{
    Rect<int> srcRect, dstRect;

    // Instead of creating an object for each item we have
    // We just render the items we have to a single texture
    // and render that instead
    auto const currentRenderingTarget = Renderer::getInstance().pushRenderingTarget(m_texture);

    for (int i = 0; i < INVENTORY_MAX_WEAPONS; i++)
    {
        if (m_weaponItems[i] != InventoryWeapon(WeaponItem::WPN_NONE, WeaponLevel::WPN_LEVEL_NONE))
        {
            srcRect = inventoryWeaponSpriteSrc(m_weaponItems[i]);

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
            ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
        }
    }

    Renderer::getInstance().popRenderingTarget(currentRenderingTarget);

    for (int i = 0; i < INVENTORY_MAX_WEAPONS; i++)
    {
        if (m_weaponItems[i] != InventoryWeapon(WeaponItem::WPN_NONE, WeaponLevel::WPN_LEVEL_NONE))
        {
            dstRect =
            {
                WEAPON_LEVEL_X + ((((i & 1) == 1) ? 1 : 0) * WEAPON_LEVEL_SPACING_X),
                WEAPON_LEVEL_Y + ((i / 2) * WEAPON_LEVEL_SPACING_Y),
                WEAPON_LEVEL_WIDTH,
                WEAPON_LEVEL_HEIGHT
            };

            drawWeaponLevel(m_texture, m_weaponItems[i].first, dstRect);
        }
    }
  

}

void Inventory::drawSelector() noexcept
{
    auto const currentRenderingTarget = Renderer::getInstance().pushRenderingTarget(m_texture);

    Rect<int> srcRect, dstRect;
    // Render the selector

    // Selector animation
    toggleItem(m_flashSelector, m_selectorTimer, INVENTORY_SELECTOR_FPS);

    if (m_flashSelector)
    {
        srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_1];
        dstRect = { m_selectorX, m_selectorY, srcRect.w , srcRect.h };
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    }
    Renderer::getInstance().popRenderingTarget(currentRenderingTarget);

}

void Inventory::drawInventoryDividers() noexcept
{
    Rect<int> srcRect, dstRect;
    auto const currentRenderingTarget = Renderer::getInstance().pushRenderingTarget(m_texture);

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
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
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
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    }

    Renderer::getInstance().popRenderingTarget(currentRenderingTarget);
}

void Inventory::drawHUD() noexcept 
{
    auto const currentRenderingTarget = Renderer::getInstance().pushRenderingTarget(m_texture);
    Rect<int> srcRect, dstRect;

    // Copy "B" 
    srcRect = m_inventorySpritesSrc[INVENTORY_B_BUTTON];
    dstRect = m_inventorySpritesDst[INVENTORY_B_BUTTON];
    ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

    // Copy "A"
    srcRect = m_inventorySpritesSrc[INVENTORY_A_BUTTON];
    dstRect = m_inventorySpritesDst[INVENTORY_A_BUTTON];
    ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

    // Copy selector
    srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_1];
    dstRect = m_inventorySpritesDst[INVENTORY_SELECTOR_BUTTON_1];
    ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

    srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_2];
    dstRect = m_inventorySpritesDst[INVENTORY_SELECTOR_BUTTON_2];
    ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

    // Ruppee icon
    srcRect = m_inventorySpritesSrc[INVENTORY_RUPPEE];
    dstRect = m_inventorySpritesDst[INVENTORY_RUPPEE];
    ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

    // Draw health
    drawHealth();

    // Draw weapon A
    if (m_weaponA != InventoryWeapon(WeaponItem::WPN_NONE, WeaponLevel::WPN_LEVEL_NONE))
    {
        // Draw the actual weapon
        srcRect = inventoryWeaponSpriteSrc(m_weaponA);
        dstRect = {48,0, srcRect.w, srcRect.h };
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

        // Draw the weapon level
        dstRect = { 56,8, 8, 8 };
        drawWeaponLevel(m_texture, m_weaponA.first, dstRect);
    }

    // Draw weapon B
    if (m_weaponB != InventoryWeapon(WeaponItem::WPN_NONE, WeaponLevel::WPN_LEVEL_NONE))
    {
        srcRect = inventoryWeaponSpriteSrc(m_weaponB);
        dstRect = { 8,0, srcRect.w, srcRect.h };
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

        dstRect = { 16,8, 8, 8 };
        drawWeaponLevel(m_texture, m_weaponB.first, dstRect);
    }

    // Draw current ruppees
    dstRect = { 80,8,8,8 };
    drawNumber(m_texture, false, true, 2, m_ruppees, dstRect);

    // Pop rendering target
    Renderer::getInstance().popRenderingTarget(currentRenderingTarget);

}

void Inventory::drawSubscreen() const noexcept
{

    // TODO: Transition the subscreen
    auto dstRect = m_inventorySpritesDst[INVENTORY_SUBSCREEN];
    Rect<int> srcRect = { 0,0,dstRect.w, dstRect.h };
    m_subscreen.drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    auto currentRenderingTarget = Renderer::getInstance().pushRenderingTarget(m_subscreen);

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
    ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

    // Heart pieces
    srcRect = m_inventorySpritesSrc[INVENTORY_HEART_PIECES];
    dstRect = m_inventorySpritesDst[INVENTORY_HEART_PIECES];

    assert(m_heartPieces > HEART_NONE && m_heartPieces < HEART_COUNT);
    srcRect.x += (m_heartPieces * (srcRect.w + 2));
    ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

    // Photographs
    srcRect = m_inventorySpritesSrc[INVENTORY_PHOTOGRAPHS];
    dstRect = m_inventorySpritesDst[INVENTORY_PHOTOGRAPHS];
    ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

    // Inventory "/"
    srcRect = m_inventorySpritesSrc[INVENTORY_SLASH];
    dstRect = m_inventorySpritesDst[INVENTORY_SLASH];
    ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);
    
    dstRect.x = 64; dstRect.y = 8;
    ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, dstRect);

    // Draw how many heart pieces we have (out of 4)
    dstRect = { 56,7,8,8 };
    drawNumber(m_subscreen, false, false, 0, m_heartPieces, dstRect);
    dstRect = { 72,7,8,8 };
    drawNumber( m_subscreen, false, false, 0, HEARTS_PIECE_MAX, dstRect);

    // Draw number of photographs
    dstRect = { 24,23,8,8 };
    drawNumber(m_subscreen, false, false, 1, m_photographs, dstRect);
    dstRect = { 48,23,8,8 };
    drawNumber(m_subscreen, false, false, 1, MAX_PHOTOGRAPHS, dstRect);

    // Remember! This resets the drawing target to the screen
    Renderer::getInstance().popRenderingTarget(currentRenderingTarget);
}

// Draw a number or level onto a texture
// examples
// 2
// L-1 L-2
// 09
// 320

void Inventory::drawNumber(const Sprite& srcTexture, bool drawLevel, bool useNormalFont, int trailingDigits, int number, const Rect<int>& dstRect) const noexcept
{
    // drawLevel      = Draw the "L-" text next to the number
    // useNormalFont  = Use the normal digit text or text with black background
    // trailingDigits = Number of trailing digits to append to the LHS of the number (e.g 1 01 001)

    assert(number >= 0);
    assert(trailingDigits >= 0);
    assert(dstRect != Rect<int>());

    // Save the current renderering target
    auto const currentRenderingTarget = Renderer::getInstance().pushRenderingTarget(srcTexture);

    Rect<int> srcRect;
    auto rectDst = dstRect;

    // Draw level
    if (drawLevel)
    {
        // Draw the "L-"
        srcRect = m_inventorySpritesSrc[INVENTORY_LEVEL];
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, rectDst);

        if (useNormalFont)
        {
            srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_W];
        }
        else
        {
            srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_B];
        }

        srcRect.x += 2 * number + srcRect.w * number;
        rectDst.x += srcRect.w;
        ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, rectDst);
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
            ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, rectDst);
            rectDst.x += srcRect.w;
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
            ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, rectDst);
            rectDst.x += srcRect.w;
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
            ResourceManager::getInstance()[Graphic::GFX_INVENTORY].drawSprite(Renderer::getInstance().getRenderer(), srcRect, rectDst);
            rectDst.x += srcRect.w;
        }
    }
    // Restore "pop" the target backk
    Renderer::getInstance().popRenderingTarget(currentRenderingTarget);
}

void Inventory::drawWeaponLevel(const Sprite& srcTexture, WeaponItem weapon, const Rect<int>& dstRect) noexcept
{
    switch (weapon)
    {
    case WPN_SHIELD:
    {
        auto const shieldLevel = (int)itemLevel(WPN_SHIELD);
        assert(shieldLevel != WPN_LEVEL_NONE);
        drawNumber(srcTexture, true, true, 0, shieldLevel, dstRect);
    }
        break;
    case WPN_SWORD:
    {
        auto const swordLevel = (int)itemLevel(WPN_SWORD);
        assert(swordLevel != WPN_LEVEL_NONE);
        drawNumber(srcTexture, true, true, 0, swordLevel, dstRect);
    }
        break;
    case WPN_POWER_BRACELET:
    {
        auto const braceletLevel = (int)itemLevel(WPN_POWER_BRACELET);
        assert(braceletLevel != WPN_LEVEL_NONE);
        drawNumber(srcTexture, true, true, 0, braceletLevel, dstRect);
    }
        break;
    case WPN_BOMBS:
        drawNumber(srcTexture, false, true, 1, m_bombs, dstRect);
        break;
    case WPN_BOW:
        drawNumber(srcTexture, false, true, 1, m_arrows, dstRect);
        break;
    case WPN_MAGIC_POWDER:
        drawNumber(srcTexture, false, true, 1, m_magicPowder, dstRect);
        break;
    case WPN_OCARINA:
        drawNumber(srcTexture, false, true, 0, (int)m_ocarinaSong, dstRect);
        break;
    case WPN_BOOMERANG:
    case WPN_ROC_FEATHER:
    case WPN_HOOKSHOT:
    case WPN_PEGASUS_BOOT:
    case WPN_SHOVEL:
    case WPN_FLAME_ROD:
        break;
    default:
        assert(false);
    }
}

void Inventory::moveSelectorRight() noexcept
{
    if (m_selectorX == SELECTOR_INITIAL_X + SELECTOR_INCREASE_X)
    {
        m_selectorX = SELECTOR_INITIAL_X;
        // If not the bottom right of the inventory
        if (m_selectorY != SELECTOR_INITIAL_Y + 4 * SELECTOR_INCREASE_Y)
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

void Inventory::moveSelectorUp() noexcept
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

void Inventory::moveSelectorDown() noexcept
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

void Inventory::moveSelectorLeft() noexcept
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

bool Inventory::itemExists(const InventoryWeapon& inventoryWeapon) const noexcept
{
    if (m_weaponA == inventoryWeapon || m_weaponB == inventoryWeapon)
    {
        return true;
    }
    for (int i = 0; i < INVENTORY_MAX_WEAPONS; i++)
    {
        if (m_weaponItems[i] == inventoryWeapon)
        {
            return true;
        }
    }
    return false;
}

bool Inventory::itemExists(WeaponItem item) const noexcept
{
    if (m_weaponA.first == item || m_weaponB.first == item)
    {
        return true;
    }
    for (int i = 0; i < INVENTORY_MAX_WEAPONS; i++)
    {
        if (m_weaponItems[i].first == item)
        {
            return true;
        }
    }
    return false;
}

bool Inventory::itemExists(DungeonKey dungeonKey) const noexcept
{
    for (int i = 0; i < KEY_COUNT; i++)
    {
        if (m_dungeonEntraceKeys[i] == dungeonKey)
        {
            return true;
        }
    }
    return false;
}

WeaponLevel Inventory::itemLevel(WeaponItem item) const noexcept
{
    assert(itemExists(item) == true);
    if (m_weaponA.first == item)
    {
        return m_weaponA.second;
    }
    if (m_weaponB.first == item)
    {
        return m_weaponB.second;
    }
    for (int i = 0; i < INVENTORY_MAX_WEAPONS; i++)
    {
        if (m_weaponItems[i].first == item)
        {
            return m_weaponItems[i].second;
        }
    }

    assert(false);
    return WeaponLevel();
}

void Inventory::inDungeon(bool inside) noexcept
{
    m_inDungeon = inside;
}


}