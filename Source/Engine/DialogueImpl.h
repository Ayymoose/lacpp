#pragma once

#include <string>
#include <queue>
#include <variant>
#include <memory>

namespace Zelda
{

    class DialogueImpl
    {
    public:
        DialogueImpl();
        void message(const std::string& message, float yPos);
        void question(const std::string& question, const std::string& choice1, const std::string& choice2, float yPos);
    
        int maxLines() const;

        int lineHeight() const;

        int charWidth() const;

        int charHeight() const;

        int dialogueWidth() const;

        int dialogueHeight() const;

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

            Message(const std::string& message, const float y) : message(message), y(y) 
            {
            }
        };

        struct Question
        {
            std::string question;
            int y;
            std::string choice1;
            std::string choice2;
            int optionPaddingLength;

            Question(const std::string& question, const int y, const std::string& choice1, const std::string& choice2, const int optionPaddingLength) :
                question(question), y(y), choice1(choice1), choice2(choice2), optionPaddingLength(optionPaddingLength)
            {
            }
        };
    
        std::queue<std::variant<Message, Question>> m_messages;

        static void checkCharacters(const std::string& string);

    };
}