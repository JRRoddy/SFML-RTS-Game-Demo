#pragma once
#include "StatusEffect.h"

class StatusEffectInitialiser {


public:
	StatusEffectInitialiser() {};


	//StatusEffectInitialiser(StatusEffect* StatusEffect) { // initialse the deep copy object with a ptr to the alloacted heap memory

	//	basePtr = StatusEffect;

	//}


	//StatusEffectInitialiser(const StatusEffectInitialiser& other) {

	//	basePtr = other.basePtr->clone();

	//}
	//StatusEffectInitialiser operator = (const StatusEffectInitialiser& other) {

	//	basePtr = other.basePtr->clone();

	//	return *this;
	//}

	//StatusEffect* getHeldObjectCopy() {

	//	StatusEffect* copy;  // create a pointer to assign the allocated memory from the current held StatusEffect's clone method 
	//	copy = basePtr->clone(); // assign the heap allocated memeory to the unique ptr to be managed

	//	return copy; // return the deep copy 


	//};


	//~StatusEffectInitialiser() {
	//	delete basePtr;
	//}

	//StatusEffect* getHeldObject() {
	//	return basePtr;
	//};

private:
	StatusEffect* basePtr = nullptr;



};