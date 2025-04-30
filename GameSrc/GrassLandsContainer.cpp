#include "GrassLandsContainer.h"
#include "ForestTile.h"
#include "Goblin.h"
#include "PawnAlly.h"
GrassLandsArea::GrassLandsArea(){}
GrassLandsArea::~GrassLandsArea(){}
// setting properties specifc to the grasslands area which is a child class of the level area container class
GrassLandsArea::GrassLandsArea(SpriteGenerator* spriteGenerator,std::vector<TileInitialiser>& randomPostionedTiles,std::map<std::string,TileInitialiser>& imageMappedTiles,std::vector<std::string>& backgroundPaths, std::vector<std::string>& tileMapPaths):LevelAreaContainer(spriteGenerator,randomPostionedTiles,imageMappedTiles,backgroundPaths,tileMapPaths){ 
	m_areaType = GRASSLANDS;  

	// store specifc enemy instialisers associated with this area used to generate pooling objects for enemies 
	m_enemies = { EnemyInitialiser(new Goblin()) }; 
	// same as above but for allies associated with area
	m_allies = { AllyInitialiser(new Pawn()) };
	m_maxSpawnCoolDown = 10.0f; 
	m_minSpawnCoolDown = 8.0f; 
	m_allyRefreshCoolDown = 3.0f;
	m_maxAllyCap = 10;
}






// clone method t create deep copies of this specifc area while maintaining the derrvied class type
// and keeping dynamic linkage
LevelAreaContainer* GrassLandsArea::clone()
{
	GrassLandsArea * copy = new GrassLandsArea();; 
	LevelAreaContainer::clone(copy);
	return copy ;
}



