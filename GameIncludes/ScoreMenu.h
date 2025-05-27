#pragma once
#include "Menu.h"
#include "UIActionBinder.h"

// here we create a struct which gives us the ability to create a function object
// by overloading the () operator usually used to call a function allowing us to 
// pass the struct to various STL algorithms such as std::sort which is 
// used to sort player scores being read from a file 
// using the struct for a functor is also quite flexible as the way in which 
/// the functor behaves can be easily edited by editing the way the operator() is overloaded in terms of its functionality 
struct scoreSort{
	
	bool operator()(std::string scoreTextA, std::string  scoreTextB) { 
		
		size_t scoreALocationStart = scoreTextA.find_last_of(":") + 1;
		size_t scoreBLocationStart = scoreTextB.find_last_of(":") + 1;

		int scoreA = std::stoi(scoreTextA.substr(scoreALocationStart, scoreTextA.find("\n")));
		int scoreB = std::stoi(scoreTextB.substr(scoreBLocationStart, scoreTextB.find("\n")));



		return scoreA > scoreB;
	}

};


class ScoreMenu:public Menu {
public:
	ScoreMenu();
	ScoreMenu(sf::RenderWindow* window, InputManager* inputManager);
	~ScoreMenu() {
		std::cout << "score menu destructor called" << std::endl;
	};
	void initialise();
	void initialiseButtons();
	void initUiBindings();
	void updateUiBindings();
	void initialiseLoneText();
	void initialiseSliders() {};
	void draw(sf::RenderWindow* window);
	std::vector<std::string> readScoreValues() const;
	std::vector<std::string> readScoreValues(std::string& filePath) const;
private:
	void backButtonAction();
	std::shared_ptr<UiActionBinder<ScoreMenu>>m_uiActionBinder;

	
	sf::Font m_scoreHeaderTextFont;
	std::string m_scoreHeaderTextFontPath;
	std::string m_scoreMenuHeadertext;
	sf::Color m_scoreHeaderTextColour;
	unsigned int m_scoreHeaderCharSize = 0; 
	unsigned int m_scoresCharSize = 0;
	

	std::string m_runCountPath = "../Assets/PlayerData/runData.txt";
	std::string m_savedScoresFilePath = "../Assets/PlayerData/scores.txt";
};