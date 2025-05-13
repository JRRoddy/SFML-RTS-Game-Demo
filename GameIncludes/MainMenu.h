#pragma once
#include "Menu.h"
#include "UIActionBinder.h"
#include "ScoreMenu.h"

class MainMenu:public Menu{
public: 
	MainMenu(sf::RenderWindow * window,InputManager * inputManager);
	~MainMenu() {
		std::cout << "main menu destructor called" << std::endl;
	};
	void initialise();
	void initialiseButtons();
	void initUiBindings();
	void updateUiBindings();
private:
	void playButtonAction();
	std::unique_ptr<UiActionBinder<MainMenu>>m_uiActionBinder;

};