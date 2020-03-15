#ifndef INVENTORY_H
#define INVENTORY_H

#include "Controllable.h"
#include "Renderable.h"

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

#define HEARTS_PER_ROW 7

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
    WPN_LEVEL_1 = 1,
    WPN_LEVEL_2,
};

enum OCARINA_SONG
{
    SNG_MARIN = 1,
    SNG_FROG,
    SNG_FISH
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
    INVENTORY_COUNT = 12
};

class Inventory : public Controllable, public Renderable
{
public:
    Inventory();
    ~Inventory() = default;
    void control() override;
    void render(SDL_Renderer* pRenderer) override;
    void open();
    void close();
  
private:
    bool m_open;
    SDL_Texture* m_inventorySelector;   // Selector sprite
    SDL_Texture* m_inventoryDividerH;   // Horizontal divider
    SDL_Texture* m_inventoryDividerV;   // Vertical divider


    void drawInventoryItems(SDL_Renderer* pRenderer);
    void drawSelector(SDL_Renderer* pRenderer);
    void drawInventoryDividers(SDL_Renderer* pRenderer);
    void drawTopHUD(SDL_Renderer* pRenderer);
    void drawNumber(SDL_Renderer* pRenderer, SDL_Texture* srcTexture, bool drawLevel, bool useNormalFont, uint8_t trailingDigits, uint16_t number, SDL_Rect* dstRect);
    void drawWeaponLevel(SDL_Renderer* pRenderer, SDL_Texture* srcTexture, WEAPON weapon, SDL_Rect* dstRect);

    // Inventory related variables
    uint8_t m_arrows;         // Number of arrows
    uint8_t m_bombs;          // Number of bombs
    uint8_t m_magicPowder;    // Number of magic powder
    uint8_t m_swordLevel;     // Sword Level 1 or 2
    uint8_t m_shieldLevel;    // Shield Level 1 or 2
    uint8_t m_braceletLevel;  // Bracelet Level 1 or 2
    uint8_t m_ocarinaSong;    // Ocarina song level

    WEAPON m_weaponA;
    WEAPON m_weaponB;

    // Selector position 
    int m_selector_x; 
    int m_selector_y;
    // Index into inventory array
    uint8_t m_selector_index;
    // Timer for flashing the selector
    UpdateTimer m_selectorTimer;
    // Weapons
    WEAPON m_items[INVENTORY_MAX_WEAPONS];
    // Key press related stuff
    bool m_singleLeftRight;
    bool m_singleUpDown;
    bool m_singlePressA;
    bool m_singlePressB;
    bool m_flashSelector;

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
    };

    SDL_Rect m_inventorySpritesDst[sizeof(m_inventorySpritesSrc)] =
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
        {104,0,8,8},   // INVENTORY_HEART_WHOLE
    };
};



#endif // !INVENTORY_H
