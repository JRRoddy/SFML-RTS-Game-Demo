#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SpriteGenerator.h"
#include "TextureManager.h"
#include "LevelGenerator.h"
#include "InputManager.h"
#include "Camera.h"
// simple scene manager class that will hold the current game state and all the main components of the game ensuring 
// that the game is encapsulated into one class
class SceneManager {

public:
	SceneManager(sf::RenderWindow* _window, unsigned int _windowWidth, unsigned int _windowHeight);
	~SceneManager();

	void draw();
	void update(float dt,sf::Event & event); 

private:

	sf::RenderWindow * m_window;
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;
	std::unique_ptr<InputManager> m_inputManager;

	LevelGenerator *  m_levelGenerator;
	std::unique_ptr<TextureManager> m_textureManager;
	std::unique_ptr<SpriteGenerator> m_spriteGenerator;
	std::unique_ptr<Camera> m_camera;
	std::unique_ptr<Player> m_player;
	std::string m_pathToTextures = "../Assets/Textures/PathsToTextures.txt";
	std::string m_pathToAnims = "../Assets/Animations/PathsToAnimations.txt";
};