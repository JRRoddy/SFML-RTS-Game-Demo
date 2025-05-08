#pragma once
#include "EnemyBase.h"

class EnemyInitialiser {


public:
	EnemyInitialiser() {};
	

	EnemyInitialiser(EnemyBase* EnemyBase) { // initialse the deep copy object with a ptr to the alloacted heap memory

		basePtr = EnemyBase;

	}


	EnemyInitialiser(const EnemyInitialiser& other) {

		basePtr = other.basePtr->clone();

	}
	EnemyInitialiser operator = (const EnemyInitialiser& other) {

		basePtr = other.basePtr->clone();

		return *this;
	}

	EnemyBase* getHeldObjectCopy() {

		EnemyBase* copy;  // create a pointer to assign the allocated memory from the current held EnemyBase's clone method 
		copy = basePtr->clone(); // assign the heap allocated memeory to the unique ptr to be managed

		return copy; // return the deep copy 

		
	};


	~EnemyInitialiser() {
		delete basePtr;
	}

	EnemyBase* getHeldObject() {
		return basePtr;
	};

private:
	EnemyBase* basePtr = nullptr;



};