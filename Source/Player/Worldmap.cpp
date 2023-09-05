#include "Worldmap.h"
//#include "Toggle.h"
#include "Dialogue.h"
#include "ResourceManager.h"
#include "Depth.h"
#include "Renderer.h"
#include "InputControl.h"
#include "Keyboard.h"
#include "Controller.h"
#include "Engine.h"

namespace Zelda
{
    Worldmap::Worldmap() :
        IRenderable("Worldmap", *ResourceManager::getInstance()[SpriteResource::SPR_WORLD_MAP], ZD_DEPTH_WORLDMAP),
        Controllable(m_name),
        m_show(false),
        m_scopeSelect(false)
    {
        m_worldMapImpl.setLocation(WORLDMAP_INITIAL_POS_X, WORLDMAP_INITIAL_POS_Y);
        std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
        Renderer::getInstance().addRenderable(this);
    }

    void Worldmap::control()
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
            m_worldMapImpl.moveMarker(Direction::DIRECTION_RIGHT);
            std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
        }
        if (Keyboard::getInstance().keyPressed(BUTTON_LEFT))
        {
            m_worldMapImpl.moveMarker(Direction::DIRECTION_LEFT);
            std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
        }
        if (Keyboard::getInstance().keyPressed(BUTTON_UP))
        {
            m_worldMapImpl.moveMarker(Direction::DIRECTION_UP);
            std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
        }
        if (Keyboard::getInstance().keyPressed(BUTTON_DOWN))
        {
            m_worldMapImpl.moveMarker(Direction::DIRECTION_DOWN);
            std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
        }

        // Display location name if any
        if (Keyboard::getInstance().keyPressed(BUTTON_B))
        {
            // Display location name above/below scope
            Dialogue::getInstance().message(m_worldMapImpl.locationName(), (WORLDMAP_START_Y + m_scopeY * 8) - 10);
        }
    }

    void Worldmap::moveMarker(Direction direction)
    {
        m_worldMapImpl.moveMarker(direction);
        std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
    }

    void Worldmap::setLocation(const int x, const int y)
    {
        m_worldMapImpl.setLocation(x, y);
        std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
    }

    void Worldmap::render()
    {
        if (m_show)
        {
            // Draw the grey squares (if any)
            drawUnvisitedLocations();

            // Render the worldmap
            m_sprite->drawSprite(Rect<int>{},Rect<int>{});
            
            // Draw any location image
            drawLocationImage();

            // Draw the "scope" we use to move around
            drawScope();
        }
    }

    void Worldmap::open()
    {
        m_show = true;
    }

    void Worldmap::close()
    {
        m_show = false;
    }

    void Worldmap::drawUnvisitedLocations() const
    {
        auto const target = Renderer::getInstance().pushRenderingTarget(*m_sprite);
        
        for (int y = 0; y < WORLDMAP_MAX_Y; ++y)
        {
            for (int x = 0; x < WORLDMAP_MAX_X; ++x)
            {
                // If the location isn't visited then mark it as an unvisited square
                if (!m_worldMapImpl.locationVisited(x, y))
                {
                    ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(m_worldmapSrcSprites[WORLDMAP_AREA_UNVISITED],Rect<int>{ WORLDMAP_START_X + x * 8, WORLDMAP_START_Y + y * 8, 7, 7 });
                }
            }
        }

        Renderer::getInstance().popRenderingTarget(target);
    }

    void Worldmap::drawLocationImage() const
    {
        // Draw the location if we hit upon one
        if (m_worldMapImpl.locationType() != LT_NONE)
        {
            Rect<int> srcRectLocation;
            switch (m_worldMapImpl.locationType())
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
    }

    void Worldmap::drawScope() const
    {
        ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSprite(
            m_worldmapSrcSprites[WORLDMAP_AREA_SCOPE],
            Rect<int>{ (WORLDMAP_START_X + m_scopeX * 8) - 5, (WORLDMAP_START_Y + m_scopeY * 8) - 5, 16, 16 });

        // TODO: Animation of scope markers
        // TODO: Check if sea needs to be animated
        //toggleItem(m_scopeSelect, m_scopeSelectTimer, WORLDMAP_SELECTOR_FPS);

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
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSpriteEx(srcRect,dstRect, 90, SpriteFlip::FLIP_NONE);

            // Down arrow
            dstRect.x -= 15;
            dstRect.y += 15;
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSpriteEx(srcRect,dstRect, 180, SpriteFlip::FLIP_NONE);

            // Left arrow
            dstRect.x -= 15;
            dstRect.y -= 15;
            ResourceManager::getInstance()[SpriteResource::SPR_INVENTORY]->drawSpriteEx(srcRect,dstRect, 270, SpriteFlip::FLIP_NONE);
        }
    }

}