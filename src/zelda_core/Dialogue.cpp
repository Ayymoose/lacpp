
#include "Dialogue.h"

#include <cassert>
#include <algorithm>
#include <expected>

namespace
{
// Textbox dimensions
constexpr int DIALOGUE_WIDTH = 144;
constexpr int DIALOGUE_HEIGHT = 40;

// Position of textbox on screen
constexpr int DIALOGUE_POS_X = 8;
constexpr int DIALOGUE_POS_Y_LOW = 80;
constexpr int DIALOGUE_POS_Y_HIGH = 8;

// Max characters per line
constexpr int MAX_CHAR_PER_LINE = 16;
constexpr int LINE_HEIGHT = 16;
constexpr int MAX_LINES = 2;

// Dimensions of a character
constexpr int CHAR_WIDTH = 8;
constexpr int CHAR_HEIGHT = 8;
} // namespace

namespace zelda::core
{
Dialogue::Dialogue()
    : m_optionPaddingLength(0)
    , m_dialogueY(0)
    , m_isQuestion(false)
{}

void Dialogue::message(const std::string& message, float yPos)
{
    // Displays a message on screen to the player
    // Engine is paused while the message is being displayed

    checkCharacters(message);

    // Dialogue is simple in LA
    // For each character in the message
    // Copy a character from the srcTexture to the screen
    // Delay a short while then repeat

    // If all characters are displayed then display the blinking red arrow in
    // the corner Once user pressers the continue key, move the text up

    m_messages.emplace(
        Message(message, (yPos > DIALOGUE_HEIGHT + DIALOGUE_POS_Y_HIGH) ? DIALOGUE_POS_Y_HIGH : DIALOGUE_POS_Y_LOW));
}

void Dialogue::question(const std::string& question, const std::string& choice1, const std::string& choice2, float yPos)
{
    // Acceptable characters in the message are only
    // a-z A-Z !?'.,- 0-9 space
    // TODO: Special characters are for items which are represented by ...

    checkCharacters(question);
    checkCharacters(choice1);
    checkCharacters(choice2);

    // If it's a question
    // Output the message and then add an extra line with the given options
    assert(choice1.length() < MAX_CHAR_PER_LINE);
    assert(choice2.length() < MAX_CHAR_PER_LINE);

    // Determine how much padding is needed to force a new line
    auto const messagePadding = MAX_CHAR_PER_LINE - (question.length() % MAX_CHAR_PER_LINE);

    assert(messagePadding > 0 && messagePadding <= MAX_CHAR_PER_LINE);

    std::string messagePad;
    if (messagePadding != MAX_CHAR_PER_LINE)
    {
        messagePad = std::string(messagePadding, ' ');
    }

    const std::string OPTIONS_SPACE("  ");
    assert(choice1.length() + OPTIONS_SPACE.length() + choice2.length() + 1 < MAX_CHAR_PER_LINE);

    auto const options = choice1 + OPTIONS_SPACE + choice2;
    auto const optionsPadding = (MAX_CHAR_PER_LINE - options.length() + 1) / 2;
    std::string optionsPad(optionsPadding, ' ');

    m_messages.emplace(
        Question(question + messagePad + optionsPad + options,
                 (yPos > DIALOGUE_HEIGHT + DIALOGUE_POS_Y_HIGH) ? DIALOGUE_POS_Y_HIGH : DIALOGUE_POS_Y_LOW,
                 choice1,
                 choice2,
                 optionsPadding));
}

void Dialogue::checkCharacters(const std::string& message)
{
    assert(!message.empty());

    // Only the following characters allowed
    std::for_each(message.cbegin(),
                  message.cend(),
                  [](const char c)
                  {
                      // TODO: Char set is missing
                      // & ( )
                      bool isLowerCaseCharacter = (c >= 'a' && c <= 'z');
                      bool isUppperCaseCharacter = (c >= 'A' && c <= 'Z');
                      bool isDigit = (c >= '0' && c <= '9');
                      bool isPunctuation = (c == '(' || c == ')' || c == '&' || c == '!' || c == '?' || c == '\''
                                            || c == '.' || c == ',' || c == '-');
                      bool isSpace = (c == ' ');

                      // TODO: Check each character for its usage
                      bool isSpecialCharacter = (c == '#' || c == '<' || c == '>' || c == '@');
                      if (!(isSpecialCharacter || isLowerCaseCharacter || isUppperCaseCharacter || isDigit
                            || isPunctuation || isSpace))
                      {
                          std::unreachable();
                      }
                  });
}

int Dialogue::dialoguePosYLow() const
{
    return DIALOGUE_POS_Y_LOW;
}

int Dialogue::dialoguePosYHigh() const
{
    return DIALOGUE_POS_Y_HIGH;
}

int Dialogue::dialoguePosX() const
{
    return DIALOGUE_POS_X;
}

int Dialogue::optionPaddingLength() const
{
    return m_optionPaddingLength;
}

bool Dialogue::isQuestion() const
{
    return m_isQuestion;
}

int Dialogue::maxLines() const
{
    return MAX_LINES;
}

int Dialogue::lineHeight() const
{
    return LINE_HEIGHT;
}

int Dialogue::charWidth() const
{
    return CHAR_WIDTH;
}

int Dialogue::charHeight() const
{
    return CHAR_HEIGHT;
}

int Dialogue::dialogueWidth()
{
    return DIALOGUE_WIDTH;
}

int Dialogue::dialogueHeight()
{
    return DIALOGUE_HEIGHT;
}

int Dialogue::dialogueY() const
{
    return m_dialogueY;
}

int Dialogue::messages() const
{
    return m_messages.size();
}

std::string Dialogue::message() const
{
    return m_message;
}

int Dialogue::maxCharsPerLine() const
{
    return MAX_CHAR_PER_LINE;
}

std::string Dialogue::choice() const
{
    return m_choice;
}

std::string Dialogue::choice1() const
{
    return m_choice1;
}

std::string Dialogue::choice2() const
{
    return m_choice2;
}

void Dialogue::setChoice1()
{
    m_choice = m_choice1;
}

void Dialogue::setChoice2()
{
    m_choice = m_choice2;
}

void Dialogue::checkForNewMessages(const int currentChar)
{
    // If there are any messages in the queue, pop them off one by one and display
    if (!m_messages.empty() && currentChar == 0)
    {
        auto const& item = m_messages.front();

        if (std::holds_alternative<Message>(item))
        {
            auto const& message = std::get<Message>(item);
            m_dialogueY = message.y;
            m_message = message.message;
            m_isQuestion = false;
        }
        else
        {
            auto const& question = std::get<Question>(item);
            m_dialogueY = question.y;
            m_message = question.question;
            m_isQuestion = true;
            m_optionPaddingLength = question.optionPaddingLength;
            m_choice1 = question.choice1;
            m_choice2 = question.choice2;

            // Choice 1 will always be selected first
            m_choice = m_choice1;
        }

        m_messages.pop();
    }
}

} // namespace zelda::core