#pragma once
#include "GameObject.h"
// pure abstract base class for object pooling classes
// this is pure abstract due to objects having the potential
// to be pooled in different ways depding on functionaility
// also template class so the type of object to be pooled
// can be decided in derrived pool classes
template<class objectType>
class ObjectPool {

public: 
	
	virtual objectType* activateObject() = 0; 
	virtual bool hasAvailabeObject() = 0;
	virtual void resetActiveObject(int index) = 0;
	virtual void refreshActiveObjects() = 0;
		
protected:
	// here raw pointers are used other wise a pool could not be fully generic 
	// for example you could not have a pool containing multiple enemy types under an enemy base class
	// if you used a smart pointer like a shared ptr as it requires an instance of that class in order to be
	// instantiated itself
	std::vector<objectType*>m_activeObjects;
	std::vector<objectType*> m_pool;
	int m_maxObjects = 0;








};