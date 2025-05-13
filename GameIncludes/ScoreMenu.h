#pragma once
#include "Menu.h"
#include "UIActionBinder.h"
class ScoreMenu:public Menu {
public:
	ScoreMenu(sf::RenderWindow* window, InputManager* inputManager);
	~ScoreMenu() {
		std::cout << "score menu destructor called" << std::endl;
	};
	void initialise();
	void initialiseButtons();
	void initUiBindings();
	void updateUiBindings();
private:
	void backButtonAction();
	std::shared_ptr<UiActionBinder<ScoreMenu>>m_uiActionBinder;

};