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
	m_levelAreaManufacturer = std::make_shared<LevelAreaManufacturer>(LevelAreaManufacturer());
	m_levelAreaBuilder = std::make_shared<LevelAreaBuilder>(LevelAreaBuilder(m_spriteGenerator));
	
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
	
	m_areas = {
		{GRASSLANDS, AreaInitialiser(new GrassLandsArea(),m_spriteGenerator)}

	};
	
	parseLevelMaps();
	
	// intiate the initial level area with the enemies we want the alies we want 
	// the type of area we want and its starting position along with a refernce to 
	// the current builder object we are using to generate the level area 
	generateFullNewArea(m_levelAreaBuilder.get(), m_startArea, startAreaOffsetPosition,GOBLINS,KNIGHTS); 
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

void LevelGenerator::generateFullNewArea(LevelAreaBuilder * areaBuilder,AreaTypes areaType, sf::Vector2f offsetPosition,EnemyFactionIds enemyFactionInArea, AllyFactionIds allyFactionInArea)
{
	// get new level area to build of specifc type 
	// assign new level area to be constructed to the level area manufacturer
	m_levelAreaManufacturer->setLevelBuilder(areaBuilder);
	m_levelAreaManufacturer->assignNewLevelAreaObject(m_areas[areaType].getDefaultCopy());
	// pass in initial data needed to construct a level area(that can be drawn to the screen) 
	// to the manufacturer which has a reference to the current builder being used 
	m_levelAreaManufacturer->createLevelArea(areaBuilder, areaType,m_areaBackgroundTextures[areaType]);
	// add tiles that area randomly generated to the level area that will be included in its construction by the builder
	m_levelAreaManufacturer->addRandomlyGeneratedTileToArea(m_randomMappedTiles[areaType]);
	// add tile map data  to the level area that will be included in its construction by the builder
	m_levelAreaManufacturer->addTileMapsToArea(m_tileMapImages[areaType], m_imageMappedTiles[areaType], m_tileImageMapInformation[areaType]);
	// add npcs based on the passed in faction ids to the area 
	m_levelAreaManufacturer->addLevelAreaNpcs(allyFactionInArea, m_allyFactions[allyFactionInArea], enemyFactionInArea, m_enemyFactions[enemyFactionInArea]);
	// get the final constructed area from the manufacturer object based on all the properties
	// passed to the builder from the level manufacturer 
	m_areaContainersPool.push_back(m_levelAreaManufacturer->manufactureLevelArea(offsetPosition, m_gridDimensions, m_ChunkSize));

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
		m_tileImageMapInformation.insert({ areaImageMapDescriptorPair.first, parsedData });


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
	// object pools based on their stored initialisers and the faction type of
	// the npc's being stored 
	for  (std::map<EnemyFactionIds,std::vector<EnemyInitialiser>>::iterator it = m_enemyFactions.begin( );it != m_enemyFactions.end(); it++)
	{
		m_enemyManager.get()->initEnemyPool(it->first, it->second, m_spriteGenerator);

	}
	for (std::map<AllyFactionIds, std::vector<AllyInitialiser>>::iterator it = m_allyFactions.begin(); it != m_allyFactions.end(); it++)
	{
		m_allyManager.get()->initAllyPools(it->first, it->second, m_spriteGenerator);

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




