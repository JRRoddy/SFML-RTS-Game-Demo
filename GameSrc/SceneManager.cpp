#include "SceneManager.h"

SceneManager::SceneManager(sf::RenderWindow* window, unsigned int windowWidth, unsigned int windowHeight)
{
	srand(time(0));
	m_window = window; 
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;
	std::cout << "initialising scene manager:" << std::endl;

	// allocate memory that will be tracked via unique ptrs for each object that will only have a single instance within the game 
	m_textureManager = std::make_unique<TextureManager>(TextureManager()); 
	m_textureManager.get()->loadTextures(pathToTextures);

	m_spriteGenerator = std::make_unique<SpriteGenerator>(SpriteGenerator(m_textureManager.get()));

	m_levelGenerator = std::make_unique<LevelGenerator>(LevelGenerator(m_spriteGenerator.get(), sf::Vector2f(window->getSize()) / 2.0f,sf::Vector2i(64,64)));

}

SceneManager::~SceneManager()
{
}

void SceneManager::draw()
{
	m_levelGenerator.get()->getCurrentAreaGrid()->draw(m_window);

}

void SceneManager::update(float dt){}
