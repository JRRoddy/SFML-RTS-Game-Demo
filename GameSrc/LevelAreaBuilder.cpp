#include "LevelAreaBuilder.h"

LevelAreaBuilder::LevelAreaBuilder(SpriteGenerator* spriteGenerator)
{
	// sprite generate refernce for getting the sprites 
	// needed for various level area objects during their construction
	m_spriteGenerator = spriteGenerator;
	m_levelArea;
}

LevelAreaContainer* LevelAreaBuilder::getLevelArea()
{
	// final construction of the level area object after all needed
	//properties have been set for the builder to build the area
	std::cout << "initialsing final constrcuted area " << std::endl;
	std::cout << "final area type " << typeid(*m_levelArea).name() << std::endl; 
	std::cout << "max ally spawn cap for area " << m_levelArea->getMaxAllyCap() << std::endl;
	m_levelArea->getSprites(m_spriteGenerator);
	m_levelArea->init(m_spriteGenerator);
	m_levelArea->initGrid();

	// return the level area object from the  ptr holding it as 
	// it has been constructed and no longer needs to be handled by
	// the level area builder
	return m_levelArea;
}
// used to assign a level area object to be constructed and edited 
void LevelAreaBuilder::assignNewArea(LevelAreaContainer* levelArea)
{
	m_levelArea = levelArea;

}

void LevelAreaBuilder::initNewArea()
{
	m_levelArea = new LevelAreaContainer();
}


void LevelAreaBuilder::assignAllyFaction(AllyFactionIds allyFaction)
{
	m_levelArea->setAllyFaction(allyFaction);

}
void LevelAreaBuilder::assignEnemyFaction(EnemyFactionIds enemyFaction)
{
	m_levelArea->setEnemyFaction(enemyFaction);

}
// various getters and setters that allow a level area object to have particualr 
// properties defined before it is constructed and released from the level area builder object 
void LevelAreaBuilder::assignBackgroundTexturePaths(std::vector<std::string>& paths)
{
	m_levelArea->setBackgroundTexturePaths(paths);

}

void LevelAreaBuilder::assignTileMapPaths(std::vector<std::string>& tileMapPaths)
{ 
	m_levelArea->setTileMapPaths(tileMapPaths);

}

void LevelAreaBuilder::assignTileMapImages(std::vector<sf::Image>& tileMapImages)
{
	m_levelArea->setTileMapImages(tileMapImages);
}

void LevelAreaBuilder::assignImageParsedTiles(std::map<std::string, TileInitialiser>& imageParsedTiles)
{ 
	m_levelArea->setImageParsedTiles(imageParsedTiles);
}

void LevelAreaBuilder::assignTileInfoColoursMap(std::map<imageMapColour, std::string>& tileInfocoloursMap)
{
	m_levelArea->setTileInfoColoursMap(tileInfocoloursMap);
}

void LevelAreaBuilder::assignDimensionsForArea(sf::Vector2i& gridDimensions, sf::Vector2f& tileSize)
{ 
	m_levelArea->setDimensionsForArea(gridDimensions,tileSize);
}

void LevelAreaBuilder::assignPositionForArea(sf::Vector2f& position)
{ 
	m_levelArea->setPosition(position);
}

void LevelAreaBuilder::assignAreaType(AreaTypes areaType)
{
	m_levelArea->setAreaType(areaType);
}

void LevelAreaBuilder::assignRandomlyGeneratedTiles(std::vector<TileInitialiser>& tiles)
{
	m_levelArea->setRandomlyGeneratedTiles(tiles);
}

void LevelAreaBuilder::setEnemyIntialisers(std::vector<EnemyInitialiser>& enemyInitialisers)
{
	m_levelArea->setEnemyIntialisers(enemyInitialisers);
}

void LevelAreaBuilder::setAllyInitialisers(std::vector<AllyInitialiser>& allyInitialisers)
{
	m_levelArea->setAllyInitialisers(allyInitialisers);
}


