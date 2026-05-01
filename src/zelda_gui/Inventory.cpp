#include "zelda_core/Inventory.h"
#include "core/Renderer.h"
#include "Depth.h"
#include "core/Keyboard.h"
#include "core/InputControl.h"
#include "core/Controller.h"
#include "Link.h"
#include "core/Colour.h"
#include "core/Engine.h"
#include "core/ResourceManager.h"
#include "core/SDL_RenderTarget.h"

namespace zelda::gui
{
Inventory::Inventory()
    : Renderable("Inventory",
                 engine::Sprite(engine::Renderer::instance().getRenderer(), INVENTORY_WIDTH, INVENTORY_HEIGHT),
                 std::to_underlying(core::ZOrdering::INVENTORY))
    , Controllable(m_name)
    , m_subscreen(std::make_unique<engine::Sprite>(engine::Renderer::instance().getRenderer(), SELECT_SUBSCREEN_WIDTH,
                                                   SELECT_SUBSCREEN_HEIGHT))
    , m_open(false)
    , m_selectorX(SELECTOR_INITIAL_X)
    , m_selectorY(SELECTOR_INITIAL_Y)
    , m_flashSelector(false)
    , m_flashSelect(false)
    , m_selectPressed(false)
{
    // Select sub screen
    assert(m_subscreen->data());
    // m_texture is the main texture we draw ontoas
    assert(m_sprite->data());
    engine::Rect<int> srcRect = {0, 0, m_subscreen->width(), m_subscreen->height()};
    m_subscreen->colour(srcRect, engine::Colour::makeRGB(0, 0, 0));

    // 7 -> 39 x increases of 32
    // 27 -> 50 y increases by 23

    // Initialise inventory

    engine::Renderer::instance().addRenderable(this);
}

void Inventory::control()
{
    if (engine::Keyboard::instance().keyPressed(BUTTON_A))
    {
        m_inventoryImpl.swapItemA();
    }
    if (engine::Keyboard::instance().keyPressed(BUTTON_B))
    {
        m_inventoryImpl.swapItemB();
    }

    // Show the subscreen only when the select key is pushed
    // TODO: Transition it in
    if (engine::Keyboard::instance().keyPushed(BUTTON_SELECT))
    {
        m_selectPressed = true;
    }
    else if (engine::Keyboard::instance().keyReleased(BUTTON_SELECT))
    {
        m_selectPressed = false;
    }

    if (engine::Keyboard::instance().keyPressed(BUTTON_START))
    {
        close();
        engine::Controller::instance().popController();
        core::Link::instance().updateState();
        engine::Engine::instance().pause(false);
        Logger::instance().log<Logger::Mask::INFO>("Inventory closed!");
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
    if (engine::Keyboard::instance().keyPressed(BUTTON_RIGHT))
    {
        moveSelector(engine::Direction::RIGHT);
    }
    if (engine::Keyboard::instance().keyPressed(BUTTON_LEFT))
    {
        moveSelector(engine::Direction::LEFT);
    }
    if (engine::Keyboard::instance().keyPressed(BUTTON_UP))
    {
        moveSelector(engine::Direction::UP);
    }
    if (engine::Keyboard::instance().keyPressed(BUTTON_DOWN))
    {
        moveSelector(engine::Direction::DOWN);
    }

    // If any select keys pressed, reset the flashing animation
    if (engine::Keyboard::instance().keyPushed(BUTTON_RIGHT) || engine::Keyboard::instance().keyPushed(BUTTON_LEFT)
        || engine::Keyboard::instance().keyPushed(BUTTON_DOWN) || engine::Keyboard::instance().keyPushed(BUTTON_UP))
    {
        m_flashSelector = true;
    }

    if (engine::Keyboard::instance().keyReleased(BUTTON_SELECT))
    {
        m_selectPressed = true;
    }
}

void Inventory::render()
{
    drawInventoryBackground();
    drawHUD();

    // If the inventory is open
    if (m_open)
    {
        drawInventoryDividers();
        drawInventoryWeapons();
        drawSelector();
        if (m_inventoryImpl.inDungeon())
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

void Inventory::update()
{}

void Inventory::open()
{
    m_open = true;
}

void Inventory::close()
{
    m_open = false;
}

/*
auto Inventory::inventoryWeaponSpriteSrc(const InventoryWeapon& item) const
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
*/

void Inventory::drawDungeonMap()
{
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


    engine::Rect<int> srcRect;
    engine::Rect<int> dstRect;

    // Draw current location grid arrow
    // auto srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW];
    // auto dstRect = m_inventorySpritesDst[INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW];

    switch (m_inventoryImpl.dungeon())
    {
    case core::Inventory::Dungeon::Name::COLOUR_DUNGEON:
        break;
    case core::Inventory::Dungeon::Name::TAIL_CAVE:
        dstRect.x = 112;
        break;
    case core::Inventory::Dungeon::Name::BOTTLE_GROTTO:
        break;
    case core::Inventory::Dungeon::Name::KEY_CAVERN:
        break;
    case core::Inventory::Dungeon::Name::ANGLER_TUNNEL:
        break;
    case core::Inventory::Dungeon::Name::CATFISH_MAW:
        break;
    case core::Inventory::Dungeon::Name::FACE_SHRINE:
        break;
    case core::Inventory::Dungeon::Name::EAGLE_TOWER:
        break;
    case core::Inventory::Dungeon::Name::TURTLE_ROCK:
        break;
    default:
        assert(false);
    }

    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

    // Draw dungeon map level
    engine::Rect<int> dstRectMapLevel = {72, 64, 8, 8};
    drawNumber(*m_sprite, true, true, 0, static_cast<int>(m_inventoryImpl.dungeon()), dstRectMapLevel);

    // Draw the dungeon map

    // Without a map, all the paths are not drawn
    // Unvisited areas are marked with a grey block
    for (int x = 0; x < core::Inventory::MAX_DUNGEON_BLOCKS_X; ++x)
    {
        for (int y = 0; y < core::Inventory::MAX_DUNGEON_BLOCKS_Y; ++y)
        {
            // Don't display anything if dungeon map not present
            if (m_inventoryImpl.dungeonItem(core::Inventory::Dungeon::Item::MAP))
            {
                // Show the room in the map if we visited it already
                if (m_inventoryImpl.dungeonMapLocationVisited(x, y))
                {
                    // TODO: Hidden rooms are not connected on the map until they are explored
                    // This will probably be the most tricky one to implement

                    // TODO: enum these magic values
                    /*switch (m_inventoryImpl.dungeonMapLocationRoomType(x,y))
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
                    }*/
                }
                else
                {
                    if (m_inventoryImpl.dungeonMapLocationVisited(x, y))
                    {
                        // Display a "unvisited" square
                        // srcRect = m_inventorySpritesSrc[INVENTORY_AREA_UNVISITED];
                        // dstRect = m_inventorySpritesDst[INVENTORY_AREA_UNVISITED];
                    }
                    else if (m_inventoryImpl.dungeonMapLocationVisited(x, y) == 1)
                    {
                        continue;
                    }
                    else
                    {
                        // srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EMPTY];
                        // dstRect = m_inventorySpritesDst[INVENTORY_AREA_EMPTY];
                    }
                }
            }
            else
            {
                // Add empty square
                if (m_inventoryImpl.dungeonMapLocationVisited(x, y) != 1)
                {
                    // srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EMPTY];
                    // dstRect = m_inventorySpritesDst[INVENTORY_AREA_EMPTY];
                }
            }

            // If we have the compass, show the nightmare and treasure chests
            if (m_inventoryImpl.dungeonItem(core::Inventory::Dungeon::Item::COMPASS))
            {
                if (m_inventoryImpl.dungeonMapLocationRoomItem(x, y)
                    == core::Inventory::Dungeon::MapItem::NIGHTMARE_KEY)
                {
                    // srcRect = m_inventorySpritesSrc[INVENTORY_AREA_NIGHTMARE];
                    // dstRect = m_inventorySpritesDst[INVENTORY_AREA_NIGHTMARE];
                }
                else if (m_inventoryImpl.dungeonMapLocationRoomItem(x, y)
                         == core::Inventory::Dungeon::MapItem::CHEST_CLOSED)
                {
                    // srcRect = m_inventorySpritesSrc[INVENTORY_AREA_TREASURE];
                    // dstRect = m_inventorySpritesDst[INVENTORY_AREA_TREASURE];
                }
            }

            dstRect.x += x * srcRect.w;
            dstRect.y += y * srcRect.w;

            engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

            auto const dungeonPosition = m_inventoryImpl.dungeonMapPositionLocation();
            // Draw current location flashing
            if (dungeonPosition.x == x && dungeonPosition.y == y)
            {
                // srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_MAP_CURRENT_LOCATION];
                // basicAnimate(Renderer::getInstance().getRenderer(),
                // *ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY], srcRect, dstRect, 2, 0, 2,
                // INSTRUMENT_FPS, Engine::getInstance().paused());
            }
        }
    }
}

void Inventory::drawSelectStatus()
{
    engine::Rect<int> srcRect, dstRect;

    // Draw two red arrows
    // srcRect = m_inventorySpritesSrc[INVENTORY_RED_ARROW];
    // dstRect = m_inventorySpritesDst[INVENTORY_RED_ARROW];

    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

    dstRect.x += 73;
    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

    // srcRect = m_inventorySpritesSrc[INVENTORY_PUSH_SELECT];
    // dstRect = m_inventorySpritesDst[INVENTORY_PUSH_SELECT];

    // toggleItem(m_flashSelect, m_pushSelectTimer, PUSH_SELECTOR_FPS);

    // Draw "PUSH SELECT"
    if (m_flashSelect)
    {
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
    }
}

void Inventory::drawMiscItems()
{
    engine::Rect<int> srcRect, dstRect;

    if (m_inventoryImpl.miscItemExists(core::Inventory::MiscItem::FLIPPERS))
    {
        // srcRect = m_inventorySpritesSrc[INVENTORY_FLIPPERS];
        // dstRect = m_inventorySpritesDst[INVENTORY_FLIPPERS];
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
    }

    if (m_inventoryImpl.miscItemExists(core::Inventory::MiscItem::RED_POTION))
    {
        // srcRect = m_inventorySpritesSrc[INVENTORY_POTION];
        // dstRect = m_inventorySpritesDst[INVENTORY_POTION];
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
    }

    // Draw number of seashells
    // srcRect = m_inventorySpritesSrc[INVENTORY_SEASHELLS];
    // dstRect = m_inventorySpritesDst[INVENTORY_SEASHELLS];
    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

    dstRect.w = 8;
    dstRect.h = 8;
    dstRect.x += dstRect.w;
    dstRect.y += dstRect.h;
    drawNumber(*m_sprite, false, true, 1, m_inventoryImpl.secretSeaShells(), dstRect);

    // Draw currently traded item (if any)
    if (m_inventoryImpl.tradedItem() != core::Inventory::TradeItem::NONE)
    {
        // srcRect = m_inventorySpritesSrc[TRADE_ITEM_SPRITE(m_tradeItem)];
        // dstRect = m_inventorySpritesDst[TRADE_ITEM_SPRITE(m_tradeItem)];
        // ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
    }
}

void Inventory::drawInventoryItems()
{
    // Depending on whether we are in a dungeon or not,
    // draws the inventory items or the dungeon items

    engine::Rect<int> srcRect, dstRect;

    // Draw any keys we have
    if (m_inventoryImpl.dungeonEntranceKey(core::Inventory::Dungeon::EntranceKey::TAIL))
    {
        // srcRect = m_inventorySpritesSrc[INVENTORY_TAIL_KEY];
        // dstRect = m_inventorySpritesDst[INVENTORY_TAIL_KEY];
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
    }

    if (m_inventoryImpl.dungeonEntranceKey(core::Inventory::Dungeon::EntranceKey::SLIME))
    {
        // srcRect = m_inventorySpritesSrc[INVENTORY_SLIME_KEY];
        // dstRect = m_inventorySpritesDst[INVENTORY_SLIME_KEY];
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
    }

    if (m_inventoryImpl.dungeonEntranceKey(core::Inventory::Dungeon::EntranceKey::ANGLER))
    {
        // srcRect = m_inventorySpritesSrc[INVENTORY_ANGLER_KEY];
        // dstRect = m_inventorySpritesDst[INVENTORY_ANGLER_KEY];
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
    }

    if (m_inventoryImpl.dungeonEntranceKey(core::Inventory::Dungeon::EntranceKey::FACE))
    {
        // srcRect = m_inventorySpritesSrc[INVENTORY_FACE_KEY];
        // dstRect = m_inventorySpritesDst[INVENTORY_FACE_KEY];
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
    }

    if (m_inventoryImpl.dungeonEntranceKey(core::Inventory::Dungeon::EntranceKey::BIRD))
    {
        // srcRect = m_inventorySpritesSrc[INVENTORY_BIRD_KEY];
        // dstRect = m_inventorySpritesDst[INVENTORY_BIRD_KEY];
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
    }

    drawInstruments();
}

void Inventory::drawDungeonItems()
{
    engine::Rect<int> srcRect, dstRect;

    if (m_inventoryImpl.dungeonItem(core::Inventory::Dungeon::Item::COMPASS))
    {
        // srcRect = m_inventorySpritesSrc[INVENTORY_COMPASS];
        // dstRect = m_inventorySpritesDst[INVENTORY_COMPASS];
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
    }

    if (m_inventoryImpl.dungeonItem(core::Inventory::Dungeon::Item::NIGHTMARE_KEY))
    {
        // srcRect = m_inventorySpritesSrc[INVENTORY_NIGHTMARE_KEY];
        // dstRect = m_inventorySpritesDst[INVENTORY_NIGHTMARE_KEY];
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
    }

    if (m_inventoryImpl.dungeonItem(core::Inventory::Dungeon::Item::OWL_BEAK))
    {
        // srcRect = m_inventorySpritesSrc[INVENTORY_OWL_BEAK];
        // dstRect = m_inventorySpritesDst[INVENTORY_OWL_BEAK];
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
    }

    if (m_inventoryImpl.dungeonItem(core::Inventory::Dungeon::Item::MAP))
    {
        // srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_MAP];
        // dstRect = m_inventorySpritesDst[INVENTORY_DUNGEON_MAP];
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
    }

    // Draw the dungeon map
    drawDungeonMap();

    // Draw dungeon keys
    // srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_KEY];
    // dstRect = m_inventorySpritesDst[INVENTORY_DUNGEON_KEY];
    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

    dstRect.w = 8;
    dstRect.h = 8;
    dstRect.x += dstRect.w;
    dstRect.y += dstRect.h;
    drawNumber(*m_sprite,
               false,
               true,
               0,
               m_inventoryImpl.dungeonItem(core::Inventory::Dungeon::Item::LOCKED_DOOR_KEY),
               dstRect);
}

void Inventory::drawInstruments()
{
    // Rect<int> srcRect, dstRect;

    // Instrument positions
    // 1st 120,60
    // 2nd 136,80
    // 3rd 136,104
    // 4th 120,120
    // 5th 96,120
    // 6th 80,104
    // 7th 80,80
    // 8th 96,64

    auto const instruments = m_inventoryImpl.instruments();

    for (int i = 0; i < std::ssize(instruments); ++i)
    {
        /*switch (instruments[i])
        {
            case Instrument::INSTRUMENT_FULL_MOON_CELLO:
            case Instrument::INSTRUMENT_CONCH_HORN:
            case Instrument::INSTRUMENT_SEA_LILY_BELL:
            case Instrument::INSTRUMENT_SURF_HARP:
            case Instrument::INSTRUMENT_WIND_MARIMBA:
            case Instrument::INSTRUMENT_CORAL_TRIANGLE:
            case Instrument::INSTRUMENT_ORGAN_OF_EVENING_CALM:
            case Instrument::INSTRUMENT_THUNDER_DRUM:
                //srcRect = m_inventorySpritesSrc[INVENTORY_INSTRUMENT_0 + (i-1)];
                //dstRect = m_inventorySpritesDst[INVENTORY_INSTRUMENT_0 + (i-1)];
                //basicAnimate(Renderer::getInstance().getRenderer(),
        *ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY], srcRect, dstRect, 0, 0, INSTRUMENTS_FRAME,
        INSTRUMENT_FPS, Engine::getInstance().paused()); break; default:
                // If we don't have the instrument yet
                //srcRect = m_inventorySpritesSrc[INVENTORY_INSTRUMENT_BACK_0];
                //dstRect = m_inventorySpritesDst[INVENTORY_INSTRUMENT_BACK_0 + i - 1];
                ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

                dstRect.x += 8; dstRect.y += 8; dstRect.w = 8; dstRect.h = 8;
                drawNumber(*m_sprite, false, true, 0, i, dstRect);
                break;
        }*/
    }
}

void Inventory::drawHealth()
{
    auto const currentHeartPieces = m_inventoryImpl.heartPieces();
    auto const maxHeartPieces = m_inventoryImpl.maxHeartPieces();
    auto const halfHearts = currentHeartPieces - static_cast<int>(currentHeartPieces);

    auto const wholeHearts = static_cast<int>(currentHeartPieces);
    auto const emptyHearts = (currentHeartPieces - static_cast<int>(currentHeartPieces) > 0
                                  ? maxHeartPieces - std::ceil(currentHeartPieces)
                                  : maxHeartPieces - wholeHearts);

    engine::Rect<int> srcRect, dstRect;

    // auto srcRect = m_inventorySpritesSrc[INVENTORY_HEART_WHOLE];
    // auto dstRect = m_inventorySpritesDst[INVENTORY_HEART_WHOLE];

    int drawnHearts = 0;

    auto drawHeart = [&]()
    {
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
        dstRect.x += srcRect.w;

        // Append to new row of hearts
        drawnHearts++;
        if (drawnHearts == HEARTS_PER_ROW)
        {
            dstRect.y += srcRect.h;
            // dstRect.x = m_inventorySpritesDst[INVENTORY_HEART_WHOLE].x;
        }
    };

    // Draw whole hearts
    for (int i = 0; i < wholeHearts; ++i)
    {
        drawHeart();
    }

    assert(halfHearts == 0.0 || halfHearts == 0.5);
    // Draw any half hearts
    if (halfHearts == 0.5)
    {
        srcRect.x = (srcRect.w + 2) * 2;
        drawHeart();
    }

    // Draw empty hearts
    srcRect.x = (srcRect.w + 2) * 4;
    for (int i = 0; i < emptyHearts; i++)
    {
        drawHeart();
    }
}

void Inventory::drawInventoryWeapons()
{
    engine::Rect<int> srcRect, dstRect;

    // Instead of creating an object for each item we have
    // We just render the items we have to a single texture
    // and render that instead
    auto const inventoryItems = m_inventoryImpl.inventoryItems();
    {
        engine::RenderTarget target(engine::Renderer::instance().getRenderer(), m_sprite->data());

        for (int i = 0; i < std::ssize(inventoryItems); ++i)
        {
            if (inventoryItems[i] != core::Inventory::Item{})
            {
                // srcRect = inventoryWeaponSpriteSrc(m_weaponItems[i]);

                // dstRect is the position on the internal inventory lhs
                // This correctly positions the item
                dstRect = {INVENTORY_POS_X + ((((i & 1) == 1) ? 1 : 0) * INVENTORY_X_SPACING),
                           INVENTORY_POS_Y + ((i / 2) * INVENTORY_Y_SPACING),
                           INVENTORY_SPRITE_WIDTH,
                           INVENTORY_SPRITE_HEIGHT};
                // Draw the inventory items onto the internal inventory
                engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
            }
        }
    }

    for (int i = 0; i < std::ssize(inventoryItems); ++i)
    {
        if (inventoryItems[i] != core::Inventory::Item{})
        {
            dstRect = {WEAPON_LEVEL_X + ((((i & 1) == 1) ? 1 : 0) * WEAPON_LEVEL_SPACING_X),
                       WEAPON_LEVEL_Y + ((i / 2) * WEAPON_LEVEL_SPACING_Y),
                       WEAPON_LEVEL_WIDTH,
                       WEAPON_LEVEL_HEIGHT};

            drawInventoryItemAttribute(*m_sprite, inventoryItems[i], dstRect);
        }
    }
}

void Inventory::drawSelector()
{
    engine::RenderTarget target(engine::Renderer::instance().getRenderer(), m_sprite->data());
    engine::Rect<int> srcRect, dstRect;
    // Render the selector

    // Selector animation
    // toggleItem(m_flashSelector, m_selectorTimer, INVENTORY_SELECTOR_FPS);

    if (m_flashSelector)
    {
        // srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_1];
        dstRect = {m_selectorX, m_selectorY, srcRect.w, srcRect.h};
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
    }
}

void Inventory::drawInventoryDividers()
{
    engine::Rect<int> srcRect, dstRect;
    engine::RenderTarget target(engine::Renderer::instance().getRenderer(), m_sprite->data());

    // srcRect = m_inventorySpritesSrc[INVENTORY_DIVIDER_H];

    // Draw horizontal divider
    for (int i = 0; i < (INVENTORY_WIDTH / INVENTORY_DIVIDER_WIDTH_H) - 2; ++i)
    {
        dstRect = {INVENTORY_DIVIDER_XH + i + INVENTORY_DIVIDER_WIDTH_H * i,
                   INVENTORY_DIVIDER_YH,
                   INVENTORY_DIVIDER_WIDTH_H,
                   INVENTORY_DIVIDER_HEIGHT_H};
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
    }
    // srcRect = m_inventorySpritesSrc[INVENTORY_DIVIDER_V];
    //  Draw vertical divider
    for (int i = 0; i < ((INVENTORY_HEIGHT - INVENTORY_DIVIDER_YV) / INVENTORY_DIVIDER_WIDTH_V); ++i)
    {
        dstRect = {INVENTORY_DIVIDER_XV,
                   INVENTORY_DIVIDER_YV + i + INVENTORY_DIVIDER_HEIGHT_V * i,
                   INVENTORY_DIVIDER_WIDTH_V,
                   INVENTORY_DIVIDER_HEIGHT_V};
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);
    }
}

void Inventory::drawHUD()
{
    engine::RenderTarget target(engine::Renderer::instance().getRenderer(), m_sprite->data());
    engine::Rect<int> srcRect, dstRect;

    // Copy "B"
    // srcRect = m_inventorySpritesSrc[INVENTORY_B_BUTTON];
    // dstRect = m_inventorySpritesDst[INVENTORY_B_BUTTON];
    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

    // Copy "A"
    // srcRect = m_inventorySpritesSrc[INVENTORY_A_BUTTON];
    // dstRect = m_inventorySpritesDst[INVENTORY_A_BUTTON];
    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

    // Copy selector
    // srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_1];
    // dstRect = m_inventorySpritesDst[INVENTORY_SELECTOR_BUTTON_1];
    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

    // srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_2];
    // dstRect = m_inventorySpritesDst[INVENTORY_SELECTOR_BUTTON_2];
    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

    // Ruppee icon
    // srcRect = m_inventorySpritesSrc[INVENTORY_RUPPEE];
    // dstRect = m_inventorySpritesDst[INVENTORY_RUPPEE];
    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

    // Draw health
    drawHealth();

    // Draw weapon A
    if (m_inventoryImpl.itemA() != core::Inventory::Item{})
    {
        // Draw the actual weapon
        // srcRect = inventoryWeaponSpriteSrc(m_weaponA);
        dstRect = {48, 0, srcRect.w, srcRect.h};
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

        // Draw the weapon level
        dstRect = {56, 8, 8, 8};
        drawInventoryItemAttribute(*m_sprite, m_inventoryImpl.itemA(), dstRect);
    }

    // Draw weapon B
    if (m_inventoryImpl.itemB() != core::Inventory::Item{})
    {
        // srcRect = inventoryWeaponSpriteSrc(m_weaponB);
        dstRect = {8, 0, srcRect.w, srcRect.h};
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

        dstRect = {16, 8, 8, 8};
        drawInventoryItemAttribute(*m_sprite, m_inventoryImpl.itemB(), dstRect);
    }

    // Draw current ruppees
    dstRect = {80, 8, 8, 8};
    drawNumber(*m_sprite, false, true, 2, m_inventoryImpl.rupees(), dstRect);
}

void Inventory::drawInventoryBackground()
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
        renderY = engine::CAMERA_HEIGHT;
    }

    // Render the inventory background
    m_sprite->draw(engine::Rect<int>{}, engine::Rect<int>{0, renderY, m_sprite->width(), m_sprite->height()});
    m_sprite->colour(engine::Rect<int>{}, engine::Colour::makeRGB(INVENTORY_R, INVENTORY_G, INVENTORY_B));
}

void Inventory::drawSubscreen() const
{
    engine::Rect<int> dstRect; // = m_inventorySpritesDst[INVENTORY_SUBSCREEN];
    engine::Rect<int> srcRect = {0, 0, dstRect.w, dstRect.h};
    m_subscreen->draw(srcRect, dstRect);

    // Remember! This resets the drawing target to the screen
    engine::RenderTarget target(engine::Renderer::instance().getRenderer(), m_sprite->data());

    // Tunic
    // srcRect = m_inventorySpritesSrc[INVENTORY_TUNIC];
    switch (m_inventoryImpl.tunic())
    {
    case core::Inventory::Tunic::GREEN:
        break;
    case core::Inventory::Tunic::BLUE:
        srcRect.x += srcRect.w + 2;
        break;
    case core::Inventory::Tunic::RED:
        srcRect.x = 2 * (srcRect.w + 2);
        break;
    default:
        break;
    }

    // dstRect = m_inventorySpritesDst[INVENTORY_TUNIC];
    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

    // Heart pieces
    // srcRect = m_inventorySpritesSrc[INVENTORY_HEART_PIECES];
    // dstRect = m_inventorySpritesDst[INVENTORY_HEART_PIECES];

    srcRect.x += (m_inventoryImpl.heartPieces() * (srcRect.w + 2));
    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

    // Photographs
    // srcRect = m_inventorySpritesSrc[INVENTORY_PHOTOGRAPHS];
    // dstRect = m_inventorySpritesDst[INVENTORY_PHOTOGRAPHS];
    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

    // Inventory "/"
    // srcRect = m_inventorySpritesSrc[INVENTORY_SLASH];
    // dstRect = m_inventorySpritesDst[INVENTORY_SLASH];
    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

    dstRect.x = 64;
    dstRect.y = 8;
    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect);

    // Draw how many heart pieces we have (out of 4)
    dstRect = {56, 7, 8, 8};
    drawNumber(*m_subscreen, false, false, 0, m_inventoryImpl.heartPieces(), dstRect);
    dstRect = {72, 7, 8, 8};
    drawNumber(*m_subscreen, false, false, 0, m_inventoryImpl.maxHeartPieces(), dstRect);

    // Draw number of photographs
    dstRect = {24, 23, 8, 8};
    drawNumber(*m_subscreen, false, false, 1, m_inventoryImpl.numberOfPhotographs(), dstRect);
    dstRect = {48, 23, 8, 8};
    drawNumber(*m_subscreen, false, false, 1, core::Inventory::MAX_PHOTOGRAPHS, dstRect);
}

// Draw a number or level onto a texture
// examples
// 2
// L-1 L-2
// 09
// 320

// TODO: These drawNumber and drawWeaponLevel functions are used in the shop too so must be moved elsewhere
void Inventory::drawNumber(const engine::Sprite& srcSprite, bool drawLevel, bool useNormalFont, int trailingDigits,
                           int number, const engine::Rect<int>& dstRect) const
{
    // drawLevel      = Draw the "L-" text next to the number
    // useNormalFont  = Use the normal digit text or text with black background
    // trailingDigits = Number of trailing digits to append to the LHS of the number (e.g 1 01 001)

    assert(number >= 0);
    assert(trailingDigits >= 0);
    assert(dstRect != engine::Rect<int>());

    // Save the current renderering target
    engine::RenderTarget target(engine::Renderer::instance().getRenderer(), srcSprite.data());

    engine::Rect<int> srcRect;
    auto rectDst = dstRect;

    // Draw level
    if (drawLevel)
    {
        // Draw the "L-"
        // srcRect = m_inventorySpritesSrc[INVENTORY_LEVEL];
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, rectDst);

        if (useNormalFont)
        {
            // srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_W];
        }
        else
        {
            // srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_B];
        }

        srcRect.x += 2 * number + srcRect.w * number;
        rectDst.x += srcRect.w;
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, rectDst);
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
            // srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_W];
        }
        else
        {
            // srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_B];
        }

        // Add any trailing digits if needed in front of the number
        for (int i = 0; i < (number == 0 ? trailingDigits : trailingDigits + 1 - numberLength); i++)
        {
            engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, rectDst);
            rectDst.x += srcRect.w;
        }

        // Just draw a standard number with or without trailing digits
        do
        {
            if (useNormalFont)
            {
                // srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_W];
            }
            else
            {
                // srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_B];
            }

            srcRect.x += 2 * (number % 10) + srcRect.w * (number % 10);
            engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, rectDst);
            rectDst.x += srcRect.w;
            number /= 10;
        } while (number != 0);

        if (useNormalFont)
        {
            // srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_W];
        }
        else
        {
            // srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_B];
        }

        // Draw any reversed number whose 0 was lost
        for (int i = 0; i < trailingZeros; i++)
        {
            engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, rectDst);
            rectDst.x += srcRect.w;
        }
    }
}

void Inventory::drawInventoryItemAttribute(const engine::Sprite& srcSprite, const core::Inventory::Item& item,
                                           const engine::Rect<int>& dstRect)
{
    switch (item.itemAttribute)
    {
    case core::Inventory::Item::Attribute::LEVEL:
        switch (item.usableItem)
        {
        case core::Inventory::Item::Type::SHIELD:
        case core::Inventory::Item::Type::SWORD:
        case core::Inventory::Item::Type::POWER_BRACELET:
            drawNumber(srcSprite, true, true, 0, item.value, dstRect);
            break;
        case core::Inventory::Item::Type::BOMBS:
            drawNumber(srcSprite, false, true, 1, m_inventoryImpl.bombs(), dstRect);
            break;
        case core::Inventory::Item::Type::BOW:
            drawNumber(srcSprite, false, true, 1, m_inventoryImpl.arrows(), dstRect);
            break;
        case core::Inventory::Item::Type::MAGIC_POWDER:
            drawNumber(srcSprite, false, true, 1, m_inventoryImpl.magicPowder(), dstRect);
            break;
        case core::Inventory::Item::Type::OCARINA:
            drawNumber(srcSprite, false, true, 0, m_inventoryImpl.ocarinaSongs().size(), dstRect);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void Inventory::moveSelector(engine::Direction direction)
{
    switch (direction)
    {
    case engine::Direction::DOWN:  m_inventoryImpl.moveInventorySelector<engine::Direction::DOWN>();  break;
    case engine::Direction::UP:    m_inventoryImpl.moveInventorySelector<engine::Direction::UP>();    break;
    case engine::Direction::RIGHT: m_inventoryImpl.moveInventorySelector<engine::Direction::RIGHT>(); break;
    case engine::Direction::LEFT:  m_inventoryImpl.moveInventorySelector<engine::Direction::LEFT>();  break;
    default: std::unreachable();
    }

    switch (direction)
    {
    case engine::Direction::DOWN:
        if (m_selectorY == SELECTOR_INITIAL_Y + (core::Inventory::MAX_ROWS - 1) * SELECTOR_INCREASE_Y)
        {
            if (m_selectorX == SELECTOR_INITIAL_X + SELECTOR_INCREASE_X)
            {
                m_selectorX -= SELECTOR_INCREASE_X;
            }
            m_selectorY = SELECTOR_INITIAL_Y;
        }
        else
        {
            m_selectorY += SELECTOR_INCREASE_Y;
            // Change by 2 because of the way we index the array (see above)
        }
        break;
    case engine::Direction::UP:
        if (m_selectorY == SELECTOR_INITIAL_Y)
        {
            if (m_selectorX == SELECTOR_INITIAL_X)
            {
                m_selectorX += SELECTOR_INCREASE_X;
            }
            m_selectorY = SELECTOR_INITIAL_Y + (core::Inventory::MAX_ROWS - 1) * SELECTOR_INCREASE_Y;
        }
        else
        {
            m_selectorY -= SELECTOR_INCREASE_Y;
        }
        break;
    case engine::Direction::RIGHT:
        if (m_selectorX == SELECTOR_INITIAL_X + SELECTOR_INCREASE_X)
        {
            m_selectorX = SELECTOR_INITIAL_X;
            // If not the bottom right of the inventory
            if (m_selectorY != SELECTOR_INITIAL_Y + (core::Inventory::MAX_ROWS - 1) * SELECTOR_INCREASE_Y)
            {
                m_selectorY += SELECTOR_INCREASE_Y;
            }
            else
            {
                m_selectorY = SELECTOR_INITIAL_Y;
            }
        }
        else
        {
            m_selectorX += SELECTOR_INCREASE_X;
        }
        break;
    case engine::Direction::LEFT:
        if (m_selectorX == SELECTOR_INITIAL_X)
        {
            m_selectorX = SELECTOR_INITIAL_X + SELECTOR_INCREASE_X;
            // If not the top left of the inventory
            if (m_selectorY != SELECTOR_INITIAL_Y)
            {
                m_selectorY -= SELECTOR_INCREASE_Y;
            }
            else
            {
                m_selectorY = SELECTOR_INITIAL_Y + (core::Inventory::MAX_ROWS - 1) * SELECTOR_INCREASE_Y;
            }
        }
        else
        {
            m_selectorX -= SELECTOR_INCREASE_X;
        }
        break;
    default:
        break;
    }
}

} // namespace zelda::gui