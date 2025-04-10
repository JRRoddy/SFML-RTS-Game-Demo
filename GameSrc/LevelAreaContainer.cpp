#include "LevelAreaContainer.h"






// this constructor will create a grid based on defined dimesnions and the size of the area passed in 
// genertaing a space that repsens the current area that encapsulates the player 
LevelAreaContainer::LevelAreaContainer(SpriteGenerator* spriteGenerator, sf::Vector2f offsetPosition ,std::string backGroundTexture,sf::Vector2i gridDimensions, sf::Vector2f gridSectionSize):GameObject(offsetPosition)
{
	// defining the dimensions for the grid 
	m_gridDimensions = gridDimensions;
    m_gridSectionSize = gridSectionSize;
	m_fullWidth = m_gridDimensions.x * m_gridSectionSize.x;
	m_fullheight = m_gridDimensions.y * m_gridSectionSize.y;
	// define a refernce point for which the first grid item will be centred 
	sf::Vector2f topLeftcentre = sf::Vector2f(m_position.x - m_gridSectionSize.x/2.0f,m_position.y - m_gridSectionSize.y/2.0f);

	std::cout <<"levelgrid top left centre "<< topLeftcentre.x << ":" << m_topLeft.y << std::endl;

	//defining a top left for the current area that can be used to track where the player is in the current area a
	// and calculate an index into the global area grid held within the level generator class
	m_topLeft = sf::Vector2f(topLeftcentre.x - m_gridSectionSize.x / 2.0f, topLeftcentre.y - m_gridSectionSize.y / 2.0f);
	
	m_backgroundVertecies.setPrimitiveType(tilePrimitiveType);
	m_backgroundVertecies.resize(size_t(m_gridDimensions.x * m_gridDimensions.y * m_tileVertexCount));
	// generate the grid and assign the sprites to this current area container 
	getSprites(spriteGenerator);
	
	for (int i = 0; i < m_gridDimensions.y; i++) {
		for (int j = 0; j < m_gridDimensions.x; j++) {


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

	initTiles(spriteGenerator);
	

}

LevelAreaContainer::LevelAreaContainer(SpriteGenerator* spriteGenerator, std::vector<TileInitialiser>& randomPostionedTiles,std::vector<std::string>& backgroundPaths)
{
	//m_mappedTiles = fixedTiles; 
	m_randomPositionedTiles = randomPostionedTiles; 
	m_backgroundTextures = backgroundPaths;
	getSprites(spriteGenerator); 
	initTiles(spriteGenerator);
	for (TileInitialiser &tileinitialiser : m_randomPositionedTiles) {

		m_generatedTilesCap += tileinitialiser.getHeldObject()->getSpawnCap();

	}



}



LevelAreaContainer::LevelAreaContainer(){}

LevelAreaContainer::LevelAreaContainer(SpriteGenerator* spriteGenerator)
{
	std::cout << "base level area container constructor called" << std::endl;
	
}


void LevelAreaContainer::draw(sf::RenderWindow* window)
{
	
	window->draw(m_backgroundVertecies, m_baseSpriteRef.get()->getTexture());

	for (int i = 0; i < m_worldTiles.size(); i++) {
		m_worldTiles[i]->draw(window);
	}


}


void LevelAreaContainer::getSprites(SpriteGenerator* m_spriteGenerator)
{
	std::string randomTextureForArea = m_backgroundTextures[rand() % m_backgroundTextures.size()];
	m_baseSpriteRef = m_spriteGenerator->GenerateSprite(randomTextureForArea);
}

void LevelAreaContainer::setBackgroundTexturePaths(std::vector<std::string>& paths)
{
	m_backgroundTextures = paths;
}


void LevelAreaContainer::initGrid() {

	m_backgroundVertecies.setPrimitiveType(tilePrimitiveType);
	m_backgroundVertecies.resize(size_t(m_gridDimensions.x * m_gridDimensions.y * m_tileVertexCount));
	sf::Vector2f topLeftcentre = sf::Vector2f(m_position.x - m_gridSectionSize.x / 2.0f, m_position.y - m_gridSectionSize.y / 2.0f);
	m_topLeft = sf::Vector2f(topLeftcentre.x - m_gridSectionSize.x / 2.0f, topLeftcentre.y - m_gridSectionSize.y / 2.0f);
	m_fullWidth = m_gridDimensions.x * m_gridSectionSize.x; 
	m_fullheight = m_gridDimensions.y * m_gridSectionSize.y;
	for (int i = 0; i < m_gridDimensions.y; i++) {
		for (int j = 0; j < m_gridDimensions.x; j++) {


			// here we are generating a current grid position for the centre of each chunk that will be within the grid for this area container 
			// this is done by taking the current section size defined for the area and offsetting it from the tope left based on the current width and height 
			sf::Vector2f position = sf::Vector2f(j * m_gridSectionSize.x + topLeftcentre.x, i * m_gridSectionSize.y + topLeftcentre.y);
			sf::Vertex* currentTile = &m_backgroundVertecies[size_t(i * m_gridDimensions.x + j) * m_tileVertexCount];

			// here we use a vertex before in which we pack all of the verticies required to draw the grid allowing all of the grid to be draw in a single draw call 
			currentTile[0] = sf::Vertex(sf::Vector2f(position.x - m_gridSectionSize.x / 2.0f, position.y - m_gridSectionSize.y / 2.0f), sf::Vector2f(0.0f, 0.0f));
			currentTile[1] = sf::Vertex(sf::Vector2f(position.x - m_gridSectionSize.x / 2.0f, position.y + m_gridSectionSize.y / 2.0f), sf::Vector2f(0.0f, m_gridSectionSize.y));
			currentTile[2] = sf::Vertex(sf::Vector2f(position.x + m_gridSectionSize.x / 2.0f, position.y + m_gridSectionSize.y / 2.0f), sf::Vector2f(m_gridSectionSize.x, m_gridSectionSize.y));
			currentTile[3] = sf::Vertex(sf::Vector2f(position.x + m_gridSectionSize.x / 2.0f, position.y - m_gridSectionSize.y / 2.0f), sf::Vector2f(m_gridSectionSize.x, 0.0f));

		}
	}
}


AreaTypes LevelAreaContainer::getType()
{
	return m_areaType;
}

void LevelAreaContainer::setAreaType(AreaTypes areaType)
{
	m_areaType = areaType;
}

LevelAreaContainer::~LevelAreaContainer()
{
	std::cout << "deallocating tile stored in memory for level area" << std::endl;
	for (int i = 0; i < m_worldTiles.size(); i++) {
		delete m_worldTiles[i];
	}

}

void LevelAreaContainer::setRandomlyGeneratedTiles(std::vector<TileInitialiser>& tiles)
{
	m_randomPositionedTiles = tiles;
}

void LevelAreaContainer::setMappedTiles(std::map<const sf::Color, TileInitialiser>& tiles)
{
	m_mappedTiles = tiles;
}



LevelAreaContainer* LevelAreaContainer::clone()
{
	LevelAreaContainer* copy = new LevelAreaContainer();
	copy->setMappedTiles(this->m_mappedTiles);
	copy->setRandomlyGeneratedTiles(this->m_randomPositionedTiles);
	copy->setAreaType(this->m_areaType);
	copy->setBackgroundTexturePaths(this->m_backgroundTextures);
	return copy;
}

float LevelAreaContainer::getFullWidth()
{
	return m_fullWidth;
}

float LevelAreaContainer::getFullHeight()
{
	return m_fullheight;
}


void LevelAreaContainer::initTiles(SpriteGenerator* spriteGenerator)
{
	for (int i = 0; i < m_randomPositionedTiles.size(); i++) {
		m_randomPositionedTiles[i].getHeldObject()->getSprites(spriteGenerator);
		
	}
	

	/*for (std::map<sf::Color, TileInitialiser>::iterator it = m_mappedTiles.begin(); it != m_mappedTiles.end(); it++) {
		it->second.basePtr->getSprites(spriteGenerator);
	}*/




}

void LevelAreaContainer::setDimensionsForArea(sf::Vector2i gridDimensions, sf::Vector2f tileSize)
{
	m_gridDimensions = gridDimensions;
	m_gridSectionSize = tileSize;
}

void LevelAreaContainer::setGridDimensions(sf::Vector2i dim)
{
	m_gridDimensions = dim;
	
}
void LevelAreaContainer::setGridAreaSize(sf::Vector2f dim)
{
	m_gridSectionSize = dim;
}

void LevelAreaContainer::setBackgroundTextures(std::vector<std::string>& backgroundTexturePaths)
{
	m_backgroundTextures = backgroundTexturePaths;
}

sf::Vector2f LevelAreaContainer::getTopLeft()
{
	return m_topLeft;
}

int LevelAreaContainer::getRandomGeneratedTilesCap()
{
	return m_generatedTilesCap;
}

Tile * LevelAreaContainer::initNewRandomTileInArea(sf::Vector2f position, float width, float height)
{

	size_t randomTileIndex = rand() % m_randomPositionedTiles.size();
	Tile * worldTileToInit = m_randomPositionedTiles[randomTileIndex].getHeldObjectCopy();  
	
	worldTileToInit->setVerticies(width, height, position);
	m_worldTiles.push_back(worldTileToInit);

	return m_worldTiles.back();
}
