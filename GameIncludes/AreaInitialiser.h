#pragma once
#include "AreaInitialiser.h"
#include "LevelAreaContainer.h"
class AreaInitialiser {


public:

	
	AreaInitialiser() {}

	AreaInitialiser(const AreaInitialiser& other) {
		
		basePtr = other.basePtr->clone();
		m_spriteGenerator = other.m_spriteGenerator;
		std::cout << "area initialiser copy called " << std::endl;

	}
	AreaInitialiser operator= (const AreaInitialiser& other) {
		std::cout << "area initialiser = copy called " << std::endl;
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
		std::cout << "grid dim x" << gridDim.x << ": Y " << gridDim.y << std::endl;
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
