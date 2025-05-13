#include "MenuManager.h"

MenuManager::MenuManager(std::vector<std::shared_ptr<Menu>> &nonGameplayMenus,size_t startMenuIndex, bool editMode)
{
	m_nonGameplayMenus = nonGameplayMenus;
	m_activeOutOfGameMenu = m_nonGameplayMenus[startMenuIndex].get();
	m_editMode = editMode;
}



MenuManager::~MenuManager(){
 

	
}

void MenuManager::update(float dt)
{
	
	if (m_editMode) {
		m_activeOutOfGameMenu->editModeUpdate(dt);

		

		return;
	}
	if (isDrawingOutOfGameMenus()){
		m_activeOutOfGameMenu->update();
	}
	
}



void MenuManager::draw(sf::RenderWindow* window)
{
	if (isDrawingOutOfGameMenus()) {
		m_activeOutOfGameMenu->draw(window);
	}

}



Menu* MenuManager::getActiveMenu()
{
	return m_activeOutOfGameMenu;
}
bool MenuManager::sumActiveMenus(std::shared_ptr<Menu> a, std::shared_ptr<Menu> b)
{
	return a->shouldDraw() + b->shouldDraw();
}
bool MenuManager::isDrawingOutOfGameMenus()
{
	
	return m_activeOutOfGameMenu->shouldDraw();
	 

}


