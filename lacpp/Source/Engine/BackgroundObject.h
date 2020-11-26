#pragma once

#include "Renderable.h"
#include "Resource.h"
#include <iostream>
#include "Depth.h"
#include "ZD_Assert.h"

class BackgroundObject : public Renderable
{
public:
	BackgroundObject(Graphic resource, int x, int y, double orientation);
    BackgroundObject() = delete;
    void render(SDL_Renderer* renderer) noexcept override;

private:
    int m_render_x;
    int m_render_y;

};

BackgroundObject::BackgroundObject(Graphic resource, int x, int y, double orientation)
{

    m_depth = ZD_DEPTH_BACKGROUND_OBJECT;

    m_texture = ResourceManager::getInstance()[resource];
    m_width = 16;
    m_height = 16;
    m_render_x = x;
    m_render_y = y;
    m_animationFPS = BACKGROUND_OBJECT_FPS;
    m_orientation = orientation;
	switch (resource)
	{
	case Graphic::GFX_CANDLE:
        m_animateXPos = 0;
        m_animateYPos = 0;
        m_currentFrame = 1;
        m_endFrame = 3;
        m_name = "Candle";

        break;
    case Graphic::GFX_TORCH_1:
        m_animateXPos = 0;
        m_animateYPos = 0;
        m_currentFrame = 0;
        m_endFrame = 3;
        m_name = "Torch";

        break;
    case Graphic::GFX_TORCH_2:
        break;
    case Graphic::GFX_SPIKE:
        break;
    case Graphic::GFX_WATER_1:
        break;
    case Graphic::GFX_WATER_2:
        break;
    case Graphic::GFX_WATER_3:
        break;
    case Graphic::GFX_WATER_4:
        break;
    case Graphic::GFX_RAPID:
        break;
    case Graphic::GFX_FLOWER_1:
        break;
    case Graphic::GFX_FLOWER_2:
        break;
    default:
        break;
	}

    Renderer::getInstance().addRenderable(this);

}

void BackgroundObject::render(SDL_Renderer* renderer) noexcept
{
    // srcRect is the sprite sheet
    SDL_Rect srcRect = { m_animateXPos + (m_currentFrame * m_width), m_animateYPos, m_width , m_height };
    // dstRect is the screen
    SDL_Rect dstRect = { m_render_x - Camera::getInstance().getX() , m_render_y - Camera::getInstance().getY() , m_width, m_height};
    ZD_ASSERT(SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, "SDL Error: " << SDL_GetError());

    // Animation
    if (m_currentFrame <= m_endFrame)
    {
        if (m_animationTimer.elapsed(m_animationFPS))
        {
            m_currentFrame++;
            if (m_currentFrame > m_endFrame)
            {
                m_currentFrame = 1;
            }
        }
    }
}