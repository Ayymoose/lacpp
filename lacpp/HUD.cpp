#include "HUD.h"
#include "Resource.h"
#include "Camera.h"

HUD::HUD()
{
    m_Texture = ResourceManager::getInstance()[RSC_HUD];
}

HUD::~HUD()
{

}

void HUD::render(SDL_Renderer* pRenderer)
{
    SDL_Rect rect = { 0,CAMERA_HEIGHT,160,16 };
    SDL_RenderCopyEx(pRenderer, m_Texture, nullptr, &rect, 0, nullptr, SDL_FLIP_NONE);
}