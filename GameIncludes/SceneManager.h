#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SpriteGenerator.h"
#include "TextureManager.h"
#include "LevelGenerator.h"
// simple scene manager class that will hold the current game state and all the main components of the game ensuring 
// that the game is encapsulated into one class
class SceneManager {

public:
	SceneManager(sf::RenderWindow* _window, unsigned int _windowWidth, unsigned int _windowHeight);
	~SceneManager();

	void draw();
	void update(float dt); 

private:

	sf::RenderWindow * m_window;
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;
	
	std::unique_ptr<LevelGenerator> m_levelGenerator;
	std::unique_ptr<TextureManager> m_textureManager;
	std::unique_ptr<SpriteGenerator> m_spriteGenerator;
	std::string pathToTextures = "../Assets/Textures/PathsToTextures.txt";
};