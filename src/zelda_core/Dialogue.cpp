#include "Dialogue.h"

#include <algorithm>
#include <cassert>

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

    assert(checkCharacters(message));

    // Dialogue is simple in LA
    // For each character in the message
    // Copy a character from the srcTexture to the screen
    // Delay a short while then repeat

    // If all characters are displayed then display the blinking red arrow in
    // the corner Once user pressers the continue key, move the text up

    m_messages.emplace(
        Message(message, yPos > dialogueHeight() + dialoguePosYHigh() ? dialoguePosYHigh() : dialoguePosYLow()));
}

void Dialogue::question(const std::string& question, const std::string& choice1, const std::string& choice2, float yPos)
{
    // Acceptable characters in the message are only
    // a-z A-Z !?'.,- 0-9 space
    // TODO: Special characters are for items which are represented by ...

    assert(checkCharacters(question));
    assert(checkCharacters(choice1));
    assert(checkCharacters(choice2));

    // If it's a question
    // Output the message and then add an extra line with the given options
    assert(choice1.length() < static_cast<std::size_t>(maxCharsPerLine()));
    assert(choice2.length() < static_cast<std::size_t>(maxCharsPerLine()));

    // Determine how much padding is needed to force a new line
    const int messagePadding = maxCharsPerLine() - (question.length() % maxCharsPerLine());

    assert(messagePadding > 0 && messagePadding <= maxCharsPerLine());

    std::string messagePad;
    if (messagePadding != maxCharsPerLine())
    {
        messagePad = std::string(messagePadding, ' ');
    }

    constexpr std::string space("  ");
    assert(choice1.length() + space.length() + choice2.length() + 1 < static_cast<std::size_t>(maxCharsPerLine()));

    const auto options = choice1 + space + choice2;
    const int optionsPadding = (maxCharsPerLine() - options.length() + 1) / 2;
    std::string optionsPad(optionsPadding, ' ');

    m_messages.emplace(Question(question + messagePad + optionsPad + options,
                                yPos > dialogueHeight() + dialoguePosYHigh() ? dialoguePosYHigh() : dialoguePosYLow(),
                                choice1,
                                choice2,
                                optionsPadding));
}

bool Dialogue::checkCharacters(const std::string& message)
{
    assert(!message.empty());

    // TODO: Check each character for its sprite usage
    static constexpr std::string_view allowedChars = " ()&!?'.,- #<>@";

    return std::ranges::all_of(message,
                               [](const char c)
                               {
                                   return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')
                                          || allowedChars.contains(c);
                               });
}

int Dialogue::optionPaddingLength() const
{
    return m_optionPaddingLength;
}

bool Dialogue::isQuestion() const
{
    return m_isQuestion;
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

void Dialogue::checkForNewMessages(int currentChar)
{
    // If there are any messages in the queue, pop them off one by one and display
    if (!m_messages.empty() && currentChar == 0)
    {
        const auto& item = m_messages.front();

        if (std::holds_alternative<Message>(item))
        {
            const auto& message = std::get<Message>(item);
            m_dialogueY = message.y;
            m_message = message.message;
            m_isQuestion = false;
        }
        else
        {
            const auto& question = std::get<Question>(item);
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