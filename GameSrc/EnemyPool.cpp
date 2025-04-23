#include "EnemyPool.h"

EnemyObjectPool::EnemyObjectPool(std::vector<EnemyInitialiser>& enemiesToPool)
{
	// generate enemy pool
	
	int spawnCount = 0;
	for (int i = 0; i < enemiesToPool.size(); i++) {
		spawnCount += enemiesToPool[i].getHeldObject()->getSpawnCap();
		
	} 
	m_maxObjects = spawnCount;
	m_pool.resize(m_maxObjects);
	int EnemyInitPointer = 0;
	EnemyInitialiser* enemyInit = &enemiesToPool[EnemyInitPointer];
	std::cout << "initialising enemy pool" << std::endl;
	for (int i = 0; i < m_maxObjects; i++) {
		if (i == enemyInit->getHeldObject()->getSpawnCap()) {
			EnemyInitPointer++;
			enemyInit = &enemiesToPool[EnemyInitPointer];
		}
		EnemyBase* enemy = enemyInit->getHeldObjectCopy();
		m_pool[i] = enemy;
		

	}

}

EnemyObjectPool::~EnemyObjectPool()
{
	std::cout << "ENEMY POOL DESTRUCTOR CALLED " << std::endl;
	// clean up object pools
	for (int i = 0; i < m_activeObjects.size(); i++) {
		delete m_activeObjects[i];
	}
	for (int i = 0; i < m_pool.size(); i++) {
		delete m_pool[i];
	}



}

void EnemyObjectPool::resetActiveObject(int index)
{
	m_pool.push_back(m_activeObjects[index]);
	m_activeObjects.erase(m_activeObjects.begin() + index);

}
void EnemyObjectPool::refreshActiveObjects() {
	for (int i = 0; i < m_activeObjects.size(); i++) {
		if (!m_activeObjects[i]->getIsActive()) {

			m_pool.push_back(m_activeObjects[i]);
			m_activeObjects.erase(m_activeObjects.begin() + i);

		}
	}
}

EnemyBase* EnemyObjectPool::activateObject()
{
	if (hasAvailabeObject()) {
		int randomEnemyIndexSelection = rand() % m_pool.size();
		EnemyBase* enemy = m_pool[randomEnemyIndexSelection];
		enemy->setIsActive(true);
		m_activeObjects.push_back(m_pool[randomEnemyIndexSelection]);
		m_pool.erase(m_pool.begin() + randomEnemyIndexSelection);
		return enemy;
	}
	
	return nullptr;

}

bool EnemyObjectPool::hasAvailabeObject()
{
	return m_activeObjects.size()!=m_maxObjects;
}


