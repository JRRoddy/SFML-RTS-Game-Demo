#pragma once
#include "AreaTypes.h"
#include "map"
#include "vector"
#include "TileDeepCopyUtil.h"
#include "LevelGenerator.h"
// class that will be used to generate new tiles to be placed in the world 
class TileGenerator {

public:

	TileGenerator(LevelGenerator * levelGenerator);









private:
	// map the area type to various data structures that hold tile initialisers which are deep copy objects 
	// that hold a specifc tile returning a deepy copy of that held tile on demand
	//std::map<AreaTypes, std::vector<TileInitialiser>> m_randomPositionedTiles{ {GRASSLANDS,{}} };
	//std::map<AreaTypes, std::map<sf::Color,TileInitialiser>> m_MappedTiles;
	

};