#pragma once
#include "Menu.h"
#include "UIActionBinder.h"
#include "ScoreMenu.h"
#include "OptionsMenu.h"

class MainMenu:public Menu{
public: 
	MainMenu(sf::RenderWindow * window,InputManager * inputManager, SpriteGenerator * spriteGenerator);
	~MainMenu() {
		std::cout << "main menu destructor called" << std::endl;
	};
	void initialise();
	void initialiseButtons();
	void initUiBindings();
	void updateUiBindings();
	void initialiseLoneText() {};
	void initialiseSliders() {};
private:
	void playButtonAction();
	void exitButtonAction();
	std::unique_ptr<UiActionBinder<MainMenu>>m_uiActionBinder;

};