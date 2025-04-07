#pragma once
#include "Tile.h"
// a simple deep copy class that can be assifgned a new tile object and have that object be deep copied 
// based on the current held tile clone method 
class TileInitialiser {


public:

	std::unique_ptr<Tile> basePtr;
	TileInitialiser(){}

	TileInitialiser(TileInitialiser& dc) : basePtr(dc.basePtr->clone()) {


	}
	TileInitialiser operator= (const TileInitialiser& dc) {
	    
		basePtr.reset(dc.basePtr.get()->clone());

		return *this;

        



	}
	TileInitialiser(Tile * tile) { // initialse the deep copy object with a ptr to the alloacted heap memory

		basePtr.reset(tile);

	}

	std::unique_ptr<Tile> getHeldObjectCopy() {

		std::unique_ptr<Tile> copyObjectToReturn; // create a new unique pointer to assign the allocated memeory from the current held tile's clone method 
		copyObjectToReturn.reset(basePtr.get()->clone()); // assign the heap allocated memeory to the unique ptr to be managed
		return copyObjectToReturn; // return the deep copy 


	};

	void setObject(Tile& tile) {
		basePtr = std::make_unique<Tile>(tile);
	}



};
