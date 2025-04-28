#pragma once

#include "AreaTypes.h"
#include "EnemyBase.h" 
#include "EnemyInitialsier.h"
#include "EnemyPool.h"
#include "LevelAreaContainer.h"
#include "Player.h"
#include "collisionHandler.h"
#include "Astar.h" 
#include "LevelGrid.h"
class EnemyManager {

public:
	
	EnemyManager(Player * player,Astar * astar, LevelGrid * levelGrid);
	~EnemyManager();
	void initEnemyPool(AreaTypes areaType,std::vector<EnemyInitialiser>& enemies, SpriteGenerator * spriteGenerator);
	void update(float dt); 
	void drawEnemies(sf::RenderWindow * window);
	void setCurrentEnemyPool(AreaTypes areaType);
	bool checkEnemyRemoval(int index);
	void getNewSpawnDelay(); 
	std::vector<EnemyBase*>& getActiveEnemyBuffer();
	void updateCollision();
	void setCurrentArea(LevelAreaContainer* levelArea);
	void spawnEnemy();
	void setPathFinder(Astar* astar);
	void setLevelGrid(LevelGrid* levelGrid);
private:
	
	std::map<AreaTypes, EnemyObjectPool> m_AreaPools;
	std::vector<EnemyBase*> m_activeEnemyBuffer;
	std::shared_ptr<CollisonHandler<EnemyBase>>  m_enemyCollisonHandler;
	EnemyObjectPool* m_currentEnemyPool = nullptr;
	Astar* m_AStar = nullptr;
	sf::Clock m_spawnTimer; 
	sf::Time m_spawnDelay;
	LevelAreaContainer* m_currentArea = nullptr;
	Player* m_playerRef;   
	LevelGrid* m_levelGrid;
	int m_maxCollisionTreeDepth;
	std::vector<GameObject*> m_collisionBuffer;


};