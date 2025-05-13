#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "InputManager.h"
#include "fstream"
#include "sstream"


class Menu {

public:
	Menu(sf::RenderWindow* window, InputManager* inputManager)
	{
		m_window = window;
		m_inputManager = inputManager;
	}

	Menu* getActiveMenu()
	{

		if (m_hasActiveSubMenu) {
			return m_activeSubmenu;
		}

		return this;
	}
	void parseUIdata()
	{
		std::ifstream file;

		file.open(m_menuUiDataPath);
		if (file.is_open()) {
			std::string line;
			std::map<std::string, Button>::iterator button = m_buttons.begin();
			std::istringstream input;
			std::cout << "found ui data path: " << m_menuUiDataPath << std::endl;
			while (std::getline(file, line)) {
				std::cout << "found line " << std::endl;
				if (line.find("TPos:")) {

					line.erase(0, line.find(":") + 1);
					input.str(line);
					std::cout << "parsing ui data " << line << std::endl;
					float x, y;
					input >> x;
					input >> y;
					std::cout << "x:" << x << " y:" << y << std::endl;
					if (button != m_buttons.end()); {
						button->second.setTextPos(sf::Vector2f(x, y));
						button++;
						input.clear();
						input.str("");
						continue;
					}
					std::cout << "line amout greater than number of buttons check file " << m_menuUiDataPath << std::endl;




				}



			}
		}
		else {
			std::cout << "could not get ui data at path " << m_menuUiDataPath << std::endl;
		}
		file.close();
	}
	virtual void editModeUpdate(float dt)
	{

		if (!m_hasActiveSubMenu) {
			editButtons();
			saveUiData();
			return;
		}

		if (m_hasActiveSubMenu && !m_activeSubmenu->shouldDraw()) {
			m_hasActiveSubMenu = false;
			m_activeSubmenu = nullptr;
		}
		else {
			m_activeSubmenu->editModeUpdate(dt);
		}



	}
	void saveUiData() {
		if (m_inputManager->keyReleased(sf::Keyboard::S)) {
			saveTextPositions();
			std::cout << "saving ui data" << std::endl;
		}

	}
	void editButtons() {


		sf::Text* selected = nullptr;
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*m_window));
		m_clickedElementId = "";
		for (std::map<std::string, Button>::iterator it = m_buttons.begin(); it != m_buttons.end(); it++) {

			if (it->second.getTextRef()->getGlobalBounds().contains(mousePos))
			{
				if (m_inputManager->isMouseDown(sf::Mouse::Left)) {
					selected = it->second.getTextRef();
					selected->setPosition(mousePos);
					break;
				}
				if (m_inputManager->keyReleased(sf::Keyboard::Enter)) {
					
					m_clickedElementId = it->second.getButtonId();
					updateUiBindings();
					try {
						std::cout << "clicked element id set to " << m_clickedElementId << std::endl;
						m_activeSubmenu = m_subMenus.at(it->second.getLinkedMenuId()).get();
						std::cout << "set sub menu to " << it->first << std::endl;
						m_activeSubmenu->setShouldDraw(true);
						m_hasActiveSubMenu = true;
					}
					catch (...) {
						std::cout << "button sub menu not found button id:" << it->first << " not found " << std::endl;
					}
					

					break;
				}



			}

		}

		

	}
	virtual ~Menu() {
		std::cout << "menu destructor called" << std::endl;

	}
	void draw(sf::RenderWindow* window)
	{

		if (m_hasActiveSubMenu) {
			m_activeSubmenu->draw(window);
			return;
		}
		drawButtons(window);

	}
	virtual void update()
	{

		if (!m_hasActiveSubMenu) {
			updateUI();
			updateUiBindings();
			return;
		}
		if (m_hasActiveSubMenu && !m_activeSubmenu->shouldDraw()) {
			m_hasActiveSubMenu = false;
			m_activeSubmenu = nullptr;
		}
		else {
			m_activeSubmenu->update();
		}


	}
	void updateUI() {
		m_clickedElementId = "";
		updateButtons();


	}
	void drawButtons(sf::RenderWindow* window)
	{
		for (std::map<std::string, Button>::iterator it = m_buttons.begin(); it != m_buttons.end(); it++) {

			it->second.draw(window);
		}
	}
	void updateButtons()
	{  
		
		for (std::map<std::string, Button>::iterator it = m_buttons.begin(); it != m_buttons.end(); it++) {

			if (it->second.getShape().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*m_window))) &&
				m_inputManager->mouseReleased(sf::Mouse::Left))
			{
				try {
					m_clickedElementId = it->second.getButtonId();
					std::cout << "clicked element id set to " << m_clickedElementId << std::endl;
					m_activeSubmenu = m_subMenus.at(it->second.getLinkedMenuId()).get();
					std::cout << "set sub menu to " << it->first << std::endl;
					m_activeSubmenu->setShouldDraw(true);
					m_hasActiveSubMenu = true;
				}
				catch (...) {
					std::cout << "button sub menu not found button id:" << it->first << " not found " << std::endl;
				}
				std::cout << "button is being hovered " << std::endl;

			}

		}
	}

	virtual void initialise() = 0;
	virtual void initUiBindings() = 0;
	virtual void updateUiBindings() = 0;

	bool shouldDraw() const
	{
		return m_shouldDraw;
	}
	void setShouldDraw(bool shouldDraw)
	{
		m_shouldDraw = shouldDraw;
	}
	virtual void initialiseButtons() = 0;
	void saveTextPositions()
	{
		if (m_hasActiveSubMenu) {

			m_activeSubmenu->saveTextPositions();
			return;
		}
		std::ofstream file(m_menuUiDataPath);
		std::cout << "saving data for ui path is:" << m_menuUiDataPath << std::endl;
		if (!file.is_open()) {
			std::cout << "could not find path to ui data " << m_menuUiDataPath << std::endl;
		}
		std::string textData = "";
		for (std::map<std::string, Button>::iterator it = m_buttons.begin(); it != m_buttons.end(); it++) {
			textData = std::to_string(it->second.getTextPosition().x) + " " + std::to_string(it->second.getTextPosition().y);
			std::cout << "saving text data " << textData << std::endl;
			std::string fullText = "Tpos:" + textData + "\n";
			std::cout << "full text data " << fullText << std::endl;
			file << fullText;
		}

		file.close();


	}

protected:
	sf::RenderWindow* m_window = nullptr;
	std::vector<std::string> m_buttonIds; 
	
	std::map<std::string,Button> m_buttons;
	
	InputManager* m_inputManager = nullptr;
	std::map<std::string, std::shared_ptr<Menu>> m_subMenus;
	std::string m_buttonFontPath; 
	sf::Color m_buttonTextColour;
	sf::Color m_buttonBackgroundColour;
	sf::Vector2f m_buttonSize; 
	std::string m_menuUiDataPath;
	std::string menuInfoFilePath;
	sf::Vector2f m_buttonSpacing;
	std::string m_clickedElementId;
	float m_buttonWidth = 0.0f;
	float m_buttonHeight = 0.0f;
	unsigned int m_buttonCharSize = 0; 
	bool m_shouldDraw = false;
	bool m_hasActiveSubMenu = false;
	Menu * m_activeSubmenu = nullptr;
	




};