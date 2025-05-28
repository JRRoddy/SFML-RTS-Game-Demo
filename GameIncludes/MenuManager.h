#pragma once
#include "Menu.h"
#include "numeric"
class MenuManager {

public:

	MenuManager(std::vector<std::shared_ptr<Menu>> &nonGameplayMenus, size_t startMenuIndex, bool editMode = false);
	~MenuManager();
	void update(float dt); 
	void draw(sf::RenderWindow* window);
	Menu* getActiveMenu();
	bool isDrawingOutOfGameMenus();
	bool sumActiveMenus(std::shared_ptr<Menu> a, std::shared_ptr<Menu> b);
	
private:

	std::vector<std::shared_ptr<Menu>> m_nonGameplayMenus;
	Menu* m_activeOutOfGameMenu = nullptr;
	bool m_editMode = false;



};


