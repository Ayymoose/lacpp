#pragma once

#include "core/Singleton.h"
#include "core/Renderable.h"
#include "core/Controllable.h"
#include "core/Updateable.h"
#include "core/Toggle.h"
#include "core/Sprite.h"
#include "zelda_core/Dialogue.h"

#include <string>
#include <queue>
#include <memory>


namespace zelda::gui
{
// RGB components of text colour
constexpr int TEXT_R = 248;
constexpr int TEXT_G = 248;
constexpr int TEXT_B = 168;

// Position of text in textbox
constexpr int TEXT_POS_X = 8;
constexpr int TEXT_POS_Y = 8;

// Red arrow more text indicator position
constexpr int ARROW_POS_X = 135;
constexpr int ARROW_POS_Y = 32;

constexpr int SCROLL_SPEED = 4;

class Dialogue :
    public engine::Renderable,
    public engine::Controllable,
    public engine::Singleton<Dialogue>,
    public engine::Updateable
{
public:
    Dialogue();
    void message(const std::string& message, float yPos);
    void question(const std::string& question, const std::string& choice1, const std::string& choice2, float yPos);

    void render() override;
    void update() override;
    void control() override;

private:
    core::Dialogue m_dialogueImpl;

    int m_dialoguePosX;
    int m_dialoguePosY;

    size_t m_currentChar;
    int m_currentLine;

    int m_dstCharX;
    int m_dstCharY;

    std::shared_ptr<engine::Sprite> m_text;
    std::unique_ptr<engine::Sprite> m_subTexture;
    bool m_moreText;

    engine::Toggle m_toggleQuestion;

    std::shared_ptr<engine::Sprite> m_questionMarker;

    // Continue arrow
    engine::Toggle m_toggleArrow;

    std::shared_ptr<engine::Sprite> m_redArrow;
    bool m_continue;
    bool m_scrollMessage;
    int m_scrolledLines;

    int m_questionXPos;
    int m_questionYPos;

    void reset();

    void drawQuestionMarker() const;
    void drawContinueArrowMarker() const;
};
} // namespace zelda::gui