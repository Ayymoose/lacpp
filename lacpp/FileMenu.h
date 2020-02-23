#ifndef FILE_MENU_H
#define FILE_MENU_H

#include "Renderable.h"
#include "Controllable.h"

class FileMenu : public Controllable, public Renderable
{
public:
    FileMenu();
    ~FileMenu();
    void control(const SDL_Event& event);
    void render(SDL_Renderer* pRenderer);

private:

};


#endif // !FILE_MENU_H
