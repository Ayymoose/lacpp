#pragma once

#include <string>
#include <queue>
#include <variant>

namespace zelda::core
{

class Dialogue
{
public:
    Dialogue();
    void message(const std::string &message, float yPos);
    void question(const std::string &question, const std::string &choice1, const std::string &choice2, float yPos);

    int maxLines() const;

    int lineHeight() const;

    int charWidth() const;

    int charHeight() const;

    static int dialogueWidth();

    static int dialogueHeight();

    // y co-ordinate of the dialogue box
    int dialogueY() const;

    // Is the current message a question
    bool isQuestion() const;

    // Number of messages in queue
    int messages() const;

    // Current message or question
    std::string message() const;

    // Max characters displayed on one line
    int maxCharsPerLine() const;

    // The current question choice
    std::string choice() const;

    std::string choice1() const;

    std::string choice2() const;

    void setChoice1();

    void setChoice2();

    int optionPaddingLength() const;

    void checkForNewMessages(const int currentChar);

    int dialoguePosX() const;

    int dialoguePosYLow() const;

    int dialoguePosYHigh() const;

private:
    std::string m_choice;
    std::string m_choice1;
    std::string m_choice2;

    std::string m_message;

    int m_optionPaddingLength;

    int m_dialogueY;

    bool m_isQuestion;

    struct Message
    {
        std::string message;
        int y;

        Message(const std::string &messageName, const float dy)
            : message(messageName)
            , y(dy)
        {}
    };

    struct Question
    {
        std::string question;
        int y;
        std::string choice1;
        std::string choice2;
        int optionPaddingLength;

        Question(const std::string &questionMessage, const int dy, const std::string &first, const std::string &second,
                 const int paddingLength)
            : question(questionMessage)
            , y(dy)
            , choice1(first)
            , choice2(second)
            , optionPaddingLength(paddingLength)
        {}
    };

    std::queue<std::variant<Message, Question>> m_messages;

    static void checkCharacters(const std::string &string);
};
} // namespace zelda::core