#pragma once
#include "LevelAreaContainer.h"
// the level area builder class is the main builder cass within the builder desgin 
// pattern that is used for the constrcution of level area objects allowing
// level areas to be constructed various different properties defined based on the needs of 
// the level generator class these properties include different enemy types that can spawn 
// different allies and different sizes for the level areas along with different tile maps
class LevelAreaBuilder {

public:
	LevelAreaBuilder(SpriteGenerator* spriteGenerator);
	
	virtual ~LevelAreaBuilder() {};
	LevelAreaContainer* getLevelArea();

	void assignNewArea(LevelAreaContainer * levelArea);
	void initNewArea();
	void assignEnemyFaction(EnemyFactionIds enemyFaction);
	
	void assignAllyFaction(AllyFactionIds allyFaction);
	void assignBackgroundTexturePaths(std::vector<std::string>& paths);
	
	void assignTileMapPaths(std::vector<std::string>& tileMapPaths); 
	void assignTileMapImages(std::vector<sf::Image>& tileMapImages);
	
	void assignImageParsedTiles(std::map<std::string, TileInitialiser>& imageParsedTiles);
	void assignTileInfoColoursMap(std::map<imageMapColour, std::string>& tileInfocoloursMap);
	
	void assignDimensionsForArea(sf::Vector2i& gridDimensions, sf::Vector2f& tileSize);
	void assignPositionForArea(sf::Vector2f& position);
	
	void assignAreaType(AreaTypes areaType);
	void assignRandomlyGeneratedTiles(std::vector<TileInitialiser>& tiles);

	void setEnemyIntialisers(std::vector<EnemyInitialiser>& enemyInitialisers);
	void setAllyInitialisers(std::vector<AllyInitialiser>& allyInitalisers);

protected:
	SpriteGenerator* m_spriteGenerator = nullptr;
	LevelAreaContainer * m_levelArea = nullptr;
};