#pragma once
#include "AllyBase.h"

class AllyInitialiser {


public:
	AllyInitialiser() {};


	AllyInitialiser(AllyBase* AllyBase) { // initialse the deep copy object with a ptr to the alloacted heap memory

		basePtr = AllyBase;

	}
	AllyInitialiser(const AllyInitialiser& other) {

		basePtr = other.basePtr->clone();

	}
	AllyInitialiser operator = (const AllyInitialiser& other) {

		basePtr = other.basePtr->clone();
		return *this;
	}

	AllyBase* getHeldObjectCopy() {

		AllyBase* copy;  // create a pointer to assign the allocated memory from the current held AllyBase's clone method 
		copy = basePtr->clone(); // assign the heap allocated memeory to the unique ptr to be managed

		return copy; // return the deep copy 


	};


	~AllyInitialiser() {
		delete basePtr;
	}

	AllyBase* getHeldObject() {
		return basePtr;
	};

private:
	AllyBase* basePtr = nullptr;



};