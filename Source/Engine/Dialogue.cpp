#include "Dialogue.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Depth.h"
#include "Engine.h"
#include "Controller.h"
#include "Keyboard.h"
#include "InputControl.h"
#include "Random.h"
#include "Toggle.h"

namespace Zelda
{

    Dialogue::Dialogue() :
        IRenderable("Dialogue", Sprite(Renderer::getInstance().getRenderer(), m_dialogueImpl.dialogueWidth(), m_dialogueImpl.dialogueHeight()), ZD_DEPTH_DIALOGUE),
        Controllable(m_name),
        m_dialoguePosX(m_dialogueImpl.dialoguePosX()),
        m_dialoguePosY(m_dialogueImpl.dialoguePosYLow()),
        m_currentChar(0),
        m_currentLine(0),
        m_dstCharX(0),
        m_dstCharY(0),
        m_text(ResourceManager::getInstance()[SpriteResource::SPR_TEXT]),
        m_subTexture(std::make_unique<Sprite>(Renderer::getInstance().getRenderer(), m_dialogueImpl.dialogueWidth(), m_dialogueImpl.dialogueHeight())),
        m_moreText(false),
        m_toggleQuestion(15),
        m_questionMarker(ResourceManager::getInstance()[SpriteResource::SPR_TEXT]),
        m_toggleArrow(30),
        m_redArrow(ResourceManager::getInstance()[SpriteResource::SPR_TEXT]),
        m_continue(false),
        m_scrollMessage(false),
        m_scrolledLines(0),
        m_questionXPos(0),
        m_questionYPos(0)
    {
        assert(m_sprite->data());
        assert(m_subTexture->data());
        m_sprite->colourSprite(Rect<int>{ 0, 0, m_sprite->width(), m_sprite->height()}, makeRGB(0, 0, 0));
        m_subTexture->colourSprite(Rect<int>{ 0, 0, m_sprite->width(), m_sprite->height()}, makeRGB(0, 0, 0));
    }

    void Dialogue::message(const std::string& message, float yPos)
    {
        // Displays a message on screen to the player
        // Engine is paused while the message is being displayed
        Engine::getInstance().pause(true);

        if (!Renderer::getInstance().inRenderSet(this))
        {
            Renderer::getInstance().addRenderable(this);
        }

        m_dialogueImpl.message(message, yPos);

        // Switch controller over to this if there is one 
        if (Controller::getInstance().getController() != this)
        {
            Controller::getInstance().pushController(this);
        }
    }

    void Dialogue::question(const std::string& question, const std::string& choice1, const std::string& choice2, float yPos)
    {
        // Displays a message on screen to the player
        // Engine is paused while the message is being displayed
        Engine::getInstance().pause(true);

        if (!Renderer::getInstance().inRenderSet(this))
        {
            Renderer::getInstance().addRenderable(this);
        }

        m_dialogueImpl.question(question, choice1, choice2, yPos);

        // Switch controller over to this if there is one 
        if (Controller::getInstance().getController() != this)
        {
            Controller::getInstance().pushController(this);
        }

    }

    void Dialogue::render()
    {
        // TODO: Fix sprite logic
        auto charSrcRect = [this](const char c)
        {
            int srcCharX = 0, srcCharY = 0;
            // Get srcRect position of current character
            if (c >= 'A' && c <= 'Z')
            {
                srcCharX = m_dialogueImpl.charWidth() * (c - 'A');
                srcCharY = 0;
            }
            else if (c >= 'a' && c <= 'z')
            {
                srcCharX = m_dialogueImpl.charWidth() * (c - 'a');
                srcCharY = 8;
            }
            else if (c >= '0' && c <= '9')
            {
                srcCharX = m_dialogueImpl.charWidth() * (c - '0');
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
                assert(false && "Unknown character: " + c);
                return Rect<int>{};
            }
            return Rect<int>{srcCharX, srcCharY, m_dialogueImpl.charWidth(), m_dialogueImpl.charHeight()};
        };

        // Start copying characters across
        Rect<int> dstRectChar =
        {
            TEXT_POS_X + m_dstCharX * m_dialogueImpl.charWidth(),
            TEXT_POS_Y + m_currentLine * m_dialogueImpl.lineHeight(),
            m_dialogueImpl.charWidth(),
            m_dialogueImpl.charHeight()
        };

        m_dialogueImpl.checkForNewMessages(m_currentChar);

        if (m_dialogueImpl.isQuestion() && m_currentChar == 0)
        {
            m_questionXPos = m_dialoguePosX + (m_dialogueImpl.optionPaddingLength() * (m_dialogueImpl.charWidth() - 1));
            m_questionYPos = m_dialogueImpl.dialogueY() + TEXT_POS_Y + m_dialogueImpl.lineHeight();
        }

        m_dialoguePosY = m_dialogueImpl.dialogueY();

        // If there is a message to display
        auto const& message = m_dialogueImpl.message();
        if (m_currentChar < message.length())
        {
            auto srcRectChar = charSrcRect(message[m_currentChar]);

            if (!m_scrollMessage)
            {
                // If we've displayed maximum chars per line
                if ((m_currentChar && (m_currentChar % m_dialogueImpl.maxCharsPerLine() == 0)) && !m_moreText)
                {
                    // Advance text onto the next line if not reached the maximum lines
                    if (m_currentLine != m_dialogueImpl.maxLines() - 1)
                    {
                        m_currentLine++;
                        m_dstCharX = 0;

                        // Copies the character onto the subtexture at given position
                        dstRectChar.x = TEXT_POS_X + m_dstCharX * m_dialogueImpl.charWidth();
                        dstRectChar.y = TEXT_POS_Y + m_currentLine * m_dialogueImpl.lineHeight();

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
                        srcRectChar = charSrcRect(message[m_currentChar]);
                    }
                }
                else
                {
                    if (!m_continue)
                    {
                        m_dstCharX = std::min(m_dstCharX + 1, m_dialogueImpl.maxCharsPerLine() - 1);
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

                // 1. Hide the top half of the sub texture
                m_subTexture->colourSprite(Rect<int>{0, 0, m_dialogueImpl.dialogueWidth(), m_dialogueImpl.dialogueHeight() / 2}, makeRGB(0, 0, 0));

                // Copy the bottom line of text to the top of the texture
                const Rect<int> srcRectSubTextureLowerHalf = { 0, m_dstCharY,m_dialogueImpl.dialogueWidth(),m_dialogueImpl.dialogueHeight() / 2 };

                // 2. Scroll up LINE_HEIGHT pixels
                if (m_dstCharY % m_dialogueImpl.lineHeight() != 0)
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
                        Sprite::copySprite(*m_subTexture, *m_subTexture, srcRectSubTextureLowerHalf, dstRectSubTextureLowerHalf);

                        // Block out the what used to be the bottom line
                        m_subTexture->colourSprite(srcRectSubTextureLowerHalf, makeRGB(0, 0, 0));

                        // Reset to the beginning of the line
                        m_currentLine = m_dialogueImpl.maxLines() - 1;
                        m_dstCharX = 0;
                        dstRectChar.x = TEXT_POS_X + m_dstCharX * m_dialogueImpl.charWidth();
                        dstRectChar.y = TEXT_POS_Y + m_currentLine * m_dialogueImpl.lineHeight();

                        // Restore last character now
                        m_currentChar++;
                        srcRectChar = charSrcRect(message[m_currentChar]);

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
            assert(dstRectChar.y < TEXT_POS_Y + m_dialogueImpl.maxLines() * m_dialogueImpl.lineHeight());
            assert(dstRectChar.x >= TEXT_POS_X);
            assert(dstRectChar.x < TEXT_POS_X + m_dialogueImpl.maxCharsPerLine() * m_dialogueImpl.charWidth());

            // Make text yellow
            Sprite::copySprite(*m_text, *m_subTexture, srcRectChar, dstRectChar, makeRGB(TEXT_R, TEXT_G, TEXT_B));

        }

        // Copy sub texture to main textbox
        Sprite::copySprite(*m_subTexture, *m_sprite, Rect<int>{}, Rect<int>{0,-m_dstCharY, m_dialogueImpl.dialogueWidth(), m_dialogueImpl.dialogueHeight()});

        // Display the textbox
        // Drawn on top or bottom depending on Link's position
        m_sprite->drawSprite(Rect<int>{}, Rect<int>{m_dialoguePosX,m_dialoguePosY, m_dialogueImpl.dialogueWidth(), m_dialogueImpl.dialogueHeight()});
    
        // Flash the continue red arrow 
        if (m_toggleArrow && m_continue)
        {
            drawContinueArrowMarker();
        }

        // Flash the question marker if it's a question
        if (m_dialogueImpl.isQuestion() && (m_currentChar == m_dialogueImpl.message().length()) && m_toggleQuestion)
        {
            drawQuestionMarker();
        }
    }

    void Dialogue::drawContinueArrowMarker()
    {
        m_redArrow->drawSprite(Rect<int>{136, 16, m_dialogueImpl.charWidth(), m_dialogueImpl.charHeight()}, Rect<int>{m_dialoguePosX + ARROW_POS_X, m_dialoguePosY + ARROW_POS_Y, m_dialogueImpl.charWidth(), m_dialogueImpl.charHeight()});
    }

    void Dialogue::drawQuestionMarker()
    {
        assert(m_questionXPos >= m_dialoguePosX);
        assert(m_questionXPos <= m_dialoguePosX + m_dialogueImpl.dialogueWidth());
        assert(m_questionYPos >= m_dialoguePosY);
        assert(m_questionYPos <= m_dialoguePosY + m_dialogueImpl.dialogueHeight());
        m_questionMarker->drawSprite(Rect<int>{144, 16, m_dialogueImpl.charWidth(), m_dialogueImpl.charHeight()}, Rect<int>{ m_questionXPos, m_questionYPos, m_dialogueImpl.charWidth(), m_dialogueImpl.charHeight() });
}


    void Dialogue::update()
    {

    }

    void Dialogue::reset()
    {
        m_dstCharX = 0;
        m_dstCharY = 0;
        m_currentLine = 0;
        m_scrollMessage = false;

        m_scrolledLines = 0;
        m_currentChar = 0;
        m_toggleArrow.reset();
        m_continue = false;
        m_moreText = false;

        m_subTexture->colourSprite(Rect<int>{}, makeRGB(0, 0, 0));

        // TODO: Correct text speed
        // TODO: Add special characters (arrows, items etc)
        // TODO: Add heart container on RHS when acquired
    }

    void Dialogue::control()
    {
        if (m_continue && Keyboard::getInstance().keyPressed(BUTTON_B))
        {
            m_scrollMessage = true;
            m_continue = false;
            m_scrolledLines = m_dialogueImpl.maxLines() - 1;
            m_toggleArrow.reset();
        }
        else if ((m_currentChar == m_dialogueImpl.message().length()) && Keyboard::getInstance().keyPressed(BUTTON_B))
        {
            reset();

            if (m_dialogueImpl.messages() == 0)
            {
                // Close dialogue box and restore control
                Controller::getInstance().popController();

                Renderer::getInstance().removeRenderable(this);

                Engine::getInstance().pause(false);
            }
        }
        else if (m_dialogueImpl.isQuestion() && m_currentChar == m_dialogueImpl.message().length())
        {
            if (Keyboard::getInstance().keyPressed(BUTTON_RIGHT) && m_dialogueImpl.choice() != m_dialogueImpl.choice2())
            {
                m_questionXPos += (m_dialogueImpl.choice().length() + 2) * m_dialogueImpl.charWidth();
                m_dialogueImpl.setChoice2();
                // If pressed right once
                // Choice is 2
            }
            else if (Keyboard::getInstance().keyPressed(BUTTON_LEFT) && m_dialogueImpl.choice() != m_dialogueImpl.choice1())
            {
                // If pressed left once
                // Choice is 1
                m_dialogueImpl.setChoice1();
                m_questionXPos -= (m_dialogueImpl.choice().length() + 2) * m_dialogueImpl.charWidth();
            }
        }
    }

}