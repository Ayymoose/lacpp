#include "Dialogue.h"
#include "Depth.h"
#include "Renderer.h"
#include "Camera.h"
#include "ZD_Assert.h"
#include "Resource.h"
#include "Keyboard.h"
#include "InputControl.h"
#include "Link.h"

namespace Zelda
{

Dialogue::Dialogue() :
    Renderable("Dialogue", Sprite(Renderer::getInstance().getRenderer(), DIALOGUE_WIDTH, DIALOGUE_HEIGHT), ZD_DEPTH_DIALOGUE),
    Controllable(m_name),
    m_dialoguePosX(DIALOGUE_POS_X),
    m_dialoguePosY(DIALOGUE_POS_Y_LOW),
    m_currentChar(0),
    m_currentLine(0),
    m_dstCharX(0),
    m_dstCharY(0),
    m_text(ResourceManager::getInstance()[Graphic::GFX_TEXT]),
    m_subTexture(Sprite(Renderer::getInstance().getRenderer(), DIALOGUE_WIDTH, DIALOGUE_HEIGHT)),
    m_moreText(false),
    m_flashQuestion(false),
    m_questionXPos(0),
    m_questionYPos(0),
    m_isQuestion(false),
    m_questionMarker(ResourceManager::getInstance()[Graphic::GFX_TEXT]),
    m_flashArrow(false),
    m_redArrow(ResourceManager::getInstance()[Graphic::GFX_TEXT]),
    m_continue(false),
    m_scrollMessage(false),
    m_scrolledLines(0)
{
    assert(m_texture.data());
    assert(m_subTexture.data());
    Rect<int> rect{ 0,0,m_texture.width(),m_texture.height()};
    Sprite::colourSprite(Renderer::getInstance().getRenderer(), m_texture, rect, SDL_RGB(0, 0, 0));
    Sprite::colourSprite(Renderer::getInstance().getRenderer(), m_subTexture, rect, SDL_RGB(0, 0, 0));
}

void Dialogue::message(const std::string& message, float yPos) noexcept
{
    // Displays a message on screen to the player
    // Engine is paused while the message is being displayed
    Engine::getInstance().pause(true);

    // Acceptable characters in the message are only
    // a-z A-Z !?'.,- 0-9 space
    Renderer::getInstance().addRenderable(this);
    // Special characters are for items which are represented by

    // Sanity tests
    // Only the following characters allowed
    std::for_each(message.cbegin(), message.cend(), [](const char c)
    {
        bool isLowerCaseCharacter = (c >= 'a' && c <= 'z');
        bool isUppperCaseCharacter = (c >= 'A' && c <= 'Z');
        bool isDigit = (c >= '0' && c <= '9');
        bool isSpecialCharacter = (c == '!' || c == '?' || c == '\'' || c == '.' || c == ',' || c == '-');
        bool isSpace = (c == ' ');
        assert(isLowerCaseCharacter || isUppperCaseCharacter || isDigit || isSpecialCharacter || isSpace);
    });

    /*
    // Assert that word length isn't longer than line 
    // Taken from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    std::string string = message;
    std::string delimiter = " ";

    // Tokenise each word by delimter ' ' and check the length doesn't exceed 16 chars
    size_t pos = 0;
    std::string token;
    while ((pos = string.find(delimiter)) != std::string::npos)
    {
        token = string.substr(0, pos);
        assert(token.length() < MAX_CHAR_PER_LINE);
        string.erase(0, pos + delimiter.length());
    }
    assert(string.length() < MAX_CHAR_PER_LINE);
    */

    // Dialogue is simple in LA
    // For each character in the message
    // Copy a character from the srcTexture to the screen
    // Delay a short while then repeat

    // If all characters are displayed then display the blinking red arrow in the corner
    // Once user pressers the continue key, move the text up 

    // Reset after use
    // TODO: Check if question() needs similar resets
    m_message = message;

    m_dstCharX = 0;
    m_dstCharY = 0;
    m_currentLine = 0;
    m_scrollMessage = false;

    m_scrolledLines = 0;
    m_currentChar = 0;
    m_flashArrow = false;
    m_continue = false;
    m_moreText = false;

    Rect<int> rect{ 0,0,m_subTexture.width(),m_subTexture.height() };
    Sprite::colourSprite(Renderer::getInstance().getRenderer(), m_subTexture, rect, SDL_RGB(0, 0, 0));

    // TODO: Correct text colour
    // TODO: Add special characters (arrows, items etc)
    // TODO: Add heart container on RHS when acquired

    // TODO: Add dialogue paramter to configure where to put on screen
    // - Not only Link uses this dialogue

    // Display at top or bottom on screen depending on yPos
    auto yDiff = yPos - Camera::getInstance().getY();
    if (yDiff > DIALOGUE_HEIGHT + DIALOGUE_POS_Y_HIGH)
    {
        m_dialoguePosY = DIALOGUE_POS_Y_HIGH;
    }
    else
    {
        m_dialoguePosY = DIALOGUE_POS_Y_LOW;
    }

    // Switch controller over to this if there is one 
    Controller::getInstance().pushController(this);

}

bool Dialogue::question(const std::string& question, const std::string& choice1, const std::string& choice2, float yPos) noexcept
{
    // TODO: Why can't this overload be called as question?
    return this->question(question.c_str(), choice1, choice2, yPos);
}

bool Dialogue::question(const char* question, const std::string& choice1, const std::string& choice2, float yPos) noexcept
{
    // If it's a question
    // Output the message and then add an extra line with the given options
    assert(choice1.length() < MAX_CHAR_PER_LINE);
    assert(choice2.length() < MAX_CHAR_PER_LINE);
    // +2 for the spaces we add
    assert(choice1.length() + choice2.length() + 2 < MAX_CHAR_PER_LINE);

    // Determine how much padding is needed to force a new line
    const int messagePadding = MAX_CHAR_PER_LINE - (std::strlen(question) % MAX_CHAR_PER_LINE);
    // If padding is 0 it means the last line is full
    assert(messagePadding != 0);
    // TODO: Fix when assert fails
    std::string messagePad(messagePadding, ' ');

    std::string options = choice1 + "  " + choice2;
    const int optionsPadding = (MAX_CHAR_PER_LINE - options.length() + 1) / 2;
    std::string optionsPad(optionsPadding, ' ');

    m_isQuestion = true;
    //'                '
    //'Red Blue'
    message(question + messagePad + optionsPad + options, yPos);

    m_questionXPos = m_dialoguePosX + (optionsPadding * (CHAR_WIDTH - 1));
    m_questionYPos = m_dialoguePosY + TEXT_POS_Y + LINE_HEIGHT;

    m_choice1 = choice1;
    m_choice2 = choice2;

    // Choice 1 will always be selected first
    m_choice = m_choice1;
    // TODO: Automatically append spaces before words in sentence

    // TODO: Fix to return correct choice
    return false;
}

void Dialogue::render() noexcept
{
    auto charSrcRect = [this](const char c) noexcept
    {
        int srcCharX = 0, srcCharY = 0;
        // Get srcRect position of current character
        if (c >= 'A' && c <= 'Z')
        {
            srcCharX = CHAR_WIDTH * (c - 'A');
            srcCharY = 0;
        }
        else if (c >= 'a' && c <= 'z')
        {
            srcCharX = CHAR_WIDTH * (c - 'a');
            srcCharY = 8;
        }
        else if (c >= '0' && c <= '9')
        {
            srcCharX = CHAR_WIDTH * (c - '0');
            srcCharY = 16;
        }
        else if (c == ' ')
        {
            srcCharX = 80;
            srcCharY = 16;
        }
        else if (c == '-')
        {
            srcCharX = 88;
            srcCharY = 16;
        }
        else if (c == '?')
        {
            srcCharX = 96;
            srcCharY = 16;
        }
        else if (c == '!')
        {
            srcCharX = 104;
            srcCharY = 16;
        }
        else if (c == '.')
        {
            srcCharX = 112;
            srcCharY = 16;
        }
        else if (c == ',')
        {
            srcCharX = 120;
            srcCharY = 16;
        }
        else if (c == '\'')
        {
            srcCharX = 128;
            srcCharY = 16;
        }
        else
        {
            assert(false && "Unknown character");
        }
        return Rect<int>{srcCharX, srcCharY, CHAR_WIDTH, CHAR_HEIGHT};
    };

    // Start copying characters across
    Rect<int> dstRectChar =
    {
        TEXT_POS_X + m_dstCharX * CHAR_WIDTH,
        TEXT_POS_Y + m_currentLine * LINE_HEIGHT,
        CHAR_WIDTH,
        CHAR_HEIGHT
    };

    // If there is a message to display
    if (m_currentChar < m_message.length())
    {
        auto srcRectChar = charSrcRect(m_message[m_currentChar]);

        if (!m_scrollMessage)
        {
            // If we've displayed maximum chars per line
            if ((m_currentChar && (m_currentChar % MAX_CHAR_PER_LINE == 0)) && !m_moreText)
            {
                // Advance text onto the next line if not reached the maximum lines
                if (m_currentLine != MAX_LINES-1)
                {
                    m_currentLine++;
                    m_dstCharX = 0;

                    // Copies the character onto the subtexture at given position
                    dstRectChar.x = TEXT_POS_X + m_dstCharX * CHAR_WIDTH;
                    dstRectChar.y = TEXT_POS_Y + m_currentLine * LINE_HEIGHT;

                    m_dstCharX++;
                }
                else
                {
                    // Otherwise begin scrolling text up
                    if (m_scrolledLines == 0)
                    {
                        m_continue = true;
                    }
                    else
                    {
                        m_scrollMessage = true;
                        m_scrolledLines--;
                    }

                    m_currentChar--;
                    srcRectChar = charSrcRect(m_message[m_currentChar]);
                }
            }
            else
            {
                if (!m_continue)
                {
                    m_dstCharX = std::min(m_dstCharX + 1, MAX_CHAR_PER_LINE-1);
                }

                // TODO: This snippet is weird
                if (m_moreText)
                {
                    m_moreText = false;
                }
            }

            // Advance next character
            if (!m_continue && !m_scrollMessage)
            {
                m_currentChar++;
            }
        }
        else if (m_scrollMessage)
        {
            // Scrolls the message and continues on to the next
            const Rect<int> srcSubTextureHalf =
            {
                0,
                0,
                DIALOGUE_WIDTH,
                DIALOGUE_HEIGHT / 2
            };

            // 1. Hide the top half of the sub texture
            Sprite::colourSprite(Renderer::getInstance().getRenderer(), m_subTexture, srcSubTextureHalf, SDL_RGB(0, 0, 0));

            // Copy the bottom line of text to the top of the texture
            const Rect<int> srcRectSubTextureLowerHalf =
            {
                0,
                m_dstCharY,
                DIALOGUE_WIDTH,
                DIALOGUE_HEIGHT / 2
            };

            // 2. Scroll up LINE_HEIGHT pixels
            if (m_dstCharY % LINE_HEIGHT != 0)
            {
                // Scroll sub-texture box up
                m_dstCharY += SCROLL_SPEED;
            }
            else
            {
                if (m_dstCharY != 0)
                {

                    auto dstRectSubTextureLowerHalf = srcRectSubTextureLowerHalf;
                    m_dstCharY = 0;
                    dstRectSubTextureLowerHalf.y = m_dstCharY;

                    // 3. Copy to a bottom half of texture to top half 
                    Sprite::copySprite(Renderer::getInstance().getRenderer(), m_subTexture, m_subTexture, srcRectSubTextureLowerHalf, dstRectSubTextureLowerHalf);

                    // Block out the what used to be the bottom line
                    Sprite::colourSprite(Renderer::getInstance().getRenderer(), m_subTexture, srcRectSubTextureLowerHalf, SDL_RGB(0, 0, 0));

                    // Reset to the beginning of the line
                    m_currentLine = MAX_LINES - 1;
                    m_dstCharX = 0;
                    dstRectChar.x = TEXT_POS_X + m_dstCharX * CHAR_WIDTH;
                    dstRectChar.y = TEXT_POS_Y + m_currentLine * LINE_HEIGHT;

                    // Restore last character now
                    m_currentChar++;
                    srcRectChar = charSrcRect(m_message[m_currentChar]);

                    m_scrollMessage = false;
                    m_moreText = true;
                }
                else
                {
                    m_dstCharY += SCROLL_SPEED;
                }
            }

        }

        // Copy text to sub texture
        assert(dstRectChar.y >= TEXT_POS_Y);
        assert(dstRectChar.y < TEXT_POS_Y + MAX_LINES * LINE_HEIGHT);
        assert(dstRectChar.x >= TEXT_POS_X);
        assert(dstRectChar.x < TEXT_POS_X + MAX_CHAR_PER_LINE * CHAR_WIDTH);
        Sprite::copySprite(Renderer::getInstance().getRenderer(), m_text, m_subTexture, srcRectChar, dstRectChar);

    }

    const Rect<int> dstRectSubTexture =
    {
        0,
        -m_dstCharY,
        DIALOGUE_WIDTH,
        DIALOGUE_HEIGHT
    };

    // Copy sub texture to main textbox
    Sprite::copySprite(Renderer::getInstance().getRenderer(), m_subTexture, m_texture, Rect<int>{ 0, 0, m_subTexture.width(), m_subTexture.height() }, dstRectSubTexture);

    // Display the textbox
   // Drawn on top or bottom depending on Link's position
    const Rect<int> dstRectDialogue =
    {
        m_dialoguePosX,
        m_dialoguePosY,
        DIALOGUE_WIDTH,
        DIALOGUE_HEIGHT
    };

    m_texture.drawSprite(Renderer::getInstance().getRenderer(), Rect<int>{0,0, m_texture.width(), m_texture.height()}, dstRectDialogue);
    
    // Flashing red arrow 
    if (m_flashArrow && m_continue)
    {
        const Rect<int> srcRectArrow =
        {
            136,
            16,
            CHAR_WIDTH,
            CHAR_HEIGHT
        };

        const Rect<int> dstRectArrow =
        {
            m_dialoguePosX + ARROW_POS_X,
            m_dialoguePosY + ARROW_POS_Y,
            CHAR_WIDTH,
            CHAR_HEIGHT
        };
        m_redArrow.drawSprite(Renderer::getInstance().getRenderer(), srcRectArrow, dstRectArrow);
    }

    // Flash the continue arrow
    toggleItem(m_flashArrow, m_redArrowTimer, INVENTORY_SELECTOR_FPS);

    // Flash the question marker if it's a question
    if (m_isQuestion)
    {
        toggleItem(m_flashQuestion, m_questionTimer, INVENTORY_SELECTOR_FPS);
        if (m_flashQuestion && m_currentChar == m_message.length())
        {
            const Rect<int> srcQuestionRect = { 144,16, CHAR_WIDTH, CHAR_HEIGHT };
            const Rect<int> dstQuestionRect = { m_questionXPos, m_questionYPos, CHAR_WIDTH, CHAR_HEIGHT };

            m_questionMarker.drawSprite(Renderer::getInstance().getRenderer(), srcQuestionRect, dstQuestionRect);
        }
    }
}

void Dialogue::update() noexcept
{

}

void Dialogue::control(double ts) noexcept
{
    if (m_continue && Keyboard::getInstance().keyPressed(BUTTON_B))
    {
        m_scrollMessage = true;
        m_continue = false;
        m_scrolledLines = MAX_LINES - 1;
    }
    else if (m_currentChar == m_message.length() && Keyboard::getInstance().keyPressed(BUTTON_B))
    {
        // Close dialogue box and restore control
        Controller::getInstance().popController(); 
        
        Renderer::getInstance().removeRenderable(this);
        // Unpause
        Engine::getInstance().pause(false);
    }
    else if (m_isQuestion)
    {
        if (Keyboard::getInstance().keyPressed(BUTTON_RIGHT) && m_choice != m_choice2)
        {
            m_questionXPos += (m_choice.length() + 2) * CHAR_WIDTH;
            m_choice = m_choice2;
            // If pressed right once
            // Choice is 2
        }
        else if (Keyboard::getInstance().keyPressed(BUTTON_LEFT) && m_choice != m_choice1)
        {
            // If pressed left once
            // Choice is 1
            m_choice = m_choice1;
            m_questionXPos -= (m_choice.length() + 2) * CHAR_WIDTH;
        }
    }
}

}