#pragma once

#include "IRenderable.h"
#include "Controllable.h"
#include "core/Singleton.h"
#include "zelda_core/Worldmap.h"

namespace zelda::gui
{
enum WorldmapSprites
{
    UNVISITED = 0,
    ARROW,
    SCOPE,
    SHOP,
    UNKNOWN,
    DUNGEON,
    OWL,
    LOCATION
};


// Starting point of (0,0) on top left of map
constexpr int WORLDMAP_START_X = 17;
constexpr int WORLDMAP_START_Y = 9;

// Initial starting position of scope (Marin and Tarin house)
constexpr uint8_t WORLDMAP_INITIAL_POS_X = 2;
constexpr uint8_t WORLDMAP_INITIAL_POS_Y = 10;

constexpr float WORLDMAP_SELECTOR_FPS = (1.0f / 4.0f);
constexpr float WORLDMAP_LOCATION_FPS = (1.0f / 6.0f);


class Worldmap : public IRenderable, public Controllable, public engine::Singleton<Worldmap>
{
public:
    Worldmap();
    void control() override;
    void render() override;
    void open();
    void close();

    void moveMarker(core::Direction direction);

    void setLocation(const int x, const int y);

private:

    uint8_t m_scopeX;
    uint8_t m_scopeY;
    bool m_show;

    bool m_scopeSelect;

    core::Worldmap m_worldMapImpl;

    engine::Rect<int> m_worldmapSrcSprites[8] = {
        {110, 162, 7, 7},   // UNVISITED
        {100, 162, 9, 8},   // ARROW
        {108, 84, 16, 16},  // SCOPE
        {140, 130, 30, 30}, // SHOP
        {170, 130, 30, 30}, // UNKNOWN
        {200, 130, 30, 30}, // DUNGEON
        {230, 130, 30, 30}, // OWL
        {110, 152, 8, 8}    // LOCATION
    };

    void drawLocationImage() const;
    void drawScope() const;
    void drawUnvisitedLocations() const;
};

} // namespace zelda::gui