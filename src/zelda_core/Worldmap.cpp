#include "Worldmap.h"

#include <cassert>

namespace zelda::core
{
Worldmap::Worldmap()
    : m_worldX(0)
    , m_worldY(0)
{}

void Worldmap::setLocation(const int x, const int y)
{
    assert(x >= 0 && x < WORLDMAP_MAX_X && y >= 0 && y < WORLDMAP_MAX_Y);
    m_worldX = x;
    m_worldY = y;
    m_worldmapLocation[m_worldX][m_worldY].visited = true;
}

void Worldmap::moveMarker(Direction direction)
{
    switch (direction)
    {
    case Direction::RIGHT:
        if (m_worldmapLocation[(m_worldX + 1) % WORLDMAP_MAX_X][m_worldY].visited)
        {
            m_worldX = (m_worldX + 1) % WORLDMAP_MAX_X;
            assert(m_worldX >= 0 && m_worldX < WORLDMAP_MAX_X);
        }
        break;
    case Direction::LEFT:
        if (m_worldmapLocation[(m_worldX - 1) % WORLDMAP_MAX_X][m_worldY].visited)
        {
            m_worldX = (m_worldX - 1) % WORLDMAP_MAX_X;
            assert(m_worldX >= 0 && m_worldX < WORLDMAP_MAX_X);
        }
        break;
    case Direction::UP:
        if (m_worldmapLocation[m_worldX][(m_worldY - 1) % WORLDMAP_MAX_Y].visited)
        {
            m_worldY = (m_worldY - 1) % WORLDMAP_MAX_Y;
            assert(m_worldY >= 0 && m_worldY < WORLDMAP_MAX_Y);
        }
        break;
    case Direction::DOWN:
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

bool Worldmap::locationVisited(const int x, const int y) const
{
    assert(x >= 0 && x < WORLDMAP_MAX_X && y >= 0 && y < WORLDMAP_MAX_Y);
    return m_worldmapLocation[x][y].visited;
}

std::pair<int, int> Worldmap::location() const
{
    return {m_worldX, m_worldY};
}

LocationType Worldmap::locationType() const
{
    return m_worldmapLocation[m_worldX][m_worldY].locationType;
}

std::string Worldmap::locationName() const
{
    switch (m_worldmapLocation[m_worldX][m_worldY].locationName)
    {
    case TAIL_CAVE:
        return "Level 1--       "
               "     Tail Cave";
    case BOTTLE_GROTTO:
        return "Level 2--       "
               "   Bottle Grotto";
    case KEY_CAVERN:
        return "Level 3--       "
               "      Key Cavern";
    case ANGLER_TUNNEL:
        return "Level 4--       "
               " Angler's Tunnel";
    case CATFISH_MAW:
        return "Level 5--       "
               "   Catfish's Maw";
    case FACE_SHRINE:
        return "Level 6--       "
               "     Face Shrine";
    case EAGLE_TOWER:
        return "Level 7--       "
               "   Eagle's Tower";
    case TURTLE_ROCK:
        return "Level 8--       "
               "     Turtle Rock";
    case WINDFISH_EGG:
        return "Wind Fish's Egg  ";
    case SALE_HOUSE_BANANA:
        return "Sale's House O' "
               "    Bananas";
    case POTHOLE_FIELD:
        return "Pothole Field ";
    case HOUSE_BY_THE_BAY:
        return "    House By    "
               "     The Bay ";
    case TRENDY_GAME:
        return "   Trendy Game ";
    case TOWN_TOOL_SHOP:
        return "  Town Tool Shop ";
    case MARIN_AND_TARIN_HOUSE:
        return "Marin and       "
               "   Tarin's House";
    case WITCH_HUT:
        return "   Witch's Hut ";
    case YARNA_DESERT:
        return "  Yarna Desert ";
    case UKUKU_PRAIRIE:
        return "  Ukuku Prairie ";
    case MYSTERIOUS_WOODS:
        return "Mysterious Woods ";
    case MT_TAMARANCH:
        return "  Mt. Tamaranch  ";
    case TAL_TAL_MOUNTAIN_RANGE:
        return "     Tal Tal    "
               " Mountain Range ";
    case SIGNPOST_MAZE:
        return "  Signpost Maze  ";
    case MABE_VILLAGE:
        return "  Mabe Village   ";
    case ANIMAL_VILLAGE:
        return " Animal Village  ";
    case CEMETERY:
        return "    Cemetery     ";
    case RAPIDS_RIDE:
        return "   Rapids Ride   ";
    case KOHOLINT_PRAIRIE:
        return "Koholint Prairie ";
    case TORONBO_SHORES:
        return " Toronbo Shores ";
    case MARTHA_BAY:
        return "  Martha's Bay ";
    case EAST_OF_THE_BAY:
        return "East of the Bay ";
    case GOPONGA_SWAMP:
        return "  Goponga Swamp ";
    case SHRINE:
        return "   Face Shrine  ";
    case KANALET_CASTLE:
        return " Kanalet Castle ";
    case TAL_TAL_HEIGHTS:
        return "Tal Tal Heights ";
    case TABAHL_WASTELANDS:
        return "Tabahl Wasteland ";
    case SOUTH_OF_THE_VILLAGE:
        return "  South of the  "
               "    Village ";
    case FISHING_POND:
        return "  Fishing Pond   ";
    case MADAM_MEOWMEOW_HOUSE:
        return "Madam MeowMeow's"
               "     House      "
               " Beware of Dog! ";
    case OLD_MAN_ULRIRA_HOUSE:
        return "Old Man Ulrira's"
               "     House      ";
    case WEIRD_MR_WRITE:
        return "Weird Mr. Write  ";
    case CRAZY_TRACY_HOUSE:
        return " Crazy Tracy's  "
               "  Health Spa ";
    case QUADRUPULETS_HOUSE:
        return "Quadruplet's    "
               "      House ";
    case DREAM_SHRINE:
        return "  Dream Shrine   ";
    case TELEPHONE_BOOTH:
        return "Telephone Booth ";
    case SEASHELL_MANSION:
        return "Seashell Mansion ";
    case RICHARD_VILLA:
        return "Richard's Villa  ";
    case HEN_HOUSE:
        return "     Hen House   ";
    case VILLAGE_LIBRARY:
        return "Village Library  ";
    case RAFT_SHOP:
        return "    Raft Shop    ";
    case PHOTO_SHOP:
        return "Step right up   "
               "and get your    "
               "souvenir photo!";
    default:
        assert(false);
        return "";
    }
}


} // namespace zelda::core