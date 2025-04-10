#pragma once
#include "Tile.h"
// a simple deep copy class that can be assigned a new tile object and have that object be deep copied 
// based on the current held tile clone method 
class TileInitialiser {


public:


	TileInitialiser() {};

	
	TileInitialiser(Tile * tile) { // initialse the deep copy object with a ptr to the alloacted heap memory

		basePtr = tile;
		

	}
	
	
	TileInitialiser(const TileInitialiser& other) {
	
		
		basePtr = other.basePtr->clone();

		
	}
	TileInitialiser operator = (const TileInitialiser& other) {
		
		
		basePtr = other.basePtr->clone() ;

		return *this;
	}

	Tile * getHeldObjectCopy() {

		Tile * copy;  // create a pointer to assign the allocated memory from the current held tile's clone method 
		copy = basePtr->clone(); // assign the heap allocated memeory to the unique ptr to be managed
		
		return copy; // return the deep copy 


	};


	~TileInitialiser() {
		std::cout << "tile initialiser destructor called" << std::endl;
		delete basePtr;
	}

	Tile* getHeldObject() {
		return basePtr;
	};

private:
	Tile* basePtr = nullptr;



};
