#pragma once
#include "ObjectPool.h"
#include "EnemyInitialsier.h"

class EnemyObjectPool:public  ObjectPool<EnemyBase> {

public:
	EnemyObjectPool() {};
	EnemyObjectPool(std::vector<EnemyInitialiser>&enemiesToPool); 
	~EnemyObjectPool();
	void resetActiveObject(int index);
	void refreshActiveObjects();
	EnemyBase* activateObject();
	bool hasAvailabeObject();

private:




};