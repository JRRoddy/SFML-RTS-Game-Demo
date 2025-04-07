#include "LevelAreaContainer.h"



// this constructor will create a grid based on defined dimesnions and the size of the area passed in 
// genertaing a space that repsens the current area that encapsulates the player 
LevelAreaContainer::LevelAreaContainer(SpriteGenerator* spriteGenerator, sf::Vector2f offsetPosition, AreaTypes areaType, std::string backGroundTexture,sf::Vector2i gridDimensions, sf::Vector2f gridSectionSize):GameObject(offsetPosition)
{
	// defining the dimensions for the grid 
	m_gridDimensions = gridDimensions;
    m_gridSectionSize = gridSectionSize;
	// define a refernce point for which the first grid item will be centred 
	sf::Vector2f topLeftcentre = sf::Vector2f(m_position.x - m_gridSectionSize.x/2.0f,m_position.y - m_gridSectionSize.y/2.0f);
	m_areaType = areaType; // current area type 
	//defining a top left for the current area that can be used to track where the player is in the current area a
	// and calculate an index into the global area grid held within the level generator class
	m_topLeft = sf::Vector2f(topLeftcentre.x - m_gridSectionSize.x / 2.0f, topLeftcentre.y - m_gridSectionSize.y / 2.0f);
	
	m_backgroundVertecies.setPrimitiveType(tilePrimitiveType);
	m_backgroundVertecies.resize(size_t(m_gridDimensions.x * m_gridDimensions.y * m_tileVertexCount));
	// generate the grid and assign the sprites to this current area container 
	getSprites(spriteGenerator,backGroundTexture);
	
	for (int i = 0; i < m_gridDimensions.y; i++) {
		for (int j = 0; j < m_gridDimensions.y; j++) {


			// here we are generating a current grid position for the centre of each chunk that will be wihtin the grid for this area container 
			// this is done by taking the current section size defined for the area and offsetting it from the tope left based on the current width and height 
			sf::Vector2f position = sf::Vector2f(j * m_gridSectionSize.x + topLeftcentre.x, i * m_gridSectionSize.y + topLeftcentre.y);
			sf::Vertex* currentTile = &m_backgroundVertecies[size_t(i * m_gridDimensions.x + j) * m_tileVertexCount];
		    
			// here we use a vertex before in which we pack all of the vertecies required to draw the grid allowing all of the grid to be draw in a single draw call 
			currentTile[0] = sf::Vertex(sf::Vector2f(position.x - m_gridSectionSize.x / 2.0f, position.y - m_gridSectionSize.y / 2.0f), sf::Vector2f(0.0f, 0.0f));
			currentTile[1] = sf::Vertex(sf::Vector2f(position.x - m_gridSectionSize.x / 2.0f, position.y + m_gridSectionSize.y / 2.0f), sf::Vector2f(0.0f, m_gridSectionSize.y));
			currentTile[2] = sf::Vertex(sf::Vector2f(position.x + m_gridSectionSize.x / 2.0f, position.y + m_gridSectionSize.y / 2.0f), sf::Vector2f(m_gridSectionSize.x, m_gridSectionSize.y));
			currentTile[3] = sf::Vertex(sf::Vector2f(position.x + m_gridSectionSize.x / 2.0f, position.y - m_gridSectionSize.y / 2.0f), sf::Vector2f(m_gridSectionSize.x, 0.0f));



		}
	}
}



void LevelAreaContainer::draw(sf::RenderWindow* window)
{

	window->draw(m_backgroundVertecies, m_baseSpriteRef.get()->getTexture());


	
}

void LevelAreaContainer::getSprites(SpriteGenerator* m_spriteGenerator,std::string spriteTexturePath)
{
	m_baseSpriteRef = m_spriteGenerator->GenerateSprite(spriteTexturePath);
}

Tile* LevelAreaContainer::initWorldTileFixed(sf::Vector2f position)
{
	return nullptr;
}

Tile* LevelAreaContainer::initWorldTileRandom(sf::Vector2f position)
{
	return nullptr;
}



AreaTypes LevelAreaContainer::getType()
{
	return m_areaType;
}
