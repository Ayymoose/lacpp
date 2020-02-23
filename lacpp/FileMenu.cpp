#include "FileMenu.h"
#include "Resource.h"

FileMenu::FileMenu()
{
    m_Texture = ResourceManager::getInstance()[RSC_FILE_MENU_1];
}

FileMenu::~FileMenu()
{

}

void FileMenu::control(const SDL_Event& event)
{

}

void FileMenu::render(SDL_Renderer* pRenderer)
{

}