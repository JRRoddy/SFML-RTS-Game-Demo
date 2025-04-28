#include "EnemyPool.h"

EnemyObjectPool::EnemyObjectPool(std::vector<EnemyInitialiser>& enemiesToPool)
{
	// generate enemy pool
	
	int spawnCount = 0;
	// sum up the max amount of enemies within the pool
	for (int i = 0; i < enemiesToPool.size(); i++) {
		spawnCount += enemiesToPool[i].getHeldObject()->getSpawnCap();
		
	} 
	m_maxObjects = spawnCount; // max enemies held in pool
	m_pool.resize(m_maxObjects);
	int EnemyInitPointer = 0; // current index into enemy initialiser vector 
	// current enemy initialiser being used to generate the pool
	EnemyInitialiser* enemyInit = &enemiesToPool[EnemyInitPointer];
	std::cout << "initialising enemy pool" << std::endl;
	
	// generate the pool through constructing and allocating memory 
	// for enemies within the pool using the deep copy
	// enemy initialiser objects to create multiple copies of enemies 
	for (int i = 0; i < m_maxObjects; i++) { 
		// take into account multiple enemy initialisers 
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
	// remove object from specifc index within active pool
	// and move it back into the main pool
	m_pool.push_back(m_activeObjects[index]);
	m_activeObjects.erase(m_activeObjects.begin() + index);

}
void EnemyObjectPool::refreshActiveObjects() {
	// loop through all objects and check if any need to be removed from the 
	//active pool
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
		// select random enemy from pool and set it to be active
		// return enemy for any further manipulation 
		int randomEnemyIndexSelection = rand() % m_pool.size();
		EnemyBase* enemy = m_pool[randomEnemyIndexSelection];
		enemy->setIsActive(true);
		// push enemy into active pool and erase it from the main pool
		//as it is now active
		m_activeObjects.push_back(m_pool[randomEnemyIndexSelection]);
		m_pool.erase(m_pool.begin() + randomEnemyIndexSelection);
		return enemy;
	}
	
	return nullptr;

}

bool EnemyObjectPool::hasAvailabeObject()
{
	// if the number of active enemies is not equal to max object
	//held by enemy pool object 
	return m_activeObjects.size()!=m_maxObjects;
}


