#include "GrassLandsContainer.h"
#include "ForestTile.h"
GrassLandsArea::GrassLandsArea(){}
// setting properties specifc to the grasslands area which is a child class of the level area container class
GrassLandsArea::GrassLandsArea(SpriteGenerator* spriteGenerator,std::vector<TileInitialiser> & randomPostionedTiles,std::vector<std::string> & backgroundPaths):LevelAreaContainer(spriteGenerator,randomPostionedTiles,backgroundPaths){ 
	std::cout << "grasslands constructor called" << std::endl;
	m_areaType = GRASSLANDS;
}




// clone method t create deep copies of this specifc area while maintaining the derrvied class type
// and keeping dynamic linkage
LevelAreaContainer* GrassLandsArea::clone()
{

	GrassLandsArea * copy = new GrassLandsArea();
	copy->setMappedTiles(this->m_mappedTiles); 
	copy->setRandomlyGeneratedTiles(this->m_randomPositionedTiles);
	copy->setAreaType(this->m_areaType);
	copy->setBackgroundTexturePaths(this->m_backgroundTextures); 

	return copy ;
}



