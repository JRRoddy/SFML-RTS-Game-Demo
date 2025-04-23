#pragma once
#include "ObjectPool.h"
#include "AllyInitialiser.h"

class AllyObjectPool :public  ObjectPool<AllyBase> {

public:
	AllyObjectPool() {};
	AllyObjectPool(std::vector<AllyInitialiser>& enemiesToPool);
	~AllyObjectPool();
	void resetActiveObject(int index);
	void refreshActiveObjects();
	AllyBase* activateObject();
	bool hasAvailabeObject();

private:




};