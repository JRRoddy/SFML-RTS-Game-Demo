#include "GrassLandsContainer.h"
#include "ForestTile.h"
GrassLandsArea::GrassLandsArea(){}
GrassLandsArea::~GrassLandsArea(){}
// setting properties specifc to the grasslands area which is a child class of the level area container class
GrassLandsArea::GrassLandsArea(SpriteGenerator* spriteGenerator,std::vector<TileInitialiser>& randomPostionedTiles,std::map<std::string,TileInitialiser>& imageMappedTiles,std::vector<std::string>& backgroundPaths, std::vector<std::string>& tileMapPaths):LevelAreaContainer(spriteGenerator,randomPostionedTiles,imageMappedTiles,backgroundPaths,tileMapPaths){ 
	m_areaType = GRASSLANDS; 
	m_tileMapDescriptorPath = "";
}

void GrassLandsArea::getTileFromSelectedMap(int x, int y )
{


  

}




// clone method t create deep copies of this specifc area while maintaining the derrvied class type
// and keeping dynamic linkage
LevelAreaContainer* GrassLandsArea::clone()
{
	GrassLandsArea * copy = new GrassLandsArea();; 
	LevelAreaContainer::clone(copy);
	return copy ;
}



