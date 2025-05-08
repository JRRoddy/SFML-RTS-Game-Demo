#pragma once
#include "LevelAreaBuilder.h"
// the manufactueuer class is responsible for taking in and defining the properties 
// for the builder to then use to construct a levele area 
class LevelAreaManufacturer {

public:
	LevelAreaManufacturer() {};
	~LevelAreaManufacturer() {};
	LevelAreaContainer* manufactureLevelArea(sf::Vector2f & position,sf::Vector2i& gridDimensions, sf::Vector2f& tileSize);
	void setLevelBuilder(LevelAreaBuilder * levelBuilder);
	void createLevelArea(LevelAreaBuilder* areaBuilder,AreaTypes areaType,std::vector < std::string>& backgroundPaths);
	
	void initNewLevelArea();
	
	void assignNewLevelAreaObject(LevelAreaContainer* levelArea);
	
	void addTileMapsToArea(std::vector<std::string>& tileMapPaths,std::map<std::string, TileInitialiser>& imageMappedTiles, std::map<imageMapColour, std::string>& tileMapDescriptor);
	void addRandomlyGeneratedTileToArea(std::vector<TileInitialiser>& randomPostionedTiles);
	void addLevelAreaNpcs(AllyFactionIds allyFactionId,std::vector<AllyInitialiser> & allyNpcs,EnemyFactionIds enemyFactionId ,std::vector<EnemyInitialiser>& enemyNpcs);
	void addAlliesToArea(AllyFactionIds allyFactionId,std::vector<AllyInitialiser>& allyNpcs);
	void addEnemiesToArea(EnemyFactionIds enemyFactionId,std::vector<EnemyInitialiser>& enemyNpcs);
private:
	LevelAreaBuilder* m_levelAreaBuilder = nullptr;
	
};