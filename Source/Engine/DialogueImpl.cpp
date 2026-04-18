
#include "DialogueImpl.h"

#include <cassert>

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
}

namespace Zelda
{
    DialogueImpl::DialogueImpl() : m_optionPaddingLength(0), m_dialogueY(0), m_isQuestion(false)
    {
    }

    void DialogueImpl::message(const std::string& message, float yPos)
    {
        // Displays a message on screen to the player
        // Engine is paused while the message is being displayed

        checkCharacters(message);

        // Dialogue is simple in LA
        // For each character in the message
        // Copy a character from the srcTexture to the screen
        // Delay a short while then repeat

        // If all characters are displayed then display the blinking red arrow in the corner
        // Once user pressers the continue key, move the text up 

        m_messages.emplace(Message(message, (yPos > DIALOGUE_HEIGHT + DIALOGUE_POS_Y_HIGH) ? DIALOGUE_POS_Y_HIGH : DIALOGUE_POS_Y_LOW));
    }

    void DialogueImpl::question(const std::string& question, const std::string& choice1, const std::string& choice2, float yPos)
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

        m_messages.emplace(Question(question + messagePad + optionsPad + options,
            (yPos > DIALOGUE_HEIGHT + DIALOGUE_POS_Y_HIGH) ? DIALOGUE_POS_Y_HIGH : DIALOGUE_POS_Y_LOW,
            choice1,
            choice2,
            optionsPadding));

    }

    void DialogueImpl::checkCharacters(const std::string& message)
    {
        assert(!message.empty());

        // Only the following characters allowed
        std::for_each(message.cbegin(), message.cend(), [](const char c)
        {
            // TODO: Char set is missing
            // & ( )
            bool isLowerCaseCharacter = (c >= 'a' && c <= 'z');
            bool isUppperCaseCharacter = (c >= 'A' && c <= 'Z');
            bool isDigit = (c >= '0' && c <= '9');
            bool isPunctuation = (c == '(' || c == ')' || c == '&' || c == '!' || c == '?' || c == '\'' || c == '.' || c == ',' || c == '-');
            bool isSpace = (c == ' ');

            // TODO: Check each character for its usage
            bool isSpecialCharacter = (c == '#' || c == '<' || c == '>' || c == '@');
            assert(isSpecialCharacter || isLowerCaseCharacter || isUppperCaseCharacter || isDigit || isPunctuation || isSpace);
        });
    }

    int DialogueImpl::dialoguePosYLow() const
    {
        return DIALOGUE_POS_Y_LOW;
    }

    int DialogueImpl::dialoguePosYHigh() const
    {
        return DIALOGUE_POS_Y_HIGH;
    }

    int DialogueImpl::dialoguePosX() const
    {
        return DIALOGUE_POS_X;
    }

    int DialogueImpl::optionPaddingLength() const
    {
        return m_optionPaddingLength;
    }

    bool DialogueImpl::isQuestion() const
    {
        return m_isQuestion;
    }

    int DialogueImpl::maxLines() const
    {
        return MAX_LINES;
    }

    int DialogueImpl::lineHeight() const
    {
        return LINE_HEIGHT;
    }

    int DialogueImpl::charWidth() const
    {
        return CHAR_WIDTH;
    }

    int DialogueImpl::charHeight() const
    {
        return CHAR_HEIGHT;
    }

    int DialogueImpl::dialogueWidth() const
    {
        return DIALOGUE_WIDTH;
    }

    int DialogueImpl::dialogueHeight() const
    {
        return DIALOGUE_HEIGHT;
    }

    int DialogueImpl::dialogueY() const
    {
        return m_dialogueY;
    }

    int DialogueImpl::messages() const
    {
        return m_messages.size();
    }

    std::string DialogueImpl::message() const
    {
        return m_message;
    }

    int DialogueImpl::maxCharsPerLine() const
    {
        return MAX_CHAR_PER_LINE;
    }

    std::string DialogueImpl::choice() const
    {
        return m_choice;
    }

    std::string DialogueImpl::choice1() const
    {
        return m_choice1;
    }

    std::string DialogueImpl::choice2() const
    {
        return m_choice2;
    }

    void DialogueImpl::setChoice1()
    {
        m_choice = m_choice1;
    }

    void DialogueImpl::setChoice2()
    {
        m_choice = m_choice2;
    }

    void DialogueImpl::checkForNewMessages(const int currentChar)
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

}