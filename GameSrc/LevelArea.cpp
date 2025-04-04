#include "LevelArea.h"

LevelArea::LevelArea()
{
	m_width = 128.0f;
	m_height = 128.0f;
	m_areaVertexArray = new sf::VertexArray(sf::Quads,4);

	setVerticies();


}

LevelArea::LevelArea(sf::Vector2f position):GameObject(position)
{
	m_width = 128.0f;
	m_height = 128.0f;
	m_areaVertexArray = new sf::VertexArray(sf::Quads, 4); 
	std::cout << "level area base constructor called " << std::endl;
	std::cout << "new position x is " << m_position.x << " new position y is " << m_position.y << std::endl;
	setVerticies();

}

int LevelArea::getSpawnCount()
{
	return m_maxSpawnCount;
}
// update the quads vertcies that will be used to draw the area and display its background

void LevelArea::draw(sf::RenderWindow * window) {

	window->draw(*m_areaVertexArray, m_baseSpriteRef.get()->getTexture());


}


void LevelArea::setBounds()
{
	m_areaVertexArray[0][0].position =  sf::Vector2f(m_position.x - m_width, m_position.y - m_height);
	m_areaVertexArray[0][1].position = sf::Vector2f(m_position.x - m_width, m_position.y + m_height);
	m_areaVertexArray[0][2].position = sf::Vector2f(m_position.x + m_width, m_position.y + m_height);
	m_areaVertexArray[0][3].position = sf::Vector2f(m_position.x + m_width, m_position.y - m_height);

}

void LevelArea::setVerticies()
{
	m_areaVertexArray[0][0] = sf::Vertex(sf::Vector2f(m_position.x - m_width, m_position.y - m_height),sf::Vector2f(0.0f,0.0f));
	m_areaVertexArray[0][1] = sf::Vertex(sf::Vector2f(m_position.x - m_width, m_position.y + m_height),sf::Vector2f(0.0f,m_height));
	m_areaVertexArray[0][2] = sf::Vertex(sf::Vector2f(m_position.x + m_width, m_position.y + m_height),sf::Vector2f(m_width,m_height));
	m_areaVertexArray[0][3] = sf::Vertex(sf::Vector2f(m_position.x + m_width, m_position.y - m_height),sf::Vector2f(m_width,0.0f));


}

void LevelArea::getSprites(SpriteGenerator* spriteGenerator)
{

	std::cout << "level texture paths  size " << m_backgroundImagePaths.size() << std::endl;
	std::string randomBackground = m_backgroundImagePaths[rand() % m_backgroundImagePaths.size()]; 
	
	m_baseSpriteRef = spriteGenerator->GenerateSprite(randomBackground);






}

AreaTypes LevelArea::getAreaType()
{
	return m_areaType;
}




