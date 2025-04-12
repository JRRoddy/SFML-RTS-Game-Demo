#pragma once

#include "LevelGrid.h" 
#include "EnemyBase.h"
#include "AreaInitialiser.h"
#include "areaHeaders.h" 
#include "tileHeaders.h" 
#include "ImageMapInfoParser.h"

// main class that is used to generate the current area for the player with it having classes such as a tile generator 
// and a vector that holds all of the level area containers
// currenlty on the map along with keeping track of the current level area container the player is in 
class LevelGenerator {

public:
	LevelGenerator(SpriteGenerator* spriteGenerator, sf::Vector2f startAreaOffsetPosition,Player * playerRef,sf::Vector2i tileDimensions, sf::Vector2f gridChunkSize,sf::Vector2i gridDim);
	void generateNewAreaGrid(AreaTypes areaType,sf::Vector2f offsetPosition);
	LevelAreaContainer* getCurrentAreaGrid();
	float getGridAreaWidth()const;
	float getGridAreaHeight()const; 
	int getLevelChunkWidth() const;
	int getlevelChunkHeight() const; 
	void parseLevelMaps();
	void update(float dt);
	void updatePlayerTileState(); 
	~LevelGenerator();
	
private:
	LevelAreaContainer* m_currentArea; 
	Player* m_playerRef;
	Tile* m_currentPlayerTile;
	SpriteGenerator* m_spriteGenerator;
	std::unique_ptr<LevelGrid> m_levelGrid;
	
	
	sf::Vector2f m_ChunkSize; 
	sf::Vector2i m_gridDimensions;
	sf::Vector2i m_tileSize;
	std::vector<LevelAreaContainer*> m_areaContainersPool;
	std::map<AreaTypes, std::vector<EnemyBase*>>m_areaEnemyPools;
	
	std::map<AreaTypes, AreaInitialiser> m_areas;
	std::map <AreaTypes, std::vector<TileInitialiser>> m_randomMappedTiles;
	
	
	std::map<AreaTypes, std::vector<std::string>> m_areaBackgroundTextures = 
	{
		{GRASSLANDS,{"../Assets/Textures/GrassBackground0.png"}}
	
	};
	
	std::map<AreaTypes, std::vector<std::string>> m_tileMapImages =
	{
		{GRASSLANDS,{"../Assets/TileMapImages/GrassLands/GrassLandsMap.png"}}
	};
	std::map<AreaTypes, std::map<std::string ,TileInitialiser>> m_imageMappedTiles;
	
	std::map<AreaTypes, std::string> m_imageMapInfoFilePaths =
	{
		{GRASSLANDS,"../Assets/TileMapImages/GrassLands/GrassLandsImageMapInfo.txt"}
	};
	





	

		


	

};