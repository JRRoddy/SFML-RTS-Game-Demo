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

	init(spriteGenerator);
	

}

LevelAreaContainer::LevelAreaContainer(SpriteGenerator* spriteGenerator, std::vector<TileInitialiser>& randomPostionedTiles,std::map<std::string,TileInitialiser>& imageMappedTiles,std::vector<std::string>& backgroundPaths,std::vector<std::string>& tileMapPaths)
{
	m_randomPositionedTiles = randomPostionedTiles; 
	m_backgroundTextures = backgroundPaths;
	m_tileMapPaths = tileMapPaths; 
	m_imageMappedTiles = imageMappedTiles;
	getSprites(spriteGenerator); 
	init(spriteGenerator);
	



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

std::vector<std::string>& LevelAreaContainer::getBackgroundTexturePaths()
{
	return m_backgroundTextures;
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


AreaTypes LevelAreaContainer::getAreaType()
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



//  below two methods are used for deep copying one level area container and creating a copy of it(new heap allocated memeory at a new address)
LevelAreaContainer* LevelAreaContainer::clone()
{
	LevelAreaContainer* copy = new LevelAreaContainer();
	copy->setRandomlyGeneratedTiles(this->getRandomlyGeneratedTiles());
	copy->setAreaType(this->getAreaType());
	copy->setBackgroundTexturePaths(this->getBackgroundTexturePaths());
	copy->setTileMapPaths(this->getTileMapPaths());
	copy->setTileMapImages(this->getTileMapImages());
	copy->setImageParsedTiles(this->getImageParsedTiles());
	copy->setTileInfoColoursMap(this->getTileInfoColourMap());
	return copy;
}

void LevelAreaContainer::clone(LevelAreaContainer* copy)
{
	copy->setRandomlyGeneratedTiles(this->getRandomlyGeneratedTiles());
	copy->setAreaType(this->getAreaType());
	copy->setBackgroundTexturePaths(this->getBackgroundTexturePaths());
	copy->setTileMapPaths(this->getTileMapPaths());
	copy->setTileMapImages(this->getTileMapImages()); 
	copy->setImageParsedTiles(this->getImageParsedTiles());
	copy->setTileInfoColoursMap(this->getTileInfoColourMap());


}

void LevelAreaContainer::getTileFromSelectedMap(int x, int y) {};

float LevelAreaContainer::getFullWidth()
{
	return m_fullWidth;
}

float LevelAreaContainer::getFullHeight()
{
	return m_fullheight;
}


void LevelAreaContainer::init(SpriteGenerator* spriteGenerator)
{
	initTiles(spriteGenerator);

	// load maps associated with this area type 
	for (int i = 0; i < m_tileMapPaths.size(); i++) {
		
		m_loadedTileMaps.emplace_back(); 
		if (!m_loadedTileMaps.back().loadFromFile(m_tileMapPaths[i])) 
		{
			std::cout << "could not load tile map image " << m_tileMapPaths[i] << std::endl;
		};

	}




	



}

void LevelAreaContainer::setDimensionsForArea(sf::Vector2i gridDimensions, sf::Vector2f tileSize)
{
	m_gridDimensions = gridDimensions;
	m_gridSectionSize = tileSize;
}

std::vector<TileInitialiser>& LevelAreaContainer::getRandomlyGeneratedTiles()
{
	return m_randomPositionedTiles;
}

void LevelAreaContainer::setGridDimensions(sf::Vector2i dim)
{
	m_gridDimensions = dim;
	
}
void LevelAreaContainer::setGridAreaSize(sf::Vector2f dim)
{
	m_gridSectionSize = dim;
}

void LevelAreaContainer::initTiles(SpriteGenerator * spriteGenerator)
{

	for (int i = 0; i < m_randomPositionedTiles.size(); i++) { // loop through all the tile that can be renaomdly positioned


			m_randomPositionedTiles[i].getHeldObject()->getSprites(spriteGenerator); // assign sprites to the tiles held in the deep copy object allowing the sprites to be reused across the copies created from the ile iniitaliser class 
			m_generatedTilesCap += m_randomPositionedTiles[i].getHeldObject()->getSpawnCap();// geta sum of the toatal amount of tiles that can be ranomdly placed in the area 
		

	}
	// initialise all tiles that can be mapped to an image
	for each (std::pair<std::string,TileInitialiser> pair in m_imageMappedTiles) {
		pair.second.getHeldObject()->getSprites(spriteGenerator);
	}
		

	
			
	
}



std::vector<std::string>& LevelAreaContainer::getTileMapPaths()
{

	return m_tileMapPaths;
}

void LevelAreaContainer::setTileMapPaths(std::vector <std::string>& tileMapPaths) {

	m_tileMapPaths = tileMapPaths;
}
void LevelAreaContainer::setNewTileMapImage()
{
	m_currentTileMapImage = m_loadedTileMaps[rand() % m_loadedTileMaps.size()];

}
std::vector<sf::Image>& LevelAreaContainer::getTileMapImages()
{
	return m_loadedTileMaps;
}

void LevelAreaContainer::setTileMapImages(std::vector<sf::Image>& tileMapImages)
{
	m_loadedTileMaps = tileMapImages;
}

void LevelAreaContainer::setImageParsedTiles(std::map<std::string, TileInitialiser>& imageParsedTiles)
{
	m_imageMappedTiles = imageParsedTiles;
}

std::map<std::string, TileInitialiser>& LevelAreaContainer::getImageParsedTiles()
{
	return m_imageMappedTiles;
}

void LevelAreaContainer::setTileInfoColoursMap(std::map<imageMapColour, std::string>& tileInfocoloursMap)
{
	m_tileInfocoloursMap = tileInfocoloursMap;
}

std::map<imageMapColour, std::string>& LevelAreaContainer::getTileInfoColourMap() 
{
	return m_tileInfocoloursMap;

};


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
