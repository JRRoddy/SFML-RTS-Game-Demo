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
#include "Enemies.h"
#include "Allies.h"
#include "LevelAreaManufacturer.h"

// main class that is used to generate the current area for the player with it having classes such the level grid
// and a vector that holds all of the level area containers
// currenlty on the map along with keeping track of the current level area container the player is in 
// the level generate is also broadly responsible for updating objects conatined within the level 
// but has various manager classes to help update objects of a specifc type such as 
// allies or enemies 
class LevelGenerator {

public:
	LevelGenerator(SpriteGenerator* spriteGenerator, sf::Vector2f startAreaOffsetPosition, Player* playerRef, sf::Vector2i tileDimensions, sf::Vector2f gridChunkSize, sf::Vector2i gridDim);
	void generateFullNewArea(LevelAreaBuilder* areaBuilder, AreaTypes areaType, sf::Vector2f offsetPosition, EnemyFactionIds enemyFactionInArea, AllyFactionIds allyFactionInArea);
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
	void savePlayerScoreOnLevel();
	void setPlayerIsInLevel(bool playerIsInLevel);
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
	std::string m_saveScorePath ="../Assets/PlayerData/scores.txt";
	std::string m_saveRunCountPath = "../Assets/PlayerData/runData.txt";
	int m_maxLevelAreaColTreeDepth;
	bool m_playerHasEnteredLevel = false;
	AreaTypes m_startArea = GRASSLANDS;
	// a level generator has a lvel area builder and a level area manufacturer
	std::shared_ptr<LevelAreaBuilder> m_levelAreaBuilder; 
	std::shared_ptr<LevelAreaManufacturer> m_levelAreaManufacturer;

	

	// all data here is used by a builder design pattern that can be used 
	// to create many different level areas with different background textures, enemies,
	// and other non playable characters allowing for more flexible creation of level areas
	
	// storing background textures for level areas mapping them to a particualr id 
	std::map<AreaTypes, std::vector<std::string>> m_areaBackgroundTextures =
	{
		{GRASSLANDS,{"../Assets/Textures/GrassBackground0.png"}}

	};
	// storing the image maps that are used to generate tiles at fixed locations 
	// mapping them to a particualr area id asscoiated with all level area classes 
	std::map<AreaTypes, std::vector<std::string>> m_tileMapImages =
	{
		{GRASSLANDS,{"../Assets/TileMapImages/GrassLands/GrassLandsMap.png"}}
	};
	
	std::map<AreaTypes, std::map<std::string, TileInitialiser>> m_imageMappedTiles;
	std::map <AreaTypes, std::vector<TileInitialiser>> m_randomMappedTiles;
	// store all of the files that describe a particualr tile image map 
	std::map<AreaTypes, std::string> m_imageMapInfoFilePaths =
	{
		{GRASSLANDS,"../Assets/TileMapImages/GrassLands/GrassLandsImageMapInfo.txt"}
	};

	// store ally factions and ally initialiser objects assoicated with those factions
	std::map < AllyFactionIds, std::vector<AllyInitialiser>> m_allyFactions
	{
		{KNIGHTS, {AllyInitialiser(new Pawn())}}

	};
	// same as above but for enemies 
	std::map < EnemyFactionIds, std::vector<EnemyInitialiser>> m_enemyFactions
	{
		{GOBLINS, {EnemyInitialiser(new Goblin())}}
	
	};
	std::map<AreaTypes, AreaInitialiser> m_areas;

	std::map < AreaTypes, std::map<imageMapColour, std::string>> m_tileImageMapInformation;









};