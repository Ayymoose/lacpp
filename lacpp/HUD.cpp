#include "HUD.h"
#include "Resource.h"
#include "Camera.h"

HUD::HUD()
{
    m_texture = ResourceManager::getInstance()[RSC_HUD];
    m_height = 16;
    m_width = 160;
}

HUD::~HUD()
{

}

void HUD::render(SDL_Renderer* pRenderer)
{
    SDL_Rect dstRect = { 0,CAMERA_HEIGHT,m_width,m_height };
    SDL_RenderCopy(pRenderer, m_texture, nullptr, &dstRect);
}