#pragma once

#include "LevelGrid.h" 
#include "Astar.h"
#include "random.h"
#include "AreaInitialiser.h"
#include "areaHeaders.h" 
#include "tileHeaders.h" 
#include "ImageMapInfoParser.h"
#include "EnemyManager.h" 
#include "AllyManager.h"

// main class that is used to generate the current area for the player with it having classes such the level grid
// and a vector that holds all of the level area containers
// currenlty on the map along with keeping track of the current level area container the player is in 
class LevelGenerator {

public:
	LevelGenerator(SpriteGenerator* spriteGenerator, sf::Vector2f startAreaOffsetPosition, Player* playerRef, sf::Vector2i tileDimensions, sf::Vector2f gridChunkSize, sf::Vector2i gridDim);
	void generateNewAreaGrid(AreaTypes areaType, sf::Vector2f offsetPosition);
	LevelAreaContainer* getCurrentAreaGrid();

	float getGridAreaWidth()const;
	float getGridAreaHeight()const;
	int getLevelChunkWidth() const;
	int getlevelChunkHeight() const;
	void parseLevelMaps();
	void update(float dt);
	void drawObjects(sf::RenderWindow* window);
	void updatePlayerTileState(float dt);
	void initManagerPools();
	void playerNextTileCheck(float dt);
	~LevelGenerator();

private:
	LevelAreaContainer* m_currentArea;
	Player* m_playerRef;
	Tile* m_currentPlayerTile;
	SpriteGenerator* m_spriteGenerator;
	std::unique_ptr<LevelGrid> m_levelGrid;
	std::unique_ptr<AllyManager> m_allyManager;
	std::unique_ptr<EnemyManager> m_enemyManager;
	std::vector<StaticObject*> quadTreeDebug;
	std::unique_ptr<Astar> m_astarObject;
	sf::Vector2f m_ChunkSize;
	sf::Vector2i m_gridDimensions;
	sf::Vector2i m_tileSize;
	std::vector<LevelAreaContainer*> m_areaContainersPool;
	std::map<AreaTypes, std::vector<EnemyBase*>>m_areaEnemyPools;
	std::vector<sf::CircleShape> m_debugQuadTreePositions;
	std::map<AreaTypes, AreaInitialiser> m_areas;
	std::map <AreaTypes, std::vector<TileInitialiser>> m_randomMappedTiles;
	int m_maxLevelAreaColTreeDepth;
	AreaTypes m_startArea = GRASSLANDS;

	std::map<AreaTypes, std::vector<std::string>> m_areaBackgroundTextures =
	{
		{GRASSLANDS,{"../Assets/Textures/GrassBackground0.png"}}

	};
	
	std::map<AreaTypes, std::vector<std::string>> m_tileMapImages =
	{
		{GRASSLANDS,{"../Assets/TileMapImages/GrassLands/GrassLandsMap.png"}}
	};
	std::map<AreaTypes, std::map<std::string, TileInitialiser>> m_imageMappedTiles;

	std::map<AreaTypes, std::string> m_imageMapInfoFilePaths =
	{
		{GRASSLANDS,"../Assets/TileMapImages/GrassLands/GrassLandsImageMapInfo.txt"}
	};













};