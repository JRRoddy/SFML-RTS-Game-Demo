#include "EnemyManager.h"


void EnemyManager::update(float dt) {

	// main update loop for the enemy manager 
   // this pass information to enemies and sets data such as their current path 

	for (int i = 0; i < m_activeEnemyBuffer.size();i++)
	{   
		if(checkEnemyRemoval(i)) continue;// check if the enemy needs to be removed from active buffer
		EnemyBase* enemyToUpdate = m_activeEnemyBuffer[i];
		// get the current path and set it for the enemy to folllow 
		m_activeEnemyBuffer[i]->updateGridTileState(m_levelGrid->getGridTile(enemyToUpdate->getPosition()));
		
		m_activeEnemyBuffer[i]->setPath(m_AStar->getPath(enemyToUpdate->getPosition(),enemyToUpdate->getTargetPosition()));
		m_activeEnemyBuffer[i]->update(dt); // update enemy 
		//  update enemies status in collision tree
	    m_enemyCollisonHandler.get()->insertItem(enemyToUpdate->getBounds(), enemyToUpdate);
	    
	}
	//update any collisions within the collision tree and 
	// reset it ready for next update
	updateCollision();

	spawnEnemy();
	

}



void EnemyManager::drawEnemies(sf::RenderWindow* window)
{
	// draw all active enemies
	for (GameObject * enemy : m_activeEnemyBuffer)
	{
		enemy->draw(window);
	} 
	
	//m_enemyCollisonHandler.get()->drawCollisionTree(window);
}




void EnemyManager::setCurrentEnemyPool(AreaTypes areaType)
{

	m_currentEnemyPool = &m_AreaPools[areaType];

}

bool EnemyManager::checkEnemyRemoval(int index)
{
	// since the active enemy buffer for the enemy manager lines up with the 
	// buffer of the current enemy pool we can match the index of the enemy
	// that has become inactive with that inside the current enemy pool object
	if (!m_activeEnemyBuffer[index]->getIsActive()) {
		m_currentEnemyPool->resetActiveObject(index);
		m_activeEnemyBuffer.erase(m_activeEnemyBuffer.begin() + index);
		return true;
	}
	return false;
}

// get new spawn delay for enemies based on current level area
void EnemyManager::getNewSpawnDelay()
{

	m_spawnTimer.restart(); 
	std::cout << "restarting spawn timer " << m_spawnTimer.getElapsedTime().asSeconds() << std::endl;
	m_spawnDelay = sf::seconds(m_currentArea->getRandomSpawnDelay());
	std::cout << "new spawn delay is " << m_spawnDelay.asSeconds() << std::endl;

}

std::vector<EnemyBase*>& EnemyManager::getActiveEnemyBuffer()
{
	return m_activeEnemyBuffer;
}

void EnemyManager::updateCollision()
{ 
	// go through all of the items in the collision buffer 
	// which contains all objects that could collide with enemies
	for (int i = 0; i < m_collisionBuffer.size(); i++) {
		
		if (!m_collisionBuffer[i]->getIsActive()) { // ignore object if its not active 
			m_collisionBuffer.erase(m_collisionBuffer.begin() + i);
		}
		
		std::vector<quadTreeItem<EnemyBase>> resultingCollisionItems = {};
		// check the space around the object through the collision tree
		// checking all the segments of the quad tree that this objects bounds 
		// intersect therefore reducing the number of objects we need to check every frame
		// through the quad tree as only objects that are close enough to be checked will be checked 
		// through the spatial partitioning performed by the quad tree 
		m_enemyCollisonHandler->queryCollisionTree(m_collisionBuffer[i]->getBounds(), resultingCollisionItems);
		
		// deal with any collisions that were returned by querying the tree
		for (quadTreeItem<EnemyBase>& collideResult : resultingCollisionItems) {

			collideResult.gameObject->collision(m_collisionBuffer[i]);
			m_collisionBuffer[i]->collision(collideResult.gameObject);
		}

	}
	m_enemyCollisonHandler.get()->resetCollisionTreeItems();

}

void EnemyManager::setCurrentArea(LevelAreaContainer* levelArea)
{
	m_currentArea = levelArea;
	m_currentEnemyPool = &m_AreaPools[levelArea->getAreaType()];
	m_enemyCollisonHandler.get()->resizeTree(sf::FloatRect(m_currentArea->getTopLeft(), m_currentArea->getWorldDimensions()));

}

void EnemyManager::spawnEnemy()
{
	// used to spawn enemies based on a specifc timing range determined by the current area 
	if (m_spawnTimer.getElapsedTime().asSeconds() >= m_spawnDelay.asSeconds() && m_currentEnemyPool->hasAvailabeObject()) {

		std::cout << "spawning enemy elapsed time was "<<m_spawnTimer.getElapsedTime().asSeconds()<<"  spawn delay was "<<m_spawnDelay.asSeconds() << std::endl;
		EnemyBase * enemyToSpawn = m_currentEnemyPool->activateObject(); 
		enemyToSpawn->setPosition(m_currentArea->getEnemySpawnPosition(enemyToSpawn));
		enemyToSpawn->setGridTile(m_levelGrid->getGridTile(enemyToSpawn->getPosition()));
		m_activeEnemyBuffer.push_back(enemyToSpawn);

		getNewSpawnDelay();

	}



}

void EnemyManager::setPathFinder(Astar* astar)
{
	m_AStar = astar;
}

void EnemyManager::setLevelGrid(LevelGrid* levelGrid)
{
	m_levelGrid = levelGrid;
}


EnemyManager::EnemyManager(Player * player,Astar * astar,LevelGrid * levelGrid)
{
	m_playerRef = player;
	m_levelGrid = levelGrid;
	m_collisionBuffer.push_back(player);
	m_maxCollisionTreeDepth = 8;
	m_AStar = astar;
	m_enemyCollisonHandler = std::make_shared<CollisonHandler<EnemyBase>>(CollisonHandler<EnemyBase>());
	std::cout <<"collision handler ptr "<< m_enemyCollisonHandler.get() << std::endl; 
	m_enemyCollisonHandler.get()->setTreeMaxDepth(m_maxCollisionTreeDepth);

}

EnemyManager::~EnemyManager()
{
	
}


// initialsier a new pool to be used and managed by the enemy manager
void EnemyManager::initEnemyPool(AreaTypes areaType, std::vector<EnemyInitialiser>& enemies, SpriteGenerator * spriteGenerator)
{
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].getHeldObject()->setPlayerCharacterRef(m_playerRef);
		enemies[i].getHeldObject()->setTargetPlayer();
		enemies[i].getHeldObject()->getSprites(spriteGenerator);
	}
	m_AreaPools.emplace(areaType,enemies);
}






