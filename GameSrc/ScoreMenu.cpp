#include "ScoreMenu.h"

ScoreMenu::ScoreMenu()
{
	m_buttonIds = { "back" };

	m_buttonCharSize = 50;
	m_buttonWidth = 200.0f;
	m_buttonTextColour = sf::Color::White;
	m_buttonBackgroundColour = sf::Color::Color(128, 128, 128, 255);
	m_textObjectSpacing = sf::Vector2f(0.0f, 20.0f);
	m_buttonSpacing = sf::Vector2f(20.0f, 20.0f);
	m_buttonHeight = 100.0f;
	m_menuUiDataPath = "../Assets/UiData/ScoreMenu.txt";
	m_textFontPath = "../Assets/Fonts/Roboto.ttf";
	m_uiButtonTexturePath = "../Assets/Textures/UiBlueButton.png";

	m_buttonSize = sf::Vector2f(m_buttonWidth, m_buttonHeight);
	m_shouldDraw = true;
	m_scoreHeaderCharSize = 40;
	m_scoreHeaderTextColour = sf::Color::White;
	m_scoreHeaderTextFontPath = "../Assets/Fonts/Roboto.ttf";
	m_scoreMenuHeadertext = "Scores:";
	m_scoresCharSize = 40;

	m_uiActionBinder = std::shared_ptr<UiActionBinder<ScoreMenu>>(new UiActionBinder<ScoreMenu>());


}

ScoreMenu::ScoreMenu(sf::RenderWindow* window, InputManager* inputManager, SpriteGenerator * spriteGenerator,AudioManager * audioManager):Menu(window,inputManager,spriteGenerator,audioManager)
{
	std::cout << "initialsing main menu " << std::endl;

	m_buttonIds = { "back" };

	m_buttonCharSize = 50;
	m_buttonWidth = 200.0f;
	m_buttonTextColour = sf::Color::White;
	m_buttonBackgroundColour = sf::Color::Color(128, 128, 128, 255);
	m_textObjectSpacing = sf::Vector2f(0.0f,20.0f);
	m_buttonSpacing = sf::Vector2f(10.0f, 10.0f);
	m_buttonHeight = 100.0f;
	m_menuUiDataPath = "../Assets/UiData/ScoreMenu.txt";
	m_textFontPath = "../Assets/Fonts/Roboto.ttf"; 
	m_uiButtonTexturePath = "../Assets/Textures/UiBlueButton.png";
	m_buttonSize = sf::Vector2f(m_buttonWidth, m_buttonHeight);
	m_shouldDraw = true;
	m_scoreHeaderCharSize = 40;
	m_scoreHeaderTextColour = sf::Color::White;
	m_scoreHeaderTextFontPath = "../Assets/Fonts/Roboto.ttf";
	m_scoreMenuHeadertext = "Scores:";
	m_scoresCharSize = 40; 

	m_uiActionBinder = std::shared_ptr<UiActionBinder<ScoreMenu>>(new UiActionBinder<ScoreMenu>());

	
}

void ScoreMenu::initialise()
{
	initUiBindings();
	initialiseButtons();
	parseUIdata();
	initialiseLoneText();
	initSounds();


}

void ScoreMenu::initialiseButtons()
{
	std::cout << "score menu initialise buttons called" << std::endl;
	std::shared_ptr<sf::Sprite> buttonSprite = m_spriteGenerator->GenerateSpriteCopy(m_uiButtonTexturePath);

	m_buttons.insert({ m_buttonIds[0],Button(m_buttonSize,m_buttonIds[0],m_buttonCharSize) }); 
	m_buttons[m_buttonIds[0]].setSpirte(buttonSprite);
	sf::Vector2f buttonPos = (sf::Vector2f(m_window->getSize()) - sf::Vector2f(buttonSprite->getGlobalBounds().getSize()/2.0f)-m_buttonSpacing );
	m_buttons[m_buttonIds[0]].setPosition(buttonPos);
	m_buttons[m_buttonIds[0]].setTextColour(m_buttonTextColour);
	m_buttons[m_buttonIds[0]].setBackgroundColour(m_buttonBackgroundColour);
	m_buttons[m_buttonIds[0]].setFont(m_textFontPath);
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

void ScoreMenu::initialiseLoneText()
{

	std::vector<std::string> scoresSorted = readScoreValues();
	
	// create header text for the score menu
	m_scoreHeaderTextFont.loadFromFile(m_scoreHeaderTextFontPath);
	m_menuHeaderText.setFillColor(m_scoreHeaderTextColour);
	m_menuHeaderText.setCharacterSize(m_scoreHeaderCharSize);
	m_menuHeaderText.setFont(m_scoreHeaderTextFont);
	m_menuHeaderText.setString(m_scoreMenuHeadertext);
	std::cout << "score header text size " << m_scoreHeaderCharSize << std::endl;
	sf::Vector2f scoreHeaderTextPos = sf::Vector2f(m_window->getSize().x / 2.0f, float(0+m_scoreHeaderCharSize));
	m_menuHeaderText.setOrigin(m_menuHeaderText.getGlobalBounds().getSize()/2.0f);
	m_menuHeaderText.setPosition(scoreHeaderTextPos);

	m_textFont.loadFromFile(m_textFontPath);
	for (int i = 0; i < scoresSorted.size();i++) {

		m_textObjects.emplace_back();
		sf::Text& textObjectBack = m_textObjects.back();
		textObjectBack.setFont(m_textFont);
		textObjectBack.setCharacterSize(m_scoresCharSize);
		textObjectBack.setColor(m_scoreHeaderTextColour);
		textObjectBack.setString(scoresSorted[i]);
		textObjectBack.setOrigin(textObjectBack.getGlobalBounds().getSize()/2.0f);
		sf::Vector2f textObjectPos = sf::Vector2f(scoreHeaderTextPos.x, scoreHeaderTextPos.y + (i + 1) * m_scoreHeaderCharSize);
		m_textObjects.back().setPosition(textObjectPos+m_textObjectSpacing*float(i+1));

	}




}

void ScoreMenu::draw(sf::RenderWindow* window)
{
	if (m_hasActiveSubMenu) {
		m_activeSubmenu->draw(window);
		return;
	}
	drawButtons(window);
	drawTextObjects(window);
	window->draw(m_menuHeaderText);
}

std::vector<std::string> ScoreMenu::readScoreValues() const
{
	std::ifstream readScores;
	readScores.open(m_savedScoresFilePath);
	std::vector<std::string> scoresSorted;
	if (readScores.is_open()) {
		std::string line;
		int playSessionCount = 1;
		while (std::getline(readScores, line)) {

			scoresSorted.emplace_back("Run/session:" + std::to_string(playSessionCount) + " Score:" + line);
			playSessionCount++;
		}
		// sort the scores read in from the file using a functor as the predicate 
		// which defines the boolean operation used to determine which element  will be placed further 
		// to the back and which element will be placed closer to the beggining of the final sorted vector
		// i.e. sorting them in decending order in this case based on the score embeded in the string
		scoreSort sortScores{};
		std::sort(scoresSorted.begin(), scoresSorted.end(), sortScores);

	}
	return scoresSorted;
}

std::vector<std::string> ScoreMenu::readScoreValues(std::string &filePath) const
{
	std::ifstream readScores;
	readScores.open(filePath);
	std::vector<std::string> scoresSorted;
	if (readScores.is_open()) {
		std::string line;
		int playSessionCount = 1;
		while (std::getline(readScores, line)) {

			scoresSorted.emplace_back("Run/session:" + std::to_string(playSessionCount) + " Score:" + line);
			playSessionCount++;
		}
		// sort the scores read in from the file using a functor as the predicate 
		// which defines the boolean operation used to determine which element  will be placed further 
		// to the back and which element will be placed closer to the beggining of the final sorted vector
		// i.e. sorting them in decending order in this case based on the score embeded in the string
		scoreSort sortScores{};
		std::sort(scoresSorted.begin(), scoresSorted.end(), sortScores);

	}
	return scoresSorted;
}


void ScoreMenu::backButtonAction()
{
	m_shouldDraw = false;

}
