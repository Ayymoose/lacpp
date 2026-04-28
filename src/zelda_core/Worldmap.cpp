#include "Worldmap.h"

namespace zelda::core
{
Worldmap::Worldmap()
    : m_worldX(0)
    , m_worldY(0)
{}

void Worldmap::setLocation(int x, int y)
{
    assert(x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y);
    m_worldX = x;
    m_worldY = y;
    setVisited(m_worldX, m_worldY);
}

void Worldmap::setVisited(int x, int y)
{
    assert(x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y);
    m_worldmapLocation[x][y].visited = true;
}

bool Worldmap::locationVisited(int x, int y) const
{
    assert(x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y);
    return m_worldmapLocation[x][y].visited;
}

std::pair<int, int> Worldmap::location() const
{
    return {m_worldX, m_worldY};
}

Worldmap::Type Worldmap::locationType() const
{
    return m_worldmapLocation[m_worldX][m_worldY].locationType;
}

std::string Worldmap::locationName() const
{
    switch (m_worldmapLocation[m_worldX][m_worldY].locationName)
    {
    case Name::TAIL_CAVE:
        return "Level 1--       "
               "     Tail Cave";
    case Name::BOTTLE_GROTTO:
        return "Level 2--       "
               "   Bottle Grotto";
    case Name::KEY_CAVERN:
        return "Level 3--       "
               "      Key Cavern";
    case Name::ANGLER_TUNNEL:
        return "Level 4--       "
               " Angler's Tunnel";
    case Name::CATFISH_MAW:
        return "Level 5--       "
               "   Catfish's Maw";
    case Name::FACE_SHRINE:
        return "Level 6--       "
               "     Face Shrine";
    case Name::EAGLE_TOWER:
        return "Level 7--       "
               "   Eagle's Tower";
    case Name::TURTLE_ROCK:
        return "Level 8--       "
               "     Turtle Rock";
    case Name::WINDFISH_EGG:
        return "Wind Fish's Egg  ";
    case Name::SALE_HOUSE_BANANA:
        return "Sale's House O' "
               "    Bananas";
    case Name::POTHOLE_FIELD:
        return "Pothole Field ";
    case Name::HOUSE_BY_THE_BAY:
        return "    House By    "
               "     The Bay ";
    case Name::TRENDY_GAME:
        return "   Trendy Game ";
    case Name::TOWN_TOOL_SHOP:
        return "  Town Tool Shop ";
    case Name::MARIN_AND_TARIN_HOUSE:
        return "Marin and       "
               "   Tarin's House";
    case Name::WITCH_HUT:
        return "   Witch's Hut ";
    case Name::YARNA_DESERT:
        return "  Yarna Desert ";
    case Name::UKUKU_PRAIRIE:
        return "  Ukuku Prairie ";
    case Name::MYSTERIOUS_WOODS:
        return "Mysterious Woods ";
    case Name::MT_TAMARANCH:
        return "  Mt. Tamaranch  ";
    case Name::TAL_TAL_MOUNTAIN_RANGE:
        return "     Tal Tal    "
               " Mountain Range ";
    case Name::SIGNPOST_MAZE:
        return "  Signpost Maze  ";
    case Name::MABE_VILLAGE:
        return "  Mabe Village   ";
    case Name::ANIMAL_VILLAGE:
        return " Animal Village  ";
    case Name::CEMETERY:
        return "    Cemetery     ";
    case Name::RAPIDS_RIDE:
        return "   Rapids Ride   ";
    case Name::KOHOLINT_PRAIRIE:
        return "Koholint Prairie ";
    case Name::TORONBO_SHORES:
        return " Toronbo Shores ";
    case Name::MARTHA_BAY:
        return "  Martha's Bay ";
    case Name::EAST_OF_THE_BAY:
        return "East of the Bay ";
    case Name::GOPONGA_SWAMP:
        return "  Goponga Swamp ";
    case Name::SHRINE:
        return "   Face Shrine  ";
    case Name::KANALET_CASTLE:
        return " Kanalet Castle ";
    case Name::TAL_TAL_HEIGHTS:
        return "Tal Tal Heights ";
    case Name::TABAHL_WASTELANDS:
        return "Tabahl Wasteland ";
    case Name::SOUTH_OF_THE_VILLAGE:
        return "  South of the  "
               "    Village ";
    case Name::FISHING_POND:
        return "  Fishing Pond   ";
    case Name::MADAM_MEOWMEOW_HOUSE:
        return "Madam MeowMeow's"
               "     House      "
               " Beware of Dog! ";
    case Name::OLD_MAN_ULRIRA_HOUSE:
        return "Old Man Ulrira's"
               "     House      ";
    case Name::WEIRD_MR_WRITE:
        return "Weird Mr. Write  ";
    case Name::CRAZY_TRACY_HOUSE:
        return " Crazy Tracy's  "
               "  Health Spa ";
    case Name::QUADRUPULETS_HOUSE:
        return "Quadruplet's    "
               "      House ";
    case Name::DREAM_SHRINE:
        return "  Dream Shrine   ";
    case Name::TELEPHONE_BOOTH:
        return "Telephone Booth ";
    case Name::SEASHELL_MANSION:
        return "Seashell Mansion ";
    case Name::RICHARD_VILLA:
        return "Richard's Villa  ";
    case Name::HEN_HOUSE:
        return "     Hen House   ";
    case Name::VILLAGE_LIBRARY:
        return "Village Library  ";
    case Name::RAFT_SHOP:
        return "    Raft Shop    ";
    case Name::PHOTO_SHOP:
        return "Step right up   "
               "and get your    "
               "souvenir photo!";
    default:
        return "";
    }
}


} // namespace zelda::core