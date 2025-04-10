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

	m_levelGrid = std::make_unique<LevelGrid>(LevelGrid((gridDim.x * chunkDimensions.x) / tileDimensions.x, (gridDim.y * chunkDimensions.y) / tileDimensions.y,tileDimensions));

// initialising the areas that will have their data copied from in order to create new areas of that type  
// here we pass in data such as the tiles that will be randomly placed in the area and those that are fixed in placement  
// this allows us to then create deep copies of any of these areas at any point through the Area initialiser 
// deep copy object essentially acting as a instantiate method for any area placed within this map 
// a map has been used as it allows an id to be attached to each area that allows for fast access to any of the objects stored 
// through a key value pair relationship between the object and the id (area type enums)
	m_areas =  
	{ 
    {GRASSLANDS,AreaInitialiser(new GrassLandsArea(m_spriteGenerator,m_randomMappedTiles[GRASSLANDS],m_areaBackgroundTextures[GRASSLANDS]),m_spriteGenerator)}
     
	};
	
	generateNewAreaGrid(GRASSLANDS, startAreaOffsetPosition); 
	m_currentArea = m_areaContainersPool.back();
	m_levelGrid.get()->setNewWorldArea(m_currentArea);
	m_levelGrid.get()->generateTilesRelativeToArea(m_currentArea); 

	m_currentPlayerTile = m_levelGrid.get()->getWorldToLocalPosition(m_playerRef->getPosition());


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

void LevelGenerator::update(float dt)
{ 
	updatePlayerTileState();

}

void LevelGenerator::updatePlayerTileState()
{
	Tile* realPlayerTile = m_levelGrid.get()->getWorldToLocalPosition(m_playerRef->getPosition());
	if (m_currentPlayerTile != realPlayerTile) {
		if (m_currentPlayerTile) {
			m_currentPlayerTile->resetPlayerEffect(m_playerRef);
		}
		m_currentPlayerTile = realPlayerTile;
	}
	if (m_currentPlayerTile) {
		m_currentPlayerTile->playerEffect(m_playerRef);
	}



}

LevelGenerator::~LevelGenerator()
{
	std::cout << "level generator destructor called" << std::endl;
	for (int i = 0; i < m_areaContainersPool.size(); i++) {

		delete m_areaContainersPool[i];
	}

}




