#pragma once
#include "Menu.h"
#include "UIActionBinder.h"
class OptionsMenu:public Menu {
	
public:
	OptionsMenu(sf::RenderWindow* window, InputManager* inputManage);
	~OptionsMenu() {};
	void initialise();
	void initUiBindings() ;
	void updateUiBindings() ;
	void draw(sf::RenderWindow* window);
	void initialiseButtons() ;
	void backButtonAction();
	void initialiseLoneText() ;
	void initialiseSliders();

private:
	std::shared_ptr<UiActionBinder<OptionsMenu>> m_uiActionBinder;

	sf::Font m_optionsHeaderTextFont;
	std::string m_optionsHeaderTextFontPath;
	std::string m_optionsMenuHeadertext;
	sf::Color m_optionsHeaderTextColour;
	sf::Vector2f m_sliderSpacing;
	unsigned int m_optionsHeaderCharSize = 0;

};