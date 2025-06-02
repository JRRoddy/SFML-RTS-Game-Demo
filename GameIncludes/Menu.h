#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "InputManager.h"
#include "fstream"
#include "sstream"
#include "UiSlider.h"
#include "SpriteGenerator.h"

// the menu class is the main abstarct class for all other menu objects 
// providing an interface for various child menu objects to then define 
// the functionaility of on there own as menus mmay initilaise things such as
// ui text and other elements differenlty but will all potentila have 
// those elements therefore having this interface makes it easier to quickly 
// create and reuse common features found across all child menu classes 
// of this abstract menu class 
class Menu {

public:
	Menu(sf::RenderWindow* window, InputManager* inputManager,SpriteGenerator * spriteGenerator);
	Menu() {};

	Menu* getActiveMenu();
	
	void parseUIdata();
	
	virtual void editModeUpdate(float dt);
	
	void saveUiData();
	void initSubMenus();
	void editButtons();
	virtual ~Menu() {
		std::cout << "menu destructor called" << std::endl;

	}
	virtual void draw(sf::RenderWindow* window);
	
	virtual void update();

	void resetSelectedElementIds();
	
	void updateUI();
		
	void drawTextObjects(sf::RenderWindow* window);

	void drawButtons(sf::RenderWindow* window);
	void drawSliders(sf::RenderWindow* window);

	void updateButtons();
	void updateSliders();
	void updateSelectedSlider();
	virtual void initialise() = 0;
	virtual void initUiBindings() = 0;
	virtual void updateUiBindings() = 0;
	virtual void initialiseButtons() = 0;
	virtual void initialiseLoneText() = 0;
	virtual void initialiseSliders() = 0;
	bool shouldDraw() const;
	void setShouldDraw(bool shouldDraw);
	void saveTextPositions();
	

protected:
	sf::RenderWindow* m_window = nullptr;
	std::vector<std::string> m_buttonIds; 
	std::vector<std::string> m_sliderIds; 
	std::vector<std::string> m_sliderStringText;
	std::map<std::string,Button> m_buttons;
	std::map<std::string,UiSlider> m_sliders;
	sf::Text m_menuHeaderText;
	sf::Vector2f m_defaultSliderSize; 
	sf::Color m_defaultSliderColour; 
	sf::Color m_defaultSliderIndicatorColour;  
	float m_sliderTextPadding = 0.0f;
	float m_defaultSliderIndicatorRadi = 0.0f; 
	float m_defaultSliderPercentage = 0.0f; 
	sf::Color m_sliderTextColour; 
	unsigned int m_sliderTextCharSize = 0; 
	bool m_draggingElementSelected = false;
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
	std::string m_uiButtonTexturePath;
	sf::Vector2f m_textObjectSpacing; 
	std::string m_clickedElementId;
	std::string m_draggingElementId;
	sf::Font m_textFont;
	float m_buttonWidth = 0.0f;
	float m_buttonHeight = 0.0f;
	unsigned int m_buttonCharSize = 0; 
	bool m_shouldDraw = false;
	bool m_hasActiveSubMenu = false;
	Menu * m_activeSubmenu = nullptr;
	SpriteGenerator* m_spriteGenerator = nullptr;
	




};