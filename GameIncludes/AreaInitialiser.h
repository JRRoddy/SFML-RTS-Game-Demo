#pragma once
#include "AreaInitialiser.h"
#include "LevelAreaContainer.h"
class AreaInitialiser {


public:

	
	AreaInitialiser() {}

	AreaInitialiser(const AreaInitialiser& other) {
		
		basePtr = other.basePtr->clone();
		m_spriteGenerator = other.m_spriteGenerator;

	}
	AreaInitialiser operator= (const AreaInitialiser& other) {
		basePtr = other.basePtr->clone();
		m_spriteGenerator = other.m_spriteGenerator;

		return *this;





	}
	AreaInitialiser(LevelAreaContainer* LevelAreaContainer, SpriteGenerator * spriteGenerator) { // initialse the deep copy object with a ptr to the alloacted heap memory

		basePtr = LevelAreaContainer;
		m_spriteGenerator = spriteGenerator;

	}

	LevelAreaContainer *  getNewAreaCopy(sf::Vector2f positionForArea,sf::Vector2i gridDim,sf::Vector2f tileSize) {

		LevelAreaContainer * copyObjectToReturn; // create a new unique pointer to assign the allocated memeory from the current held LevelAreaContainer's clone method 
		copyObjectToReturn = basePtr->clone(); // assign the heap allocated memeory to the unique ptr to be managed
		copyObjectToReturn->getSprites(m_spriteGenerator); /// get the sprite ref for the new area
		copyObjectToReturn->setDimensionsForArea(gridDim, tileSize); // set grid dimensions for new area
		copyObjectToReturn->setPosition(positionForArea); // set position
		copyObjectToReturn->initGrid();// initial the grid for the area
		return copyObjectToReturn; // return the new copy 


	};

	LevelAreaContainer* getHeldObject() {
		return basePtr;
	}
	

private:
	LevelAreaContainer* basePtr = nullptr;
	SpriteGenerator* m_spriteGenerator = nullptr;

};
