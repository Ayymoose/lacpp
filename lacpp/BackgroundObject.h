#ifndef BACKGROUND_OBJECT_H
#define BACKGROUND_OBJECT_H

#include "Renderable.h"
#include "Resource.h"
#include <iostream>
#include "Depth.h"
#include "MyAssert.h"

class BackgroundObject : public Renderable
{
public:
	BackgroundObject(RESOURCE resource, int x, int y, double orientation);
    BackgroundObject() = delete;
	~BackgroundObject() = default;
    void render(SDL_Renderer* pRenderer) override;

private:
    int m_render_x;
    int m_render_y;

};

BackgroundObject::BackgroundObject(RESOURCE resource, int x, int y, double orientation)
{

    m_depth = BACKGROUND_OBJECT_DEPTH;

    m_texture = ResourceManager::getInstance()[resource];
    m_width = 16;
    m_height = 16;
    m_render_x = x;
    m_render_y = y;
    m_animationFPS = BACKGROUND_OBJECT_FPS;
    m_orientation = orientation;
	switch (resource)
	{
	case RSC_CANDLE:
        m_animateXPos = 0;
        m_animateYPos = 0;
        m_currentFrame = 1;
        m_endFrame = 3;
        m_name = "Candle";

        break;
    case RSC_TORCH_1:
        m_animateXPos = 0;
        m_animateYPos = 0;
        m_currentFrame = 0;
        m_endFrame = 3;
        m_name = "Torch";

        break;
    case RSC_TORCH_2:
        break;
    case RSC_SPIKE:
        break;
    case RSC_WATER_1:
        break;
    case RSC_WATER_2:
        break;
    case RSC_WATER_3:
        break;
    case RSC_WATER_4:
        break;
    case RSC_RAPID:
        break;
    case RSC_FLOWER_1:
        break;
    case RSC_FLOWER_2:
        break;
    default:
        break;
	}

    Renderer::getInstance().addRenderable(this);

}

void BackgroundObject::render(SDL_Renderer* pRenderer)
{
    // srcRect is the sprite sheet
    SDL_Rect srcRect = { m_animateXPos + (m_currentFrame * m_width), m_animateYPos, m_width , m_height };
    // dstRect is the screen
    SDL_Rect dstRect = { m_render_x - Camera::getInstance().getX() , m_render_y - Camera::getInstance().getY() , m_width, m_height};
    DASSERT(SDL_RenderCopyEx(pRenderer, m_texture, &srcRect, &dstRect, m_orientation, nullptr, SDL_FLIP_NONE) == 0, SDL_GetError());

    // Animation
    if (m_currentFrame <= m_endFrame)
    {
        if (m_animationTimer.update(m_animationFPS))
        {
            m_currentFrame++;
            if (m_currentFrame > m_endFrame)
            {
                m_currentFrame = 1;
            }
        }
    }
}


#endif // !BACKGROUND_OBJECT_H
