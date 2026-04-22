#include "Worldmap.h"
#include "Dialogue.h"
#include "core/ResourceManager.h"
#include "Depth.h"
#include "core/Renderer.h"
#include "core/InputControl.h"
#include "core/Keyboard.h"
#include "core/Controller.h"
#include "core/Engine.h"

namespace zelda::gui
{
Worldmap::Worldmap()
    : IRenderable("Worldmap", *engine::ResourceManager::instance()[engine::SpriteResource::SPR_WORLD_MAP],
                  core::ZD_DEPTH_WORLDMAP)
    , Controllable(m_name)
    , m_show(false)
    , m_scopeSelect(false)
{
    m_worldMapImpl.setLocation(WORLDMAP_INITIAL_POS_X, WORLDMAP_INITIAL_POS_Y);
    std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
    engine::Renderer::instance().addRenderable(this);
}

void Worldmap::control()
{
    // TODO: Fix key press overlaps between inventory and worldmap
    if (engine::Keyboard::instance().keyPressed(BUTTON_SELECT))
    {
        close();
        engine::Controller::instance().popController();
        engine::Engine::instance().pause(false);
        DEBUG_MACRO(engine::DBG_INFO, "Worldmap closed!");
    }

    // Move scope around map if the area is visited
    if (engine::Keyboard::instance().keyPressed(BUTTON_RIGHT))
    {
        m_worldMapImpl.moveMarker(core::Direction::DIRECTION_RIGHT);
        std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
    }
    if (engine::Keyboard::instance().keyPressed(BUTTON_LEFT))
    {
        m_worldMapImpl.moveMarker(core::Direction::DIRECTION_LEFT);
        std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
    }
    if (engine::Keyboard::instance().keyPressed(BUTTON_UP))
    {
        m_worldMapImpl.moveMarker(core::Direction::DIRECTION_UP);
        std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
    }
    if (engine::Keyboard::instance().keyPressed(BUTTON_DOWN))
    {
        m_worldMapImpl.moveMarker(core::Direction::DIRECTION_DOWN);
        std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
    }

    // Display location name if any
    if (engine::Keyboard::instance().keyPressed(BUTTON_B))
    {
        // Display location name above/below scope
        Dialogue::instance().message(m_worldMapImpl.locationName(), (WORLDMAP_START_Y + m_scopeY * 8) - 10);
    }
}

void Worldmap::moveMarker(core::Direction direction)
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
        m_sprite->drawSprite(engine::Rect<int>{}, engine::Rect<int>{});

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
    auto const target = engine::Renderer::instance().pushRenderingTarget(*m_sprite);

    for (int y = 0; y < core::WORLDMAP_MAX_Y; ++y)
    {
        for (int x = 0; x < core::WORLDMAP_MAX_X; ++x)
        {
            // If the location isn't visited then mark it as an unvisited square
            if (!m_worldMapImpl.locationVisited(x, y))
            {
                engine::ResourceManager::instance()[engine::SpriteResource::SPR_INVENTORY]
                    ->drawSprite(m_worldmapSrcSprites[WORLDMAP_AREA_UNVISITED],
                                 engine::Rect<int>{WORLDMAP_START_X + x * 8, WORLDMAP_START_Y + y * 8, 7, 7});
            }
        }
    }

    engine::Renderer::instance().popRenderingTarget(target);
}

void Worldmap::drawLocationImage() const
{
    // Draw the location if we hit upon one
    if (m_worldMapImpl.locationType() != core::LT_NONE)
    {
        engine::Rect<int> srcRectLocation;
        switch (m_worldMapImpl.locationType())
        {
        case core::LT_SHOP:
            srcRectLocation = m_worldmapSrcSprites[WORLDMAP_AREA_SHOP];
            break;
        case core::LT_UNKNOWN:
            srcRectLocation = m_worldmapSrcSprites[WORLDMAP_AREA_UNKNOWN];
            break;
        case core::LT_DUNGEON:
            srcRectLocation = m_worldmapSrcSprites[WORLDMAP_AREA_DUNGEON];
            break;
        case core::LT_OWL:
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

        engine::ResourceManager::instance()[engine::SpriteResource::SPR_INVENTORY]
            ->drawSprite(srcRectLocation, engine::Rect<int>{sx, sy, 30, 30});
    }
}

void Worldmap::drawScope() const
{
    engine::ResourceManager::instance()[engine::SpriteResource::SPR_INVENTORY]
        ->drawSprite(m_worldmapSrcSprites[WORLDMAP_AREA_SCOPE],
                     engine::Rect<int>{(WORLDMAP_START_X + m_scopeX * 8) - 5,
                                       (WORLDMAP_START_Y + m_scopeY * 8) - 5,
                                       16,
                                       16});

    // TODO: Animation of scope markers
    // TODO: Check if sea needs to be animated
    // toggleItem(m_scopeSelect, m_scopeSelectTimer, WORLDMAP_SELECTOR_FPS);

    if (m_scopeSelect)
    {
        // Draw the flashing arrows
        auto srcRect = m_worldmapSrcSprites[WORLDMAP_AREA_ARROW];
        engine::Rect<int> dstRect = {(WORLDMAP_START_X + m_scopeX * 8) - 5, (WORLDMAP_START_Y + m_scopeY * 8) - 5, 8, 8};
        dstRect.w = 9;
        dstRect.h = 8;
        dstRect.x += 4;
        dstRect.y -= 10;

        // Up arrow
        engine::ResourceManager::instance()[engine::SpriteResource::SPR_INVENTORY]
            ->drawSpriteEx(srcRect, dstRect, 0, engine::SpriteFlip::FLIP_NONE);

        // Right arrow
        dstRect.x += 15;
        dstRect.y += 14;
        engine::ResourceManager::instance()[engine::SpriteResource::SPR_INVENTORY]
            ->drawSpriteEx(srcRect, dstRect, 90, engine::SpriteFlip::FLIP_NONE);

        // Down arrow
        dstRect.x -= 15;
        dstRect.y += 15;
        engine::ResourceManager::instance()[engine::SpriteResource::SPR_INVENTORY]
            ->drawSpriteEx(srcRect, dstRect, 180, engine::SpriteFlip::FLIP_NONE);

        // Left arrow
        dstRect.x -= 15;
        dstRect.y -= 15;
        engine::ResourceManager::instance()[engine::SpriteResource::SPR_INVENTORY]
            ->drawSpriteEx(srcRect, dstRect, 270, engine::SpriteFlip::FLIP_NONE);
    }
}

} // namespace zelda::gui