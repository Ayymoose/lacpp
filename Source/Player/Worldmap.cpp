#include "Worldmap.h"
#include "Common.h"
#include "Dialogue.h"

namespace Zelda
{

Worldmap::Worldmap() :
    Renderable("Worldmap", *ResourceManager::getInstance()[SpriteResource::SPR_WORLD_MAP], ZD_DEPTH_WORLDMAP),
    Controllable(m_name),
    m_scopeX(WORLDMAP_INITIAL_POS_X),
    m_scopeY(WORLDMAP_INITIAL_POS_Y),
    m_show(false),
    m_scopeSelect(false),
    m_worldX(WORLDMAP_INITIAL_POS_X),
    m_worldY(WORLDMAP_INITIAL_POS_Y)
{
    Renderer::getInstance().addRenderable(this);
}

void Worldmap::control() noexcept
{
    // TODO: Fix key press overlaps between inventory and worldmap
    if (Keyboard::getInstance().keyPressed(BUTTON_SELECT))
    {
        close();
        Controller::getInstance().popController();
        Engine::getInstance().pause(false);
        DEBUG(DBG_INFO, "Worldmap closed!");
    }

    // Move scope around map if the area is visited
    if (Keyboard::getInstance().keyPressed(BUTTON_RIGHT))
    {
        if (m_worldmapLocation[(m_scopeX + 1) % WORLDMAP_MAX_X][m_scopeY].visited)
        {
            m_scopeX = (m_scopeX + 1) % WORLDMAP_MAX_X;
            assert(m_scopeX >= 0 && m_scopeX < WORLDMAP_MAX_X);
        }
    }
    if (Keyboard::getInstance().keyPressed(BUTTON_LEFT))
    {
        if (m_worldmapLocation[(uint8_t)(m_scopeX - 1) % WORLDMAP_MAX_X][m_scopeY].visited)
        {
            m_scopeX = (uint8_t)(m_scopeX - 1) % WORLDMAP_MAX_X;
            assert(m_scopeX >= 0 && m_scopeX < WORLDMAP_MAX_X);
        }
    }
    if (Keyboard::getInstance().keyPressed(BUTTON_UP))
    {
        if (m_worldmapLocation[m_scopeX][(uint8_t)(m_scopeY - 1) % WORLDMAP_MAX_Y].visited)
        {
            m_scopeY = (uint8_t)(m_scopeY - 1) % WORLDMAP_MAX_Y;
            assert(m_scopeY >= 0 && m_scopeY < WORLDMAP_MAX_Y);
        }
    }
    if (Keyboard::getInstance().keyPressed(BUTTON_DOWN))
    {
        if (m_worldmapLocation[m_scopeX][(uint8_t)(m_scopeY + 1) % WORLDMAP_MAX_Y].visited)
        {
            m_scopeY = (uint8_t)(m_scopeY + 1) % WORLDMAP_MAX_Y;
            assert(m_scopeY >= 0 && m_scopeY < WORLDMAP_MAX_Y);
        }
    }

    // Display location name if any
    if (Keyboard::getInstance().keyPressed(BUTTON_B))
    {
        // Display location name above/below scope
        const float yPos = (WORLDMAP_START_Y + m_scopeY * 8) - 10;
        switch (m_worldmapLocation[m_scopeX][m_scopeY].locationName)
        {
        case LN_TAIL_CAVE:
            Dialogue::getInstance().message("Level 1--       ""     Tail Cave", yPos);
            break;
        case LN_BOTTLE_GROTTO:
            Dialogue::getInstance().message("Level 2--       ""   Bottle Grotto", yPos);
            break;
        case LN_KEY_CAVERN:
            Dialogue::getInstance().message("Level 3--       ""      Key Cavern", yPos);
            break;
        case LN_ANGLER_TUNNEL:
            Dialogue::getInstance().message("Level 4--       "" Angler's Tunnel", yPos);
            break;
        case LN_CATFISH_MAW:
            Dialogue::getInstance().message("Level 5--       ""   Catfish's Maw", yPos);
            break;
        case LN_FACE_SHRINE:
            Dialogue::getInstance().message("Level 6--       ""     Face Shrine", yPos);
            break;
        case LN_EAGLE_TOWER:
            Dialogue::getInstance().message("Level 7--       ""   Eagle's Tower", yPos);
            break;
        case LN_TURTLE_ROCK:
            Dialogue::getInstance().message("Level 8--       ""     Turtle Rock", yPos);
            break;
        case LN_WINDFISH_EGG:
            Dialogue::getInstance().message("Wind Fish's Egg  ", yPos);
            break;
        case LN_SALE_HOUSE_BANANA:
            Dialogue::getInstance().message("Sale's House O' ""    Bananas", yPos);
            break;
        case LN_POTHOLE_FIELD:
            Dialogue::getInstance().message("Pothole Field ", yPos);
            break;
        case LN_HOUSE_BY_THE_BAY:
            Dialogue::getInstance().message("    House By    ""     The Bay ", yPos);
            break;
        case LN_TRENDY_GAME:
            Dialogue::getInstance().message("   Trendy Game ", yPos);
            break;
        case LN_TOWN_TOOL_SHOP:
            Dialogue::getInstance().message("  Town Tool Shop ", yPos);
            break;
        case LN_MARIN_AND_TARIN_HOUSE:
            Dialogue::getInstance().message("Marin and       ""   Tarin's House", yPos);
            break;
        case LN_WITCH_HUT:
            Dialogue::getInstance().message("   Witch's Hut ", yPos);
            break;
        case LN_YARNA_DESERT:
            Dialogue::getInstance().message("  Yarna Desert ", yPos);
            break;
        case LN_UKUKU_PRAIRIE:
            Dialogue::getInstance().message("  Ukuku Prairie ", yPos);
            break;
        case LN_MYSTERIOUS_WOODS:
            Dialogue::getInstance().message("Mysterious Woods ", yPos);
            break;
        case LN_MT_TAMARANCH:
            Dialogue::getInstance().message("  Mt. Tamaranch  ", yPos);
            break;
        case LN_TAL_TAL_MOUNTAIN_RANGE:
            Dialogue::getInstance().message("     Tal Tal    "" Mountain Range ", yPos);
            break;
        case LN_SIGNPOST_MAZE:
            Dialogue::getInstance().message("  Signpost Maze  ", yPos);
            break;
        case LN_MABE_VILLAGE:
            Dialogue::getInstance().message("  Mabe Village   ", yPos);
            break;
        case LN_ANIMAL_VILLAGE:
            Dialogue::getInstance().message(" Animal Village  ", yPos);
            break;
        case LN_CEMETERY:
            Dialogue::getInstance().message("    Cemetery     ", yPos);
            break;
        case LN_RAPIDS_RIDE:
            Dialogue::getInstance().message("   Rapids Ride   ", yPos);
            break;
        case LN_KOHOLINT_PRAIRIE:
            Dialogue::getInstance().message("Koholint Prairie ", yPos);
            break;
        case LN_TORONBO_SHORES:
            Dialogue::getInstance().message(" Toronbo Shores ", yPos);
            break;
        case LN_MARTHA_BAY:
            Dialogue::getInstance().message("  Martha's Bay ", yPos);
            break;
        case LN_EAST_OF_THE_BAY:
            Dialogue::getInstance().message("East of the Bay ", yPos);
            break;
        case LN_GOPONGA_SWAMP:
            Dialogue::getInstance().message("  Goponga Swamp ", yPos);
            break;
        case LN_SHRINE:
            Dialogue::getInstance().message("   Face Shrine  ", yPos);
            break;
        case LN_KANALET_CASTLE:
            Dialogue::getInstance().message(" Kanalet Castle ", yPos);
            break;
        case LN_TAL_TAL_HEIGHTS:
            Dialogue::getInstance().message("Tal Tal Heights ", yPos);
            break;
        case LN_TABAHL_WASTELANDS:
            Dialogue::getInstance().message("Tabahl Wasteland ", yPos);
            break;
        case LN_SOUTH_OF_THE_VILLAGE:
            Dialogue::getInstance().message("  South of the  ""    Village ", yPos);
            break;
        case LN_FISHING_POND:
            Dialogue::getInstance().message("  Fishing Pond   ", yPos);
            break;
        case LN_MADAM_MEOWMEOW_HOUSE:
            Dialogue::getInstance().message("Madam MeowMeow's""     House      "" Beware of Dog! ", yPos);
            break;
        case LN_OLD_MAN_ULRIRA_HOUSE:
            Dialogue::getInstance().message("Old Man Ulrira's""     House      ", yPos);
            break;
        case LN_WEIRD_MR_WRITE:
            Dialogue::getInstance().message("Weird Mr. Write  ", yPos);
            break;
        case LN_CRAZY_TRACY_HOUSE:
            Dialogue::getInstance().message(" Crazy Tracy's  ""  Health Spa ", yPos);
            break;
        case LN_QUADRUPULETS_HOUSE:
            Dialogue::getInstance().message("Quadruplet's    ""      House ", yPos);
            break;
        case LN_DREAM_SHRINE:
            Dialogue::getInstance().message("  Dream Shrine   ", yPos);
            break;
        case LN_TELEPHONE_BOOTH:
            Dialogue::getInstance().message("Telephone Booth ", yPos);
            break;
        case LN_SEASHELL_MANSION:
            Dialogue::getInstance().message("Seashell Mansion ", yPos);
            break;
        case LN_RICHARD_VILLA:
            Dialogue::getInstance().message("Richard's Villa  ", yPos);
            break;
        case LN_HEN_HOUSE:
            Dialogue::getInstance().message("     Hen House   ", yPos);
            break;
        case LN_VILLAGE_LIBRARY:
            Dialogue::getInstance().message("Village Library  ", yPos);
            break;
        case LN_RAFT_SHOP:
            Dialogue::getInstance().message("    Raft Shop    ", yPos);
            break;
        case LN_PHOTO_SHOP:
            Dialogue::getInstance().message("Step right up   ""and get your    ""souvenir photo!", yPos);
            break;
        default:
            assert(false);
        }
    }
}

void Worldmap::render() noexcept
{
    if (m_show)
    {
        auto const target = Renderer::getInstance().pushRenderingTarget(*m_sprite);

        for (int y = 0; y < WORLDMAP_MAX_Y; y++)
        {
            for (int x = 0; x < WORLDMAP_MAX_X; x++)
            {
                // If the location isn't visited then mark it as an unvisited square
                WorldmapLocation wml = m_worldmapLocation[x][y];
                if (!wml.visited)
                {
                    ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(
                        m_worldmapSrcSprites[WORLDMAP_AREA_UNVISITED],
                        Rect<int>{ WORLDMAP_START_X + x * 8, WORLDMAP_START_Y + y * 8, 7, 7 });
                }
            }
        }

        Renderer::getInstance().popRenderingTarget(target);

        // Render the worldmap
        m_sprite->drawSprite(
            Rect<int>{ 0, 0, m_sprite->width(), m_sprite->height()},
            Rect<int>{ 0, 0, m_sprite->width(), m_sprite->height() });

        // Draw the location if we hit upon one
        if (m_worldmapLocation[m_scopeX][m_scopeY].locationType != LT_NONE)
        {
            Rect<int> srcRectLocation;
            switch (m_worldmapLocation[m_scopeX][m_scopeY].locationType)
            {
            case LT_SHOP:
                srcRectLocation = m_worldmapSrcSprites[WORLDMAP_AREA_SHOP];
                break;
            case LT_UNKNOWN:
                srcRectLocation = m_worldmapSrcSprites[WORLDMAP_AREA_UNKNOWN];
                break;
            case LT_DUNGEON:
                srcRectLocation = m_worldmapSrcSprites[WORLDMAP_AREA_DUNGEON];
                break;
            case LT_OWL:
                srcRectLocation = m_worldmapSrcSprites[WORLDMAP_AREA_OWL];
                break;
            default:
                assert(false);
                break;
            }
            // Show the location type which depends on whether the scope is in one of four quarters on the map it seems
            uint8_t sx, sy;

            if (m_scopeX / 8 == 0)
            {
                sx = 105;
            }
            else
            {
                sx = 25;
            }

            if (m_scopeY / 8 == 0)
            {
                sy = 16;
            }
            else
            {
                sy = 97;
            }

            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(srcRectLocation, Rect<int>{ sx, sy, 30, 30 });
        }

        // Draw the "scope" we use to move around
        drawScope();
    }
}

void Worldmap::open() noexcept
{
    m_show = true;
}

void Worldmap::close() noexcept
{
    m_show = false;
}

void Worldmap::drawScope() noexcept
{
    ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(
        m_worldmapSrcSprites[WORLDMAP_AREA_SCOPE],
        Rect<int>{ (WORLDMAP_START_X + m_scopeX * 8) - 5, (WORLDMAP_START_Y + m_scopeY * 8) - 5, 16, 16 });

    toggleItem(m_scopeSelect, m_scopeSelectTimer, WORLDMAP_SELECTOR_FPS);

    if (m_scopeSelect)
    {
        // Draw the flashing arrows
        auto srcRect = m_worldmapSrcSprites[WORLDMAP_AREA_ARROW];
        Rect<int> dstRect = { (WORLDMAP_START_X + m_scopeX * 8) - 5, (WORLDMAP_START_Y + m_scopeY * 8) - 5, 8,8 };
        dstRect.w = 9;
        dstRect.h = 8;
        dstRect.x += 4;
        dstRect.y -= 10;
        // Up arrow
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSpriteEx(srcRect,dstRect, 0, SpriteFlip::FLIP_NONE);
        
        // Right arrow
        dstRect.x += 15;
        dstRect.y += 14;
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSpriteEx(srcRect, dstRect, 90, SpriteFlip::FLIP_NONE);

        // Down arrow
        dstRect.x -= 15;
        dstRect.y += 15;
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSpriteEx(srcRect, dstRect, 180, SpriteFlip::FLIP_NONE);

        // Left arrow
        dstRect.x -= 15;
        dstRect.y -= 15;
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSpriteEx(srcRect, dstRect, 270, SpriteFlip::FLIP_NONE);
    }
}

}