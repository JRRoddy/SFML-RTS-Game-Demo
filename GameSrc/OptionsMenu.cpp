#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(sf::RenderWindow* window, InputManager* inputManager):Menu(window,inputManager)
{
	m_buttonIds = { "back" };
	m_sliderIds = { "sound" };
	m_buttonCharSize = 50;
	m_buttonWidth = 200.0f;
	m_buttonHeight = 50.0f;
	m_buttonSize = sf::Vector2f(m_buttonWidth, m_buttonHeight);
	m_buttonSpacing = sf::Vector2f(20.0f, 20.0f);
	m_buttonTextColour = sf::Color::White;
	m_buttonBackgroundColour = sf::Color::Color(128, 128, 128, 255);
	m_textFontPath = "../Assets/Fonts/Roboto.ttf";
	m_menuUiDataPath = "../Assets/UiData/OptionsMenu.txt";
	m_uiActionBinder = std::shared_ptr<UiActionBinder<OptionsMenu>>(new UiActionBinder<OptionsMenu>());
	m_optionsHeaderCharSize = 40;
	m_optionsHeaderTextColour = sf::Color::White;
	m_optionsHeaderTextFontPath = "../Assets/Fonts/Roboto.ttf";
	m_optionsMenuHeadertext = "Options:";
	m_defaultSliderSize = sf::Vector2f(400.0f,40.0f);
	m_defaultSliderColour = sf::Color::Color(128,128,128,255);
	m_defaultSliderIndicatorColour = sf::Color::Color(255,255,255,255);
	m_defaultSliderIndicatorRadi = 10.0f;
	m_defaultSliderPercentage = 0.85f;
	m_sliderSpacing = sf::Vector2f(0.0f, 50.0f);

}

void OptionsMenu::initialise()
{
	initialiseButtons();
	initUiBindings();
	parseUIdata();
	initialiseLoneText();
	initialiseSliders();
}

void OptionsMenu::initUiBindings()
{

	m_uiActionBinder->addBinding("back", &OptionsMenu::backButtonAction);
	m_uiActionBinder->addBinding("sound", &OptionsMenu::volumeSliderAction);
}

void OptionsMenu::updateUiBindings()
{
	if (m_clickedElementId != "" && m_uiActionBinder->getActionBinding(m_clickedElementId) != nullptr) {

		((*this).*(m_uiActionBinder->getActionBinding(m_clickedElementId)))();

	}

	if (m_draggingElementId != "" && m_uiActionBinder->getActionBinding(m_draggingElementId) != nullptr) {

		((*this).*(m_uiActionBinder->getActionBinding(m_draggingElementId)))();
	}


}
void OptionsMenu::draw(sf::RenderWindow* window)
{
	if (m_hasActiveSubMenu) {
		m_activeSubmenu->draw(window);
		return;
	}
	drawButtons(window);
	drawTextObjects(window);
	drawSliders(window);
	window->draw(m_menuHeaderText);
}
void OptionsMenu::initialiseButtons()
{

	m_buttons.insert({ m_buttonIds[0],Button(m_buttonSize,m_buttonIds[0],m_buttonCharSize) });
	sf::Vector2f buttonPos = (sf::Vector2f(m_window->getSize()) - sf::Vector2f(m_buttonWidth, m_buttonHeight) / 2.0f) - m_buttonSpacing;
	m_buttons[m_buttonIds[0]].setPosition(buttonPos);
	m_buttons[m_buttonIds[0]].setTextColour(m_buttonTextColour);
	m_buttons[m_buttonIds[0]].setBackgroundColour(m_buttonBackgroundColour);
	m_buttons[m_buttonIds[0]].setFont(m_textFontPath);
	m_buttons[m_buttonIds[0]].setButtonId(m_buttonIds[0]);

}

void OptionsMenu::backButtonAction()
{
	m_shouldDraw = false;

}

void OptionsMenu::volumeSliderAction()
{
	GameSettings::soundVolumeModifier = m_sliders["sound"].getInterpolater();

}

void OptionsMenu::initialiseLoneText()
{
	m_optionsHeaderTextFont.loadFromFile(m_optionsHeaderTextFontPath);
	m_menuHeaderText.setFillColor(m_optionsHeaderTextColour);
	m_menuHeaderText.setCharacterSize(m_optionsHeaderCharSize);
	m_menuHeaderText.setFont(m_optionsHeaderTextFont);
	m_menuHeaderText.setString(m_optionsMenuHeadertext);
	sf::Vector2f optionsHeaderTextPos = sf::Vector2f(m_window->getSize().x / 2.0f, float(0 + m_optionsHeaderCharSize));
	m_menuHeaderText.setOrigin(m_menuHeaderText.getGlobalBounds().getSize() / 2.0f);
	m_menuHeaderText.setPosition(optionsHeaderTextPos);
}

void OptionsMenu::initialiseSliders()
{
	for (int i = 0; i < m_sliderIds.size();i++) {

		sf::Vector2f headerTextPos = m_menuHeaderText.getPosition();
		sf::Vector2f position = headerTextPos + (sf::Vector2f(0.0f, m_defaultSliderSize.y * (i + 1)) + sf::Vector2f(m_sliderSpacing * float(i + 1)));
		m_sliders.insert({
			m_sliderIds[i], 
			UiSlider(m_defaultSliderPercentage,
				     m_defaultSliderSize,
					 position,
					 m_defaultSliderColour,
					 m_defaultSliderIndicatorRadi,
					 m_defaultSliderIndicatorColour) 
		});

		m_sliders[m_sliderIds[i]].setElementId(m_sliderIds[i]);
	}

}
