#include "SceneManager.h"

SceneManager::SceneManager(sf::RenderWindow* window, unsigned int windowWidth, unsigned int windowHeight)
{
	srand(time(0));
	m_window = window; 
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

	m_textureManager = std::make_unique<TextureManager>(TextureManager()); 
	m_spriteGenerator = std::make_unique<SpriteGenerator>(SpriteGenerator(m_textureManager.get()));


	//std::cout << "texture manager is null"<<(m_textureManager.get() == nullptr) << std::endl;

}

SceneManager::~SceneManager()
{
}

void SceneManager::draw()
{


}

void SceneManager::update(float dt)
{
}
