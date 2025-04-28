
#include "LevelAreaContainer.h"
#include "collisionHandler.h"
#include "AllyInitialiser.h" 
#include "AllyObjectPool.h"
#include "LevelGrid.h"
#include "Astar.h"
// class responsible for managing all instantiated ally objects 
// will upfdate things such as pathfinding for allies and their current 
// collision status
class AllyManager {


public:
	AllyManager(Player* player, Astar* astar, LevelGrid* levelGrid);
	~AllyManager();
	void spawnAllies(); 
	void update(float dt);
	void initAllyPools(AreaTypes areaType, std::vector<AllyInitialiser>& m_alliesToInit, SpriteGenerator * spriteGenerator);
	void setCurrentArea(LevelAreaContainer * levelArea);
	bool checkAllyRemoval(int index);
	void resetSpawnDelay();
	void updateAllySelectedStatus(AllyBase * ally);
	void updateEnemyCollision(std::vector<EnemyBase*> &enemyBuffer);
	void updateAllyPath(AllyBase* ally);
	void drawAllies(sf::RenderWindow * window);
private:
	LevelGrid* m_levelGrid = nullptr;
	Player* m_playerRef = nullptr;
	std::shared_ptr<CollisonHandler<AllyBase>> m_AllyCollisionHandler;
	LevelAreaContainer* m_currentArea = nullptr;
	std::map<AreaTypes, AllyObjectPool> m_areaPools;
	std::vector<AllyBase*> m_activeBuffer;
	int m_maxCollisionTreeDepth = 1; 
	int m_staticAlliesCount = 0;
	Astar* m_AStar = nullptr;
	AllyObjectPool* m_currentPool = nullptr;
	sf::Time m_refereshTime; 
	sf::Clock m_refreshAlliesTimer;
};