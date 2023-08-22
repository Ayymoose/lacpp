#pragma once

#include "IRenderable.h"
#include "Controllable.h"
#include "Singleton.h"
#include "WorldmapImpl.h"

namespace Zelda
{
    enum WorldmapSprites
    {
        WORLDMAP_AREA_UNVISITED = 0,
        WORLDMAP_AREA_ARROW,
        WORLDMAP_AREA_SCOPE,
        WORLDMAP_AREA_SHOP,
        WORLDMAP_AREA_UNKNOWN,
        WORLDMAP_AREA_DUNGEON,
        WORLDMAP_AREA_OWL,
        WORLDMAP_AREA_LOCATION
    };


    // Starting point of (0,0) on top left of map
    constexpr int WORLDMAP_START_X = 17;
    constexpr int WORLDMAP_START_Y = 9;

    // Initial starting position of scope (Marin and Tarin house)
    constexpr uint8_t WORLDMAP_INITIAL_POS_X = 2;
    constexpr uint8_t WORLDMAP_INITIAL_POS_Y = 10;

    constexpr float WORLDMAP_SELECTOR_FPS = (1.0f / 4.0f);
    constexpr float WORLDMAP_LOCATION_FPS = (1.0f / 6.0f);


    class Worldmap : public IRenderable, public Controllable, public Singleton<Worldmap>
    {
        friend class Singleton<Worldmap>;
    public:
        void control() override;
        void render() override;
        void open();
        void close();

        void moveMarker(MarkerDirection direction);

        void setLocation(const int x, const int y);

    private:
        Worldmap();

        uint8_t m_scopeX;
        uint8_t m_scopeY;
        bool m_show;

        bool m_scopeSelect;

        WorldmapImpl m_worldMapImpl;

        Rect<int> m_worldmapSrcSprites[8] =
        {
            {110,162,7,7},   // WORLDMAP_AREA_UNVISITED
            {100,162,9,8},   // WORLDMAP_AREA_ARROW
            {108,84,16,16},   // WORLDMAP_AREA_SCOPE
            {140,130,30,30},   // WORLDMAP_AREA_SHOP
            {170,130,30,30},   // WORLDMAP_AREA_UNKNOWN
            {200,130,30,30},   // WORLDMAP_AREA_DUNGEON
            {230,130,30,30},   // WORLDMAP_AREA_OWL
            {110,152,8,8} // WORLDMAP_AREA_LOCATION
        };

        void drawLocationImage() const;
        void drawScope() const;
        void drawUnvisitedLocations() const;
    };

}