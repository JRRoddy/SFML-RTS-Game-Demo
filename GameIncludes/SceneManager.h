#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SpriteGenerator.h"
#include "TextureManager.h"
#include "LevelGenerator.h"
#include "InputManager.h"
#include "Camera.h"
#include "MenuManager.h"
#include "MenuHeaders.h"
#include "thread"
#include "mutex" 
#include "SFML/Audio/Sound.hpp"
#include "GameSettings.h"
#include "AudioManager.h"


// simple scene manager class that will hold the current game state and all the main components of the game ensuring 
// that the game is encapsulated into one class 


class SceneManager {

public:
	SceneManager(sf::RenderWindow* _window, unsigned int _windowWidth, unsigned int _windowHeight, bool editMode = false);
	~SceneManager();

	void draw();
	void update(float dt,sf::Event & event); 
	void loadMenuSplashScreen(sf::RenderWindow* window);
	void readUserDataFile() ;

private:

	sf::RenderWindow * m_window;
	unsigned int m_windowWidth;
	unsigned int m_windowHeight; 
	bool m_menuLoadingComplete = false;
	bool m_editMode;
	std::unique_ptr<InputManager> m_inputManager;
	std::unique_ptr<MenuManager> m_menuManager;
	std::vector<std::shared_ptr<Menu>>m_menusPresentInScene; 
	LevelGenerator *  m_levelGenerator;
	std::unique_ptr<TextureManager> m_textureManager; 
	std::unique_ptr<AudioManager> m_audioManager;
	std::unique_ptr<SpriteGenerator> m_spriteGenerator;
	std::unique_ptr<Camera> m_camera;
	std::unique_ptr<Player> m_player;
	std::vector<std::string> m_userData;
	std::string m_pathToTextures = "../Assets/Textures/PathsToTextures.txt";
	std::string m_pathToAnims = "../Assets/Animations/PathsToAnimations.txt";
	std::string m_userDetails = "../Assets/UserDetails/UserDetails - Copy.csv";
	std::string m_pathToSounds = "../Assets/Audio/PathsToAudio.txt"; 
	std::string m_pathToMusic = "../Assets/Audio/PathsToMusic.txt";
	std::mutex m_loadingMenuMutex;
	std::thread m_loadUserFileData;
	std::thread m_loadingMenuSplashScreen; 
	std::mutex m_menuCanLoad;
	std::mutex m_menuCanInteract;
	std::condition_variable m_menuLoadingCompleteCvar;
	
}; 



