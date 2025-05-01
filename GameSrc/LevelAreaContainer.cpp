#include "LevelAreaContainer.h"


// this constructor will create a grid based on defined dimesnions and the size of the area passed in 
// genertaing a space that represents the current area that encapsulates the player 
LevelAreaContainer::LevelAreaContainer(SpriteGenerator* spriteGenerator, sf::Vector2f offsetPosition ,std::string backGroundTexture,sf::Vector2i gridDimensions, sf::Vector2f gridSectionSize):GameObject(offsetPosition)
{
	// defining the dimensions for the grid 
	m_gridDimensions = gridDimensions;
    m_gridSectionSize = gridSectionSize;
	m_fullWidth = m_gridDimensions.x * m_gridSectionSize.x;
	m_fullheight = m_gridDimensions.y * m_gridSectionSize.y;
	// define a refernce point for which the first grid item will be centred 
	sf::Vector2f topLeftcentre = sf::Vector2f(m_position.x - m_gridSectionSize.x/2.0f,m_position.y - m_gridSectionSize.y/2.0f);


	//defining a top left for the current area that can be used to track where the player is in the current area a
	// and calculate an index into the global area grid held within the level generator class
	m_topLeft = sf::Vector2f(topLeftcentre.x - m_gridSectionSize.x / 2.0f, topLeftcentre.y - m_gridSectionSize.y / 2.0f);
	m_bottomRight = m_topLeft + sf::Vector2f(m_fullWidth, m_fullheight);

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
		    
			// here we use a   we pack all of the vertecies required to draw the grid allowing all of the grid to be draw in a single draw call 
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


bool LevelAreaContainer::testForUnwalkableTileCollisions(sf::Vector2f & pos) {

	std::vector<quadTreeItem<Tile>> result;
	m_collisionTreeForUnwalkableTiles.get()->queryCollisionTree(pos, result);

	return result.size();

}

void LevelAreaContainer::draw(sf::RenderWindow* window)
{
	
	window->draw(m_backgroundVertecies, m_baseSpriteRef.get()->getTexture());

	for (int i = 0; i < m_worldTiles.size(); i++) {
		m_worldTiles[i]->draw(window);
	}

	m_collisionTreeForUnwalkableTiles->drawCollisionTree(window);
}


void LevelAreaContainer::getSprites(SpriteGenerator* m_spriteGenerator)
{
	std::string randomTextureForArea = m_backgroundTextures[rand() % m_backgroundTextures.size()];
	m_baseSpriteRef = m_spriteGenerator->GenerateSprite(randomTextureForArea);
}

void LevelAreaContainer::setMaxAllySpawnCap(int spawnCap)
{
	m_maxAllyCap = spawnCap;
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
	m_bottomRight = m_topLeft + sf::Vector2f(m_fullWidth, m_fullheight);

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
	for (int i = 0; i < m_worldTiles.size(); i++) {
		delete m_worldTiles[i];
	}

}

void LevelAreaContainer::setRandomlyGeneratedTiles(std::vector<TileInitialiser>& tiles)
{
	m_randomPositionedTiles = tiles;
}


// enemies will be spawned on the edge of the level area by default 
sf::Vector2f LevelAreaContainer::getEnemySpawnPosition(GameObject * enemy)
{
	sf::FloatRect enemySpriteBounds = enemy->getBaseSprite()->getGlobalBounds();

	sf::Vector2f positionOnEdge = getRandomEdgePosition(enemySpriteBounds);
	return positionOnEdge;
}

void LevelAreaContainer::setSpawnDelays(float& min, float &max)
{
	m_minSpawnCoolDown = min;  
	m_maxSpawnCoolDown = max;
}

//  below two methods are used for deep copying one level area container and creating a copy of it(new heap allocated memeory at a new address)
LevelAreaContainer* LevelAreaContainer::clone()
{
	LevelAreaContainer* copy = new LevelAreaContainer();

	copy->setRandomlyGeneratedTiles(this->getRandomlyGeneratedTiles());
	copy->setAreaType(this->getAreaType());

	copy->setBackgroundTexturePaths(this->getBackgroundTexturePaths());
	copy->setRandomGeneratedTilesCap(this->getRandomGeneratedTilesCap());

	copy->setTileMapPaths(this->getTileMapPaths());
	copy->setTileMapImages(this->getTileMapImages());

	copy->setImageParsedTiles(this->getImageParsedTiles());
	copy->setTileInfoColoursMap(this->getTileInfoColourMap());
	copy->setNewTileMapImage();




	return copy;
}

// used for deep copying a level area 
void LevelAreaContainer::clone(LevelAreaContainer* copy)
{
	copy->setRandomlyGeneratedTiles(this->getRandomlyGeneratedTiles());
	copy->setRandomGeneratedTilesCap(this->getRandomGeneratedTilesCap());

	copy->setAreaType(this->getAreaType());
	copy->setBackgroundTexturePaths(this->getBackgroundTexturePaths());

	copy->setTileMapPaths(this->getTileMapPaths());
	copy->setTileMapImages(this->getTileMapImages()); 

	copy->setImageParsedTiles(this->getImageParsedTiles());
	copy->setTileInfoColoursMap(this->getTileInfoColourMap());
	copy->setEnemyIntialisers(this->getEnemyIntialisers());
	copy->setAllyInitialisers(this->getAllyIntialisers());
	copy->setMaxAllySpawnCap(this->getMaxAllyCap());
	copy->setAllyRefreshCoolDown(this->getAllyRefreshCoolDown());
	copy->setSpawnDelays(this->getSpawnDelayMin(), this->getSpawnDelayMax());
	
}

// convert a pixel coolour from the top left corner of a tile within an image map to a tile in the world 
Tile * LevelAreaContainer::initTileFromSelectedMap(sf::Vector2i imageMapTexcoords,sf::Vector2f position, float width, float height) 
{
	sf::Color mapColour =  m_currentTileMapImage->getPixel(imageMapTexcoords.x, imageMapTexcoords.y); // read the pixel associated with the image map  


	if (mapColour.a > 0.0f) { // if the pixel is not blank in terms of alpha 

		imageMapColour mappedColour = imageMapColour(mapColour.r, mapColour.g, mapColour.b, mapColour.a);
		// construct an imageMapColour from the colour values of the read pixel 
		std::string tileNameId;
		try { // try catch as .at will throw an out of range expection if the key does not exsist in the map
			
			tileNameId = m_tileInfocoloursMap.at(mappedColour); 
		}
		catch (...) {  // report that the colour found did not have associated tile id stored if it could not be found in the tile info  std::map 
			std::cout << "colour in image map did not have associated tile id " << std::endl;
			return nullptr;

		}

		Tile* worldTile = m_imageMappedTiles[tileNameId].getHeldObjectCopy();  // get a copy from the tile initialiser stored as a value associated with a particular string id parsed from the associated imageMap info file for this area 
		
		worldTile->setVerticies(width, height, position);
		
		m_worldTiles.push_back(worldTile);
		if (!worldTile->isWalkable()) {
			m_collisionTreeForUnwalkableTiles->insertItem(worldTile->getBounds(), worldTile);
		}
		return worldTile; // return the new world tile 
		
	}
       
	return nullptr; // return nullptr if the colour was blank
	   



};

std::vector<EnemyInitialiser>& LevelAreaContainer::getEnemyIntialisers()
{
	return m_enemies;
}

std::vector<AllyInitialiser>& LevelAreaContainer::getAllyIntialisers()
{
	return m_allies;
}

void LevelAreaContainer::initCollisionTree(int maxCollisionTreeDepth)
{
	m_collisionTreeForUnwalkableTiles = std::make_shared<CollisonHandler<Tile>>((CollisonHandler<Tile>(getBounds(),maxCollisionTreeDepth )));




}

void LevelAreaContainer::setEnemyIntialisers(std::vector<EnemyInitialiser>& enemyInitialisers)
{
	m_enemies = enemyInitialisers;
}

void LevelAreaContainer::setAllyInitialisers(std::vector<AllyInitialiser>& allyInitalisers)
{
	m_allies = allyInitalisers;
}

float LevelAreaContainer::getRandomSpawnDelay()
{
	float delay = m_minSpawnCoolDown + ((static_cast<float>(rand()))/ static_cast<float>(RAND_MAX/(m_maxSpawnCoolDown - m_minSpawnCoolDown)));

	return delay;
}

float LevelAreaContainer::getFullWidth()
{
	return m_fullWidth;
}

float LevelAreaContainer::getFullHeight()
{
	return m_fullheight;
}

float &LevelAreaContainer::getSpawnDelayMin()
{
	return m_minSpawnCoolDown;
}
float &LevelAreaContainer::getSpawnDelayMax()
{
	return m_maxSpawnCoolDown;
}

float& LevelAreaContainer::getAllyRefreshCoolDown()
{
	return m_allyRefreshCoolDown;
}

void LevelAreaContainer::setAllyRefreshCoolDown(float& coolDown)
{
	m_allyRefreshCoolDown = coolDown;
}

int& LevelAreaContainer::getMaxAllyCap()
{
	return m_maxAllyCap;
}

sf::Vector2f LevelAreaContainer::getWorldDimensions()
{
	return sf::Vector2f(m_fullWidth,m_fullheight);
}


void LevelAreaContainer::init(SpriteGenerator* spriteGenerator)
{
	initTiles(spriteGenerator);
	initLevelMaps();

}

void LevelAreaContainer::setDimensionsForArea(sf::Vector2i &gridDimensions, sf::Vector2f &tileSize)
{
	m_gridDimensions = gridDimensions;
	m_gridSectionSize = tileSize;
}

std::vector<TileInitialiser> LevelAreaContainer::getRandomlyGeneratedTiles()
{
	return m_randomPositionedTiles;
}

void LevelAreaContainer::setGridDimensions(sf::Vector2i& dim)
{
	m_gridDimensions = dim;
	
}
void LevelAreaContainer::setGridAreaSize(sf::Vector2f& dim)
{
	m_gridSectionSize = dim;
}

void LevelAreaContainer::initTiles(SpriteGenerator * spriteGenerator)
{

	for (int i = 0; i < m_randomPositionedTiles.size(); i++) { // loop through all the tile that can be renaomdly positioned
			m_randomPositionedTiles[i].getHeldObject()->getSprites(spriteGenerator); // assign sprites to the tiles held in the deep copy object allowing the sprites to be reused across the copies created from the ile iniitaliser class 
			m_generatedTilesCap += m_randomPositionedTiles[i].getHeldObject()->getSpawnCap();// geta sum of the total amount of tiles that can be ranomdly placed in the area 
	}
	// initialise all tiles that can be mapped to an image
	for (std::map< std::string, TileInitialiser>::iterator it = m_imageMappedTiles.begin(); it != m_imageMappedTiles.end();it++) {
		it->second.getHeldObject()->getSprites(spriteGenerator);
	}
		
	
}

void LevelAreaContainer::initLevelMaps()
{
	// load maps associated with this area type 
	for (int i = 0; i < m_tileMapPaths.size(); i++) {
		sf::Image image = sf::Image(); 
		
		m_loadedTileMaps.push_back(image);
		if (!(m_loadedTileMaps.back().loadFromFile(m_tileMapPaths[i])))
		{
			std::cout << "could not load tile map image " << m_tileMapPaths[i] << std::endl;
		};

	}
	
	setNewTileMapImage();
}

// initialise a world tile for this area and return it for any further manipluation
Tile* LevelAreaContainer::initNewRandomTileInArea(sf::Vector2f position, float width, float height)
{
	// get a random index into the random positioned tiles vector which stores all of the tile initialiser objects for this area 
	// that hold tiles that can be randomly generated 
	size_t randomTileIndex =  rand() % m_randomPositionedTiles.size();
	// ensure that random tiles do not go over their spawn cap
	// based on the number of recorded instances within this current level area 
	if (m_randomPositionedTiles[randomTileIndex].hasHitInitialiseCap()) {
		m_randomPositionedTiles.erase(m_randomPositionedTiles.begin() + randomTileIndex);
	    randomTileIndex = rand() % m_randomPositionedTiles.size();

	}
	Tile* worldTileToInit = m_randomPositionedTiles[randomTileIndex].getHeldObjectCopy();   // initialise a new world tile from the selected tile initialsier
	
	worldTileToInit->setVerticies(width, height, position); // set the quad for the tile 
	
	
	m_worldTiles.push_back(worldTileToInit); // add it to world tiles vector for it to be drawn to the screen 
	if (!worldTileToInit->isWalkable()) {
		m_collisionTreeForUnwalkableTiles->insertItem(worldTileToInit->getBounds(), worldTileToInit);
	}
	return m_worldTiles.back(); // retrun the initialised tile 
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
	/// set a random level map image to be used for the area in order to generate its initial objects
	m_currentTileMapImage = &(m_loadedTileMaps[rand() % m_loadedTileMaps.size()]); 
	
}
std::vector<sf::Image>& LevelAreaContainer::getTileMapImages()
{
	return m_loadedTileMaps;
}

void LevelAreaContainer::setTileMapImages(std::vector<sf::Image>& tileMapImages)
{
	m_loadedTileMaps = tileMapImages;
	setNewTileMapImage();
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

}
sf::FloatRect LevelAreaContainer::getBounds()
{
	return sf::FloatRect(m_topLeft,getWorldDimensions());
}
;


sf::Vector2f LevelAreaContainer::getTopLeft()
{
	return m_topLeft;
}

sf::Vector2f LevelAreaContainer::getRandomPosition() const
{


	float randX = randomFloat(m_topLeft.x, m_bottomRight.x);
	float randY = randomFloat(m_topLeft.y, m_bottomRight.y);

	return sf::Vector2f(randX,randY);
}

sf::Vector2f LevelAreaContainer::getRandomEdgePosition() const
{

	float randX = randomFloat(0.0f, m_fullWidth);
	float randY = randomFloat(0.0f, m_fullheight);

	float clampRandomAxis = randomFloat(0.0f, 1.0f); 

	if (clampRandomAxis < 0.5f) {
		randX = randX < m_fullWidth / 2 ? 0.0f :m_fullWidth; 
		return m_topLeft + sf::Vector2f(randX, randY);

	}
	
	randY = randY < m_fullheight / 2 ? 0.0f : m_fullheight;
	return m_topLeft + sf::Vector2f(randX, randY);



}
// used to get a random position along the edge of the level area
sf::Vector2f LevelAreaContainer::getRandomEdgePosition(sf::FloatRect boundsToAccomodate) const
{
	 

	// random offset along the edge
	float randX = randomFloat(0.0f, m_fullWidth); 
	float randY = randomFloat(0.0f, m_fullheight);


	float clampRandomAxis = randomFloat(0.0f, 1.0f);
	// determine which axis should be clamped to the edge 
	// also taking into acount the bounds passed in
	// to ensure that whatever is encapsulated in those bounds would 
	// go of the edge 
	if (clampRandomAxis < 0.5f) { // clamping x
		randX = randX < m_fullWidth / 2 ? 0.0f - boundsToAccomodate.width/2 : m_fullWidth + boundsToAccomodate.width/2;
		return m_topLeft + sf::Vector2f(randX, randY);

	}
	//clamping y if x not chosen
	randY = randY < m_fullheight / 2 ? 0.0f - boundsToAccomodate.height/2 : m_fullheight + boundsToAccomodate.height/2;
	return m_topLeft + sf::Vector2f(randX, randY);


}

int LevelAreaContainer::getRandomGeneratedTilesCap()
{
	return m_generatedTilesCap;
}

void LevelAreaContainer::setRandomGeneratedTilesCap(int cap)
{
	m_generatedTilesCap = cap;
}


