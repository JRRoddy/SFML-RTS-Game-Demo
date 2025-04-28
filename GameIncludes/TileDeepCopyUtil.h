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

		// keep track of the number of times we initilalise a
		// tile of the type held by this tile initialiser 
		// as some tiles have spawn caps
		m_tileInitCount++;  
		return copy; // return the deep copy 


	};
	// used to check if we have initialise the tile more than or equal to its spawn cap
	// tiles with spawn cap 0 have no spawn cap
	bool hasHitInitialiseCap() {
		return  basePtr->getSpawnCap()>0 && m_tileInitCount >= basePtr->getSpawnCap();
	}
	int getTileInitCound() {
		return m_tileInitCount;
	}
	~TileInitialiser() {
		delete basePtr;
	}

	Tile* getHeldObject() {
		return basePtr;
	};

private:
	Tile* basePtr = nullptr;
	int m_tileInitCount = 0;


};
