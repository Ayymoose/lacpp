#define BOOST_TEST_MODULE ZeldaCoreTests
#include <boost/test/included/unit_test.hpp>

#include "zelda_core/Dialogue.h"
#include "zelda_core/Inventory.h"
#include "zelda_core/Worldmap.h"

#include <numeric>
#include <unordered_set>
#include <sstream>
#include <ranges>
#include <algorithm>
#include <string>

using namespace zelda;
using namespace zelda::core;

namespace dialogue_tests
{
struct QuestionChoices
{
    std::string question;
    std::string choice1;
    std::string choice2;

    bool empty() const { return question.empty() && choice1.empty() && choice2.empty(); }
};

static std::string rtrim(const std::string &s)
{
    auto view = s | std::views::reverse | std::views::drop_while([](char c) { return c == ' '; }) | std::views::reverse;
    return std::string(view.begin(), view.end());
}

static QuestionChoices findQuestionChoices(const std::string &str)
{
    if (str.length() < 16)
    {
        return {};
    }

    const auto askPos = str.rfind("<ask>");
    if (askPos == std::string::npos)
    {
        return {};
    }

    const auto searchString = str.substr(0, str.length() - 16);

    constexpr std::string_view questionChars = "?.! ";

    const auto start = std::accumulate(questionChars.begin(),
                                       questionChars.end(),
                                       std::string::npos,
                                       [&](size_t acc, char c)
                                       {
                                           const auto pos = searchString.find_last_of(c);
                                           if (pos == std::string::npos)
                                           {
                                               return acc;
                                           }
                                           return acc == std::string::npos ? pos : std::max(acc, pos);
                                       });

    if (start == std::string::npos)
    {
        return {};
    }

    const auto choices = str.substr(start + 1, askPos - (start + 1));
    const auto spaceStart = choices.find_first_not_of(' ');

    if (spaceStart == std::string::npos)
    {
        return {};
    }

    std::istringstream iss(choices.substr(spaceStart));
    std::string choice1, choice2;
    iss >> choice1;
    std::getline(iss >> std::ws, choice2);

    return {.question = rtrim(searchString), .choice1 = choice1, .choice2 = choice2};
}

static const std::unordered_set<std::string> ALL_GAME_MESSAGES = {
    "Whoa, boy! Where"
    "ya off to in    "
    "such a hurry?   "
    "Set a spell, I  "
    "got somethin' ta"
    "tell ya!@",
    "What a relief! I"
    "thought you'd   "
    "never wake up!  "
    "You were tossing"
    "and turning...  "
    "What?  Zelda?   "
    "No, my name's   "
    "Marin!  You must"
    "still be feeling"
    "a little woozy. "
    "You are on      "
    "Koholint Island!@",
    "So, how do you  "
    "like it?  It's  "
    "really touching,"
    "isn't it?  Does "
    "it stick in your"
    "mind?           "
    "    Yes  No<ask>",
    "Will you give me"
    "28 Rupees for my"
    "secret?         "
    "    Give Don't<ask>",
    "How about it?   "
    "42 Rupees for my"
    "little secret..."
    "    Give Don't<ask>",
    "Bow & Arrow Set "
    "Only 980 Rupees!"
    "    Buy  No Way<ask>",
    "   10 Arrows    "
    "   10 Rupees    "
    "    Buy  Don't<ask>",
    "  TRENDY GAME!  "
    " One Play 10 Rs."
    "    Play No<ask>",
    "Challenge Again?"
    "    Play No<ask>",
    "How about some  "
    "fishing, little "
    "buddy? I'll only"
    "charge you 10   "
    "Rupees...       "
    "    Fish Not Now"
    "<ask>",
    "Why not try one "
    "more time,      "
    "little buddy?   "
    "    Cast Not Now"
    "<ask>",
    "Ribbit!  Ribbit!"
    "I'm Mamu, on    "
    "vocals!  But I  "
    "don't need to   "
    "tell you that,  "
    "do I?  Everybody"
    "knows me!  Want "
    "to hang out and "
    "listen to us    "
    "jam?  For 300   "
    "Rupees, we'll   "
    "let you listen  "
    "to a previously "
    "unreleased cut! "
    "What do you do? "
    "    Pay  Leave<ask>",
    "Hey, Kid!  You  "
    "woke me up from "
    "a fine nap!!    "
    "...Thanks a lot!"
    "But now, I'll   "
    "get my revenge! "
    "Are you ready?! "
    "    Yes  N-No<ask>",
    "Red for offense,"
    "blue for        "
    "defense. Which  "
    "do you choose?  "
    "    RED  BLUE<ask>",
    "Are you sure?   "
    "    YES  NO<ask>",
    "Welcome, #####. "
    "I admire you for"
    "coming this far."
    "I will give you "
    "the power of    "
    "color. If you   "
    "want offense,   "
    "choose red. If  "
    "you want defense"
    "choose blue.    "
    "Which power do  "
    "you want?       "
    "    RED  BLUE<ask>",
    "Wow!  #####, can"
    "I try this?!    "
    "What do you say?"
    "    Okay No Way<ask>",
    "Oh!  Will you   "
    "give that doll  "
    "to my baby?!    "
    "    Yes  No<ask>",
    "Want to go on a "
    "raft ride for a "
    "hundred Rupees? "
    "    Yes  No Way<ask>",
};

BOOST_AUTO_TEST_SUITE(DialogueTests)

BOOST_AUTO_TEST_CASE(FindQuestionChoices_EmptyString)
{
    const auto result = findQuestionChoices("");
    BOOST_TEST(result.empty());
}

BOOST_AUTO_TEST_CASE(FindQuestionChoices_NoAskTag)
{
    const auto result = findQuestionChoices("aaa");
    BOOST_TEST(result.empty());
}

BOOST_AUTO_TEST_CASE(FindQuestionChoices_ValidQuestion)
{
    const auto result = findQuestionChoices("Will you give me"
                                            "28 Rupees for my"
                                            "secret?         "
                                            "    Give Don't<ask>");

    BOOST_TEST(result.question
               == "Will you give me"
                  "28 Rupees for my"
                  "secret?");
    BOOST_TEST(result.choice1 == "Give");
    BOOST_TEST(result.choice2 == "Don't");
}

BOOST_AUTO_TEST_CASE(FindQuestionChoices_YesNo)
{
    const auto result = findQuestionChoices("Are you sure?   "
                                            "    YES  NO<ask>");

    BOOST_TEST(result.choice1 == "YES");
    BOOST_TEST(result.choice2 == "NO");
}

BOOST_AUTO_TEST_CASE(FindQuestionChoices_HyphenatedChoice)
{
    const auto result = findQuestionChoices("Are you ready?! "
                                            "    Yes  N-No<ask>");

    BOOST_TEST(result.choice1 == "Yes");
    BOOST_TEST(result.choice2 == "N-No");
}

BOOST_AUTO_TEST_CASE(FindQuestionChoices_ChoicesOnNewLine)
{
    const auto result = findQuestionChoices("How about some  "
                                            "fishing, little "
                                            "buddy? I'll only"
                                            "charge you 10   "
                                            "Rupees...       "
                                            "    Fish Not Now"
                                            "<ask>");

    BOOST_TEST(result.choice1 == "Fish");
    BOOST_TEST(result.choice2 == "Not Now");
}

BOOST_AUTO_TEST_CASE(AllGameMessagesAreValid)
{
    Dialogue d;
    BOOST_CHECK_NO_THROW(for (const auto &msg : ALL_GAME_MESSAGES) {
        if (const auto result = findQuestionChoices(msg); !result.empty())
        {
            d.question(result.question, result.choice1, result.choice2, 0);
        }
        else
        {
            d.message(msg, 0);
        }
    });
}

BOOST_AUTO_TEST_CASE(AllGameMessagesQueuedCorrectly)
{
    Dialogue d;

    for (const auto &msg : ALL_GAME_MESSAGES)
    {
        if (const auto result = findQuestionChoices(msg); !result.empty())
        {
            d.question(result.question, result.choice1, result.choice2, 0);
        }
        else
        {
            d.message(msg, 0);
        }
    }

    BOOST_TEST(d.messages() == static_cast<int>(ALL_GAME_MESSAGES.size()));
}

BOOST_AUTO_TEST_CASE(MessageIsQueued)
{
    Dialogue d;
    d.message("Hello world!", 0);
    BOOST_TEST(d.messages() == 1);
}

BOOST_AUTO_TEST_CASE(MultipleMessagesQueued)
{
    Dialogue d;
    d.message("Hello world!", 0);
    d.message("Another message", 0);
    BOOST_TEST(d.messages() == 2);
}

BOOST_AUTO_TEST_CASE(MessagePopsCorrectly)
{
    Dialogue d;
    d.message("Hello world!", 0);
    d.checkForNewMessages(0);
    BOOST_TEST(d.message() == "Hello world!");
    BOOST_TEST(d.messages() == 0);
}

BOOST_AUTO_TEST_CASE(MessageIsNotPoppedWhenCurrentCharIsNotZero)
{
    Dialogue d;
    d.message("Hello world!", 0);
    d.checkForNewMessages(1);
    BOOST_TEST(d.messages() == 1);
}

BOOST_AUTO_TEST_CASE(MessageIsNotQuestion)
{
    Dialogue d;
    d.message("Hello world!", 0);
    d.checkForNewMessages(0);
    BOOST_TEST(!d.isQuestion());
}

BOOST_AUTO_TEST_CASE(MessageSetsDialogueYLow)
{
    Dialogue d;
    d.message("Hello world!", 0);
    d.checkForNewMessages(0);
    BOOST_TEST(d.dialogueY() == d.dialoguePosYLow());
}

BOOST_AUTO_TEST_CASE(MessageSetsDialogueYHigh)
{
    Dialogue d;
    d.message("Hello world!", 200.0f);
    d.checkForNewMessages(0);
    BOOST_TEST(d.dialogueY() == d.dialoguePosYHigh());
}

BOOST_AUTO_TEST_CASE(MessagesPopInOrder)
{
    Dialogue d;
    d.message("First", 0);
    d.message("Second", 0);

    d.checkForNewMessages(0);
    BOOST_TEST(d.message() == "First");

    d.checkForNewMessages(0);
    BOOST_TEST(d.message() == "Second");
}

BOOST_AUTO_TEST_CASE(QuestionIsQueued)
{
    Dialogue d;
    d.question("Are you sure?", "Yes", "No", 0);
    BOOST_TEST(d.messages() == 1);
}

BOOST_AUTO_TEST_CASE(QuestionPopsCorrectly)
{
    Dialogue d;
    d.question("Are you sure?", "Yes", "No", 0);
    d.checkForNewMessages(0);
    BOOST_TEST(d.isQuestion());
}

BOOST_AUTO_TEST_CASE(QuestionChoice1IsDefaultSelected)
{
    Dialogue d;
    d.question("Are you sure?", "Yes", "No", 0);
    d.checkForNewMessages(0);
    BOOST_TEST(d.choice() == d.choice1());
    BOOST_TEST(d.choice1() == "Yes");
}

BOOST_AUTO_TEST_CASE(QuestionChoice2IsCorrect)
{
    Dialogue d;
    d.question("Are you sure?", "Yes", "No", 0);
    d.checkForNewMessages(0);
    BOOST_TEST(d.choice2() == "No");
}

BOOST_AUTO_TEST_CASE(SetChoice1)
{
    Dialogue d;
    d.question("Are you sure?", "Yes", "No", 0);
    d.checkForNewMessages(0);
    d.setChoice2();
    d.setChoice1();
    BOOST_TEST(d.choice() == "Yes");
}

BOOST_AUTO_TEST_CASE(SetChoice2)
{
    Dialogue d;
    d.question("Are you sure?", "Yes", "No", 0);
    d.checkForNewMessages(0);
    d.setChoice2();
    BOOST_TEST(d.choice() == "No");
}

BOOST_AUTO_TEST_CASE(QuestionSetsDialogueYLow)
{
    Dialogue d;
    d.question("Are you sure?", "Yes", "No", 0);
    d.checkForNewMessages(0);
    BOOST_TEST(d.dialogueY() == d.dialoguePosYLow());
}

BOOST_AUTO_TEST_CASE(QuestionSetsDialogueYHigh)
{
    Dialogue d;
    d.question("Are you sure?", "Yes", "No", 200.0f);
    d.checkForNewMessages(0);
    BOOST_TEST(d.dialogueY() == d.dialoguePosYHigh());
}

BOOST_AUTO_TEST_CASE(QuestionIsNotPoppedWhenCurrentCharIsNotZero)
{
    Dialogue d;
    d.question("Are you sure?", "Yes", "No", 0);
    d.checkForNewMessages(1);
    BOOST_TEST(d.messages() == 1);
}

BOOST_AUTO_TEST_CASE(MessageThenQuestion)
{
    Dialogue d;
    d.message("Hello world!", 0);
    d.question("Are you sure?", "Yes", "No", 0);

    d.checkForNewMessages(0);
    BOOST_TEST(!d.isQuestion());
    BOOST_TEST(d.message() == "Hello world!");

    d.checkForNewMessages(0);
    BOOST_TEST(d.isQuestion());
    BOOST_TEST(d.choice1() == "Yes");
    BOOST_TEST(d.choice2() == "No");
}

BOOST_AUTO_TEST_CASE(QuestionThenMessage)
{
    Dialogue d;
    d.question("Are you sure?", "Yes", "No", 0);
    d.message("Hello world!", 0);

    d.checkForNewMessages(0);
    BOOST_TEST(d.isQuestion());

    d.checkForNewMessages(0);
    BOOST_TEST(!d.isQuestion());
    BOOST_TEST(d.message() == "Hello world!");
}

BOOST_AUTO_TEST_CASE(DialogueWidth)
{
    BOOST_TEST(Dialogue::dialogueWidth() == 144);
}

BOOST_AUTO_TEST_CASE(DialogueHeight)
{
    BOOST_TEST(Dialogue::dialogueHeight() == 40);
}

BOOST_AUTO_TEST_CASE(MaxLines)
{
    Dialogue d;
    BOOST_TEST(d.maxLines() == 2);
}

BOOST_AUTO_TEST_CASE(LineHeight)
{
    Dialogue d;
    BOOST_TEST(d.lineHeight() == 16);
}

BOOST_AUTO_TEST_CASE(CharWidth)
{
    Dialogue d;
    BOOST_TEST(d.charWidth() == 8);
}

BOOST_AUTO_TEST_CASE(CharHeight)
{
    Dialogue d;
    BOOST_TEST(d.charHeight() == 8);
}

BOOST_AUTO_TEST_CASE(MaxCharsPerLine)
{
    Dialogue d;
    BOOST_TEST(d.maxCharsPerLine() == 16);
}

BOOST_AUTO_TEST_CASE(DialoguePosX)
{
    Dialogue d;
    BOOST_TEST(d.dialoguePosX() == 8);
}

BOOST_AUTO_TEST_CASE(DialoguePosYLow)
{
    Dialogue d;
    BOOST_TEST(d.dialoguePosYLow() == 80);
}

BOOST_AUTO_TEST_CASE(DialoguePosYHigh)
{
    Dialogue d;
    BOOST_TEST(d.dialoguePosYHigh() == 8);
}

BOOST_AUTO_TEST_CASE(ValidLowerCase)
{
    Dialogue d;
    BOOST_CHECK_NO_THROW(d.message("hello world", 0));
}

BOOST_AUTO_TEST_CASE(ValidUpperCase)
{
    Dialogue d;
    BOOST_CHECK_NO_THROW(d.message("HELLO WORLD", 0));
}

BOOST_AUTO_TEST_CASE(ValidDigits)
{
    Dialogue d;
    BOOST_CHECK_NO_THROW(d.message("0123456789", 0));
}

BOOST_AUTO_TEST_CASE(ValidPunctuation)
{
    Dialogue d;
    BOOST_CHECK_NO_THROW(d.message("Hello! Are you okay? It's fine, yes.", 0));
}

BOOST_AUTO_TEST_CASE(ValidSpecialCharacters)
{
    Dialogue d;
    BOOST_CHECK_NO_THROW(d.message("#####", 0));
}

BOOST_AUTO_TEST_CASE(ValidParenthesesAndAmpersand)
{
    Dialogue d;
    BOOST_CHECK_NO_THROW(d.message("(hello) & world", 0));
}

BOOST_AUTO_TEST_CASE(OptionPaddingIsSet)
{
    Dialogue d;
    d.question("Are you sure?", "Yes", "No", 0);
    d.checkForNewMessages(0);
    BOOST_TEST(d.optionPaddingLength() > 0);
}

BOOST_AUTO_TEST_CASE(OptionPaddingSymmetric)
{
    Dialogue d1;
    Dialogue d2;

    d1.question("Are you sure?", "Yes", "No", 0);
    d2.question("Different question here", "Yes", "No", 0);

    d1.checkForNewMessages(0);
    d2.checkForNewMessages(0);

    BOOST_TEST(d1.optionPaddingLength() == d2.optionPaddingLength());
}

BOOST_AUTO_TEST_CASE(EmptyQueueOnConstruction)
{
    Dialogue d;
    BOOST_TEST(d.messages() == 0);
}

BOOST_AUTO_TEST_CASE(CheckForNewMessagesOnEmptyQueueDoesNotCrash)
{
    Dialogue d;
    BOOST_CHECK_NO_THROW(d.checkForNewMessages(0));
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace dialogue_tests

namespace inventory_tests
{
// A few convenient InventoryItem factories
static InventoryItem makeSword()
{
    return InventoryItem{UsableItem::SWORD, ItemAttribute::LEVEL, 1};
}
static InventoryItem makeShield()
{
    return InventoryItem{UsableItem::SHIELD, ItemAttribute::LEVEL, 1};
}
static InventoryItem makeBow()
{
    return InventoryItem{UsableItem::BOW, ItemAttribute::QUANTITY, 5};
}

BOOST_AUTO_TEST_SUITE(InventoryTests)

BOOST_AUTO_TEST_CASE(DefaultState)
{
    Inventory inv;

    BOOST_TEST(inv.rupees() == 0);
    BOOST_TEST(inv.bombs() == 0);
    BOOST_TEST(inv.arrows() == 0);
    BOOST_TEST(inv.magicPowder() == 0);
    BOOST_TEST(inv.heartContainerPieces() == 0);
    BOOST_TEST(inv.heartPieces() == 0.0f);
    BOOST_TEST(inv.maxHeartPieces() == 0.0f);
    BOOST_TEST(inv.goldenLeaves() == 0);
    BOOST_TEST(inv.secretSeaShells() == 0);
    BOOST_TEST(inv.photograph() == 0);
    BOOST_TEST(inv.getInDungeon() == false);
    BOOST_TEST(std::to_underlying(inv.dungeon()) == std::to_underlying(Dungeon::NONE));
    BOOST_TEST(std::to_underlying(inv.tunic()) == std::to_underlying(Tunic::GREEN));
    BOOST_TEST(std::to_underlying(inv.tradedItem()) == std::to_underlying(TradeItem::NONE));
    BOOST_TEST(std::to_underlying(inv.ocarinaSong()) == std::to_underlying(OcarinaSong::NONE));

    // itemA / itemB should be default (NONE) items
    BOOST_TEST(inv.itemA() == InventoryItem{});
    BOOST_TEST(inv.itemB() == InventoryItem{});

    // All inventory slots empty
    for (const auto &item : inv.inventoryItems())
        BOOST_TEST(item == InventoryItem{});
}

BOOST_AUTO_TEST_CASE(AddAndExistsItem)
{
    Inventory inv;
    auto sword = makeSword();
    inv.addInventoryItem(sword);
    BOOST_TEST(inv.inventoryItemExists(sword));
}

BOOST_AUTO_TEST_CASE(AddMultipleItems)
{
    Inventory inv;
    inv.addInventoryItem(makeSword());
    inv.addInventoryItem(makeShield());
    inv.addInventoryItem(makeBow());
    BOOST_TEST(inv.inventoryItemExists(makeSword()));
    BOOST_TEST(inv.inventoryItemExists(makeShield()));
    BOOST_TEST(inv.inventoryItemExists(makeBow()));
}

BOOST_AUTO_TEST_CASE(RemoveItem)
{
    Inventory inv;
    auto sword = makeSword();
    inv.addInventoryItem(sword);
    inv.removeInventoryItem(sword);
    BOOST_TEST(!inv.inventoryItemExists(sword));
}

BOOST_AUTO_TEST_CASE(NonExistentItemNotFound)
{
    Inventory inv;
    BOOST_TEST(!inv.inventoryItemExists(makeSword()));
}

BOOST_AUTO_TEST_CASE(ItemExistsViaItemA)
{
    Inventory inv;
    auto sword = makeSword();
    inv.setItemA(sword);
    // inventoryItemExists checks itemA/B as well
    BOOST_TEST(inv.inventoryItemExists(sword));
}

BOOST_AUTO_TEST_CASE(ItemExistsViaItemB)
{
    Inventory inv;
    auto sword = makeSword();
    inv.setItemB(sword);
    BOOST_TEST(inv.inventoryItemExists(sword));
}

BOOST_AUTO_TEST_CASE(InventoryItemsArrayReturnsCorrectContent)
{
    Inventory inv;
    inv.addInventoryItem(makeSword());
    auto items = inv.inventoryItems();
    bool found = false;
    for (const auto &item : items)
        if (item == makeSword())
            found = true;
    BOOST_TEST(found);
}

BOOST_AUTO_TEST_CASE(SetItemA)
{
    Inventory inv;
    inv.setItemA(makeSword());
    BOOST_TEST(inv.itemA() == makeSword());
}

BOOST_AUTO_TEST_CASE(SetItemB)
{
    Inventory inv;
    inv.setItemB(makeShield());
    BOOST_TEST(inv.itemB() == makeShield());
}

BOOST_AUTO_TEST_CASE(SwapItemA_ExchangesWithSelectorSlot)
{
    Inventory inv;
    // Place bow in slot 0 (default selector index is 0)
    inv.addInventoryItem(makeBow());
    inv.setItemA(makeSword());
    inv.swapItemA();
    // itemA should now hold the bow; slot 0 should hold the sword
    BOOST_TEST(inv.itemA() == makeBow());
    BOOST_TEST(inv.inventoryItems()[0] == makeSword());
}

BOOST_AUTO_TEST_CASE(SwapItemB_ExchangesWithSelectorSlot)
{
    Inventory inv;
    inv.addInventoryItem(makeBow());
    inv.setItemB(makeShield());
    inv.swapItemB();
    BOOST_TEST(inv.itemB() == makeBow());
    BOOST_TEST(inv.inventoryItems()[0] == makeShield());
}

BOOST_AUTO_TEST_CASE(MoveRight_WrapsAtEnd)
{
    Inventory inv;
    // Move right 9 times to reach index 9
    for (int i = 0; i < 9; ++i)
        inv.moveInventorySelector(Direction::RIGHT);
    // One more right wraps to 0 - verified indirectly via swapItemA
    inv.addInventoryItem(makeSword());                     // fills slot 0
    inv.moveInventorySelector(Direction::RIGHT); // should wrap to 0
    inv.setItemA(makeShield());
    inv.swapItemA();
    BOOST_TEST(inv.itemA() == makeSword());
}

BOOST_AUTO_TEST_CASE(MoveLeft_WrapsAtStart)
{
    Inventory inv;
    inv.addInventoryItem(makeSword()); // fills slot 0
    // selector is at 0, moving left should wrap to MAX_INVENTORY_ITEMS-1 = 9
    inv.moveInventorySelector(Direction::LEFT);
    // Move back right 9 times to get to slot 0
    for (int i = 0; i < 9; ++i)
        inv.moveInventorySelector(Direction::LEFT);
    inv.setItemA(makeShield());
    inv.swapItemA();
    BOOST_TEST(inv.itemA() == makeSword());
}

BOOST_AUTO_TEST_CASE(MoveDown_WrapsAtBottom)
{
    Inventory inv;
    inv.addInventoryItem(makeSword()); // slot 0
    // Move down past last row (index 8 or 9 -> wraps to 0)
    for (int i = 0; i < 5; ++i)
        inv.moveInventorySelector(Direction::DOWN);
    inv.setItemA(makeShield());
    inv.swapItemA();
    BOOST_TEST(inv.itemA() == makeSword());
}

BOOST_AUTO_TEST_CASE(MoveUp_WrapsAtTop)
{
    Inventory inv;
    // selector starts at 0 - moving up should wrap to MAX_INVENTORY_ITEMS-1
    inv.moveInventorySelector(Direction::UP);
    // Slot 9 is in the last row, so one DOWN wraps back to slot 0
    inv.moveInventorySelector(Direction::DOWN);
    // Selector should now be at 0; add sword there and confirm swap
    inv.addInventoryItem(makeSword());
    inv.setItemA(makeShield());
    inv.swapItemA();
    BOOST_TEST(inv.itemA() == makeSword());
}

BOOST_AUTO_TEST_CASE(AddAndCheckKey)
{
    Inventory inv;
    inv.addDungeonEntranceKey(DungeonEntranceKey::TAIL);
    BOOST_TEST(inv.dungeonEntranceKey(DungeonEntranceKey::TAIL));
}

BOOST_AUTO_TEST_CASE(UnaddedKeyNotPresent)
{
    Inventory inv;
    BOOST_TEST(!inv.dungeonEntranceKey(DungeonEntranceKey::ANGLER));
}

BOOST_AUTO_TEST_CASE(AddAllKeys)
{
    Inventory inv;
    inv.addDungeonEntranceKey(DungeonEntranceKey::TAIL);
    inv.addDungeonEntranceKey(DungeonEntranceKey::SLIME);
    inv.addDungeonEntranceKey(DungeonEntranceKey::ANGLER);
    inv.addDungeonEntranceKey(DungeonEntranceKey::FACE);
    inv.addDungeonEntranceKey(DungeonEntranceKey::BIRD);
    BOOST_TEST(inv.dungeonEntranceKey(DungeonEntranceKey::BIRD));
}

static void enterDungeon(Inventory &inv, Dungeon d = Dungeon::TAIL_CAVE)
{
    inv.setInDungeon(true);
    inv.setDungeon(d);
}

BOOST_AUTO_TEST_CASE(AddLockedDoorKey_Increments)
{
    Inventory inv;
    enterDungeon(inv);
    inv.addDungeonItem(DungeonItem::LOCKED_DOOR_KEY);
    inv.addDungeonItem(DungeonItem::LOCKED_DOOR_KEY);
    BOOST_TEST(inv.dungeonItem(DungeonItem::LOCKED_DOOR_KEY) == 2);
}

BOOST_AUTO_TEST_CASE(UseLockedDoorKey_Decrements)
{
    Inventory inv;
    enterDungeon(inv);
    inv.addDungeonItem(DungeonItem::LOCKED_DOOR_KEY);
    inv.useDungeonItem(DungeonItem::LOCKED_DOOR_KEY);
    BOOST_TEST(inv.dungeonItem(DungeonItem::LOCKED_DOOR_KEY) == 0);
}

BOOST_AUTO_TEST_CASE(AddCompass)
{
    Inventory inv;
    enterDungeon(inv);
    inv.addDungeonItem(DungeonItem::COMPASS);
    BOOST_TEST(inv.dungeonItem(DungeonItem::COMPASS) == 1);
}

BOOST_AUTO_TEST_CASE(AddMap)
{
    Inventory inv;
    enterDungeon(inv);
    inv.addDungeonItem(DungeonItem::MAP);
    BOOST_TEST(inv.dungeonItem(DungeonItem::MAP) == 1);
}

BOOST_AUTO_TEST_CASE(AddNightmareKey)
{
    Inventory inv;
    enterDungeon(inv);
    inv.addDungeonItem(DungeonItem::NIGHTMARE_KEY);
    BOOST_TEST(inv.dungeonItem(DungeonItem::NIGHTMARE_KEY) == 1);
}

BOOST_AUTO_TEST_CASE(AddOwlBeak)
{
    Inventory inv;
    enterDungeon(inv);
    inv.addDungeonItem(DungeonItem::OWL_BEAK);
    BOOST_TEST(inv.dungeonItem(DungeonItem::OWL_BEAK) == 1);
}

BOOST_AUTO_TEST_CASE(DungeonItemsArePerDungeon)
{
    Inventory inv;
    enterDungeon(inv, Dungeon::TAIL_CAVE);
    inv.addDungeonItem(DungeonItem::LOCKED_DOOR_KEY);

    inv.setDungeon(Dungeon::BOTTLE_GROTTO);
    BOOST_TEST(inv.dungeonItem(DungeonItem::LOCKED_DOOR_KEY) == 0);
}

BOOST_AUTO_TEST_CASE(SetAndGetInDungeon)
{
    Inventory inv;
    inv.setInDungeon(true);
    BOOST_TEST(inv.getInDungeon());
    inv.setInDungeon(false);
    BOOST_TEST(!inv.getInDungeon());
}

BOOST_AUTO_TEST_CASE(SetAndGetDungeon)
{
    Inventory inv;
    inv.setDungeon(Dungeon::EAGLE_TOWER);
    BOOST_TEST(std::to_underlying(inv.dungeon()) == std::to_underlying(Dungeon::EAGLE_TOWER));
}

BOOST_AUTO_TEST_CASE(VisitedDefaultsFalse)
{
    Inventory inv;
    inv.setDungeon(Dungeon::TAIL_CAVE);
    BOOST_TEST(!inv.dungeonMapLocationVisited(0, 0));
}

BOOST_AUTO_TEST_CASE(SetVisitedReturnsTrue)
{
    Inventory inv;
    inv.setDungeon(Dungeon::TAIL_CAVE);
    engine::Vector<int> loc{2, 3};
    inv.setDungeonMapLocationVisited(loc);
    BOOST_TEST(inv.dungeonMapLocationVisited(2, 3));
}

BOOST_AUTO_TEST_CASE(RoomTypeIsReadable)
{
    Inventory inv;
    inv.setDungeon(Dungeon::COLOUR_DUNGEON);
    // Colour Dungeon row 0 is all 1s according to the initialiser
    BOOST_TEST(inv.dungeonMapLocationRoomType(0, 0) == 1);
}

BOOST_AUTO_TEST_CASE(RoomItemIsReadable)
{
    Inventory inv;
    inv.setDungeon(Dungeon::COLOUR_DUNGEON);
    // row 4, col 6 (x=6,y=4) has DUNGEON_MAP_ITEM_NIGHTMARE_KEY in colour dungeon
    BOOST_TEST(std::to_underlying(inv.dungeonMapLocationRoomItem(6, 4))
               == std::to_underlying(DungeonMapItem::NIGHTMARE_KEY));
}

BOOST_AUTO_TEST_CASE(SetAndGetPosition)
{
    Inventory inv;
    engine::Vector<int> pos{3, 4};
    inv.setPositionInDungeonMap(pos);
    BOOST_TEST(inv.dungeonMapPositionLocation().x == 3);
    BOOST_TEST(inv.dungeonMapPositionLocation().y == 4);
}

BOOST_AUTO_TEST_CASE(MoveDown_IncrementsY)
{
    Inventory inv;
    inv.setPositionInDungeonMap({0, 0});
    inv.movePositionInDungeonMap(Direction::DOWN);
    BOOST_TEST(inv.dungeonMapPositionLocation().y == 1);
}

BOOST_AUTO_TEST_CASE(MoveUp_DecrementsY)
{
    Inventory inv;
    inv.setPositionInDungeonMap({0, 2});
    inv.movePositionInDungeonMap(Direction::UP);
    BOOST_TEST(inv.dungeonMapPositionLocation().y == 1);
}

BOOST_AUTO_TEST_CASE(MoveRight_IncrementsX)
{
    Inventory inv;
    inv.setPositionInDungeonMap({0, 0});
    inv.movePositionInDungeonMap(Direction::RIGHT);
    BOOST_TEST(inv.dungeonMapPositionLocation().x == 1);
}

BOOST_AUTO_TEST_CASE(MoveLeft_DecrementsX)
{
    Inventory inv;
    inv.setPositionInDungeonMap({3, 0});
    inv.movePositionInDungeonMap(Direction::LEFT);
    BOOST_TEST(inv.dungeonMapPositionLocation().x == 2);
}

BOOST_AUTO_TEST_CASE(TradeItem_SetsCurrentTradeItem)
{
    Inventory inv;
    inv.tradeItem(TradeItem::YOSHI_DOLL);
    BOOST_TEST(std::to_underlying(inv.tradedItem()) == std::to_underlying(TradeItem::YOSHI_DOLL));
}

BOOST_AUTO_TEST_CASE(SetTradeItem)
{
    Inventory inv;
    inv.setTradeItem(TradeItem::RIBBON);
    BOOST_TEST(std::to_underlying(inv.tradedItem()) == std::to_underlying(TradeItem::RIBBON));
}

BOOST_AUTO_TEST_CASE(AddAndCheckRedPotion)
{
    Inventory inv;
    inv.addInventoryMiscItem(InventoryMiscItem::RED_POTION);
    BOOST_TEST(inv.miscItemExists(InventoryMiscItem::RED_POTION));
}

BOOST_AUTO_TEST_CASE(UseRedPotion_RemovesIt)
{
    Inventory inv;
    inv.addInventoryMiscItem(InventoryMiscItem::RED_POTION);
    inv.useInventoryMiscItem(InventoryMiscItem::RED_POTION);
    BOOST_TEST(!inv.miscItemExists(InventoryMiscItem::RED_POTION));
}

BOOST_AUTO_TEST_CASE(AddFlippers)
{
    Inventory inv;
    inv.addInventoryMiscItem(InventoryMiscItem::FLIPPERS);
    BOOST_TEST(inv.miscItemExists(InventoryMiscItem::FLIPPERS));
}

BOOST_AUTO_TEST_CASE(MiscItemAbsentByDefault)
{
    Inventory inv;
    BOOST_TEST(!inv.miscItemExists(InventoryMiscItem::RED_POTION));
}

BOOST_AUTO_TEST_CASE(AddAndCheckInstrument)
{
    Inventory inv;
    inv.addInstrument(Instrument::FULL_MOON_CELLO);
    BOOST_TEST(inv.instrumentExists(Instrument::FULL_MOON_CELLO));
}

BOOST_AUTO_TEST_CASE(UnaddedInstrumentNotPresent)
{
    Inventory inv;
    BOOST_TEST(!inv.instrumentExists(Instrument::THUNDER_DRUM));
}

BOOST_AUTO_TEST_CASE(AddAllInstruments)
{
    Inventory inv;
    inv.addInstrument(Instrument::FULL_MOON_CELLO);
    inv.addInstrument(Instrument::CONCH_HORN);
    inv.addInstrument(Instrument::SEA_LILY_BELL);
    inv.addInstrument(Instrument::SURF_HARP);
    inv.addInstrument(Instrument::WIND_MARIMBA);
    inv.addInstrument(Instrument::CORAL_TRIANGLE);
    inv.addInstrument(Instrument::ORGAN_OF_EVENING_CALM);
    inv.addInstrument(Instrument::THUNDER_DRUM);
    BOOST_TEST(inv.instrumentExists(Instrument::THUNDER_DRUM));
}

BOOST_AUTO_TEST_CASE(InstrumentsArrayReflectsAdded)
{
    Inventory inv;
    inv.addInstrument(Instrument::SURF_HARP);
    auto arr = inv.instruments();
    bool found = false;
    for (auto i : arr)
        if (i == Instrument::SURF_HARP)
            found = true;
    BOOST_TEST(found);
}

BOOST_AUTO_TEST_CASE(AddRupee_Increments)
{
    Inventory inv;
    inv.addRupee();
    BOOST_TEST(inv.rupees() == 1);
}

BOOST_AUTO_TEST_CASE(UseRupee_Decrements)
{
    Inventory inv;
    inv.addRupee();
    inv.useRupee();
    BOOST_TEST(inv.rupees() == 0);
}

BOOST_AUTO_TEST_CASE(UseRupee_DoesNotGoBelowZero)
{
    Inventory inv;
    inv.useRupee();
    BOOST_TEST(inv.rupees() == 0);
}

BOOST_AUTO_TEST_CASE(SetRupees)
{
    Inventory inv;
    inv.setRupees(500);
    BOOST_TEST(inv.rupees() == 500);
}

BOOST_AUTO_TEST_CASE(SetRupees_CapsAtMax)
{
    Inventory inv;
    inv.setRupees(MAX_RUPEES + 100);
    BOOST_TEST(inv.rupees() == MAX_RUPEES);
}

BOOST_AUTO_TEST_CASE(AddRupee_CapsAtMax)
{
    Inventory inv;
    inv.setRupees(MAX_RUPEES);
    inv.addRupee();
    BOOST_TEST(inv.rupees() == MAX_RUPEES);
}

BOOST_AUTO_TEST_CASE(SetAndGetBombs)
{
    Inventory inv;
    inv.setBombLimit(MAX_BOMBS_1);
    inv.setBombs(10);
    BOOST_TEST(inv.bombs() == 10);
}

BOOST_AUTO_TEST_CASE(SetBombs_CapsAtLimit)
{
    Inventory inv;
    inv.setBombLimit(MAX_BOMBS_1);
    inv.setBombs(MAX_BOMBS_1 + 5);
    BOOST_TEST(inv.bombs() == MAX_BOMBS_1);
}

BOOST_AUTO_TEST_CASE(UseBomb_Decrements)
{
    Inventory inv;
    inv.setBombLimit(MAX_BOMBS_1);
    inv.setBombs(5);
    inv.useBomb();
    BOOST_TEST(inv.bombs() == 4);
}

BOOST_AUTO_TEST_CASE(UseBomb_DoesNotGoBelowZero)
{
    Inventory inv;
    inv.setBombLimit(MAX_BOMBS_1);
    inv.setBombs(0);
    inv.useBomb();
    BOOST_TEST(inv.bombs() == 0);
}

BOOST_AUTO_TEST_CASE(SetBombLimit_UpgradesCapacity)
{
    Inventory inv;
    inv.setBombLimit(MAX_BOMBS_1);
    inv.setBombs(MAX_BOMBS_1);
    inv.setBombLimit(MAX_BOMBS_2);
    inv.setBombs(MAX_BOMBS_2);
    BOOST_TEST(inv.bombs() == MAX_BOMBS_2);
}

BOOST_AUTO_TEST_CASE(SetAndGetArrows)
{
    Inventory inv;
    inv.setArrowLimit(MAX_ARROWS_1);
    inv.setArrows(15);
    BOOST_TEST(inv.arrows() == 15);
}

BOOST_AUTO_TEST_CASE(SetArrows_CapsAtLimit)
{
    Inventory inv;
    inv.setArrowLimit(MAX_ARROWS_1);
    inv.setArrows(MAX_ARROWS_1 + 10);
    BOOST_TEST(inv.arrows() == MAX_ARROWS_1);
}

BOOST_AUTO_TEST_CASE(UseArrow_Decrements)
{
    Inventory inv;
    inv.setArrowLimit(MAX_ARROWS_1);
    inv.setArrows(3);
    inv.useArrow();
    BOOST_TEST(inv.arrows() == 2);
}

BOOST_AUTO_TEST_CASE(UseArrow_DoesNotGoBelowZero)
{
    Inventory inv;
    inv.setArrowLimit(MAX_ARROWS_1);
    inv.setArrows(0);
    inv.useArrow();
    BOOST_TEST(inv.arrows() == 0);
}

BOOST_AUTO_TEST_CASE(SetAndGetMagicPowder)
{
    Inventory inv;
    inv.setMagicPowderLimit(MAX_MAGIC_POWDER_1);
    inv.setMagicPowder(10);
    BOOST_TEST(inv.magicPowder() == 10);
}

BOOST_AUTO_TEST_CASE(SetMagicPowder_CapsAtLimit)
{
    Inventory inv;
    inv.setMagicPowderLimit(MAX_MAGIC_POWDER_1);
    inv.setMagicPowder(MAX_MAGIC_POWDER_1 + 5);
    BOOST_TEST(inv.magicPowder() == MAX_MAGIC_POWDER_1);
}

BOOST_AUTO_TEST_CASE(UseMagicPowder_Decrements)
{
    Inventory inv;
    inv.setMagicPowderLimit(MAX_MAGIC_POWDER_1);
    inv.setMagicPowder(5);
    inv.useMagicPowder();
    BOOST_TEST(inv.magicPowder() == 4);
}

BOOST_AUTO_TEST_CASE(UseMagicPowder_DoesNotGoBelowZero)
{
    Inventory inv;
    inv.setMagicPowderLimit(MAX_MAGIC_POWDER_1);
    inv.setMagicPowder(0);
    inv.useMagicPowder();
    BOOST_TEST(inv.magicPowder() == 0);
}

BOOST_AUTO_TEST_CASE(AddAndRetrieveOcarinaSong)
{
    Inventory inv;
    inv.addOcarinaSong(OcarinaSong::MARIN);
    auto songs = inv.ocarinaSongs();
    bool found = false;
    for (auto s : songs)
        if (s == OcarinaSong::MARIN)
            found = true;
    BOOST_TEST(found);
}

BOOST_AUTO_TEST_CASE(SetSelectedOcarinaSong)
{
    Inventory inv;
    inv.setOcarinaSong(OcarinaSong::FROG);
    BOOST_TEST(std::to_underlying(inv.ocarinaSong()) == std::to_underlying(OcarinaSong::FROG));
}

BOOST_AUTO_TEST_CASE(AddAllThreeSongs)
{
    Inventory inv;
    inv.addOcarinaSong(OcarinaSong::MARIN);
    inv.addOcarinaSong(OcarinaSong::FROG);
    inv.addOcarinaSong(OcarinaSong::FISH);
    auto songs = inv.ocarinaSongs();
    int count = 0;
    for (auto s : songs)
        if (s != OcarinaSong::NONE)
            ++count;
    BOOST_TEST(count == 3);
}

BOOST_AUTO_TEST_CASE(DefaultTunicIsGreen)
{
    Inventory inv;
    BOOST_TEST(std::to_underlying(inv.tunic()) == std::to_underlying(Tunic::GREEN));
}

BOOST_AUTO_TEST_CASE(AddTunic_ChangesTunic)
{
    Inventory inv;
    inv.addTunic(Tunic::RED);
    BOOST_TEST(std::to_underlying(inv.tunic()) == std::to_underlying(Tunic::RED));
}

BOOST_AUTO_TEST_CASE(SetTunic)
{
    Inventory inv;
    inv.setTunic(Tunic::BLUE);
    BOOST_TEST(std::to_underlying(inv.tunic()) == std::to_underlying(Tunic::BLUE));
}

BOOST_AUTO_TEST_CASE(AddHeartContainerPiece_Increments)
{
    Inventory inv;
    inv.addHeartContainerPiece();
    BOOST_TEST(inv.heartContainerPieces() == 1);
}

BOOST_AUTO_TEST_CASE(AddHeartContainerPiece_CapsAtMax)
{
    Inventory inv;
    for (int i = 0; i < HEARTS_PIECE_MAX + 2; ++i)
        inv.addHeartContainerPiece();
    BOOST_TEST(inv.heartContainerPieces() == HEARTS_PIECE_MAX);
}

BOOST_AUTO_TEST_CASE(SetHeartContainerPieces)
{
    Inventory inv;
    inv.setHeartContainerPieces(3);
    BOOST_TEST(inv.heartContainerPieces() == 3);
}

BOOST_AUTO_TEST_CASE(AddHeartPiece_Increases)
{
    Inventory inv;
    inv.setMaxHeartPieces(6.0f);
    inv.addHeartPiece(1.0f);
    BOOST_TEST(inv.heartPieces() == 1.0f);
}

BOOST_AUTO_TEST_CASE(AddHeartPiece_CapsAtMax)
{
    Inventory inv;
    inv.setMaxHeartPieces(3.0f);
    inv.addHeartPiece(10.0f);
    BOOST_TEST(inv.heartPieces() == 3.0f);
}

BOOST_AUTO_TEST_CASE(UseHeartPiece_Decreases)
{
    Inventory inv;
    inv.setMaxHeartPieces(6.0f);
    inv.setHeartPieces(4.0f);
    inv.useHeartPiece(1.0f);
    BOOST_TEST(inv.heartPieces() == 3.0f);
}

BOOST_AUTO_TEST_CASE(UseHeartPiece_DoesNotGoBelowZero)
{
    Inventory inv;
    inv.setHeartPieces(0.0f);
    inv.useHeartPiece(1.0f);
    BOOST_TEST(inv.heartPieces() == 0.0f);
}

BOOST_AUTO_TEST_CASE(SetMaxHeartPieces)
{
    Inventory inv;
    inv.setMaxHeartPieces(10.0f);
    BOOST_TEST(inv.maxHeartPieces() == 10.0f);
}

BOOST_AUTO_TEST_CASE(AddPhotograph_CountIncreases)
{
    Inventory inv;
    inv.addPhotograph(Photograph::OCEAN_VIEW);
    BOOST_TEST(inv.photograph() == 1);
}

BOOST_AUTO_TEST_CASE(AddMultiplePhotographs)
{
    Inventory inv;
    inv.addPhotograph(Photograph::OCEAN_VIEW);
    inv.addPhotograph(Photograph::GAME_OVER);
    BOOST_TEST(inv.photograph() == 2);
}

BOOST_AUTO_TEST_CASE(PhotographsArrayContainsAdded)
{
    Inventory inv;
    inv.addPhotograph(Photograph::THIEF);
    auto arr = inv.photographs();
    bool found = false;
    for (auto p : arr)
        if (p == Photograph::THIEF)
            found = true;
    BOOST_TEST(found);
}

BOOST_AUTO_TEST_CASE(AddGoldenLeaf_Increments)
{
    Inventory inv;
    inv.addGoldenLeaf();
    BOOST_TEST(inv.goldenLeaves() == 1);
}

BOOST_AUTO_TEST_CASE(AddGoldenLeaf_CapsAtMax)
{
    Inventory inv;
    for (int i = 0; i < MAX_GOLDEN_LEAVES + 2; ++i)
        inv.addGoldenLeaf();
    BOOST_TEST(inv.goldenLeaves() == MAX_GOLDEN_LEAVES);
}

BOOST_AUTO_TEST_CASE(SetGoldenLeaves)
{
    Inventory inv;
    inv.setGoldenLeaves(3);
    BOOST_TEST(inv.goldenLeaves() == 3);
}

BOOST_AUTO_TEST_CASE(AddSecretSeaShell_Increments)
{
    Inventory inv;
    inv.addSecretSeaShell();
    BOOST_TEST(inv.secretSeaShells() == 1);
}

BOOST_AUTO_TEST_CASE(AddSecretSeaShell_CapsAtMax)
{
    Inventory inv;
    for (int i = 0; i < MAX_SECRET_SEASHELLS + 5; ++i)
        inv.addSecretSeaShell();
    BOOST_TEST(inv.secretSeaShells() == MAX_SECRET_SEASHELLS);
}

BOOST_AUTO_TEST_CASE(SetSecretSeaShells)
{
    Inventory inv;
    inv.setSecretSeaShells(25);
    BOOST_TEST(inv.secretSeaShells() == 25);
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace inventory_tests

namespace worldmap_tests
{

BOOST_AUTO_TEST_CASE(Worldmap_Full_Functionality_Test)
{
    Worldmap wm;

    // 1. Test Initial State
    std::pair<int, int> initialPos = wm.location();
    BOOST_CHECK_EQUAL(initialPos.first, 0);
    BOOST_CHECK_EQUAL(initialPos.second, 0);
    BOOST_CHECK_EQUAL(wm.locationVisited(0, 0), false);

    // 2. Test setLocation and visited status
    wm.setLocation(3, 13); // Tail Cave area
    std::pair<int, int> newPos = wm.location();
    BOOST_CHECK_EQUAL(newPos.first, 3);
    BOOST_CHECK_EQUAL(newPos.second, 13);
    BOOST_CHECK(wm.locationVisited(3, 13) == true);

    // 3. Test locationType and locationName retrieval
    // Note: m_worldmapLocation[3][13] is Tail Cave in the header
    BOOST_CHECK_EQUAL(wm.locationType(), LocationType::DUNGEON);
    // locationName() returns a formatted string containing the name
    BOOST_CHECK(wm.locationName().find("Tail Cave") != std::string::npos);

    // 4. Test moveMarker (Success case)
    // We need to set a neighbor to 'visited' before we can move there
    wm.setLocation(3, 14); // Set (3, 14) to visited
    wm.setLocation(3, 13); // Move back to (3, 13)

    // Now move DOWN from 13 to 14
    wm.moveMarker(Direction::DOWN);
    BOOST_CHECK_EQUAL(wm.location().second, 14);

    // 5. Test moveMarker (Failure case - unvisited)
    // (3, 15) is false/unvisited by default
    wm.moveMarker(Direction::DOWN);
    // Position should NOT change because (3, 15) was never set to visited
    BOOST_CHECK_EQUAL(wm.location().second, 14);

    // 6. Test Wrapping/Modulo Logic in moveMarker
    // Set (4, 14) to visited so we can move right
    wm.setLocation(4, 14);
    wm.setLocation(3, 14);
    wm.moveMarker(Direction::RIGHT);
    BOOST_CHECK_EQUAL(wm.location().first, 4);

    // 7. Test various Location Names for code coverage
    wm.setLocation(0, 1);
    BOOST_CHECK(wm.locationName().find("Turtle Rock") != std::string::npos);

    wm.setLocation(10, 0);
    BOOST_CHECK(wm.locationName().find("Hen House") != std::string::npos);
}

} // namespace worldmap_tests