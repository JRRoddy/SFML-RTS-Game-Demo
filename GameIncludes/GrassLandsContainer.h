#pragma once
#include "LevelAreaContainer.h"
class GrassLandsArea : public LevelAreaContainer {

public:
	GrassLandsArea();
	~GrassLandsArea();
	GrassLandsArea(SpriteGenerator* spriteGenerator, std::vector<TileInitialiser>& randomPostionedTiles, std::vector<std::string> & backgroundPaths);
	LevelAreaContainer*  clone();

    


private:
	

};