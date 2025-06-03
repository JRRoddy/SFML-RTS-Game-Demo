#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow* window,InputManager * inputManager, SpriteGenerator * spriteGenerator,AudioManager * audioManager):Menu(window,inputManager,spriteGenerator,audioManager)
{
	std::cout << "initialsing main menu " << std::endl;

	m_buttonIds = { "play","score","options","exit"};
	
	m_buttonCharSize = 40; 
	m_buttonWidth = 200.0f; 
	m_buttonTextColour = sf::Color::White;
	m_buttonBackgroundColour = sf::Color::Color(128, 128, 128, 255);
	m_buttonSpacing = sf::Vector2f(0.0f, 20.0f);
	m_buttonHeight = 100.0f;
	m_menuUiDataPath = "../Assets/UiData/MainMenu.txt";
	m_textFontPath = "../Assets/Fonts/Roboto.ttf";
	m_uiButtonTexturePath = "../Assets/Textures/UiBlueButton.png";
	m_menuBackgroundMusicPath = "../Assets/Audio/MenuMusic.mp3";
	m_buttonSize = sf::Vector2f(m_buttonWidth, m_buttonHeight);
	m_shouldDraw = true;
	m_uiActionBinder = std::make_unique<UiActionBinder<MainMenu>>(UiActionBinder<MainMenu>());
	m_subMenus = {
      {"score",std::make_shared<ScoreMenu>(ScoreMenu(m_window,m_inputManager,m_spriteGenerator,m_audioManager))},
	  {"options",std::make_shared<OptionsMenu>(OptionsMenu(m_window,m_inputManager,m_spriteGenerator,m_audioManager))}
	};
	initialise();
}

void MainMenu::initialise()
{
	std::cout << "initialise main menu method called " << std::endl;
	initUiBindings();
	initialiseButtons();
	parseUIdata();
	initSounds();
	initMusic();


	for (std::map<std::string, std::shared_ptr<Menu>>::iterator it = m_subMenus.begin(); it != m_subMenus.end(); it++) {
		it->second->initialise();

	}
	m_backgroundMusic->setLoop(true); 
	m_backgroundMusic->play();
}

void MainMenu::initialiseButtons()
{
	std::cout << "initialsing main menu buttons " << std::endl;
	sf::Vector2f buttonStartPosY = sf::Vector2f(0.0f, 30.0f);
	for (int i = 0; i < m_buttonIds.size(); i++){

		std::shared_ptr<sf::Sprite> buttonSprite = m_spriteGenerator->GenerateSpriteCopy(m_uiButtonTexturePath);
		sf::Vector2f buttonPos = sf::Vector2f(m_window->getSize().x / 2.0f, buttonStartPosY.y + (i + 1) * buttonSprite->getGlobalBounds().getSize().y) + (m_buttonSpacing * float(i + 1));
		
		
		m_buttons.insert({ m_buttonIds[i],Button(m_buttonSize,m_buttonIds[i],m_buttonCharSize) }); 
		m_buttons[m_buttonIds[i]].setSpirte(buttonSprite);
		m_buttons[m_buttonIds[i]].setPosition(buttonPos);
		m_buttons[m_buttonIds[i]].setTextColour(m_buttonTextColour);
		m_buttons[m_buttonIds[i]].setBackgroundColour(m_buttonBackgroundColour);
		m_buttons[m_buttonIds[i]].setFont(m_textFontPath);
		m_buttons[m_buttonIds[i]].setButtonId(m_buttonIds[i]);
	}

	m_buttons["score"].setLinkedMenuId("score");
	m_buttons["options"].setLinkedMenuId("options");
}

void MainMenu::initUiBindings()
{
	std::cout << "adding binding to main menu ui " << std::endl;
	m_uiActionBinder->addBinding("play", &MainMenu::playButtonAction);
	m_uiActionBinder->addBinding("exit", &MainMenu::exitButtonAction);
}

void MainMenu::updateUiBindings()
{
	if (m_clickedElementId != "" && m_uiActionBinder->getActionBinding(m_clickedElementId) != nullptr) {

		((*this).*(m_uiActionBinder->getActionBinding(m_clickedElementId)))();


	}



}





void MainMenu::playButtonAction()
{
	m_shouldDraw = false;
	m_backgroundMusic->stop();
}

void MainMenu::exitButtonAction()
{

	m_window->close();


}
