#pragma once

#include "core/Direction.h"

#include <utility>
#include <string>
#include <cassert>

namespace zelda::core
{

class Worldmap
{
public:
    // All locations
    enum class Name
    {
        TAIL_CAVE,
        BOTTLE_GROTTO,
        KEY_CAVERN,
        ANGLER_TUNNEL,
        CATFISH_MAW,
        FACE_SHRINE,
        EAGLE_TOWER,
        TURTLE_ROCK,
        WINDFISH_EGG,
        SALE_HOUSE_BANANA,
        POTHOLE_FIELD,
        HOUSE_BY_THE_BAY,
        TRENDY_GAME,
        TOWN_TOOL_SHOP,
        MARIN_AND_TARIN_HOUSE,
        WITCH_HUT,
        YARNA_DESERT,
        UKUKU_PRAIRIE,
        MYSTERIOUS_WOODS,
        MT_TAMARANCH,
        TAL_TAL_MOUNTAIN_RANGE,
        SIGNPOST_MAZE,
        MABE_VILLAGE,
        ANIMAL_VILLAGE,
        CEMETERY,
        RAPIDS_RIDE,
        KOHOLINT_PRAIRIE,
        TORONBO_SHORES,
        MARTHA_BAY,
        EAST_OF_THE_BAY,
        GOPONGA_SWAMP,
        SHRINE,
        KANALET_CASTLE,
        TAL_TAL_HEIGHTS,
        TABAHL_WASTELANDS,
        SOUTH_OF_THE_VILLAGE,
        FISHING_POND,
        MADAM_MEOWMEOW_HOUSE,
        OLD_MAN_ULRIRA_HOUSE,
        WEIRD_MR_WRITE,
        CRAZY_TRACY_HOUSE,
        QUADRUPULETS_HOUSE,
        DREAM_SHRINE,
        TELEPHONE_BOOTH,
        SEASHELL_MANSION,
        RICHARD_VILLA,
        HEN_HOUSE,
        VILLAGE_LIBRARY,
        RAFT_SHOP,
        PHOTO_SHOP
    };

    // One of 4 location types
    enum class Type
    {
        NONE,
        SHOP,
        OWL,
        DUNGEON,
        UNKNOWN
    };

    struct Location
    {
        bool visited;      // Did we visit this location
        Type locationType; // Type of the location (see above)
        Name locationName; // The name of the location
    };

    // Worldmap dimensions
    static constexpr int MAX_X = 16;
    static constexpr int MAX_Y = 16;

    Worldmap();

    void setVisited(int x, int y);

    void setLocation(int x, int y);

    template <engine::Direction D>
    void moveMarker()
    {
        if constexpr (D == engine::Direction::RIGHT)
        {
            if (locationVisited((m_worldX + 1) % MAX_X, m_worldY))
            {
                m_worldX = (m_worldX + 1) % MAX_X;
                assert(m_worldX >= 0 && m_worldX < MAX_X);
            }
        }
        else if constexpr (D == engine::Direction::LEFT)
        {
            if (locationVisited((m_worldX - 1) % MAX_X, m_worldY))
            {
                m_worldX = (m_worldX - 1) % MAX_X;
                assert(m_worldX >= 0 && m_worldX < MAX_X);
            }
        }
        else if constexpr (D == engine::Direction::UP)
        {
            if (locationVisited(m_worldX, (m_worldY - 1) % MAX_Y))
            {
                m_worldY = (m_worldY - 1) % MAX_Y;
                assert(m_worldY >= 0 && m_worldY < MAX_Y);
            }
        }
        else if constexpr (D == engine::Direction::DOWN)
        {
            if (locationVisited(m_worldX, (m_worldY + 1) % MAX_Y))
            {
                m_worldY = (m_worldY + 1) % MAX_Y;
                assert(m_worldY >= 0 && m_worldY < MAX_Y);
            }
        }
    }

    bool locationVisited(int x, int y) const;

    std::pair<int, int> location() const;

    std::string locationName() const;

    Type locationType() const;

private:
    Location m_worldmapLocation[MAX_X][MAX_Y] = {
        {{false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::DUNGEON, Name::TURTLE_ROCK},
         {false, Type::NONE, Name::GOPONGA_SWAMP},
         {false, Type::UNKNOWN, Name::WEIRD_MR_WRITE},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::NONE, Name::MABE_VILLAGE},
         {false, Type::UNKNOWN, Name::VILLAGE_LIBRARY},
         {false, Type::NONE, Name::SOUTH_OF_THE_VILLAGE},
         {false, Type::NONE, Name::SOUTH_OF_THE_VILLAGE},
         {false, Type::NONE, Name::TORONBO_SHORES},
         {false, Type::NONE, Name::TORONBO_SHORES}},
        {{false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::UNKNOWN, Name::TELEPHONE_BOOTH},
         {false, Type::NONE, Name::GOPONGA_SWAMP},
         {false, Type::UNKNOWN, Name::TELEPHONE_BOOTH},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::SHOP, Name::FISHING_POND},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::UNKNOWN, Name::MADAM_MEOWMEOW_HOUSE},
         {false, Type::UNKNOWN, Name::OLD_MAN_ULRIRA_HOUSE},
         {false, Type::NONE, Name::SOUTH_OF_THE_VILLAGE},
         {false, Type::NONE, Name::SOUTH_OF_THE_VILLAGE},
         {false, Type::NONE, Name::TORONBO_SHORES},
         {false, Type::NONE, Name::TORONBO_SHORES}},
        {{false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::GOPONGA_SWAMP},
         {false, Type::NONE, Name::GOPONGA_SWAMP},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::UNKNOWN, Name::QUADRUPULETS_HOUSE},
         {false, Type::NONE, Name::MABE_VILLAGE},
         {false, Type::UNKNOWN, Name::MARIN_AND_TARIN_HOUSE},
         {false, Type::UNKNOWN, Name::TELEPHONE_BOOTH},
         {false, Type::NONE, Name::SOUTH_OF_THE_VILLAGE},
         {false, Type::NONE, Name::SOUTH_OF_THE_VILLAGE},
         {false, Type::NONE, Name::TORONBO_SHORES},
         {false, Type::NONE, Name::TORONBO_SHORES}},
        {{false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::GOPONGA_SWAMP},
         {false, Type::NONE, Name::GOPONGA_SWAMP},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::NONE, Name::MYSTERIOUS_WOODS},
         {false, Type::UNKNOWN, Name::DREAM_SHRINE},
         {false, Type::SHOP, Name::TOWN_TOOL_SHOP},
         {false, Type::NONE, Name::MABE_VILLAGE},
         {false, Type::SHOP, Name::TRENDY_GAME},
         {false, Type::NONE, Name::SOUTH_OF_THE_VILLAGE},
         {false, Type::DUNGEON, Name::TAIL_CAVE},
         {false, Type::SHOP, Name::SALE_HOUSE_BANANA},
         {false, Type::NONE, Name::TORONBO_SHORES}},
        {{false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::DUNGEON, Name::BOTTLE_GROTTO},
         {false, Type::NONE, Name::GOPONGA_SWAMP},
         {false, Type::NONE, Name::KOHOLINT_PRAIRIE},
         {false, Type::NONE, Name::KOHOLINT_PRAIRIE},
         {false, Type::NONE, Name::KOHOLINT_PRAIRIE},
         {false, Type::NONE, Name::KOHOLINT_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::UNKNOWN, Name::TELEPHONE_BOOTH},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::SIGNPOST_MAZE},
         {false, Type::NONE, Name::SIGNPOST_MAZE},
         {false, Type::NONE, Name::TORONBO_SHORES},
         {false, Type::NONE, Name::TORONBO_SHORES}},
        {{false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::SHOP, Name::CRAZY_TRACY_HOUSE},
         {false, Type::NONE, Name::KOHOLINT_PRAIRIE},
         {false, Type::SHOP, Name::WITCH_HUT},
         {false, Type::NONE, Name::KOHOLINT_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::DUNGEON, Name::KEY_CAVERN},
         {false, Type::NONE, Name::SIGNPOST_MAZE},
         {false, Type::NONE, Name::SIGNPOST_MAZE},
         {false, Type::NONE, Name::TORONBO_SHORES},
         {false, Type::NONE, Name::TORONBO_SHORES}},
        {{false, Type::UNKNOWN, Name::WINDFISH_EGG},
         {false, Type::NONE, Name::MT_TAMARANCH},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::NONE, Name::TABAHL_WASTELANDS},
         {false, Type::NONE, Name::TABAHL_WASTELANDS},
         {false, Type::NONE, Name::CEMETERY},
         {false, Type::NONE, Name::CEMETERY},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::POTHOLE_FIELD},
         {false, Type::UNKNOWN, Name::RICHARD_VILLA},
         {false, Type::NONE, Name::MARTHA_BAY},
         {false, Type::UNKNOWN, Name::HOUSE_BY_THE_BAY}},
        {{false, Type::NONE, Name::MT_TAMARANCH},
         {false, Type::NONE, Name::MT_TAMARANCH},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::SHOP, Name::PHOTO_SHOP},
         {false, Type::NONE, Name::TABAHL_WASTELANDS},
         {false, Type::NONE, Name::TABAHL_WASTELANDS},
         {false, Type::NONE, Name::CEMETERY},
         {false, Type::NONE, Name::CEMETERY},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::POTHOLE_FIELD},
         {false, Type::NONE, Name::POTHOLE_FIELD},
         {false, Type::NONE, Name::MARTHA_BAY},
         {false, Type::NONE, Name::MARTHA_BAY}},
        {{false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::NONE, Name::KANALET_CASTLE},
         {false, Type::NONE, Name::KANALET_CASTLE},
         {false, Type::NONE, Name::KANALET_CASTLE},
         {false, Type::NONE, Name::KANALET_CASTLE},
         {false, Type::UNKNOWN, Name::TELEPHONE_BOOTH},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::MARTHA_BAY},
         {false, Type::NONE, Name::MARTHA_BAY},
         {false, Type::UNKNOWN, Name::TELEPHONE_BOOTH},
         {false, Type::NONE, Name::MARTHA_BAY}},
        {{false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::NONE, Name::KANALET_CASTLE},
         {false, Type::NONE, Name::KANALET_CASTLE},
         {false, Type::NONE, Name::KANALET_CASTLE},
         {false, Type::NONE, Name::KANALET_CASTLE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::MARTHA_BAY},
         {false, Type::DUNGEON, Name::CATFISH_MAW},
         {false, Type::NONE, Name::MARTHA_BAY},
         {false, Type::NONE, Name::MARTHA_BAY}},
        {{false, Type::SHOP, Name::HEN_HOUSE},
         {false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::NONE, Name::KANALET_CASTLE},
         {false, Type::NONE, Name::KANALET_CASTLE},
         {false, Type::NONE, Name::KANALET_CASTLE},
         {false, Type::NONE, Name::KANALET_CASTLE},
         {false, Type::UNKNOWN, Name::SEASHELL_MANSION},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::MARTHA_BAY},
         {false, Type::NONE, Name::MARTHA_BAY},
         {false, Type::NONE, Name::MARTHA_BAY},
         {false, Type::NONE, Name::MARTHA_BAY}},
        {{false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::DUNGEON, Name::ANGLER_TUNNEL},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::UNKNOWN, Name::TELEPHONE_BOOTH},
         {false, Type::NONE, Name::KANALET_CASTLE},
         {false, Type::NONE, Name::KANALET_CASTLE},
         {false, Type::NONE, Name::KANALET_CASTLE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::UKUKU_PRAIRIE},
         {false, Type::NONE, Name::MARTHA_BAY},
         {false, Type::UNKNOWN, Name::TELEPHONE_BOOTH},
         {false, Type::NONE, Name::MARTHA_BAY},
         {false, Type::NONE, Name::MARTHA_BAY}},
        {{false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::DUNGEON, Name::FACE_SHRINE},
         {false, Type::NONE, Name::SHRINE},
         {false, Type::NONE, Name::SHRINE},
         {false, Type::NONE, Name::SHRINE},
         {false, Type::NONE, Name::ANIMAL_VILLAGE},
         {false, Type::NONE, Name::ANIMAL_VILLAGE},
         {false, Type::NONE, Name::EAST_OF_THE_BAY},
         {false, Type::NONE, Name::EAST_OF_THE_BAY}},
        {{false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::SHRINE},
         {false, Type::NONE, Name::SHRINE},
         {false, Type::NONE, Name::SHRINE},
         {false, Type::NONE, Name::SHRINE},
         {false, Type::NONE, Name::ANIMAL_VILLAGE},
         {false, Type::NONE, Name::ANIMAL_VILLAGE},
         {false, Type::NONE, Name::EAST_OF_THE_BAY},
         {false, Type::NONE, Name::EAST_OF_THE_BAY}},
        {{false, Type::DUNGEON, Name::EAGLE_TOWER},
         {false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::SHRINE},
         {false, Type::NONE, Name::SHRINE},
         {false, Type::NONE, Name::YARNA_DESERT},
         {false, Type::NONE, Name::YARNA_DESERT},
         {false, Type::NONE, Name::YARNA_DESERT},
         {false, Type::NONE, Name::YARNA_DESERT}},
        {{false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_MOUNTAIN_RANGE},
         {false, Type::NONE, Name::TAL_TAL_HEIGHTS},
         {false, Type::SHOP, Name::RAFT_SHOP},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::RAPIDS_RIDE},
         {false, Type::NONE, Name::SHRINE},
         {false, Type::NONE, Name::SHRINE},
         {false, Type::NONE, Name::YARNA_DESERT},
         {false, Type::NONE, Name::YARNA_DESERT},
         {false, Type::NONE, Name::YARNA_DESERT},
         {false, Type::NONE, Name::YARNA_DESERT}},
    };

    // Position of Link in the worldmap
    int m_worldX;
    int m_worldY;
};

} // namespace zelda::core
