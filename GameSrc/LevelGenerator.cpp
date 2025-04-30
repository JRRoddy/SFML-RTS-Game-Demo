#include "LevelGenerator.h"

// this class is responsible for holding the main data that is used for level generation keeping things such as various 
// background textures for level area containers and tile data all wrapped under a single class. All of this data  is 
// also stored within maps and vectors allowing it to then be easily accessed by other classes used to generate the level
LevelGenerator::LevelGenerator(SpriteGenerator * spriteGenerator,sf::Vector2f startAreaOffsetPosition,Player * playerRef, sf::Vector2i tileDimensions,sf::Vector2f chunkDimensions, sf::Vector2i gridDim) {
	std::cout << "initialsing level generator" <<std::endl;;
	m_spriteGenerator = spriteGenerator;
	m_ChunkSize = chunkDimensions; 
	m_gridDimensions = gridDim;
	m_playerRef = playerRef;
	m_maxLevelAreaColTreeDepth = 8;

	m_levelGrid = std::make_unique<LevelGrid>(LevelGrid((gridDim.x * chunkDimensions.x) / tileDimensions.x, (gridDim.y * chunkDimensions.y) / tileDimensions.y,tileDimensions));
	
	m_randomMappedTiles = 
	{
	{GRASSLANDS,{TileInitialiser(new ForestTile()),TileInitialiser(new RockTile())}}

	};
	m_imageMappedTiles = 
	{
	{GRASSLANDS,{{"Path",TileInitialiser(new PathTile())}}}
	};

// initialising the areas that will have their data copied from in order to create new areas of that type  
// here we pass in data such as the tiles that will be randomly placed in the area and those that are fixed in placement  
// this allows us to then create deep copies of any of these areas at any point through the Area initialiser 
// deep copy object essentially acting as a instantiate method for any area placed within this map 
// a map has been used as it allows an id to be attached to each area that allows for fast access to any of the objects stored 
// through a key value pair relationship between the object and the id (area type enums) 

// if new areas were to be generated all that would be needed would be a call to the AreaInitialiser object's copy method
// obtaining a deep copy of the object assigned to it so all the data is initialised in the first instance of the area intialiser object 
// passed into the map and a deep copy of that object can simply be made to create a new area of that type meaning all the heavy data intialisation for 
// areas such as loading tile image maps and intialising tiles happens once 
	m_areas =  
	{ 
    {GRASSLANDS,AreaInitialiser( new GrassLandsArea(m_spriteGenerator,m_randomMappedTiles[GRASSLANDS],m_imageMappedTiles[GRASSLANDS]
		                        ,m_areaBackgroundTextures[GRASSLANDS],m_tileMapImages[GRASSLANDS]),m_spriteGenerator)}
     
	};
	
	parseLevelMaps();
	
	generateNewAreaGrid(m_startArea, startAreaOffsetPosition); 
	// initialse level grid and current area
	m_currentArea = m_areaContainersPool.back();
	m_levelGrid.get()->setNewWorldArea(m_currentArea);
	m_currentArea->initCollisionTree(m_maxLevelAreaColTreeDepth);
	m_levelGrid.get()->generateTilesRelativeToArea(m_currentArea); 
	
	// initialise astar object with the current level grid 
	m_astarObject = std::make_unique<Astar>(Astar(m_levelGrid.get()));
	
	// get the current player tile to keep track of and set the area bounds for the player
	m_currentPlayerTile = m_levelGrid.get()->getWorldToLocalPosition(m_playerRef->getPosition());
	m_playerRef->setCurrentLevelAreaBounds(m_currentArea->getBounds());
	// intialse managers for allies and enemies 
	m_enemyManager = std::make_unique<EnemyManager>(EnemyManager(m_playerRef,m_astarObject.get(),m_levelGrid.get()));
	m_allyManager = std::make_unique<AllyManager>(m_playerRef, m_astarObject.get(), m_levelGrid.get());
	
	// intialise object pools for all managers that hold objects that there will
	// be many instances of 
	initManagerPools();
	
}

void LevelGenerator::generateNewAreaGrid(AreaTypes areaType, sf::Vector2f offsetPosition)
{
	LevelAreaContainer* newArea = m_areas[areaType].getNewAreaCopy(offsetPosition,m_gridDimensions,m_ChunkSize);
	m_areaContainersPool.push_back(newArea);

}



LevelAreaContainer* LevelGenerator::getCurrentAreaGrid()
{
	return m_currentArea;
}



float LevelGenerator::getGridAreaWidth()const  
{
	return m_ChunkSize.x;
}

float LevelGenerator::getGridAreaHeight()const 
{
	return m_ChunkSize.y;
}

int LevelGenerator::getLevelChunkWidth() const
{
	return m_gridDimensions.x;
}

int LevelGenerator::getlevelChunkHeight()const
{
	return m_gridDimensions.y;
}

void LevelGenerator::parseLevelMaps()
{
	ImageMapInfoParser imageMapInfoParser = ImageMapInfoParser(); //class used to parse level colour maps 

	// loop through all key value pairs that map an area type to a particualr file that holds information/data 
	// about the current level map being parsed
	for each (std::pair<AreaTypes, std::string> areaImageMapDescriptorPair in m_imageMapInfoFilePaths) {  

		std::map<imageMapColour, std::string> parsedData = imageMapInfoParser.parseImageMapInfoFile(areaImageMapDescriptorPair.second);
		// set the map for the current area type that maps all the colours 
		// found in the image map info file to a particualr tile id 
		m_areas[areaImageMapDescriptorPair.first].getHeldObject()->setTileInfoColoursMap(parsedData);
	    
	}

}

void LevelGenerator::update(float dt)
{ 
	updatePlayerTileState(dt);
	m_playerRef->update(dt);
	m_enemyManager.get()->update(dt);  
	m_allyManager.get()->update(dt);
	m_allyManager.get()->updateEnemyCollision(m_enemyManager->getActiveEnemyBuffer());
	
}

void LevelGenerator::drawObjects(sf::RenderWindow* window)
{
	m_currentArea->draw(window);
	m_enemyManager.get()->drawEnemies(window);
	m_allyManager.get()->drawAllies(window);
}

void LevelGenerator::updatePlayerTileState(float dt)
{
	// get the real time position of the player within the level grid and the associated tile with that position
	Tile* realPlayerTile = m_levelGrid.get()->getWorldToLocalPosition(m_playerRef->getPosition()); 
	
	playerNextTileCheck(dt);


	if (m_currentPlayerTile != realPlayerTile) { // if the current tile is not equal to the currenlty recorded player tile
		
		if (m_currentPlayerTile) { // if the current tile is not nullptr reset its effect
			m_currentPlayerTile->resetDynamicObjectEffect(m_playerRef);
		}
		m_currentPlayerTile = realPlayerTile; // set the current tile to the new player tile
	}
	
	if (m_currentPlayerTile) { // update the player effect of the tile if we are on a tile with an effect(not null)
		m_currentPlayerTile->dynamicObjectEffect(m_playerRef);
	}



}

void LevelGenerator::initManagerPools()
{
	// loop through all areas in the m_areas std::map and create 
	// object pools based on their stored initialisers and type 
	for  (std::map<AreaTypes,AreaInitialiser>::iterator it = m_areas.begin( );it != m_areas.end(); it++)
	{
		m_enemyManager.get()->initEnemyPool(it->first, it->second.getHeldObject()->getEnemyIntialisers(),m_spriteGenerator);
		m_allyManager.get()->initAllyPools(it->first, it->second.getHeldObject()->getAllyIntialisers(),m_spriteGenerator);
	}
	m_allyManager.get()->setCurrentArea(m_currentArea);
	m_enemyManager.get()->setCurrentArea(m_currentArea);





}

void LevelGenerator::playerNextTileCheck(float dt)
{

	// ensure that the player cant move along unwalkable tiles 
	bool collideOnNextUpdate = m_currentArea->testForUnwalkableTileCollisions(m_playerRef->getNexPos(dt));
	m_playerRef->setCanMoveToNextTile(!collideOnNextUpdate);

	

	
}



LevelGenerator::~LevelGenerator()
{
	for (int i = 0; i < m_areaContainersPool.size(); i++) {

		delete m_areaContainersPool[i];
	}

}




