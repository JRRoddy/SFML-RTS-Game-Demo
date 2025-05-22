#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "InputManager.h"
#include "fstream"
#include "sstream"

// the menu class is the main abstarct class for all other menu objects 
// providing an interface for various child menu objects to then define 
// the functionaility of on there own as menus mmay initilaise things such as
// ui text and other elements differenlty but will all potentila have 
// those elements therefore having this interface makes it easier to quickly 
// create and reuse common features found across all child menu classes 
// of this abstract menu class 
class Menu {

public:
	Menu(sf::RenderWindow* window, InputManager* inputManager);
	Menu() {};

	Menu* getActiveMenu();
	
	void parseUIdata();
	
	virtual void editModeUpdate(float dt);
	
	void saveUiData();
		
	void editButtons();
	virtual ~Menu() {
		std::cout << "menu destructor called" << std::endl;

	}
	virtual void draw(sf::RenderWindow* window);
	
	virtual void update();
	
	void updateUI();
		
	void drawTextObjects(sf::RenderWindow* window);

	void drawButtons(sf::RenderWindow* window);
	
	void updateButtons();
	
	virtual void initialise() = 0;
	virtual void initUiBindings() = 0;
	virtual void updateUiBindings() = 0;
	virtual void initialiseButtons() = 0;
	virtual void initialiseLoneText() = 0;

	bool shouldDraw() const;
	void setShouldDraw(bool shouldDraw);
	void saveTextPositions();
	

protected:
	sf::RenderWindow* m_window = nullptr;
	std::vector<std::string> m_buttonIds; 
	
	std::map<std::string,Button> m_buttons;
	
	InputManager* m_inputManager = nullptr;
	std::map<std::string, std::shared_ptr<Menu>> m_subMenus;
	std::vector<sf::Text> m_textObjects;
	std::string m_textFontPath; 
	sf::Color m_buttonTextColour;
	sf::Color m_buttonBackgroundColour;
	sf::Vector2f m_buttonSize; 
	std::string m_menuUiDataPath;
	std::string menuInfoFilePath;
	sf::Vector2f m_buttonSpacing;
	sf::Vector2f m_textObjectSpacing;
	std::string m_clickedElementId;
	sf::Font m_textFont;
	float m_buttonWidth = 0.0f;
	float m_buttonHeight = 0.0f;
	unsigned int m_buttonCharSize = 0; 
	bool m_shouldDraw = false;
	bool m_hasActiveSubMenu = false;
	Menu * m_activeSubmenu = nullptr;
	




};