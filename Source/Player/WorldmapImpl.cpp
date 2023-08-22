#include "WorldmapImpl.h"

#include <cassert>

namespace Zelda
{
    WorldmapImpl::WorldmapImpl() : m_worldX(0), m_worldY(0)
    {

    }

    void WorldmapImpl::setLocation(const int x, const int y)
    {
        assert(x >= 0 && x < WORLDMAP_MAX_X && y >= 0 && y < WORLDMAP_MAX_Y);
        m_worldX = x;
        m_worldY = y;
        m_worldmapLocation[m_worldX][m_worldY].visited = true;
    }

    void WorldmapImpl::moveMarker(MarkerDirection direction)
    {
        switch (direction)
        {
        case MarkerDirection::RIGHT:
            if (m_worldmapLocation[(m_worldX + 1) % WORLDMAP_MAX_X][m_worldY].visited)
            {
                m_worldX = (m_worldX + 1) % WORLDMAP_MAX_X;
                assert(m_worldX >= 0 && m_worldX < WORLDMAP_MAX_X);
            }
            break;
        case MarkerDirection::LEFT:
            if (m_worldmapLocation[(m_worldX - 1) % WORLDMAP_MAX_X][m_worldY].visited)
            {
                m_worldX = (m_worldX - 1) % WORLDMAP_MAX_X;
                assert(m_worldX >= 0 && m_worldX < WORLDMAP_MAX_X);
            }
            break;
        case MarkerDirection::UP:
            if (m_worldmapLocation[m_worldX][(m_worldY - 1) % WORLDMAP_MAX_Y].visited)
            {
                m_worldY = (m_worldY - 1) % WORLDMAP_MAX_Y;
                assert(m_worldY >= 0 && m_worldY < WORLDMAP_MAX_Y);
            }
            break;
        case MarkerDirection::DOWN:
            if (m_worldmapLocation[m_worldX][(m_worldY + 1) % WORLDMAP_MAX_Y].visited)
            {
                m_worldY = (m_worldY + 1) % WORLDMAP_MAX_Y;
                assert(m_worldY >= 0 && m_worldY < WORLDMAP_MAX_Y);
            }
            break;
        default:
            assert(false);
        }
    }

    bool WorldmapImpl::locationVisited(const int x, const int y) const
    {
        assert(x >= 0 && x < WORLDMAP_MAX_X && y >= 0 && y < WORLDMAP_MAX_Y);
        return m_worldmapLocation[x][y].visited;
    }

    std::pair<int, int> WorldmapImpl::location() const
    {
        return { m_worldX, m_worldY };
    }

    LocationType WorldmapImpl::locationType() const
    {
        return m_worldmapLocation[m_worldX][m_worldY].locationType;
    }

    std::string WorldmapImpl::locationName() const
    {
        switch (m_worldmapLocation[m_worldX][m_worldY].locationName)
        {
        case LN_TAIL_CAVE:
            return "Level 1--       ""     Tail Cave";
        case LN_BOTTLE_GROTTO:
            return "Level 2--       ""   Bottle Grotto";
        case LN_KEY_CAVERN:
            return "Level 3--       ""      Key Cavern";
        case LN_ANGLER_TUNNEL:
            return "Level 4--       "" Angler's Tunnel";
        case LN_CATFISH_MAW:
            return "Level 5--       ""   Catfish's Maw";
        case LN_FACE_SHRINE:
            return "Level 6--       ""     Face Shrine";
        case LN_EAGLE_TOWER:
            return "Level 7--       ""   Eagle's Tower";
        case LN_TURTLE_ROCK:
            return "Level 8--       ""     Turtle Rock";
        case LN_WINDFISH_EGG:
            return "Wind Fish's Egg  ";
        case LN_SALE_HOUSE_BANANA:
            return "Sale's House O' ""    Bananas";
        case LN_POTHOLE_FIELD:
            return "Pothole Field ";
        case LN_HOUSE_BY_THE_BAY:
            return "    House By    ""     The Bay ";
        case LN_TRENDY_GAME:
            return "   Trendy Game ";
        case LN_TOWN_TOOL_SHOP:
            return "  Town Tool Shop ";
        case LN_MARIN_AND_TARIN_HOUSE:
            return "Marin and       ""   Tarin's House";
        case LN_WITCH_HUT:
            return "   Witch's Hut ";
        case LN_YARNA_DESERT:
            return "  Yarna Desert ";
        case LN_UKUKU_PRAIRIE:
            return "  Ukuku Prairie ";
        case LN_MYSTERIOUS_WOODS:
            return "Mysterious Woods ";
        case LN_MT_TAMARANCH:
            return "  Mt. Tamaranch  ";
        case LN_TAL_TAL_MOUNTAIN_RANGE:
            return "     Tal Tal    "" Mountain Range ";
        case LN_SIGNPOST_MAZE:
            return "  Signpost Maze  ";
        case LN_MABE_VILLAGE:
            return "  Mabe Village   ";
        case LN_ANIMAL_VILLAGE:
            return " Animal Village  ";
        case LN_CEMETERY:
            return "    Cemetery     ";
        case LN_RAPIDS_RIDE:
            return "   Rapids Ride   ";
        case LN_KOHOLINT_PRAIRIE:
            return "Koholint Prairie ";
        case LN_TORONBO_SHORES:
            return " Toronbo Shores ";
        case LN_MARTHA_BAY:
            return "  Martha's Bay ";
        case LN_EAST_OF_THE_BAY:
            return "East of the Bay ";
        case LN_GOPONGA_SWAMP:
            return "  Goponga Swamp ";
        case LN_SHRINE:
            return "   Face Shrine  ";
        case LN_KANALET_CASTLE:
            return " Kanalet Castle ";
        case LN_TAL_TAL_HEIGHTS:
            return "Tal Tal Heights ";
        case LN_TABAHL_WASTELANDS:
            return "Tabahl Wasteland ";
        case LN_SOUTH_OF_THE_VILLAGE:
            return "  South of the  ""    Village ";
        case LN_FISHING_POND:
            return "  Fishing Pond   ";
        case LN_MADAM_MEOWMEOW_HOUSE:
            return "Madam MeowMeow's""     House      "" Beware of Dog! ";
        case LN_OLD_MAN_ULRIRA_HOUSE:
            return "Old Man Ulrira's""     House      ";
        case LN_WEIRD_MR_WRITE:
            return "Weird Mr. Write  ";
        case LN_CRAZY_TRACY_HOUSE:
            return " Crazy Tracy's  ""  Health Spa ";
        case LN_QUADRUPULETS_HOUSE:
            return "Quadruplet's    ""      House ";
        case LN_DREAM_SHRINE:
            return "  Dream Shrine   ";
        case LN_TELEPHONE_BOOTH:
            return "Telephone Booth ";
        case LN_SEASHELL_MANSION:
            return "Seashell Mansion ";
        case LN_RICHARD_VILLA:
            return "Richard's Villa  ";
        case LN_HEN_HOUSE:
            return "     Hen House   ";
        case LN_VILLAGE_LIBRARY:
            return "Village Library  ";
        case LN_RAFT_SHOP:
            return "    Raft Shop    ";
        case LN_PHOTO_SHOP:
            return "Step right up   ""and get your    ""souvenir photo!";
        default:
            assert(false);
            return "";
        }
    }



}