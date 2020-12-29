#include "Worldmap.h"
#include "Common.h"
#include "Drawing.h"
#include "Dialogue.h"

Zelda::Worldmap::Worldmap() : 
    m_scopeX(WORLDMAP_INITIAL_POS_X), 
    m_scopeY(WORLDMAP_INITIAL_POS_Y), 
    m_show(false), 
    m_scopeSelect(false),
    m_worldX(WORLDMAP_INITIAL_POS_X),
    m_worldY(WORLDMAP_INITIAL_POS_Y)
{
    m_texture = ResourceManager::getInstance()[Graphic::GFX_WORLD_MAP];
    m_name = "Worldmap";
    m_controllableName = m_name;
    m_depth = ZD_DEPTH_INVENTORY;

    ZD_ASSERT(SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height) == 0, "SDL Error: " << SDL_GetError());
    Renderer::getInstance().addRenderable(this);
}

void Zelda::Worldmap::control() noexcept
{
    // TODO: Fix key press overlaps between inventory and worldmap
    if (Keyboard::getInstance().keyPressed(BUTTON_SELECT))
    {
        close();
        Controller::getInstance().popController();
        Engine::getInstance().pause(false);
        std::cout << "Worldmap closed!\n";
    }

    // Move scope around map if the area is visited
    if (Keyboard::getInstance().keyPressed(BUTTON_RIGHT))
    {
        if (m_scopeX+1 < WORLDMAP_MAX_X && m_worldmapLocation[m_scopeX+1][m_scopeY].visited)
        {
            m_scopeX++;
        }
    }
    if (Keyboard::getInstance().keyPressed(BUTTON_LEFT))
    {
        if (m_scopeX - 1 >= 0 &&  m_worldmapLocation[m_scopeX-1][m_scopeY].visited)
        {
            m_scopeX--;
        }
    }
    if (Keyboard::getInstance().keyPressed(BUTTON_UP))
    {
        if (m_scopeY - 1 >= 0 && m_worldmapLocation[m_scopeX][m_scopeY - 1].visited)
        {
            m_scopeY--;
        }
    }
    if (Keyboard::getInstance().keyPressed(BUTTON_DOWN))
    {
        if (m_scopeY + 1 < WORLDMAP_MAX_Y && m_worldmapLocation[m_scopeX][m_scopeY+1].visited)
        {
            m_scopeY++;
        }
    }

    // Display location name if any
    if (Keyboard::getInstance().keyPressed(BUTTON_B))
    {
        // Display location name above/below scope
        float yPos = (WORLDMAP_START_Y + m_scopeY * 8) - 10;
        switch (m_worldmapLocation[m_scopeX][m_scopeY].locationName)
        {
        case LN_MYSTERIOUS_WOODS:
            Dialogue::getInstance().message("Mysterious Woods", yPos);
            break;
        }
    }
}

void Zelda::Worldmap::render(SDL_Renderer* renderer) noexcept
{
    if (m_show)
    {
        SDL_Rect dstRect;

        auto target = pushRenderingTarget(renderer, m_texture);

        for (int y = 0; y < WORLDMAP_MAX_Y; y++)
        {
            for (int x = 0; x < WORLDMAP_MAX_X; x++)
            {
                // If the location isn't visited then mark it as an unvisited square
                WorldmapLocation wml = m_worldmapLocation[x][y];
                if (!wml.visited)
                {
                    SDL_Rect srcRect = m_worldmapSrcSprites[WORLDMAP_AREA_UNVISITED];
                    dstRect = { WORLDMAP_START_X + x * 8, WORLDMAP_START_Y + y * 8, 7,7 };
                    ZD_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect) == 0, "SDL Error: " << SDL_GetError());
                }
            }
        }

        popRenderingTarget(renderer, target);

        // Render the worldmap
        dstRect = { 0, 0, m_width, m_height };
        ZD_ASSERT(SDL_RenderCopy(renderer, m_texture, nullptr, &dstRect) == 0, "SDL Error: " << SDL_GetError());

        // TODO: Animate properly
        // Draw current world location marker
        SDL_Rect srcRect = m_worldmapSrcSprites[WORLDMAP_AREA_LOCATION];
        dstRect = { (WORLDMAP_START_X + m_worldX * 8) - 1, (WORLDMAP_START_Y + m_worldY * 8) - 1, 8,8 };
        ZD_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect) == 0, "SDL Error: " << SDL_GetError());

        // Draw the location if we hit upon one
        if (m_worldmapLocation[m_scopeX][m_scopeY].locationType != LT_NONE)
        {
            SDL_Rect srcRectLocation;
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
            // TODO: Place in right place
            // Depends on whether the scope is in one of four quarters on the map it seems

            dstRect = { 100,100, 30,30 };
            ZD_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRectLocation, &dstRect) == 0, "SDL Error: " << SDL_GetError());
        }

        // Draw the "scope" we use to move around
        srcRect = m_worldmapSrcSprites[WORLDMAP_AREA_SCOPE];
        dstRect = { (WORLDMAP_START_X + m_scopeX * 8) - 5, (WORLDMAP_START_Y + m_scopeY * 8) - 5 , 16, 16 };
        ZD_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect) == 0, "SDL Error: " << SDL_GetError());
   

        toggleItem(m_scopeSelect, m_scopeSelectTimer, WORLDMAP_SELECTOR_FPS);

        if (m_scopeSelect)
        {
            // Draw the flashing arrows
            srcRect = m_worldmapSrcSprites[WORLDMAP_AREA_ARROW];
            dstRect.w = 9;
            dstRect.h = 8;
            dstRect.x += 4;
            dstRect.y -= 10;
            // Up arrow
            ZD_ASSERT(SDL_RenderCopy(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect) == 0, "SDL Error: " << SDL_GetError());
            // Right arrow
            dstRect.x += 15;
            dstRect.y += 14;
            ZD_ASSERT(SDL_RenderCopyEx(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect, 90, nullptr, SDL_RendererFlip::SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());
            // Down arrow
            dstRect.x -= 15;
            dstRect.y += 15;
            ZD_ASSERT(SDL_RenderCopyEx(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect, 180, nullptr, SDL_RendererFlip::SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());
            // Left arrow
            dstRect.x -= 15;
            dstRect.y -= 15;
            ZD_ASSERT(SDL_RenderCopyEx(renderer, ResourceManager::getInstance()[Graphic::GFX_INVENTORY], &srcRect, &dstRect, 270, nullptr, SDL_RendererFlip::SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());

        }
    }
}

void Zelda::Worldmap::open() noexcept
{
    m_show = true;
}

void Zelda::Worldmap::close() noexcept
{
    m_show = false;
}
