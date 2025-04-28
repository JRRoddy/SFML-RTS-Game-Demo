#include "AllyObjectPool.h"

AllyObjectPool::AllyObjectPool(std::vector<AllyInitialiser>& alliesToPool)
{
	// generate ally pool

	int spawnCount = 0;
	for (int i = 0; i < alliesToPool.size(); i++) {
		spawnCount += alliesToPool[i].getHeldObject()->getSpawnCap();

	}
	m_maxObjects = spawnCount;
	m_pool.resize(m_maxObjects);
	int allyInitPointer = 0;
	AllyInitialiser* allyInit = &alliesToPool[allyInitPointer];
	std::cout << "initialising ally pool" << std::endl;
	for (int i = 0; i < m_maxObjects; i++) {
		if (i == allyInit->getHeldObject()->getSpawnCap()) {
			allyInitPointer++;
			allyInit = &alliesToPool[allyInitPointer];
		}
		AllyBase* ally = allyInit->getHeldObjectCopy();
		m_pool[i] = ally;


	}

}

AllyObjectPool::~AllyObjectPool()
{
	std::cout << "ally POOL DESTRUCTOR CALLED " << std::endl;
	// clean up object pools
	for (int i = 0; i < m_activeObjects.size(); i++) {
		delete m_activeObjects[i];
	}
	for (int i = 0; i < m_pool.size(); i++) {
		delete m_pool[i];
	}



}

void AllyObjectPool::resetActiveObject(int index)
{
	m_pool.push_back(m_activeObjects[index]);
	m_pool[index]->reset();
	m_activeObjects.erase(m_activeObjects.begin() + index);

}
void AllyObjectPool::refreshActiveObjects() {
	for (int i = 0; i < m_activeObjects.size(); i++) {
		if (!m_activeObjects[i]->getIsActive()) {

			m_pool.push_back(m_activeObjects[i]);
			m_activeObjects.erase(m_activeObjects.begin() + i);

		}
	}
}

AllyBase* AllyObjectPool::activateObject()
{
	if (hasAvailabeObject()) {
		int randomEnemyIndexSelection = rand() % m_pool.size();
		AllyBase* ally = m_pool[randomEnemyIndexSelection];
		ally->setIsActive(true);
		m_activeObjects.push_back(m_pool[randomEnemyIndexSelection]);
		m_pool.erase(m_pool.begin() + randomEnemyIndexSelection);
		return ally;
	}

	return nullptr;

}

bool AllyObjectPool::hasAvailabeObject()
{
	return m_activeObjects.size() != m_maxObjects;
}


