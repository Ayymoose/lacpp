#include "FileMenu.h"
#include "Resource.h"

FileMenu::FileMenu()
{
    m_texture = ResourceManager::getInstance()[RSC_FILE_MENU_1];
}

FileMenu::~FileMenu()
{

}

void FileMenu::control()
{

}

void FileMenu::render(SDL_Renderer* pRenderer)
{

}