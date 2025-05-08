#include "GrassLandsContainer.h"

// setting properties specifc to the grasslands 
// area which is a child class of the level area container class
// this allows for the potential of different functionality 
// and properties per level area while still being able to mix 
// and match the objects within that area through the use of the level area manufacturer
GrassLandsArea::GrassLandsArea(){
	m_maxSpawnCoolDown = 10.0f;
	m_minSpawnCoolDown = 8.0f;
	m_allyRefreshCoolDown = 3.0f;
	m_maxAllyCap = 10;

}
GrassLandsArea::~GrassLandsArea(){}
GrassLandsArea::GrassLandsArea(SpriteGenerator* spriteGenerator,std::vector<TileInitialiser>& randomPostionedTiles,std::map<std::string,TileInitialiser>& imageMappedTiles,std::vector<std::string>& backgroundPaths, std::vector<std::string>& tileMapPaths):LevelAreaContainer(spriteGenerator,randomPostionedTiles,imageMappedTiles,backgroundPaths,tileMapPaths){ 
	
}






// clone method t create deep copies of this specifc area while maintaining the derrvied class type
// and keeping dynamic linkage
LevelAreaContainer* GrassLandsArea::clone()
{
	GrassLandsArea * copy = new GrassLandsArea();
	//LevelAreaContainer::clone(copy);
	return copy ;
}



