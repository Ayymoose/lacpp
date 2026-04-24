#include "Worldmap.h"
#include "Dialogue.h"
#include "core/ResourceManager.h"
#include "Depth.h"
#include "core/Logger.h"
#include "core/Renderer.h"
#include "core/InputControl.h"
#include "core/Keyboard.h"
#include "core/Controller.h"
#include "core/Engine.h"

namespace zelda::gui
{
Worldmap::Worldmap()
    : IRenderable("Worldmap", *engine::ResourceManager::instance()[engine::SpriteResource::WORLD_MAP], core::WORLDMAP)
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
        Logger::instance().log<Logger::Mask::INFO>("Worldmap closed!");
    }

    // Move scope around map if the area is visited
    if (engine::Keyboard::instance().keyPressed(BUTTON_RIGHT))
    {
        m_worldMapImpl.moveMarker(engine::Direction::RIGHT);
        std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
    }
    if (engine::Keyboard::instance().keyPressed(BUTTON_LEFT))
    {
        m_worldMapImpl.moveMarker(engine::Direction::LEFT);
        std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
    }
    if (engine::Keyboard::instance().keyPressed(BUTTON_UP))
    {
        m_worldMapImpl.moveMarker(engine::Direction::UP);
        std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
    }
    if (engine::Keyboard::instance().keyPressed(BUTTON_DOWN))
    {
        m_worldMapImpl.moveMarker(engine::Direction::DOWN);
        std::tie(m_scopeX, m_scopeY) = m_worldMapImpl.location();
    }

    // Display location name if any
    if (engine::Keyboard::instance().keyPressed(BUTTON_B))
    {
        // Display location name above/below scope
        Dialogue::instance().message(m_worldMapImpl.locationName(), (WORLDMAP_START_Y + m_scopeY * 8) - 10);
    }
}

void Worldmap::moveMarker(engine::Direction direction)
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
        m_sprite->draw(engine::Rect<int>{}, engine::Rect<int>{});

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
    engine::RenderTarget target(engine::Renderer::instance().getRenderer(), m_sprite->data());
    for (int y = 0; y < core::WORLDMAP_MAX_Y; ++y)
    {
        for (int x = 0; x < core::WORLDMAP_MAX_X; ++x)
        {
            // If the location isn't visited then mark it as an unvisited square
            if (!m_worldMapImpl.locationVisited(x, y))
            {
                engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]
                    ->draw(m_worldmapSrcSprites[UNVISITED],
                           engine::Rect<int>{WORLDMAP_START_X + x * 8, WORLDMAP_START_Y + y * 8, 7, 7});
            }
        }
    }
}

void Worldmap::drawLocationImage() const
{
    // Draw the location if we hit upon one
    if (m_worldMapImpl.locationType() != core::NONE)
    {
        engine::Rect<int> srcRectLocation;
        switch (m_worldMapImpl.locationType())
        {
        case core::SHOP:
            srcRectLocation = m_worldmapSrcSprites[SHOP];
            break;
        case core::UNKNOWN:
            srcRectLocation = m_worldmapSrcSprites[UNKNOWN];
            break;
        case core::DUNGEON:
            srcRectLocation = m_worldmapSrcSprites[DUNGEON];
            break;
        case core::OWL:
            srcRectLocation = m_worldmapSrcSprites[OWL];
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

        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRectLocation,
                                                                                     engine::Rect<int>{sx, sy, 30, 30});
    }
}

void Worldmap::drawScope() const
{
    engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]
        ->draw(m_worldmapSrcSprites[SCOPE],
               engine::Rect<int>{(WORLDMAP_START_X + m_scopeX * 8) - 5, (WORLDMAP_START_Y + m_scopeY * 8) - 5, 16, 16});

    // TODO: Animation of scope markers
    // TODO: Check if sea needs to be animated
    // toggleItem(m_scopeSelect, m_scopeSelectTimer, WORLDMAP_SELECTOR_FPS);

    if (m_scopeSelect)
    {
        // Draw the flashing arrows
        auto srcRect = m_worldmapSrcSprites[ARROW];
        engine::Rect<int> dstRect = {(WORLDMAP_START_X + m_scopeX * 8) - 5, (WORLDMAP_START_Y + m_scopeY * 8) - 5, 8, 8};
        dstRect.w = 9;
        dstRect.h = 8;
        dstRect.x += 4;
        dstRect.y -= 10;

        // Up arrow
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect, 0);

        // Right arrow
        dstRect.x += 15;
        dstRect.y += 14;
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect, 90);

        // Down arrow
        dstRect.x -= 15;
        dstRect.y += 15;
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect, 180);

        // Left arrow
        dstRect.x -= 15;
        dstRect.y -= 15;
        engine::ResourceManager::instance()[engine::SpriteResource::INVENTORY]->draw(srcRect, dstRect, 270);
    }
}

} // namespace zelda::gui