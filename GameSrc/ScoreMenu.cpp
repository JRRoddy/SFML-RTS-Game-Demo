#include "ScoreMenu.h"

ScoreMenu::ScoreMenu(sf::RenderWindow* window, InputManager* inputManager):Menu(window,inputManager)
{
	std::cout << "initialsing main menu " << std::endl;

	m_buttonIds = { "back" };

	m_buttonCharSize = 50;
	m_buttonWidth = 200.0f;
	m_buttonTextColour = sf::Color::White;
	m_buttonBackgroundColour = sf::Color::Color(128, 128, 128, 255);
	m_buttonSpacing = sf::Vector2f(20.0f, 20.0f);
	m_buttonHeight = 100.0f;
	m_menuUiDataPath = "../Assets/UiData/ScoreMenu.txt";
	m_buttonFontPath = "../Assets/Fonts/Roboto.ttf";
	m_buttonSize = sf::Vector2f(m_buttonWidth, m_buttonHeight);
	m_shouldDraw = true;
	m_uiActionBinder = std::shared_ptr<UiActionBinder<ScoreMenu>>(new UiActionBinder<ScoreMenu>());
	
	
}

void ScoreMenu::initialise()
{
	initUiBindings();
	initialiseButtons();
	parseUIdata();

}

void ScoreMenu::initialiseButtons()
{
	std::cout << "score menu initialise buttons called" << std::endl;
	m_buttons.insert({ m_buttonIds[0],Button(m_buttonSize,m_buttonIds[0],m_buttonCharSize) });
	sf::Vector2f buttonPos = (sf::Vector2f(m_window->getSize()) - sf::Vector2f(m_buttonWidth,m_buttonHeight)/2.0f)-m_buttonSpacing;
	m_buttons[m_buttonIds[0]].setPosition(buttonPos);
	m_buttons[m_buttonIds[0]].setTextColour(m_buttonTextColour);
	m_buttons[m_buttonIds[0]].setBackgroundColour(m_buttonBackgroundColour);
	m_buttons[m_buttonIds[0]].setFont(m_buttonFontPath);
	m_buttons[m_buttonIds[0]].setButtonId(m_buttonIds[0]);


}

void ScoreMenu::initUiBindings()
{
	m_uiActionBinder->addBinding("back", &ScoreMenu::backButtonAction);

}

void ScoreMenu::updateUiBindings()
{
	if (m_clickedElementId != "" && m_uiActionBinder->getActionBinding(m_clickedElementId) != nullptr) {

		((*this).*(m_uiActionBinder->getActionBinding(m_clickedElementId)))();


	}
}

void ScoreMenu::backButtonAction()
{
	m_shouldDraw = false;

}
