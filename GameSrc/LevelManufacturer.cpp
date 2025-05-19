#include "LevelAreaManufacturer.h"

LevelAreaContainer* LevelAreaManufacturer::manufactureLevelArea(sf::Vector2f& position, sf::Vector2i& gridDimensions, sf::Vector2f& tileSize)
{
	// final constrction of the current level area object 
	// setting the position and dimensions for the area after it 
	//properties have been defined 
	m_levelAreaBuilder->assignPositionForArea(position);
	m_levelAreaBuilder->assignDimensionsForArea(gridDimensions, tileSize);
	return m_levelAreaBuilder->getLevelArea();
}
void LevelAreaManufacturer::setLevelBuilder(LevelAreaBuilder* levelBuilder)
{
	m_levelAreaBuilder = levelBuilder;
}
// initialise all data associated with the level area object currenlty held within the leve area builder 
// class that is responisble for constrctuing a level area and handling the setting of the large amount 
// of data required 
void LevelAreaManufacturer::createLevelArea(LevelAreaBuilder* areaBuilder, AreaTypes areaType,  std::vector < std::string>& backgroundPaths)
{
	// define all data for the basic properties and looks of the level area 
	// including background images and the area id
	m_levelAreaBuilder = areaBuilder;

	if (m_levelAreaBuilder->levelAreaRef() == nullptr) {
		std::cout << "level area builder had no level area assigned to be constrcuted creating new level area for builder" << std::endl;
		m_levelAreaBuilder->initNewArea();
	}

	m_levelAreaBuilder->assignBackgroundTexturePaths(backgroundPaths); 
	m_levelAreaBuilder->assignAreaType(areaType);

}




void LevelAreaManufacturer::initNewLevelArea()
{
	// used to have the builder move on to constructing a new area without defining it
    m_levelAreaBuilder->initNewArea();
}
// used to assign a level area object to be constructed and edited 
void LevelAreaManufacturer::assignNewLevelAreaObject(LevelAreaContainer* levelArea)
{	
	m_levelAreaBuilder->assignNewArea(levelArea);


}


// individually define if the level builder should construct a level area that uses tile map data to generate tiles 
void LevelAreaManufacturer::addTileMapsToArea(std::vector<std::string>& tileMapPaths,std::map<std::string, TileInitialiser>& imageMappedTiles,std::map<imageMapColour, std::string>& tileMapDescriptor)
{
	m_levelAreaBuilder->assignTileMapPaths(tileMapPaths);
	m_levelAreaBuilder->assignTileInfoColoursMap(tileMapDescriptor);
	m_levelAreaBuilder->assignImageParsedTiles(imageMappedTiles);

}
// individually define if the level builder should construct a level area with randomly generated tiles 
void LevelAreaManufacturer::addRandomlyGeneratedTileToArea(std::vector<TileInitialiser>& randomPostionedTiles)
{
	m_levelAreaBuilder->assignRandomlyGeneratedTiles(randomPostionedTiles);

}

// define any non playable characters that will within the level area to be constructed 
// by the level area builder currenlty assigned to the manufacturer 
void LevelAreaManufacturer::addLevelAreaNpcs(AllyFactionIds allyFactionId, std::vector<AllyInitialiser>& allyNpcs, EnemyFactionIds enemyFactionId, std::vector<EnemyInitialiser>& enemyNpcs)
{
	m_levelAreaBuilder->assignAllyFaction(allyFactionId);
	m_levelAreaBuilder->assignEnemyFaction(enemyFactionId);
	m_levelAreaBuilder->setAllyInitialisers(allyNpcs);
	m_levelAreaBuilder->setEnemyIntialisers(enemyNpcs);


}

// individually assign an ally faction to a level area 
void LevelAreaManufacturer::addAlliesToArea(AllyFactionIds allyFactionId,std::vector<AllyInitialiser>& allyNpcs)
{
	m_levelAreaBuilder->assignAllyFaction(allyFactionId);

	m_levelAreaBuilder->setAllyInitialisers(allyNpcs);
}
// individually assign an enemy faction to a level area 
void LevelAreaManufacturer::addEnemiesToArea(EnemyFactionIds enemyFactionId,std::vector<EnemyInitialiser>& enemyNpcs)
{
	m_levelAreaBuilder->assignEnemyFaction(enemyFactionId);
	m_levelAreaBuilder->setEnemyIntialisers(enemyNpcs);

}
