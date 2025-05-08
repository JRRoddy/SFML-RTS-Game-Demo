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
	m_textureManager.get()->loadTextures(m_pathToTextures);
	m_textureManager.get()->loadAnims(m_pathToAnims);
	m_spriteGenerator = std::make_unique<SpriteGenerator>(SpriteGenerator(m_textureManager.get()));
	m_inputManager = std::make_unique<InputManager>(InputManager(m_window)); 
	m_camera = std::make_unique<Camera>(Camera(window, sf::FloatRect(0, 0, window->getSize().x, window->getSize().y)));
	
	m_player = std::make_unique<Player>(Player( sf::Vector2f(window->getSize()) / 2.0f, m_spriteGenerator.get(), m_inputManager.get(),m_camera.get())); 
	
	
	// as level generator has its own resoruces within the class allocated on the heap but it is a single object that is easy to track(as it exists for the life time of the prorgam) 
	// here we use a raw pointer that is simply deleted at the end of the program 
	m_levelGenerator = new LevelGenerator(m_spriteGenerator.get(), sf::Vector2f(window->getSize()) / 2.0f,m_player.get(), sf::Vector2i(64, 64), sf::Vector2f(512.0f, 512.0f), sf::Vector2i(2, 2));





}

SceneManager::~SceneManager()
{
	delete m_levelGenerator;
}

void SceneManager::draw()
{
	m_levelGenerator->drawObjects(m_window);
	m_player.get()->draw(m_window);

}

void SceneManager::update(float dt,sf::Event & event)
{
	
    m_inputManager->pollEvents(event);
	m_levelGenerator->update(dt);
	m_inputManager->endFrame();

}
