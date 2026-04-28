#pragma once

#include <array>
#include <bitset>
#include <cstdint>

namespace zelda::save
{

enum class Item : std::uint8_t
{
    NONE           = 0x00,
    SWORD          = 0x01,
    BOMBS          = 0x02,
    POWER_BRACELET = 0x03,
    SHIELD         = 0x04,
    BOW            = 0x05,
    HOOKSHOT       = 0x06,
    MAGIC_ROD      = 0x07,
    PEGASUS_BOOTS  = 0x08,
    OCARINA        = 0x09,
    ROCS_FEATHER   = 0x0A,
    SHOVEL         = 0x0B,
    MAGIC_POWDER   = 0x0C,
    BOOMERANG      = 0x0D,
};

enum class Tunic : std::uint8_t
{
    GREEN = 0,
    RED   = 1,
    BLUE  = 2,
};

enum class BowWowStatus : std::uint8_t
{
    AWAY      = 0x00,
    FOLLOWING = 0x01,
    KIDNAPPED = 0x80,
};

enum class TarinState : std::uint8_t
{
    RACCOON      = 0,
    HUMAN        = 1,
    LEFT_DUNGEON = 2,
};

enum class EggMazeStep : std::uint8_t
{
    STEP_0 = 0x00,
    STEP_1 = 0x08,
    STEP_2 = 0x10,
    STEP_3 = 0x18,
};

struct OcarinaSongs
{
    bool frogsSong   = false;
    bool manbosMambo = false;
    bool ballad      = false;
};

struct DungeonItems
{
    bool         map       = false;
    bool         compass   = false;
    bool         stoneBeak = false;
    bool         bossKey   = false;
    std::uint8_t smallKeys = 0;
};

struct SaveSlot
{
    // Validation prefix — values 1,3,5,7,9 indicate a valid save
    std::array<std::uint8_t, 5> prefix{};

    // Room status flags (bit 7 = visited, bits 0–6 = door/event flags)
    std::array<std::uint8_t, 256> overworldRoomStatus{};
    std::array<std::uint8_t, 256> indoorARoomStatus{};
    std::array<std::uint8_t, 256> indoorBRoomStatus{};

    // Equipped items
    Item buttonB = Item::NONE;
    Item buttonA = Item::NONE;
    std::array<Item, 10> inventory{};

    // Key items & collectibles
    bool         hasFlippers       = false;
    bool         hasMedicine       = false;
    Item         tradeSequenceItem = Item::NONE;
    std::uint8_t seashellCount     = 0;
    bool         hasTailKey        = false;
    bool         hasAnglerKey      = false;
    bool         hasFaceKey        = false;
    bool         hasBirdKey        = false;

    // Golden leaves (0–5) / slime key (6)
    std::uint8_t goldenLeaves = 0;

    // Dungeon items: 8 main dungeons + colour dungeon = 9 entries
    std::array<DungeonItems, 9> dungeonItems{};

    // Equipment levels & ammo
    std::uint8_t powerBraceletLevel = 0;
    std::uint8_t shieldLevel        = 0;
    std::uint8_t arrowCount         = 0;

    // Misc state
    bool         stolenFromShop   = false;
    TarinState   tarinState       = TarinState::RACCOON;
    OcarinaSongs ocarinaSongs{};
    std::uint8_t selectedSong     = 0;
    bool         hasToadstool     = false;
    std::uint8_t magicPowderCount = 0;
    std::uint8_t bombCount        = 0;
    std::uint8_t swordLevel       = 0;  // 0=none, 1=retrieved
    std::array<char, 5> playerName{};

    // NPC / follower state
    std::uint8_t  mapIndexEntry     = 0;
    bool          spokenWithRichard = false;
    BowWowStatus  bowWowStatus      = BowWowStatus::AWAY;
    std::uint16_t deathCount        = 0;

    // Health & resources
    std::uint8_t  currentHealth = 0;  // 0x08 per heart
    std::uint8_t  maxHearts     = 0;
    std::uint8_t  heartPieces   = 0;
    std::uint16_t rupees        = 0;

    // Spawn / respawn location
    bool         spawnIsIndoor   = false;
    std::uint8_t spawnMapId      = 0;
    std::uint8_t spawnRoom       = 0;
    std::uint8_t spawnX          = 0;  // 0 = use predefined
    std::uint8_t spawnY          = 0;  // 0 = use predefined
    std::uint8_t spawnIndoorRoom = 0;

    // Instruments of the Sirens (dungeons 1–8)
    std::array<bool, 8> instrumentFlags{};

    // World state
    bool         isThief                  = false;
    std::uint8_t wreckingBallRoom         = 0;
    std::uint8_t wreckingBallX            = 0;
    std::uint8_t wreckingBallY            = 0;
    std::uint8_t dungeon7PillarsDestroyed = 0;  // 0–4
    bool         marinFollowing           = false;
    bool         marinInAnimalVillage     = false;
    std::uint8_t medicinesPurchased       = 0;
    std::uint8_t maxMagicPowder           = 0;
    std::uint8_t maxBombs                 = 0;
    std::uint8_t maxArrows                = 0;
    bool         ghostFollowing           = false;
    bool         ghostSeeksGrave          = false;  // false=house by bay
    bool         roosterFollowing         = false;
    EggMazeStep  eggMazeStep             = EggMazeStep::STEP_0;
    Item         boomerangTradedItem      = Item::NONE;
    std::uint8_t kidHintIndex            = 0;  // 0–3, dialogue variation only
    std::uint8_t tradeExchangeInProgress = 0;  // 0x01/0x02 if active

    // DX extensions
    DungeonItems colorDungeonItems{};
    std::array<std::uint8_t, 32> colorDungeonRooms{};
    Tunic           tunic  = Tunic::GREEN;
    std::bitset<12> photos{};  // bit N = photo N+1 collected (bits 0–11)
};

struct SaveFile
{
    std::array<SaveSlot, 3> slots{};
};

} // namespace zelda::save
