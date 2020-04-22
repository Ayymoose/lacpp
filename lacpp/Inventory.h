#ifndef INVENTORY_H
#define INVENTORY_H

#include "Controllable.h"
#include "Renderable.h"
#include "Vec2.h"

// Initial selector position and increases
#define SELECTOR_INITIAL_X 6
#define SELECTOR_INITIAL_Y 26
#define SELECTOR_INCREASE_X 32
#define SELECTOR_INCREASE_Y 23

// Maximum "storable" items in inventory
#define INVENTORY_MAX_WEAPONS 10

// The entire inventory
#define INVENTORY_INTERNAL_X 0
#define INVENTORY_INTERNAL_Y 21
#define INVENTORY_WIDTH CAMERA_WIDTH
#define INVENTORY_HEIGHT 144 // Because of the HUD being at the top of the screen

// Inventory dividers horizontal/vertical
#define INVENTORY_DIVIDER_XH 0
#define INVENTORY_DIVIDER_YH 18
#define INVENTORY_DIVIDER_XV 67
#define INVENTORY_DIVIDER_YV 24
#define INVENTORY_DIVIDER_WIDTH_H 7
#define INVENTORY_DIVIDER_HEIGHT_H 3
#define INVENTORY_DIVIDER_WIDTH_V 3
#define INVENTORY_DIVIDER_HEIGHT_V 7

// Sprite width/height of the inventory items
#define INVENTORY_SPRITE_WIDTH 8
#define INVENTORY_SPRITE_HEIGHT 16

// Initial position of the inventory sprite item
#define INVENTORY_POS_X 8
#define INVENTORY_POS_Y 25

// Spacing between each inventory sprite item on the lhs
#define INVENTORY_X_SPACING 32
#define INVENTORY_Y_SPACING 23

// RGB components of inventory colour
#define INVENTORY_R 248
#define INVENTORY_G 248
#define INVENTORY_B 168

// Item limits
#define BOMBS_MAX 50
#define MAGIC_POWDER_MAX 50
#define ARROWS_MAX 30

// The width/height of the weapon level sprite
#define WPN_LEVEL_X 16
#define WPN_LEVEL_Y 33
#define WPN_LEVEL_SPACING_X 32
#define WPN_LEVEL_SPACING_Y 23
#define WPN_LEVEL_WIDTH 8
#define WPN_LEVEL_HEIGHT 8

#define SELECT_SUBSCREEN_WIDTH 80
#define SELECT_SUBSCREEN_HEIGHT 32

// Hearts per row
#define HEARTS_PER_ROW 7
#define HEART_PIECES_MAX 4

// Maximum photographs we are allowed
#define MAX_PHOTOGRAPHS 12

// Animation stuff
#define INSTRUMENTS_FRAME 12

#define MAX_DUNGEONS 9
#define DUNGEON_MAX_BLOCK_X 9
#define DUNGEON_MAX_BLOCK_Y 9

enum WEAPON
{
    WPN_NONE = -1,
    WPN_SWORD = 0,
    WPN_SHIELD,
    WPN_BOW,
    WPN_BOOMERANG,
    WPN_MAGIC_POWDER,
    WPN_BOMBS,
    WPN_POWER_BRACELET_1,
    WPN_POWER_BRACELET_2, // The power bracelet level 2 has a different sprite
    WPN_ROC_FEATHER,
    WPN_HOOKSHOT,
    WPN_OCARINA,
    WPN_PEGASUS_BOOT,
    WPN_SHOVEL,
    WPN_FLAME_ROD,
    WPN_COUNT
};

enum WEAPON_LEVEL
{
    WPN_LEVEL_NONE = -1,
    WPN_LEVEL_1 = 1,
    WPN_LEVEL_2,
    WPN_LEVEL_COUNT
};

enum OCARINA_SONG
{
    SNG_NONE = -1,
    SNG_MARIN = 1,
    SNG_FROG,
    SNG_FISH,
    SNG_COUNT
};

enum INVENTORY_SPRITES
{
    INVENTORY_DIVIDER_H = WPN_COUNT,
    INVENTORY_DIVIDER_V,
    INVENTORY_B_BUTTON,
    INVENTORY_A_BUTTON,
    INVENTORY_SELECTOR_BUTTON_1,
    INVENTORY_SELECTOR_BUTTON_2,
    INVENTORY_RUPPEE,
    INVENTORY_LEVEL,
    INVENTORY_DIGIT_B,
    INVENTORY_DIGIT_W,
    INVENTORY_HEART_WHOLE,
    INVENTORY_INSTRUMENT_BACK_0,
    INVENTORY_INSTRUMENT_BACK_1,
    INVENTORY_INSTRUMENT_BACK_2,
    INVENTORY_INSTRUMENT_BACK_3,
    INVENTORY_INSTRUMENT_BACK_4,
    INVENTORY_INSTRUMENT_BACK_5,
    INVENTORY_INSTRUMENT_BACK_6,
    INVENTORY_INSTRUMENT_BACK_7,
    INVENTORY_INSTRUMENT_0,
    INVENTORY_INSTRUMENT_1,
    INVENTORY_INSTRUMENT_2,
    INVENTORY_INSTRUMENT_3,
    INVENTORY_INSTRUMENT_4,
    INVENTORY_INSTRUMENT_5,
    INVENTORY_INSTRUMENT_6,
    INVENTORY_INSTRUMENT_7,
    INVENTORY_COMPASS,
    INVENTORY_NIGHTMARE_KEY,
    INVENTORY_OWL_BEAK,
    INVENTORY_DUNGEON_MAP,
    INVENTORY_DUNGEON_KEY,
    INVENTORY_FLIPPERS,
    INVENTORY_POTION,
    INVENTORY_SEASHELLS,
    INVENTORY_DOLL,
    INVENTORY_BOW,
    INVENTORY_DOG_FOOD,
    INVENTORY_BANANAS,
    INVENTORY_STICK,
    INVENTORY_HONEYCOMB,
    INVENTORY_PINEAPPLE,
    INVENTORY_HIBISCUS,
    INVENTORY_LETTER,
    INVENTORY_BROOM,
    INVENTORY_HOOK,
    INVENTORY_NECKLACE,
    INVENTORY_MERMAID_SCALE,
    INVENTORY_LENS,
    INVENTORY_TAIL_KEY,
    INVENTORY_SLIME_KEY,
    INVENTORY_ANGLER_KEY,
    INVENTORY_FACE_KEY,
    INVENTORY_BIRD_KEY,
    INVENTORY_RED_ARROW,
    INVENTORY_PUSH_SELECT,
    INVENTORY_SUBSCREEN,
    INVENTORY_TUNIC,
    INVENTORY_HEART_PIECES,
    INVENTORY_PHOTOGRAPHS,
    INVENTORY_SLASH,

    INVENTORY_AREA_EXIT_RIGHT,
    INVENTORY_AREA_EXIT_LEFT,
    INVENTORY_AREA_EXIT_RIGHT_DOWN,
    INVENTORY_AREA_EXIT_LEFT_DOWN,
    INVENTORY_AREA_EXIT_NONE,
    INVENTORY_AREA_EXIT_LEFT_UP_RIGHT,
    INVENTORY_AREA_EXIT_LEFT_DOWN_RIGHT,
    INVENTORY_AREA_UNVISITED,
    INVENTORY_AREA_EXIT_LEFT_RIGHT,
    INVENTORY_AREA_TREASURE,
    INVENTORY_AREA_NIGHTMARE,
    INVENTORY_AREA_EXIT_DOWN,
    INVENTORY_AREA_EXIT_UP,
    INVENTORY_AREA_EXIT_UP_RIGHT,
    INVENTORY_AREA_EXIT_LEFT_UP,
    INVENTORY_AREA_EXIT_ALL,
    INVENTORY_AREA_EXIT_UP_RIGHT_DOWN,
    INVENTORY_AREA_EXIT_UP_LEFT_DOWN,
    INVENTORY_AREA_EMPTY,
    INVENTORY_AREA_EXIT_UP_DOWN,
    INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW,
    INVENTORY_DUNGEON_MAP_CURRENT_LOCATION,

    INVENTORY_ARROW,

    INVENTORY_COUNT
};

enum INSTRUMENT
{
    INSTRUMENT_NONE = -1,
    FULL_MOON_CELLO,
    CONCH_HORN,
    SEA_LILY_BELL,
    SURF_HARP,
    WIND_MARIMBA,
    CORAL_TRIANGLE,
    ORGAN_OF_EVENING_CALM,
    THUNDER_DRUM,
    INSTRUMENT_COUNT
};

enum TRADE_ITEM
{
    ITEM_NONE = -1,
    ITEM_DOLL,
    ITEM_BOW,
    ITEM_DOG_FOOD,
    ITEM_BANANAS,
    ITEM_STICK,
    ITEM_HONEYCOMB,
    ITEM_PINEAPPLE,
    ITEM_HIBISCUS,
    ITEM_LETTER,
    ITEM_BROOM,
    ITEM_HOOK,
    ITEM_NECKLACE,
    ITEM_MERMAID_SCALE,
    ITEM_LENS,
    ITEM_COUNT
};

enum TUNIC
{
    TUNIC_NONE = -1,
    TUNIC_GREEN,
    TUNIC_RED,
    TUNIC_BLUE,
    TUNIC_COUNT
};

enum HEART_PIECES
{
    HEART_NONE = -1,
    HEART_ZERO = 0,
    HEART_ONE_QUARTER,
    HEART_HALF,
    HEART_THREE_QUARTER,
    HEART_FULL,
    HEART_COUNT
};

enum DUNGEON
{
    DUNGEON_NONE = -1,
    DUNGEON_COLOUR_DUNGEON,
    DUNGEON_TAIL_CAVE,
    DUNGEON_BOTTLE_GROTTO,
    DUNGEON_KEY_CAVERN,
    DUNGEON_ANGLER_TUNNEL,
    DUNGEON_CATFISH_MAW,
    DUNGEON_FACE_SHRINE,
    DUNGEON_EAGLE_TOWER,
    DUNGEON_TURTLE_ROCK,
    DUNGEON_COUNT
};

#define TRADE_ITEM_SPRITE(ITEM) (INVENTORY_DOLL + ITEM)

class Inventory : public Controllable, public Renderable
{
public:
    Inventory();
    ~Inventory() = default;
    void control() override;
    void render(SDL_Renderer* pRenderer) override;
    void open();
    void close();

    bool shieldEquipped() const;
    WEAPON_LEVEL shieldLevel() const;

    WEAPON weaponA() const;
    WEAPON weaponB() const;

private:
    SDL_Texture* m_inventorySelector;   // Selector sprite
    SDL_Texture* m_inventoryDividerH;   // Horizontal divider
    SDL_Texture* m_inventoryDividerV;   // Vertical divider
    SDL_Texture* m_subscreen;        // The select status at the bottom of the screen

    void drawDungeonMap(SDL_Renderer* pRenderer);
    void drawSelectStatus(SDL_Renderer* pRenderer);
    void drawMiscItems(SDL_Renderer* pRenderer);
    void drawInventoryItems(SDL_Renderer* pRenderer);
    void drawDungeonItems(SDL_Renderer* pRenderer);
    void drawInstruments(SDL_Renderer* pRenderer);
    void drawHealth(SDL_Renderer* pRenderer);
    void drawInventoryWeapons(SDL_Renderer* pRenderer);
    void drawSelector(SDL_Renderer* pRenderer);
    void drawInventoryDividers(SDL_Renderer* pRenderer);
    void drawTopHUD(SDL_Renderer* pRenderer);

    void drawNumber(SDL_Renderer* pRenderer, SDL_Texture* srcTexture, bool drawLevel, bool useNormalFont, uint8_t trailingDigits, uint16_t number, SDL_Rect* dstRect);
    void drawWeaponLevel(SDL_Renderer* pRenderer, SDL_Texture* srcTexture, WEAPON weapon, SDL_Rect* dstRect);

    TRADE_ITEM m_tradeItem; // Current trade item

    bool m_open;

    // Dungeon related items
    bool m_inDungeon;    // Are we in a dungeon?
    int m_dungeonKeys;  // Number of dungeon keys
    bool m_compass;      // Dungeon compass
    bool m_dungeonMap;   // Dungeon map
    bool m_nightmareKey; // Nightmare boss key
    bool m_owlBeak;      // Owl beak

    // Dungeon keys
    bool m_tailKey;
    bool m_slimeKey;
    bool m_anglerKey;
    bool m_faceKey;
    bool m_birdKey;

    // Inventory related variables
    int m_arrows;         // Number of arrows
    int m_bombs;          // Number of bombs
    int m_magicPowder;    // Number of magic powder
    WEAPON_LEVEL m_swordLevel;     // Sword Level 1 or 2
    WEAPON_LEVEL m_shieldLevel;    // Shield Level 1 or 2
    WEAPON_LEVEL m_braceletLevel;  // Bracelet Level 1 or 2
    int m_ocarinaSong;    // Ocarina song level
    int m_seashells;      // Number of Seashells
    bool m_flippers;          // Flippers
    bool m_potion;            // Red potion bottle
    TUNIC m_tunic;            // Tunic
    int m_heartPieces;    // Heart pieces (0 to 4)
    int m_goldleaf;       // Golden leaves
    int m_photographs;

    // Weapon A and B
    WEAPON m_weaponA;
    WEAPON m_weaponB;

    // Selector position 
    int m_selector_x; 
    int m_selector_y;

    // Index into inventory array
    int m_selector_index;

    // Timer for flashing the selector
    UpdateTimer m_selectorTimer;

    // Weapons
    WEAPON m_items[INVENTORY_MAX_WEAPONS];

    // Instruments
    INSTRUMENT m_instruments[INSTRUMENT_COUNT];

    UpdateTimer m_instrumentTimer;
    UpdateTimer m_pushSelectTimer;

    // Key press related stuff
    bool m_singleLeftRight;
    bool m_singleUpDown;
    bool m_singlePressA;
    bool m_singlePressB;
    bool m_flashSelector;
    bool m_flashSelect;
    bool m_selectPressed;

    // Player position in dungeon map as a vector
    Vec2<uint8_t> m_dungeonPosition;

    UpdateTimer m_dungeonMapPositionTimer;

    // Array of dungeon maps
    /*

    [X][][] Dungeon select

        0 - Colour Dungeon
        1 - Tail Cave
        2 - Bottle Grotto
        3 - Key Cavern
        4 - Anglers Tunnel
        5 - Catfishs Maw
        6 - Face Shrine
        7 - Eagle Tower
        8 - Turtle Rock

    [][X][X] Area state

        0 - Empty (navy square)
        1 - Blank (white inventory coloured block)
        2 - Unvisited navy square
        3 - Treasure chest
        4 - Nightmare location
        5 - Area RIGHT exit only
        6 - Area LEFT exit only
        7 - Area RIGHT and DOWN exit only
        8 - Area LEFT and DOWN exit only
        9 - Area no exit
        10 - Area LEFT UP and RIGHT exit only
        11 - Area LEFT RIGHT DOWN exit only
        12 - Area DOWN exit only
        13 - Area UP exit only
        14 - Area UP and RIGHT exit only
        15 - Area UP and LEFT exit only
        16 - Area all exits
        17 - Area UP RIGHT and DOWN exit only
        18 - Area UP LEFT and DOWN exit only
        19 - Area UP and DOWN exit only

        No dungeon map                 -> Empty map
        Dungeon map (no visietd areas) -> Unvisited block on each area
        Visited map                    -> Reveal area block on map

    */

    DUNGEON m_dungeon;

    uint8_t m_dungeonMaps[MAX_DUNGEONS][DUNGEON_MAX_BLOCK_X][DUNGEON_MAX_BLOCK_Y] =
    {
        {
            {0,0,0,0,0,0,0,0,1},
            {0,0,0,0,0,0,0,0,1},
            {0,0,0,0,0,0,0,0,1},
            {0,0,0,0,0,0,0,0,1},
            {0,0,0,0,0,0,0,0,1},
            {0,0,0,0,0,0,0,0,1},
            {0,0,0,0,0,0,0,0,1},
            {0,0,0,0,0,0,0,0,1},
            {0,0,0,0,0,0,0,0,1},
        },
        {
            { 1, 1, 1, 1, 1, 1, 1, 1, 1},
            { 0, 0, 0, 0, 0, 0, 0, 0, 1},
            { 0, 0, 0, 0, 0, 0, 0, 0, 1},
            { 0, 0, 0, 0, 0, 0,12, 0, 1},
            { 0, 5,11, 6, 0, 0, 4, 0, 1},
            {12, 0,17, 3, 8,12,19, 0, 1},
            {19, 5,17,10,10,18,15, 0, 1},
            {13, 0,14,11,15, 0, 0, 0, 1},
            { 0, 5,11,18, 0, 0, 0, 0, 1},
        },
        {
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
        },
        {
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
        },
        {
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
        },
        {
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
        },
        {
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
        },
        {
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
        },
        {
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
        }
    };

    // Inventory sprite positions (source Rect from the sprite sheet)
    SDL_Rect m_inventorySpritesSrc[WPN_COUNT + INVENTORY_COUNT] =
    {
        {10,20,8,16},   // WPN_SWORD
        {0, 20,8,16},   // WPN_SHIELD
        {90,20,8,16},   // WPN_BOW
        {130,20,8,16},  // WPN_BOOMERANG
        {20,20,8,16},   // WPN_MAGIC_POWDER
        {70,20,8,16},   // WPN_BOMBS
        {40,20,8,16},   // WPN_POWER_BRACELET_1
        {80,20,8,16},   // WPN_POWER_BRACELET_2
        {30,20,8,16},   // WPN_ROC_FEATHER
        {120,20,8,16},  // WPN_HOOKSHOT
        {110,20,8,16},  // WPN_OCARINA
        {50,20,8,16},   // WPN_PEGASUS_BOOT
        {60,20,8,16},   // WPN_SHOVEL
        {100,20,8,16},  // WPN_FLAME_ROD
        {102,126,7,3},  // Inventory divider horizontal
        {110,126,3,7},  // Inventory divider vertical
        {109,116,5,8},  // "B"
        {102,116,5,8},  // "A"
        {72,116,28,14}, // Inventory selector (next to B)
        {72,116,28,14}, // Inventory selector (next to A)
        {116,116,7,7},  // Ruppee icon on HUD
        {0,0,8,8},      // INVENTORY_LEVEL
        {10,10,8,8},    // INVENTORY_DIGIT_B
        {10,0,8,8},     // INVENTORY_DIGIT_W
        {0,38,8,8},     // INVENTORY_HEART_WHOLE
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_0
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_1
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_2
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_3
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_4
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_5
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_6
        {110,2,16,16},  // INVENTORY_INSTRUMENT_BACK_7
        {140,0,16,16},  // INVENTORY_INSTRUMENT_0 
        {140,16,16,16},  // INVENTORY_INSTRUMENT_1
        {140,32,16,16},  // INVENTORY_INSTRUMENT_2
        {140,48,16,16},  // INVENTORY_INSTRUMENT_3
        {140,64,16,16},  // INVENTORY_INSTRUMENT_4
        {140,80,16,16},  // INVENTORY_INSTRUMENT_5
        {140,96,16,16},  // INVENTORY_INSTRUMENT_6
        {140,112,16,16},  // INVENTORY_INSTRUMENT_7
        {120,134,8,16},  // INVENTORY_COMPASS
        {90,134,8,16},  // INVENTORY_NIGHTMARE_KEY
        {130,134,8,16},  // INVENTORY_OWL_BEAK
        {110,134,8,16},  // INVENTORY_DUNGEON_MAP
        {100,134,8,16}, // INVENTORY_DUNGEON_KEY
        {70,134,8,16},  // INVENTORY_FLIPPERS
        {60,134,8,16},  // INVENTORY_POTION
        {80,134,8,16}, // INVENTORY_SEASHELLS
        {0,48,16,16}, // INVENTORY_DOLL
        {18,48,16,16}, // INVENTORY_BOW
        {36,48,16,16}, // INVENTORY_DOG_FOOD
        {54,48,16,16}, // INVENTORY_BANANAS
        {72,48,16,16}, // INVENTORY_STICK
        {90,48,16,16}, // INVENTORY_HONEYCOMB
        {108,48,16,16}, // INVENTORY_PINEAPPLE
        {0,66,16,16}, // INVENTORY_HIBISCUS
        {18,66,16,16}, // INVENTORY_LETTER
        {36,66,16,16}, // INVENTORY_BROOM
        {54,66,16,16}, // INVENTORY_HOOK
        {72,66,16,16}, // INVENTORY_NECKLACE
        {90,66,16,16}, // INVENTORY_MERMAID_SCALE
        {108,66,16,16}, // INVENTORY_LENS

        {0,134,8,16}, // INVENTORY_TAIL_KEY
        {40,134,8,16}, // INVENTORY_SLIME_KEY
        {10,134,8,16}, // INVENTORY_ANGLER_KEY
        {20,134,8,16}, // INVENTORY_FACE_KEY
        {30,134,8,16}, // INVENTORY_BIRD_KEY

        {90,162,8,8}, // INVENTORY_RED_ARROW
        {50,38,58,8}, // INVENTORY_PUSH_SELECT,

        {0,0,SELECT_SUBSCREEN_WIDTH,SELECT_SUBSCREEN_HEIGHT}, // INVENTORY_SUBSCREEN
        {0,100,31,14}, // INVENTORY_TUNIC (Green)
        {0,84,16,14}, // INVENTORY_HEART_PIECES
        {90,84,14,12}, // INVENTORY_PHOTOGRAPHS

        {126,116,8,8}, // INVENTORY_SLASH

        {0,152,8,8}, // INVENTORY_AREA_EXIT_RIGHT
        {10,152,8,8}, // INVENTORY_AREA_EXIT_LEFT
        {20,152,8,8}, // INVENTORY_AREA_EXIT_RIGHT_DOWN
        {30,152,8,8}, // INVENTORY_AREA_EXIT_LEFT_DOWN
        {40,152,8,8}, // INVENTORY_AREA_EXIT_NONE
        {50,152,8,8}, // INVENTORY_AREA_EXIT_LEFT_UP_DOWN
        {60,152,8,8}, // INVENTORY_AREA_EXIT_LEFT_DOWN_RIGHT
        {70,152,8,8}, // INVENTORY_AREA_UNVISITED
        {80,152,8,8}, // INVENTORY_AREA_EXIT_LEFT_RIGHT
        {90,152,8,8}, // INVENTORY_AREA_TREASURE
        {100,152,8,8}, // INVENTORY_AREA_NIGHTMARE
        {0,162,8,8}, // INVENTORY_AREA_EXIT_DOWN
        {10,162,8,8}, // INVENTORY_AREA_EXIT_UP
        {20,162,8,8}, // INVENTORY_AREA_EXIT_UP_RIGHT
        {30,162,8,8}, // INVENTORY_AREA_EXIT_LEFT_UP
        {40,162,8,8}, // INVENTORY_AREA_EXIT_ALL
        {50,162,8,8}, // INVENTORY_AREA_EXIT_UP_RIGHT_DOWN
        {60,162,8,8}, // INVENTORY_AREA_EXIT_UP_LEFT_DOWN
        {70,162,8,8}, // INVENTORY_AREA_EMPTY
        {80,162,8,8 }, // INVENTORY_AREA_EXIT_UP_DOWN
        {130,152,8,8},   // INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW
        {110,152,8,8},  // INVENTORY_DUNGEON_MAP_CURRENT_LOCATION
        { 130,2,8,16 }  // INVENTORY_ARROW


    };

    SDL_Rect m_inventorySpritesDst[sizeof(m_inventorySpritesSrc) / sizeof(m_inventorySpritesSrc[0])] =
    {
        {0,0,0,0},     // WPN_SWORD
        {0,0,0,0},     // WPN_SHIELD
        {0,0,0,0},     // WPN_BOW
        {0,0,0,0},     // WPN_BOOMERANG
        {0,0,0,0},     // WPN_MAGIC_POWDER
        {0,0,0,0},     // WPN_BOMBS
        {0,0,0,0},     // WPN_POWER_BRACELET_1
        {0,0,0,0},     // WPN_POWER_BRACELET_2
        {0,0,0,0},     // WPN_ROC_FEATHER
        {0,0,0,0},     // WPN_HOOKSHOT
        {0,0,0,0},     // WPN_OCARINA
        {0,0,0,0},     // WPN_PEGASUS_BOOT
        {0,0,0,0},     // WPN_SHOVEL
        {0,0,0,0},     // WPN_FLAME_ROD
        {0,0,0,0},     
        {0,0,0,0},     
        {1,1,5,8},     // "B"
        {41,1,5,8},    // "A"
        {6,1,28,14},   // Inventory selector (next to B)
        {46,1,28,14},  // Inventory selector (next to A)
        {81,1,7,7},    // Ruppee icon on HUD
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {104,0,8,8},     // INVENTORY_HEART_WHOLE
        {120,64,16,16},  // INVENTORY_INSTRUMENT_BACK_0
        {136,80,16,16},  // INVENTORY_INSTRUMENT_BACK_1
        {136,104,16,16}, // INVENTORY_INSTRUMENT_BACK_2
        {120,120,16,16}, // INVENTORY_INSTRUMENT_BACK_3
        {96,120,16,16},  // INVENTORY_INSTRUMENT_BACK_4
        {80,104,16,16},  // INVENTORY_INSTRUMENT_BACK_5
        {80,80,16,16},   // INVENTORY_INSTRUMENT_BACK_6
        {96,64,16,16},   // INVENTORY_INSTRUMENT_BACK_7
        {120,64,16,16},  // INVENTORY_INSTRUMENT_0
        {136,80,16,16},  // INVENTORY_INSTRUMENT_1
        {136,104,16,16}, // INVENTORY_INSTRUMENT_2
        {120,120,16,16}, // INVENTORY_INSTRUMENT_3
        {96,120,16,16},  // INVENTORY_INSTRUMENT_4
        {80,104,16,16},  // INVENTORY_INSTRUMENT_5
        {80,80,16,16},   // INVENTORY_INSTRUMENT_6
        {96,64,16,16},   // INVENTORY_INSTRUMENT_7
        {96,40,8,16},  // INVENTORY_COMPASS
        {128,40,8,16},  // INVENTORY_NIGHTMARE_KEY
        {112,40,8,16},  // INVENTORY_OWL_BEAK
        {80,40,8,16},  // INVENTORY_DUNGEON_MAP
        {144,40,8,16}, // INVENTORY_DUNGEON_KEY
        {80,24,8,16},  // INVENTORY_FLIPPERS
        {96,24,8,16},  // INVENTORY_POTION
        {136,24,8,16}, // INVENTORY_SEASHELLS

        {112,24,16,16}, // INVENTORY_DOLL
        {112,24,16,16}, // INVENTORY_BOW
        {112,24,16,16}, // INVENTORY_DOG_FOOD
        {112,24,16,16}, // INVENTORY_BANANAS
        {112,24,16,16}, // INVENTORY_STICK
        {112,24,16,16}, // INVENTORY_HONEYCOMB
        {112,24,16,16}, // INVENTORY_PINEAPPLE
        {112,24,16,16}, // INVENTORY_HIBISCUS
        {112,24,16,16}, // INVENTORY_LETTER
        {112,24,16,16}, // INVENTORY_BROOM
        {112,24,16,16}, // INVENTORY_HOOK
        {112,24,16,16}, // INVENTORY_NECKLACE
        {112,24,16,16}, // INVENTORY_MERMAID_SCALE
        {112,24,16,16}, // INVENTORY_LENS

        {80,40,8,16}, // INVENTORY_TAIL_KEY
        {144,40,8,16}, // INVENTORY_SLIME_KEY
        {96,40,8,16}, // INVENTORY_ANGLER_KEY
        {112,40,8,16}, // INVENTORY_FACE_KEY
        {128,40,8,16}, // INVENTORY_BIRD_KEY

        {75,136,8,8}, // INVENTORY_RED_ARROW
        {86,136,58,8}, // INVENTORY_PUSH_SELECT,

        {75,104,SELECT_SUBSCREEN_WIDTH,SELECT_SUBSCREEN_HEIGHT}, //INVENTORY_SUBSCREEN
        {1,1,31,14}, // INVENTORY_TUNIC (Green)
        {41,1,16,14}, // INVENTORY_HEART_PIECES
        {9,18,14,12}, // INVENTORY_PHOTOGRAPHS

        {40,24,8,8}, // INVENTORY_SLASH

        {88,56,8,8}, // INVENTORY_AREA_EXIT_RIGHT
        {88,56,8,8}, // INVENTORY_AREA_EXIT_LEFT
        {88,56,8,8}, // INVENTORY_AREA_EXIT_RIGHT_DOWN
        {88,56,8,8}, // INVENTORY_AREA_EXIT_LEFT_DOWN
        {88,56,8,8}, // INVENTORY_AREA_EXIT_NONE
        {88,56,8,8}, // INVENTORY_AREA_EXIT_LEFT_UP_DOWN
        {88,56,8,8}, // INVENTORY_AREA_EXIT_LEFT_DOWN_RIGHT
        {88,56,8,8}, // INVENTORY_AREA_UNVISITED
        {88,56,8,8}, // INVENTORY_AREA_EXIT_LEFT_RIGHT
        {88,56,8,8}, // INVENTORY_AREA_TREASURE
        {88,56,8,8}, // INVENTORY_AREA_NIGHTMARE
        {88,56,8,8}, // INVENTORY_AREA_EXIT_DOWN
        {88,56,8,8}, // INVENTORY_AREA_EXIT_UP
        {88,56,8,8}, // INVENTORY_AREA_EXIT_UP_RIGHT
        {88,56,8,8}, // INVENTORY_AREA_EXIT_LEFT_UP
        {88,56,8,8}, // INVENTORY_AREA_EXIT_ALL
        {88,56,8,8}, // INVENTORY_AREA_EXIT_UP_RIGHT_DOWN
        {88,56,8,8}, // INVENTORY_AREA_EXIT_UP_LEFT_DOWN
        {88,56,8,8}, // INVENTORY_AREA_EMPTY
        {88,56,8,8 }, // INVENTORY_AREA_EXIT_UP_DOWN
        {88,128,8,8},   // INVENTORY_DUNGEON_MAP_ENTRANCE_ARROW
        {0, 0, 8, 8},  // INVENTORY_DUNGEON_MAP_CURRENT_LOCATION
        { 0,0,8,16 }  // INVENTORY_ARROW
    };

};

#endif // !INVENTORY_H
