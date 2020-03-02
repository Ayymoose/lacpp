#ifndef HUD_H
#define HUD_H

#include "Renderable.h"

class HUD : public Renderable
{
public:
    HUD();
    ~HUD();
    int height() const
    {
        return m_height;
    }
    void render(SDL_Renderer* pRenderer) override;

};


#endif // !HUD_H
