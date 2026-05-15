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

    void message(const std::string& message, float yPos);

    void question(const std::string& question, const std::string& choice1, const std::string& choice2, float yPos);

    constexpr int maxLines() const { return MAX_LINES; }

    constexpr int lineHeight() const { return LINE_HEIGHT; }

    constexpr int charWidth() const { return CHAR_WIDTH; }

    constexpr int charHeight() const { return CHAR_HEIGHT; }

    static constexpr int dialogueWidth() { return DIALOGUE_WIDTH; }

    static constexpr int dialogueHeight() { return DIALOGUE_HEIGHT; }

    // y co-ordinate of the dialogue box
    int dialogueY() const;

    // Is the current message a question
    bool isQuestion() const;

    // Number of messages in queue
    int messages() const;

    // Current message or question
    std::string message() const;

    // Max characters displayed on one line
    constexpr int maxCharsPerLine() const { return MAX_CHAR_PER_LINE; }

    // The current question choice
    std::string choice() const;

    std::string choice1() const;

    std::string choice2() const;

    void setChoice1();

    void setChoice2();

    int optionPaddingLength() const;

    void checkForNewMessages(int currentChar);

    constexpr int dialoguePosX() const { return DIALOGUE_POS_X; }

    constexpr int dialoguePosYLow() const { return DIALOGUE_POS_Y_LOW; }

    constexpr int dialoguePosYHigh() const { return DIALOGUE_POS_Y_HIGH; }

private:
    // Textbox dimensions
    static constexpr int DIALOGUE_WIDTH = 144;
    static constexpr int DIALOGUE_HEIGHT = 40;

    // Position of textbox on screen
    static constexpr int DIALOGUE_POS_X = 8;
    static constexpr int DIALOGUE_POS_Y_LOW = 80;
    static constexpr int DIALOGUE_POS_Y_HIGH = 8;

    // Max characters per line
    static constexpr int MAX_CHAR_PER_LINE = 16;
    static constexpr int LINE_HEIGHT = 16;
    static constexpr int MAX_LINES = 2;

    // Dimensions of a character
    static constexpr int CHAR_WIDTH = 8;
    static constexpr int CHAR_HEIGHT = 8;

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

        Message(const std::string& messageName, float dy)
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

        Question(const std::string& questionMessage, int dy, const std::string& first, const std::string& second,
                 int paddingLength)
            : question(questionMessage)
            , y(dy)
            , choice1(first)
            , choice2(second)
            , optionPaddingLength(paddingLength)
        {}
    };

    std::queue<std::variant<Message, Question>> m_messages;

    static bool checkCharacters(const std::string& message);
};
} // namespace zelda::core