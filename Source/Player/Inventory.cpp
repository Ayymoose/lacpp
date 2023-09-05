#include "Inventory.h"
#include "Renderer.h"
#include "Depth.h"
#include "Keyboard.h"
#include "InputControl.h"
#include "Controller.h"
#include "Link.h"
#include "Engine.h"
#include "ResourceManager.h"
//#include "Toggle.h"

namespace Zelda
{
    Inventory::Inventory() : 
        IRenderable("Inventory", Sprite(Renderer::getInstance().getRenderer(), INVENTORY_WIDTH, INVENTORY_HEIGHT), ZD_DEPTH_INVENTORY),
        Controllable(m_name),
        m_subscreen(std::make_unique<Sprite>(Renderer::getInstance().getRenderer(), SELECT_SUBSCREEN_WIDTH, SELECT_SUBSCREEN_HEIGHT)),
        m_open(false),
        m_selectorX(SELECTOR_INITIAL_X),
        m_selectorY(SELECTOR_INITIAL_Y),
        m_flashSelector(false),
        m_flashSelect(false),
        m_selectPressed(false)
    {
        // Select sub screen
        assert(m_subscreen->data());
        // m_texture is the main texture we draw ontoas
        assert(m_sprite->data());
        Rect<int> srcRect = { 0,0, m_subscreen->width(), m_subscreen->height() };
        m_subscreen->colourSprite(srcRect, makeRGB(0, 0, 0));

        // 7 -> 39 x increases of 32
        // 27 -> 50 y increases by 23

        // Initialise inventory

        Renderer::getInstance().addRenderable(this);
    }

    void Inventory::control()
    {
        if (Keyboard::getInstance().keyPressed(BUTTON_A))
        {
            m_inventoryImpl.swapItemA();
        }
        if (Keyboard::getInstance().keyPressed(BUTTON_B))
        {
            m_inventoryImpl.swapItemB();
        }

        // Show the subscreen only when the select key is pushed
        // TODO: Transition it in
        if (Keyboard::getInstance().keyPushed(BUTTON_SELECT))
        {
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
            moveSelector(Direction::DIRECTION_RIGHT);
        }
        if (Keyboard::getInstance().keyPressed(BUTTON_LEFT))
        {
            moveSelector(Direction::DIRECTION_LEFT);
        }
        if (Keyboard::getInstance().keyPressed(BUTTON_UP))
        {
            moveSelector(Direction::DIRECTION_UP);
        }
        if (Keyboard::getInstance().keyPressed(BUTTON_DOWN))
        {
            moveSelector(Direction::DIRECTION_DOWN);
        }

        // If any select keys pressed, reset the flashing animation
        if (Keyboard::getInstance().keyPushed(BUTTON_RIGHT) ||
            Keyboard::getInstance().keyPushed(BUTTON_LEFT) ||
            Keyboard::getInstance().keyPushed(BUTTON_DOWN) ||
            Keyboard::getInstance().keyPushed(BUTTON_UP))
        {
            m_flashSelector = true;
        }

        if (Keyboard::getInstance().keyReleased(BUTTON_SELECT))
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
            if (m_inventoryImpl.getInDungeon())
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
    {
    }

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


        Rect<int> srcRect, dstRect;

        // Draw current location grid arrow
        //auto srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW];
        //auto dstRect = m_inventorySpritesDst[INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW];

        switch (m_inventoryImpl.dungeon())
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
            default:
                assert(false);
        }

        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

        // Draw dungeon map level
        Rect<int> dstRectMapLevel = {72,64,8,8};
        drawNumber(*m_sprite, true, true, 0, static_cast<int>(m_inventoryImpl.dungeon()), dstRectMapLevel);

        // Draw the dungeon map
    
        // Without a map, all the paths are not drawn
        // Unvisited areas are marked with a grey block
        for (int x = 0; x < DUNGEON_MAX_BLOCKS_X; ++x)
        {
            for (int y = 0; y < DUNGEON_MAX_BLOCKS_Y; ++y)
            {
                // Don't display anything if dungeon map not present
                if (m_inventoryImpl.dungeonItem(DungeonItem::DUNGEON_ITEM_MAP))
                {
                    // Show the room in the map if we visited it already
                    if (m_inventoryImpl.dungeonMapLocationVisited(x,y))
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
                        if (m_inventoryImpl.dungeonMapLocationVisited(x, y) > 1)
                        {
                            // Display a "unvisited" square
                            //srcRect = m_inventorySpritesSrc[INVENTORY_AREA_UNVISITED];
                            //dstRect = m_inventorySpritesDst[INVENTORY_AREA_UNVISITED];
                        }
                        else if (m_inventoryImpl.dungeonMapLocationVisited(x, y) == 1)
                        {
                            continue;
                        }
                        else
                        {
                            //srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EMPTY];
                            //dstRect = m_inventorySpritesDst[INVENTORY_AREA_EMPTY];
                        }

                    }
                }
                else
                {
                    // Add empty square
                    if (m_inventoryImpl.dungeonMapLocationVisited(x, y) != 1)
                    {
                        //srcRect = m_inventorySpritesSrc[INVENTORY_AREA_EMPTY];
                        //dstRect = m_inventorySpritesDst[INVENTORY_AREA_EMPTY];
                    }
                }

                // If we have the compass, show the nightmare and treasure chests
                if (m_inventoryImpl.dungeonItem(DungeonItem::DUNGEON_ITEM_COMPASS))
                {
                    if (m_inventoryImpl.dungeonMapLocationRoomItem(x, y) == DungeonMapItem::DUNGEON_MAP_ITEM_NIGHTMARE_KEY)
                    {
                        //srcRect = m_inventorySpritesSrc[INVENTORY_AREA_NIGHTMARE];
                        //dstRect = m_inventorySpritesDst[INVENTORY_AREA_NIGHTMARE];
                    }
                    else if (m_inventoryImpl.dungeonMapLocationRoomItem(x, y) == DungeonMapItem::DUNGEON_MAP_ITEM_CHEST_CLOSED)
                    {
                        //srcRect = m_inventorySpritesSrc[INVENTORY_AREA_TREASURE];
                        //dstRect = m_inventorySpritesDst[INVENTORY_AREA_TREASURE];
                    }
                }

                dstRect.x += x * srcRect.w;
                dstRect.y += y * srcRect.w;

                ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

                auto const dungeonPosition = m_inventoryImpl.dungeonMapPositionLocation();
                // Draw current location flashing
                if (dungeonPosition.x == x && dungeonPosition.y == y)
                {
                    //srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_MAP_CURRENT_LOCATION];
                    //basicAnimate(Renderer::getInstance().getRenderer(), *ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY], srcRect, dstRect, 2, 0, 2, INSTRUMENT_FPS, Engine::getInstance().paused());
                }

            }
        }

    }

    void Inventory::drawSelectStatus()
    {
        Rect<int> srcRect, dstRect;

        // Draw two red arrows
        //srcRect = m_inventorySpritesSrc[INVENTORY_RED_ARROW];
        //dstRect = m_inventorySpritesDst[INVENTORY_RED_ARROW];

        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

        dstRect.x += 73;
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

        //srcRect = m_inventorySpritesSrc[INVENTORY_PUSH_SELECT];
        //dstRect = m_inventorySpritesDst[INVENTORY_PUSH_SELECT];

        //toggleItem(m_flashSelect, m_pushSelectTimer, PUSH_SELECTOR_FPS);

        // Draw "PUSH SELECT"
        if (m_flashSelect)
        {
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }
    }

    void Inventory::drawMiscItems()
    {
        Rect<int> srcRect, dstRect;

        if (m_inventoryImpl.miscItemExists(InventoryMiscItem::INVENTORY_MISC_ITEM_FLIPPERS))
        {
            //srcRect = m_inventorySpritesSrc[INVENTORY_FLIPPERS];
            //dstRect = m_inventorySpritesDst[INVENTORY_FLIPPERS];
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }

        if (m_inventoryImpl.miscItemExists(InventoryMiscItem::INVENTORY_MISC_ITEM_RED_POTION))
        {
            //srcRect = m_inventorySpritesSrc[INVENTORY_POTION];
            //dstRect = m_inventorySpritesDst[INVENTORY_POTION];
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }

        // Draw number of seashells
        //srcRect = m_inventorySpritesSrc[INVENTORY_SEASHELLS];
        //dstRect = m_inventorySpritesDst[INVENTORY_SEASHELLS];
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

        dstRect.w = 8; dstRect.h = 8;
        dstRect.x += dstRect.w; dstRect.y += dstRect.h;
        drawNumber(*m_sprite, false, true, 1, m_inventoryImpl.secretSeaShells(), dstRect);

        // Draw currently traded item (if any)
        if (m_inventoryImpl.tradedItem() != TradeItem::TRADE_ITEM_NONE)
        {
            //srcRect = m_inventorySpritesSrc[TRADE_ITEM_SPRITE(m_tradeItem)];
            //dstRect = m_inventorySpritesDst[TRADE_ITEM_SPRITE(m_tradeItem)];
            //ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }
    }

    void Inventory::drawInventoryItems()
    {
        // Depending on whether we are in a dungeon or not,
        // draws the inventory items or the dungeon items

        Rect<int> srcRect, dstRect;

        // Draw any keys we have
        if (m_inventoryImpl.dungeonEntranceKey(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_TAIL))
        {
            //srcRect = m_inventorySpritesSrc[INVENTORY_TAIL_KEY];
            //dstRect = m_inventorySpritesDst[INVENTORY_TAIL_KEY];
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }

        if (m_inventoryImpl.dungeonEntranceKey(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_SLIME))
        {
            //srcRect = m_inventorySpritesSrc[INVENTORY_SLIME_KEY];
            //dstRect = m_inventorySpritesDst[INVENTORY_SLIME_KEY];
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }

        if (m_inventoryImpl.dungeonEntranceKey(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_ANGLER))
        {
            //srcRect = m_inventorySpritesSrc[INVENTORY_ANGLER_KEY];
            //dstRect = m_inventorySpritesDst[INVENTORY_ANGLER_KEY];
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }
    
        if (m_inventoryImpl.dungeonEntranceKey(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_FACE))
        {
            //srcRect = m_inventorySpritesSrc[INVENTORY_FACE_KEY];
            //dstRect = m_inventorySpritesDst[INVENTORY_FACE_KEY];
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }

        if (m_inventoryImpl.dungeonEntranceKey(DungeonEntranceKey::DUNGEON_ENTRACE_KEY_BIRD))
        {
            //srcRect = m_inventorySpritesSrc[INVENTORY_BIRD_KEY];
            //dstRect = m_inventorySpritesDst[INVENTORY_BIRD_KEY];
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }

        drawInstruments();
    }

    void Inventory::drawDungeonItems()
    {
        Rect<int> srcRect, dstRect;

        if (m_inventoryImpl.dungeonItem(DungeonItem::DUNGEON_ITEM_COMPASS))
        {
            //srcRect = m_inventorySpritesSrc[INVENTORY_COMPASS];
            //dstRect = m_inventorySpritesDst[INVENTORY_COMPASS];
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }

        if (m_inventoryImpl.dungeonItem(DungeonItem::DUNGEON_ITEM_NIGHTMARE_KEY))
        {
            //srcRect = m_inventorySpritesSrc[INVENTORY_NIGHTMARE_KEY];
            //dstRect = m_inventorySpritesDst[INVENTORY_NIGHTMARE_KEY];
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }

        if (m_inventoryImpl.dungeonItem(DungeonItem::DUNGEON_ITEM_OWL_BEAK))
        {
            //srcRect = m_inventorySpritesSrc[INVENTORY_OWL_BEAK];
            //dstRect = m_inventorySpritesDst[INVENTORY_OWL_BEAK];
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }

        if (m_inventoryImpl.dungeonItem(DungeonItem::DUNGEON_ITEM_MAP))
        {
            //srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_MAP];
            //dstRect = m_inventorySpritesDst[INVENTORY_DUNGEON_MAP];
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }

        // Draw the dungeon map
        drawDungeonMap();

        // Draw dungeon keys
        //srcRect = m_inventorySpritesSrc[INVENTORY_DUNGEON_KEY];
        //dstRect = m_inventorySpritesDst[INVENTORY_DUNGEON_KEY];
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
    
        dstRect.w = 8; dstRect.h = 8;
        dstRect.x += dstRect.w; dstRect.y += dstRect.h;
        drawNumber(*m_sprite, false, true, 0, m_inventoryImpl.dungeonItem(DungeonItem::DUNGEON_ITEM_LOCKED_DOOR_KEY), dstRect);
    }

    void Inventory::drawInstruments()
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

        auto const instruments = m_inventoryImpl.instruments();

        for (int i = 0; i < instruments.size(); ++i)
        {
            switch (instruments[i])
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
                    //basicAnimate(Renderer::getInstance().getRenderer(), *ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY], srcRect, dstRect, 0, 0, INSTRUMENTS_FRAME, INSTRUMENT_FPS, Engine::getInstance().paused());
                    break;
                default:
                    // If we don't have the instrument yet
                    //srcRect = m_inventorySpritesSrc[INVENTORY_INSTRUMENT_BACK_0];
                    //dstRect = m_inventorySpritesDst[INVENTORY_INSTRUMENT_BACK_0 + i - 1];
                    ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        
                    dstRect.x += 8; dstRect.y += 8; dstRect.w = 8; dstRect.h = 8;
                    drawNumber(*m_sprite, false, true, 0, i, dstRect);
                    break;
            }
        }
    }

    void Inventory::drawHealth()
    {
        auto const currentHeartPieces = m_inventoryImpl.heartPieces();
        auto const maxHeartPieces = m_inventoryImpl.maxHeartPieces();
        auto const halfHearts = currentHeartPieces - static_cast<int>(currentHeartPieces);

        auto const wholeHearts = static_cast<int>(currentHeartPieces);
        auto const emptyHearts = (currentHeartPieces - static_cast<int>(currentHeartPieces) > 0 ? maxHeartPieces - std::ceil(currentHeartPieces) : maxHeartPieces - wholeHearts);

        Rect<int> srcRect, dstRect;

        //auto srcRect = m_inventorySpritesSrc[INVENTORY_HEART_WHOLE];
        //auto dstRect = m_inventorySpritesDst[INVENTORY_HEART_WHOLE];
        
        int drawnHearts = 0;

        auto drawHeart = [&]()
        {
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
            dstRect.x += srcRect.w;

            // Append to new row of hearts
            drawnHearts++;
            if (drawnHearts == HEARTS_PER_ROW)
            {
                dstRect.y += srcRect.h;
                //dstRect.x = m_inventorySpritesDst[INVENTORY_HEART_WHOLE].x;
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
        Rect<int> srcRect, dstRect;

        // Instead of creating an object for each item we have
        // We just render the items we have to a single texture
        // and render that instead
        auto const currentRenderingTarget = Renderer::getInstance().pushRenderingTarget(*m_sprite);
        auto const inventoryItems = m_inventoryImpl.inventoryItems();

        for (int i = 0; i < inventoryItems.size(); ++i)
        {
            if (inventoryItems[i] != InventoryItem{})
            {
                //srcRect = inventoryWeaponSpriteSrc(m_weaponItems[i]);

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
                ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
            }
        }

        Renderer::getInstance().popRenderingTarget(currentRenderingTarget);

        for (int i = 0; i < inventoryItems.size(); ++i)
        {
            if (inventoryItems[i] != InventoryItem{})
            {
                dstRect =
                {
                    WEAPON_LEVEL_X + ((((i & 1) == 1) ? 1 : 0) * WEAPON_LEVEL_SPACING_X),
                    WEAPON_LEVEL_Y + ((i / 2) * WEAPON_LEVEL_SPACING_Y),
                    WEAPON_LEVEL_WIDTH,
                    WEAPON_LEVEL_HEIGHT
                };

                drawInventoryItemAttribute(*m_sprite, inventoryItems[i], dstRect);
            }
        }
  

    }

    void Inventory::drawSelector()
    {
        auto const currentRenderingTarget = Renderer::getInstance().pushRenderingTarget(*m_sprite);

        Rect<int> srcRect, dstRect;
        // Render the selector

        // Selector animation
        //toggleItem(m_flashSelector, m_selectorTimer, INVENTORY_SELECTOR_FPS);

        if (m_flashSelector)
        {
            //srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_1];
            dstRect = { m_selectorX, m_selectorY, srcRect.w , srcRect.h };
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }
        Renderer::getInstance().popRenderingTarget(currentRenderingTarget);

    }

    void Inventory::drawInventoryDividers()
    {
        Rect<int> srcRect, dstRect;
        auto const currentRenderingTarget = Renderer::getInstance().pushRenderingTarget(*m_sprite);

        //srcRect = m_inventorySpritesSrc[INVENTORY_DIVIDER_H];

        // Draw horizontal divider
        for (int i = 0; i < (INVENTORY_WIDTH / INVENTORY_DIVIDER_WIDTH_H)-2; ++i)
        {
            dstRect = 
            {
                INVENTORY_DIVIDER_XH + i + INVENTORY_DIVIDER_WIDTH_H * i,
                INVENTORY_DIVIDER_YH,
                INVENTORY_DIVIDER_WIDTH_H,
                INVENTORY_DIVIDER_HEIGHT_H
            };
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }
        //srcRect = m_inventorySpritesSrc[INVENTORY_DIVIDER_V];
        // Draw vertical divider
        for (int i = 0; i < ((INVENTORY_HEIGHT - INVENTORY_DIVIDER_YV) / INVENTORY_DIVIDER_WIDTH_V); ++i)
        {
            dstRect =
            {
                INVENTORY_DIVIDER_XV ,
                INVENTORY_DIVIDER_YV + i + INVENTORY_DIVIDER_HEIGHT_V * i,
                INVENTORY_DIVIDER_WIDTH_V,
                INVENTORY_DIVIDER_HEIGHT_V
            };
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
        }

        Renderer::getInstance().popRenderingTarget(currentRenderingTarget);
    }

    void Inventory::drawHUD() 
    {
        auto const currentRenderingTarget = Renderer::getInstance().pushRenderingTarget(*m_sprite);
        Rect<int> srcRect, dstRect;

        // Copy "B" 
        //srcRect = m_inventorySpritesSrc[INVENTORY_B_BUTTON];
        //dstRect = m_inventorySpritesDst[INVENTORY_B_BUTTON];
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

        // Copy "A"
        //srcRect = m_inventorySpritesSrc[INVENTORY_A_BUTTON];
        //dstRect = m_inventorySpritesDst[INVENTORY_A_BUTTON];
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

        // Copy selector
        //srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_1];
        //dstRect = m_inventorySpritesDst[INVENTORY_SELECTOR_BUTTON_1];
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

        //srcRect = m_inventorySpritesSrc[INVENTORY_SELECTOR_BUTTON_2];
        //dstRect = m_inventorySpritesDst[INVENTORY_SELECTOR_BUTTON_2];
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

        // Ruppee icon
        //srcRect = m_inventorySpritesSrc[INVENTORY_RUPPEE];
        //dstRect = m_inventorySpritesDst[INVENTORY_RUPPEE];
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

        // Draw health
        drawHealth();

        // Draw weapon A
        if (m_inventoryImpl.itemA() != InventoryItem{})
        {
            // Draw the actual weapon
            //srcRect = inventoryWeaponSpriteSrc(m_weaponA);
            dstRect = {48,0, srcRect.w, srcRect.h };
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

            // Draw the weapon level
            dstRect = { 56,8, 8, 8 };
            drawInventoryItemAttribute(*m_sprite, m_inventoryImpl.itemA(), dstRect);
        }

        // Draw weapon B
        if (m_inventoryImpl.itemB() != InventoryItem{})
        {
            //srcRect = inventoryWeaponSpriteSrc(m_weaponB);
            dstRect = { 8,0, srcRect.w, srcRect.h };
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

            dstRect = { 16,8, 8, 8 };
            drawInventoryItemAttribute(*m_sprite, m_inventoryImpl.itemB(), dstRect);
        }

        // Draw current ruppees
        dstRect = { 80,8,8,8 };
        drawNumber(*m_sprite, false, true, 2, m_inventoryImpl.rupees(), dstRect);

        // Pop rendering target
        Renderer::getInstance().popRenderingTarget(currentRenderingTarget);

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
            renderY = CAMERA_HEIGHT;
        }

        // Render the inventory background
        m_sprite->drawSprite(Rect<int>{}, Rect<int>{0, renderY, m_sprite->width(), m_sprite->height()});
        m_sprite->colourSprite(Rect<int>{}, makeRGB(INVENTORY_R, INVENTORY_G, INVENTORY_B));
    }

    void Inventory::drawSubscreen() const
    {
        Rect<int> dstRect; // = m_inventorySpritesDst[INVENTORY_SUBSCREEN];
        Rect<int> srcRect = { 0,0,dstRect.w, dstRect.h };
        m_subscreen->drawSprite(srcRect, dstRect);
        auto currentRenderingTarget = Renderer::getInstance().pushRenderingTarget(*m_subscreen);

        // Tunic
        //srcRect = m_inventorySpritesSrc[INVENTORY_TUNIC];
        switch (m_inventoryImpl.tunic())
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

        //dstRect = m_inventorySpritesDst[INVENTORY_TUNIC];
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

        // Heart pieces
        //srcRect = m_inventorySpritesSrc[INVENTORY_HEART_PIECES];
        //dstRect = m_inventorySpritesDst[INVENTORY_HEART_PIECES];

        srcRect.x += (m_inventoryImpl.heartPieces() * (srcRect.w + 2));
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

        // Photographs
        //srcRect = m_inventorySpritesSrc[INVENTORY_PHOTOGRAPHS];
        //dstRect = m_inventorySpritesDst[INVENTORY_PHOTOGRAPHS];
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

        // Inventory "/"
        //srcRect = m_inventorySpritesSrc[INVENTORY_SLASH];
        //dstRect = m_inventorySpritesDst[INVENTORY_SLASH];
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);
    
        dstRect.x = 64; dstRect.y = 8;
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, dstRect);

        // Draw how many heart pieces we have (out of 4)
        dstRect = { 56,7,8,8 };
        drawNumber(*m_subscreen, false, false, 0, m_inventoryImpl.heartPieces(), dstRect);
        dstRect = { 72,7,8,8 };
        drawNumber(*m_subscreen, false, false, 0, m_inventoryImpl.maxHeartPieces(), dstRect);

        // Draw number of photographs
        dstRect = { 24,23,8,8 };
        drawNumber(*m_subscreen, false, false, 1, m_inventoryImpl.photograph(), dstRect);
        dstRect = { 48,23,8,8 };
        drawNumber(*m_subscreen, false, false, 1, MAX_PHOTOGRAPHS, dstRect);

        // Remember! This resets the drawing target to the screen
        Renderer::getInstance().popRenderingTarget(currentRenderingTarget);
    }

    // Draw a number or level onto a texture
    // examples
    // 2
    // L-1 L-2
    // 09
    // 320

    // TODO: These drawNumber and drawWeaponLevel functions are used in the shop too so must be moved elsewhere
    void Inventory::drawNumber(const Sprite& srcSprite, bool drawLevel, bool useNormalFont, int trailingDigits, int number, const Rect<int>& dstRect) const
    {
        // drawLevel      = Draw the "L-" text next to the number
        // useNormalFont  = Use the normal digit text or text with black background
        // trailingDigits = Number of trailing digits to append to the LHS of the number (e.g 1 01 001)

        assert(number >= 0);
        assert(trailingDigits >= 0);
        assert(dstRect != Rect<int>());

        // Save the current renderering target
        auto const currentRenderingTarget = Renderer::getInstance().pushRenderingTarget(srcSprite);

        Rect<int> srcRect;
        auto rectDst = dstRect;

        // Draw level
        if (drawLevel)
        {
            // Draw the "L-"
            //srcRect = m_inventorySpritesSrc[INVENTORY_LEVEL];
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, rectDst);

            if (useNormalFont)
            {
                //srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_W];
            }
            else
            {
                //srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_B];
            }

            srcRect.x += 2 * number + srcRect.w * number;
            rectDst.x += srcRect.w;
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, rectDst);
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
                //srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_W];
            }
            else
            {
                //srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_B];
            }

            // Add any trailing digits if needed in front of the number
            for (int i = 0; i < (number == 0 ? trailingDigits : trailingDigits+1 - numberLength); i++)
            {
                ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, rectDst);
                rectDst.x += srcRect.w;
            }

            // Just draw a standard number with or without trailing digits
            do
            {

                if (useNormalFont)
                {
                    //srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_W];
                }
                else
                {
                    //srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_B];
                }

                srcRect.x += 2 * (number % 10) + srcRect.w * (number % 10);
                ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, rectDst);
                rectDst.x += srcRect.w;
                number /= 10;
            } while (number != 0);

            if (useNormalFont)
            {
                //srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_W];
            }
            else
            {
                //srcRect = m_inventorySpritesSrc[INVENTORY_DIGIT_B];
            }

            // Draw any reversed number whose 0 was lost
            for (int i = 0; i < trailingZeros; i++)
            {
                ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRect, rectDst);
                rectDst.x += srcRect.w;
            }
        }
        // Restore "pop" the target backk
        Renderer::getInstance().popRenderingTarget(currentRenderingTarget);
    }

    void Inventory::drawInventoryItemAttribute(const Sprite& srcSprite, const InventoryItem& item, const Rect<int>& dstRect)
    {
        switch (item.itemAttribute)
        {
        case ItemAttribute::ITEM_ATTRIBUTE_LEVEL:
            switch (item.usuableItem)
            {
                case UsableItem::USABLE_ITEM_SHIELD:
                case UsableItem::USABLE_ITEM_SWORD:
                case UsableItem::USABLE_ITEM_POWER_BRACELET:
                    drawNumber(srcSprite, true, true, 0, item.value, dstRect);
                    break;
                case UsableItem::USABLE_ITEM_BOMBS:
                    drawNumber(srcSprite, false, true, 1, m_inventoryImpl.bombs(), dstRect);
                    break;
                case UsableItem::USABLE_ITEM_BOW:
                    drawNumber(srcSprite, false, true, 1, m_inventoryImpl.arrows(), dstRect);
                    break;
                case UsableItem::USABLE_ITEM_MAGIC_POWDER:
                    drawNumber(srcSprite, false, true, 1, m_inventoryImpl.magicPowder(), dstRect);
                    break;
                case UsableItem::USABLE_ITEM_OCARINA:
                    drawNumber(srcSprite, false, true, 0, m_inventoryImpl.ocarinaSongs().size(), dstRect);
                    break;
            }
            break;
        }
    }

    void Inventory::moveSelector(Direction direction)
    {
        m_inventoryImpl.moveSelector(direction);

        switch (direction)
        {
        case Direction::DIRECTION_DOWN:
            if (m_selectorY == SELECTOR_INITIAL_Y + (INVENTORY_ROWS - 1) * SELECTOR_INCREASE_Y)
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
        case Direction::DIRECTION_UP:
            if (m_selectorY == SELECTOR_INITIAL_Y)
            {
                if (m_selectorX == SELECTOR_INITIAL_X)
                {
                    m_selectorX += SELECTOR_INCREASE_X;
                }
                m_selectorY = SELECTOR_INITIAL_Y + (INVENTORY_ROWS - 1) * SELECTOR_INCREASE_Y;
            }
            else
            {
                m_selectorY -= SELECTOR_INCREASE_Y;
            }
            break;
        case Direction::DIRECTION_RIGHT:
            if (m_selectorX == SELECTOR_INITIAL_X + SELECTOR_INCREASE_X)
            {
                m_selectorX = SELECTOR_INITIAL_X;
                // If not the bottom right of the inventory
                if (m_selectorY != SELECTOR_INITIAL_Y + (INVENTORY_ROWS-1) * SELECTOR_INCREASE_Y)
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
        case Direction::DIRECTION_LEFT:
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
                    m_selectorY = SELECTOR_INITIAL_Y + (INVENTORY_ROWS - 1) * SELECTOR_INCREASE_Y;
                }
            }
            else
            {
                m_selectorX -= SELECTOR_INCREASE_X;
            }
            break;
        }
    }

}