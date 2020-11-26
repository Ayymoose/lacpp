#include "Dialogue.h"
#include "Depth.h"
#include "Renderer.h"
#include "Drawing.h"
#include "Camera.h"
#include "ZD_Assert.h"
#include "Resource.h"
#include "Keyboard.h"
#include "InputControl.h"
#include "Link.h"

using namespace Zelda;

Dialogue::Dialogue()
{
    m_depth = ZD_DEPTH_DIALOGUE;
    m_name = "Dialogue";
    m_controllableName = m_name;

    m_width = DIALOGUE_WIDTH;
    m_height = DIALOGUE_HEIGHT;

    m_dialoguePosX = DIALOGUE_POS_X;
    // Assume its low for now but depends on Link's position on screen
    m_dialoguePosY = DIALOGUE_POS_Y_LOW;

    m_srcCharX = TEXT_POS_X;
    m_srcCharY = TEXT_POS_Y;

    m_dstCharX = 0;
    m_dstCharY = 0;
    m_currentLine = 0;
    m_scrollMessage = false;

    m_texture = SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, m_width, m_height);
    assert(m_texture);
    m_subTexture = SDL_CreateTexture(Renderer::getInstance().getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, m_width, m_height);
    assert(m_subTexture);

    m_redArrow = ResourceManager::getInstance()[Graphic::GFX_TEXT];
    m_text = ResourceManager::getInstance()[Graphic::GFX_TEXT];
    m_questionMarker = ResourceManager::getInstance()[Graphic::GFX_TEXT];

    colourTexture(Renderer::getInstance().getRenderer(), m_texture, nullptr, SDL_RGB(0,0,0));
    colourTexture(Renderer::getInstance().getRenderer(), m_subTexture, nullptr, SDL_RGB(0, 0, 0));

    m_scrolledLines = 0;
    m_currentChar = 0;
    m_flashArrow = false;
    m_continue = false;
    m_moreText = false;

    m_flashQuestion = false;
    m_isQuestion = false;
    m_questionXPos = 0;
    m_questionYPos = 0;
}

void Dialogue::message(const std::string& message) noexcept
{
    // Displays a message on screen to the player
    // Engine is paused while the message is being displayed

    // Acceptable characters in the message are only
    // a-z A-Z !?'.,- 0-9 space
    Renderer::getInstance().addRenderable(this);
    // Special characters are for items which are represented by

#ifndef NDEBUG
    // Sanity tests
    
    // Only the following characters allowed
    std::for_each(message.begin(), message.end(), [](const char c)
    {
        bool isLowerCaseCharacter = (c >= 'a' && c <= 'z');
        bool isUppperCaseCharacter = (c >= 'A' && c <= 'Z');
        bool isDigit = (c >= '0' && c <= '9');
        bool isSpecialCharacter = (c == '!' || c == '?' || c == '\'' || c == '.' || c == ',' || c == '-');
        bool isSpace = (c == ' ');
        assert(isLowerCaseCharacter || isUppperCaseCharacter || isDigit || isSpecialCharacter || isSpace);
    });

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

#endif

    // Dialogue is simple in LA
    // For each character in the message
    // Copy a character from the srcTexture to the screen
    // Delay a short while then repeat

    // If all characters are displayed then display the blinking red arrow in the corner
    // Once user pressers the continue key, move the text up 
    m_message = message;
    m_currentChar = 0;
    m_dstCharX = 0;
    m_dstCharY = 0;
    m_currentLine = 0;
    m_scrollMessage = false;
    m_scrolledLines = 0;
    m_flashArrow = false;
    m_continue = false;

    // TODO: Correct text colour
    // TODO: Add special characters (arrows, items etc)
    // TODO: Add heart container on RHS when acquired

    // Display at top or bottom on screen depending on Link's position
    auto linkPosition = Link::getInstance().position();
    if (linkPosition.y - Camera::getInstance().getY() > DIALOGUE_HEIGHT + DIALOGUE_POS_Y_HIGH)
    {
        m_dialoguePosY = DIALOGUE_POS_Y_HIGH;
    }
    else
    {
        m_dialoguePosY = DIALOGUE_POS_Y_LOW;
    }

    // Display
    Controller::getInstance().pushController(&Link::getInstance(), this);
}

bool Dialogue::question(const std::string& question, const std::string& choice1, const std::string& choice2) noexcept
{
    // TODO: Why can't this overload be called as question?
    return this->question(question.c_str(), choice1, choice2);
}

bool Dialogue::question(const char* question, const std::string& choice1, const std::string& choice2) noexcept
{
    // If it's a question
    // Output the message and then add an extra line with the given options
    assert(choice1.length() < MAX_CHAR_PER_LINE);
    assert(choice2.length() < MAX_CHAR_PER_LINE);
    // +2 for the spaces we add
    assert(choice1.length() + choice2.length() + 2 < MAX_CHAR_PER_LINE);

    // Determine how much padding is needed to force a new line
    int messagePadding = MAX_CHAR_PER_LINE - (std::strlen(question) % MAX_CHAR_PER_LINE);
    // If padding is 0 it means the last line is full
    assert(messagePadding != 0);
    // TODO: Fix when assert fails
    std::string messagePad(messagePadding, ' ');

    std::string options = choice1 + "  " + choice2;
    int optionsPadding = (MAX_CHAR_PER_LINE - options.length() + 1) / 2;
    std::string optionsPad(optionsPadding, ' ');

    m_isQuestion = true;
    //'                '
    //'Red Blue'
    message(question + messagePad + optionsPad + options);

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

void Zelda::Dialogue::render(SDL_Renderer* renderer) noexcept
{
    // Drawn on top or bottom depending on Link's position
    SDL_Rect dstRectDialogue =
    {
        m_dialoguePosX,
        m_dialoguePosY,
        m_width,
        m_height
    };

    SDL_Rect srcRectArrow =
    {
        136,
        16,
        CHAR_WIDTH,
        CHAR_HEIGHT
    };

    SDL_Rect dstRectArrow =
    {
        m_dialoguePosX + ARROW_POS_X,
        m_dialoguePosY + ARROW_POS_Y,
        CHAR_WIDTH,
        CHAR_HEIGHT
    };

    SDL_Rect srcRectChar, dstRectChar = { 0,0,0,0 };

    // Copy each character onto the message box and display that,
    if (m_message[m_currentChar] >= 'A' && m_message[m_currentChar] <= 'Z')
    {
        m_srcCharX = CHAR_WIDTH * (m_message[m_currentChar] - 'A');
        m_srcCharY = 0;
    }
    else if (m_message[m_currentChar] >= 'a' && m_message[m_currentChar] <= 'z')
    {
        m_srcCharX = CHAR_WIDTH * (m_message[m_currentChar] - 'a');
        m_srcCharY = 8;
    }
    else if (m_message[m_currentChar] >= '0' && m_message[m_currentChar] <= '9')
    {
        m_srcCharX = CHAR_WIDTH * (m_message[m_currentChar] - '0');
        m_srcCharY = 16;
    }
    else if (m_message[m_currentChar] == ' ')
    {
        m_srcCharX = 80;
        m_srcCharY = 16;
    }
    else if (m_message[m_currentChar] == '-')
    {
        m_srcCharX = 88;
        m_srcCharY = 16;
    }
    else if (m_message[m_currentChar] == '?')
    {
        m_srcCharX = 96;
        m_srcCharY = 16;
    }
    else if (m_message[m_currentChar] == '!')
    {
        m_srcCharX = 104;
        m_srcCharY = 16;
    }
    else if (m_message[m_currentChar] == '.')
    {
        m_srcCharX = 112;
        m_srcCharY = 16;
    }
    else if (m_message[m_currentChar] == ',')
    {
        m_srcCharX = 120;
        m_srcCharY = 16;
    }
    else if (m_message[m_currentChar] == '\'')
    {
        m_srcCharX = 128;
        m_srcCharY = 16;
    }

    // Start copying characters across
    srcRectChar =
    {
        m_srcCharX,
        m_srcCharY,
        CHAR_WIDTH,
        CHAR_HEIGHT
    };

    // If there is a message to display
    
    if (m_currentChar != m_message.length())
    {
        if (m_textTimer.elapsed(TEXT_SPEED) && !m_scrollMessage)
        {

            //std::cout << "Outputting character '" << m_message[m_currentChar] << "'\n";

            m_textTimer.reset();

            // Only allow MAX_CHAR_PER_LINE characters per line
            // After that we move onto the next line
            if (m_currentChar != 0 && m_currentChar % MAX_CHAR_PER_LINE == 0 && !m_moreText)
            {
                if (m_currentLine != MAX_LINE-1)
                {
                    m_currentLine++;
                    m_dstCharX = 0;

                    // Copies the character onto the subtexture at given position
                    dstRectChar =
                    {
                        TEXT_POS_X + m_dstCharX * CHAR_WIDTH,
                        TEXT_POS_Y + m_currentLine * LINE_HEIGHT,
                        CHAR_WIDTH,
                        CHAR_HEIGHT
                    };

                    m_dstCharX++;
                }
                else 
                {

                    if (m_scrolledLines == 0)
                    {
                        m_continue = true;
                    }
                    else
                    {
                        m_scrollMessage = true;
                        m_scrolledLines--;
                    }
                }
            }
            else
            {
                if (!m_continue)
                {
                    dstRectChar =
                    {
                        TEXT_POS_X + m_dstCharX * CHAR_WIDTH,
                        TEXT_POS_Y + m_currentLine * LINE_HEIGHT,
                        CHAR_WIDTH,
                        CHAR_HEIGHT
                    };
                    m_dstCharX++;
                }
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
            SDL_Rect srcSubTextureHalf =
            {
                0,
                0,
                m_width,
                m_height / 2
            };
            // 1. Hide the top half of the sub texture
            colourTexture(Renderer::getInstance().getRenderer(), m_subTexture, &srcSubTextureHalf, SDL_RGB(0, 0, 0));


            // Copy the bottom line of text to the top of the texture
            SDL_Rect srcRectSubTextureLowerHalf =
            {
                0,
                m_dstCharY,
                m_width,
                m_height / 2
            };

            // 2. Scroll up LINE_HEIGHT pixels
            if (m_dstCharY % LINE_HEIGHT != 0)
            {
                // Scroll sub-texture box up
                m_dstCharY+= SCROLL_SPEED;
            }
            else
            {
                if (m_dstCharY != 0)
                {

                    SDL_Rect dstRectSubTextureLowerHalf = srcRectSubTextureLowerHalf;
                    m_dstCharY = 0;
                    dstRectSubTextureLowerHalf.y = m_dstCharY;

                    // 3. Copy to a bottom half of texture to top half 
                    copyToTexture(renderer, m_subTexture, m_subTexture, &srcRectSubTextureLowerHalf, &dstRectSubTextureLowerHalf);
                        
                    // Block out the what used to be the bottom line
                    colourTexture(Renderer::getInstance().getRenderer(), m_subTexture, &srcRectSubTextureLowerHalf, SDL_RGB(0, 0, 0));

                    m_currentLine = MAX_LINE - 1;
                    m_dstCharX = 0;
                    m_scrollMessage = false;
                    m_moreText = true;
                }
                else
                {
                    m_dstCharY+= SCROLL_SPEED;
                }
            }

        }

        // Copy text to sub texture
        assert(srcRectChar.x >= 0 && srcRectChar.y >= 0 && srcRectChar.w >= 0 && srcRectChar.h >= 0);
        assert(dstRectChar.x >= 0 && dstRectChar.y >= 0 && dstRectChar.w >= 0 && dstRectChar.h >= 0);

        copyToTexture(renderer, m_text, m_subTexture, &srcRectChar, &dstRectChar);

    }

    SDL_Rect dstRectSubTexture =
    {
        0,
        -m_dstCharY,
        m_width,
        m_height
    };

    // Copy sub texture to main textbox
    copyToTexture(renderer, m_subTexture, m_texture, nullptr, &dstRectSubTexture);

    // Display the textbox
    ZD_ASSERT(SDL_RenderCopy(renderer, m_texture, nullptr, &dstRectDialogue) == 0, "SDL Error: " << SDL_GetError());

    // Flashing red arrow 
    if (m_flashArrow && m_continue)
    {
        ZD_ASSERT(SDL_RenderCopy(renderer, m_redArrow, &srcRectArrow, &dstRectArrow) == 0, "SDL Error: " << SDL_GetError());
    }

    // Flash the continue arrow
    toggleItem(m_flashArrow, m_redArrowTimer, INVENTORY_SELECTOR_FPS);

    // Flash the question marker if it's a question
    if (m_isQuestion)
    {
        toggleItem(m_flashQuestion, m_questionTimer, INVENTORY_SELECTOR_FPS);
        if (m_flashQuestion && m_currentChar == m_message.length())
        {
            SDL_Rect srcQuestionRect = {144,16, CHAR_WIDTH, CHAR_HEIGHT };
            SDL_Rect dstQuestionRect = {m_questionXPos, m_questionYPos, CHAR_WIDTH, CHAR_HEIGHT };

            ZD_ASSERT(SDL_RenderCopy(renderer, m_questionMarker, &srcQuestionRect, &dstQuestionRect) == 0, "SDL Error: " << SDL_GetError());
        }
    }
}

void Zelda::Dialogue::control() noexcept
{
    if (m_continue && Keyboard::getInstance().keyPressed(BUTTON_B))
    {
        m_scrollMessage = true;
        m_continue = false;
        m_scrolledLines = MAX_LINE-1;
    }
    else if (m_currentChar == m_message.length() && Keyboard::getInstance().keyPressed(BUTTON_B))
    {
        // Close dialogue box and restore control
        Controller::getInstance().popController();
        Renderer::getInstance().removeRenderable(this);
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
